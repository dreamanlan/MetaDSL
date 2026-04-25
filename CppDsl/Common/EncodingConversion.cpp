#include "EncodingConversion.h"
#include <cstdint>
#include <cstring>
#include <cwchar>

#if defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
#   ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN
#   endif
#   ifndef NOMINMAX
#       define NOMINMAX
#   endif
#   include <windows.h>
#   define ENCCONV_HAS_ICONV 0
#elif defined(__ANDROID__) && (!defined(__ANDROID_API__) || __ANDROID_API__ < 28)
// Android NDK exposes iconv/nl_langinfo only when ANDROID_PLATFORM >= android-28.
// For lower API levels we fall back to a UTF-8-based implementation: Bionic's
// default locale is UTF-8, so treating "local" as UTF-8 matches typical apps.
#   define ENCCONV_HAS_ICONV 0
#else
// Other non-Windows platforms (glibc Linux, macOS/iOS with libiconv, Android
// API >= 28) use iconv to honor the current locale's CODESET.
#   include <iconv.h>
#   include <langinfo.h>
#   include <locale.h>
#   include <errno.h>
#   define ENCCONV_HAS_ICONV 1
#endif

namespace Utility
{
    // ------------------------------------------------------------------
    // BOM constants and helpers
    // ------------------------------------------------------------------
    namespace {
        const unsigned char UTF8_BOM[]     = { 0xEF, 0xBB, 0xBF };
        const unsigned char UTF16_LE_BOM[] = { 0xFF, 0xFE };
        const unsigned char UTF16_BE_BOM[] = { 0xFE, 0xFF };
        const unsigned char UTF32_LE_BOM[] = { 0xFF, 0xFE, 0x00, 0x00 };
        const unsigned char UTF32_BE_BOM[] = { 0x00, 0x00, 0xFE, 0xFF };

        enum UnicodeEnc {
            ENC_UNKNOWN = 0,
            ENC_UTF16_LE,
            ENC_UTF16_BE,
            ENC_UTF32_LE,
            ENC_UTF32_BE
        };

        // Skip UTF-8 BOM only. Returns pointer to content after BOM.
        const char* SkipUtf8BomInternal(const char* s, size_t len, size_t& bomLength)
        {
            bomLength = 0;
            if (s == nullptr)
                return s;
            const unsigned char* p = reinterpret_cast<const unsigned char*>(s);
            if (len >= 3 && p[0] == UTF8_BOM[0] && p[1] == UTF8_BOM[1] && p[2] == UTF8_BOM[2]) {
                bomLength = 3;
                return s + 3;
            }
            return s;
        }

        // Detect Unicode encoding by BOM. Returns ENC_UNKNOWN if no BOM matches.
        // Check order: UTF-32 (4 bytes) first, then UTF-8 (3 bytes) (not returned
        // here but consumed by caller via separate check), then UTF-16 (2 bytes).
        UnicodeEnc DetectBomEncoding(const char* s, size_t len, size_t& bomLength)
        {
            bomLength = 0;
            if (s == nullptr || len < 2)
                return ENC_UNKNOWN;
            const unsigned char* p = reinterpret_cast<const unsigned char*>(s);
            // UTF-32 LE: FF FE 00 00 (must check before UTF-16 LE which is FF FE)
            if (len >= 4 && p[0] == UTF32_LE_BOM[0] && p[1] == UTF32_LE_BOM[1] &&
                p[2] == UTF32_LE_BOM[2] && p[3] == UTF32_LE_BOM[3]) {
                bomLength = 4;
                return ENC_UTF32_LE;
            }
            // UTF-32 BE: 00 00 FE FF
            if (len >= 4 && p[0] == UTF32_BE_BOM[0] && p[1] == UTF32_BE_BOM[1] &&
                p[2] == UTF32_BE_BOM[2] && p[3] == UTF32_BE_BOM[3]) {
                bomLength = 4;
                return ENC_UTF32_BE;
            }
            // UTF-16 LE: FF FE
            if (len >= 2 && p[0] == UTF16_LE_BOM[0] && p[1] == UTF16_LE_BOM[1]) {
                bomLength = 2;
                return ENC_UTF16_LE;
            }
            // UTF-16 BE: FE FF
            if (len >= 2 && p[0] == UTF16_BE_BOM[0] && p[1] == UTF16_BE_BOM[1]) {
                bomLength = 2;
                return ENC_UTF16_BE;
            }
            return ENC_UNKNOWN;
        }

        // Heuristic: detect UTF-16 without BOM by analyzing zero-byte distribution.
        // Only UTF-16 LE/BE are probed. UTF-32 without BOM is too rare in practice
        // and easily confused with other data, so we do not guess it.
        // Returns ENC_UNKNOWN if the sample does not clearly match UTF-16.
        UnicodeEnc GuessUtf16NoBom(const char* s, size_t len)
        {
            if (s == nullptr || len < 8 || (len % 2) != 0)
                return ENC_UNKNOWN;
            const unsigned char* p = reinterpret_cast<const unsigned char*>(s);
            size_t sample = len < 64 ? len : 64;
            size_t zerosEven = 0; // bytes at even indices that are 0x00
            size_t zerosOdd  = 0; // bytes at odd  indices that are 0x00
            for (size_t i = 0; i < sample; ++i) {
                if (p[i] == 0) {
                    if ((i & 1) == 0) ++zerosEven;
                    else              ++zerosOdd;
                }
            }
            size_t halfSample = sample / 2;
            // Require one side to have many zeros AND the other side almost none.
            // This avoids classifying plain ASCII/UTF-8/GBK (few/no zeros) as UTF-16.
            if (halfSample == 0)
                return ENC_UNKNOWN;
            // Use integer-only thresholds: strong side > 25%, weak side < 5% of half.
            size_t strongThreshold = halfSample / 4;       // 25% of halfSample
            size_t weakThreshold   = halfSample / 20;      // 5%  of halfSample
            // UTF-16 LE ASCII: 'A' 00 'B' 00 -> zeros dominate odd indices.
            if (zerosOdd > strongThreshold && zerosEven <= weakThreshold)
                return ENC_UTF16_LE;
            // UTF-16 BE ASCII: 00 'A' 00 'B' -> zeros dominate even indices.
            if (zerosEven > strongThreshold && zerosOdd <= weakThreshold)
                return ENC_UTF16_BE;
            return ENC_UNKNOWN;
        }

        // Read one UTF-16 code unit at byte offset i.
        inline uint16_t ReadU16(const unsigned char* p, size_t i, bool bigEndian)
        {
            return bigEndian
                ? static_cast<uint16_t>((p[i] << 8) | p[i + 1])
                : static_cast<uint16_t>(p[i] | (p[i + 1] << 8));
        }

        // Read one UTF-32 code unit at byte offset i.
        inline uint32_t ReadU32(const unsigned char* p, size_t i, bool bigEndian)
        {
            return bigEndian
                ? (static_cast<uint32_t>(p[i]) << 24)
                  | (static_cast<uint32_t>(p[i + 1]) << 16)
                  | (static_cast<uint32_t>(p[i + 2]) << 8)
                  | static_cast<uint32_t>(p[i + 3])
                : static_cast<uint32_t>(p[i])
                  | (static_cast<uint32_t>(p[i + 1]) << 8)
                  | (static_cast<uint32_t>(p[i + 2]) << 16)
                  | (static_cast<uint32_t>(p[i + 3]) << 24);
        }

        // Append one Unicode code point as UTF-8 bytes.
        inline void AppendUtf8(std::string& out, uint32_t cp)
        {
            if (cp < 0x80) {
                out += static_cast<char>(cp);
            }
            else if (cp < 0x800) {
                out += static_cast<char>(0xC0 | (cp >> 6));
                out += static_cast<char>(0x80 | (cp & 0x3F));
            }
            else if (cp < 0x10000) {
                out += static_cast<char>(0xE0 | (cp >> 12));
                out += static_cast<char>(0x80 | ((cp >> 6) & 0x3F));
                out += static_cast<char>(0x80 | (cp & 0x3F));
            }
            else if (cp <= 0x10FFFF) {
                out += static_cast<char>(0xF0 | (cp >> 18));
                out += static_cast<char>(0x80 | ((cp >> 12) & 0x3F));
                out += static_cast<char>(0x80 | ((cp >> 6) & 0x3F));
                out += static_cast<char>(0x80 | (cp & 0x3F));
            }
        }

        // Convert UTF-16 byte stream to UTF-8 string.
        std::string Utf16BytesToUtf8(const char* content, size_t contentLen, bool bigEndian)
        {
            std::string out;
            if (contentLen < 2)
                return out;
            const unsigned char* p = reinterpret_cast<const unsigned char*>(content);
            size_t i = 0;
            size_t end = contentLen - (contentLen % 2);
            while (i + 1 < end) {
                uint16_t unit = ReadU16(p, i, bigEndian);
                i += 2;
                if (unit >= 0xD800 && unit <= 0xDBFF) {
                    // High surrogate, expect low surrogate next.
                    if (i + 1 >= end)
                        break;
                    uint16_t low = ReadU16(p, i, bigEndian);
                    if (low < 0xDC00 || low > 0xDFFF)
                        break;
                    i += 2;
                    uint32_t cp = 0x10000 + ((static_cast<uint32_t>(unit - 0xD800)) << 10)
                                  + static_cast<uint32_t>(low - 0xDC00);
                    AppendUtf8(out, cp);
                }
                else if (unit >= 0xDC00 && unit <= 0xDFFF) {
                    // Stray low surrogate, skip.
                    continue;
                }
                else {
                    AppendUtf8(out, unit);
                }
            }
            return out;
        }

        // Convert UTF-32 byte stream to UTF-8 string.
        std::string Utf32BytesToUtf8(const char* content, size_t contentLen, bool bigEndian)
        {
            std::string out;
            if (contentLen < 4)
                return out;
            const unsigned char* p = reinterpret_cast<const unsigned char*>(content);
            size_t end = contentLen - (contentLen % 4);
            for (size_t i = 0; i + 3 < end; i += 4) {
                uint32_t cp = ReadU32(p, i, bigEndian);
                if (cp > 0x10FFFF) continue;
                if (cp >= 0xD800 && cp <= 0xDFFF) continue;
                AppendUtf8(out, cp);
            }
            return out;
        }

#if ENCCONV_HAS_ICONV
        // Name of the current locale's CODESET, used as iconv "local" encoding.
        // Empty string means use the default, but nl_langinfo after setlocale("")
        // returns the actual charset name (e.g. "UTF-8", "GB18030"). We cache it
        // on first use.
        const char* LocalCodeset()
        {
            static const char* cached = nullptr;
            if (cached != nullptr)
                return cached;
            // Ensure LC_CTYPE is initialized from environment once.
            static bool initialized = false;
            if (!initialized) {
                ::setlocale(LC_CTYPE, "");
                initialized = true;
            }
            const char* cs = ::nl_langinfo(CODESET);
            if (cs == nullptr || *cs == '\0')
                cs = "UTF-8";
            cached = cs;
            return cached;
        }

        // Perform an iconv conversion from fromCode to toCode. Returns an empty
        // string on open failure. Illegal input bytes are skipped, incomplete
        // trailing bytes are dropped.
        std::string IconvConvert(const char* fromCode, const char* toCode,
                                 const char* src, size_t srcLen)
        {
            std::string out;
            if (src == nullptr || srcLen == 0)
                return out;
            iconv_t cd = ::iconv_open(toCode, fromCode);
            if (cd == reinterpret_cast<iconv_t>(-1))
                return out;
            const size_t kBufSize = 1024;
            char buf[kBufSize];
            // iconv's second parameter is non-const char** on some platforms.
            char* inBuf = const_cast<char*>(src);
            size_t inLeft = srcLen;
            while (inLeft > 0) {
                char* outBuf = buf;
                size_t outLeft = kBufSize;
                size_t r = ::iconv(cd, &inBuf, &inLeft, &outBuf, &outLeft);
                out.append(buf, kBufSize - outLeft);
                if (r == static_cast<size_t>(-1)) {
                    if (errno == E2BIG) {
                        continue;
                    }
                    else if (errno == EILSEQ) {
                        // Skip one illegal byte and retry.
                        if (inLeft == 0)
                            break;
                        ++inBuf;
                        --inLeft;
                    }
                    else if (errno == EINVAL) {
                        // Incomplete multibyte sequence at the end.
                        break;
                    }
                    else {
                        break;
                    }
                }
            }
            // Flush shift state.
            {
                char* outBuf = buf;
                size_t outLeft = kBufSize;
                ::iconv(cd, nullptr, nullptr, &outBuf, &outLeft);
                out.append(buf, kBufSize - outLeft);
            }
            ::iconv_close(cd);
            return out;
        }
#endif
    } // anonymous namespace

    // ------------------------------------------------------------------
    // UTF-8 <-> Local
    // ------------------------------------------------------------------
    std::string Utf8ToLocal(const char* utf8, int size)
    {
        if (utf8 == nullptr)
            return std::string();
        size_t actualSize = (size < 0) ? std::strlen(utf8) : static_cast<size_t>(size);
        // Only strip UTF-8 BOM here. Never strip UTF-16/UTF-32 BOM because
        // the bytes following such a BOM are not UTF-8 and must be handled
        // via UnicodeBytesToLocal instead.
        size_t bomLength = 0;
        const char* content = SkipUtf8BomInternal(utf8, actualSize, bomLength);
        size_t contentSize = actualSize - bomLength;
#if defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
        int wlen = ::MultiByteToWideChar(CP_UTF8, 0, content, static_cast<int>(contentSize), nullptr, 0);
        if (wlen <= 0)
            return std::string(content, contentSize);
        std::wstring wbuf(static_cast<size_t>(wlen), L'\0');
        ::MultiByteToWideChar(CP_UTF8, 0, content, static_cast<int>(contentSize), &wbuf[0], wlen);
        int alen = ::WideCharToMultiByte(CP_ACP, 0, wbuf.c_str(), wlen, nullptr, 0, nullptr, nullptr);
        if (alen <= 0)
            return std::string();
        std::string abuf(static_cast<size_t>(alen), '\0');
        ::WideCharToMultiByte(CP_ACP, 0, wbuf.c_str(), wlen, &abuf[0], alen, nullptr, nullptr);
        if (size < 0 && !abuf.empty() && abuf.back() == '\0')
            abuf.pop_back();
        return abuf;
#elif ENCCONV_HAS_ICONV
        // Non-Windows with iconv: convert UTF-8 to the current locale's CODESET.
        return IconvConvert("UTF-8", LocalCodeset(), content, contentSize);
#else
        // Android NDK without iconv: Bionic defaults to a UTF-8 locale, so the
        // UTF-8 bytes are already the "local" representation.
        return std::string(content, contentSize);
#endif
    }

    std::string Utf8ToLocal(const std::string& utf8)
    {
        return Utf8ToLocal(utf8.c_str(), static_cast<int>(utf8.size()));
    }

    std::string LocalToUtf8(const char* local, int size)
    {
        if (local == nullptr)
            return std::string();
        // Local bytes are ANSI/GBK/etc. and do not carry a BOM in practice,
        // so no BOM stripping is performed here.
        size_t actualSize = (size < 0) ? std::strlen(local) : static_cast<size_t>(size);
#if defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
        int wlen = ::MultiByteToWideChar(CP_ACP, 0, local, static_cast<int>(actualSize), nullptr, 0);
        if (wlen <= 0)
            return std::string(local, actualSize);
        std::wstring wbuf(static_cast<size_t>(wlen), L'\0');
        ::MultiByteToWideChar(CP_ACP, 0, local, static_cast<int>(actualSize), &wbuf[0], wlen);
        int ulen = ::WideCharToMultiByte(CP_UTF8, 0, wbuf.c_str(), wlen, nullptr, 0, nullptr, nullptr);
        if (ulen <= 0)
            return std::string();
        std::string ubuf(static_cast<size_t>(ulen), '\0');
        ::WideCharToMultiByte(CP_UTF8, 0, wbuf.c_str(), wlen, &ubuf[0], ulen, nullptr, nullptr);
        if (size < 0 && !ubuf.empty() && ubuf.back() == '\0')
            ubuf.pop_back();
        return ubuf;
#elif ENCCONV_HAS_ICONV
        // Non-Windows with iconv: convert from the current locale's CODESET to UTF-8.
        return IconvConvert(LocalCodeset(), "UTF-8", local, actualSize);
#else
        // Android NDK without iconv: local is treated as UTF-8.
        return std::string(local, actualSize);
#endif
    }

    std::string LocalToUtf8(const std::string& local)
    {
        return LocalToUtf8(local.c_str(), static_cast<int>(local.size()));
    }

    // ------------------------------------------------------------------
    // UTF-8 validity
    // ------------------------------------------------------------------
    bool IsValidUtf8(const char* s, size_t len)
    {
        if (s == nullptr)
            return false;
        // Tolerate an optional UTF-8 BOM at the start.
        size_t bomLength = 0;
        const char* content = SkipUtf8BomInternal(s, len, bomLength);
        size_t clen = len - bomLength;
        const unsigned char* p = reinterpret_cast<const unsigned char*>(content);
        size_t i = 0;
        while (i < clen) {
            unsigned char c = p[i];
            if (c < 0x80) {
                i += 1;
                continue;
            }
            size_t need = 0;
            unsigned int cp = 0;
            if ((c & 0xE0) == 0xC0) {
                need = 1;
                cp = c & 0x1F;
                if (c < 0xC2)
                    return false;
            }
            else if ((c & 0xF0) == 0xE0) {
                need = 2;
                cp = c & 0x0F;
            }
            else if ((c & 0xF8) == 0xF0) {
                need = 3;
                cp = c & 0x07;
            }
            else {
                return false;
            }
            if (i + need >= clen)
                return false;
            for (size_t k = 1; k <= need; ++k) {
                unsigned char cc = p[i + k];
                if ((cc & 0xC0) != 0x80)
                    return false;
                cp = (cp << 6) | (cc & 0x3F);
            }
            if (need == 2 && cp < 0x800)
                return false;
            if (need == 3 && cp < 0x10000)
                return false;
            if (cp > 0x10FFFF)
                return false;
            if (cp >= 0xD800 && cp <= 0xDFFF)
                return false;
            i += need + 1;
        }
        return true;
    }

    bool IsValidUtf8(const std::string& s)
    {
        return IsValidUtf8(s.c_str(), s.size());
    }

    // ------------------------------------------------------------------
    // Unicode (wchar_t) <-> Local
    // ------------------------------------------------------------------
    std::string UnicodeToLocal(const wchar_t* unicode, int size)
    {
        if (unicode == nullptr)
            return std::string();
#if defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
        int alen = ::WideCharToMultiByte(CP_ACP, 0, unicode, size, nullptr, 0, nullptr, nullptr);
        if (alen <= 0)
            return std::string();
        std::string abuf(static_cast<size_t>(alen), '\0');
        ::WideCharToMultiByte(CP_ACP, 0, unicode, size, &abuf[0], alen, nullptr, nullptr);
        if (size < 0 && !abuf.empty() && abuf.back() == '\0')
            abuf.pop_back();
        return abuf;
#elif ENCCONV_HAS_ICONV
        // Non-Windows with iconv: convert wchar_t (WCHAR_T matches the
        // platform's native wchar_t width and endianness) to the local CODESET.
        size_t actualSize = (size < 0) ? std::wcslen(unicode) : static_cast<size_t>(size);
        size_t byteLen = actualSize * sizeof(wchar_t);
        return IconvConvert("WCHAR_T", LocalCodeset(),
                            reinterpret_cast<const char*>(unicode), byteLen);
#else
        // Android NDK without iconv: encode each wchar_t as a UTF-32 code point
        // into UTF-8 bytes (Bionic wchar_t is 32-bit) which is also the local.
        size_t actualSize = (size < 0) ? std::wcslen(unicode) : static_cast<size_t>(size);
        std::string out;
        out.reserve(actualSize);
        for (size_t i = 0; i < actualSize; ++i) {
            uint32_t cp = static_cast<uint32_t>(unicode[i]);
            if (cp > 0x10FFFF || (cp >= 0xD800 && cp <= 0xDFFF)) {
                out += '?';
                continue;
            }
            AppendUtf8(out, cp);
        }
        return out;
#endif
    }

    std::string UnicodeToLocal(const std::wstring& unicode)
    {
        return UnicodeToLocal(unicode.c_str(), static_cast<int>(unicode.size()));
    }

    std::wstring LocalToUnicode(const char* local, int size)
    {
        if (local == nullptr)
            return std::wstring();
#if defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
        int wlen = ::MultiByteToWideChar(CP_ACP, 0, local, size, nullptr, 0);
        if (wlen <= 0)
            return std::wstring();
        std::wstring wbuf(static_cast<size_t>(wlen), L'\0');
        ::MultiByteToWideChar(CP_ACP, 0, local, size, &wbuf[0], wlen);
        if (size < 0 && !wbuf.empty() && wbuf.back() == L'\0')
            wbuf.pop_back();
        return wbuf;
#elif ENCCONV_HAS_ICONV
        // Non-Windows with iconv: convert from the local CODESET to WCHAR_T.
        size_t actualSize = (size < 0) ? std::strlen(local) : static_cast<size_t>(size);
        std::string bytes = IconvConvert(LocalCodeset(), "WCHAR_T", local, actualSize);
        if (bytes.empty())
            return std::wstring();
        size_t wlen = bytes.size() / sizeof(wchar_t);
        std::wstring out(wlen, L'\0');
        if (wlen > 0)
            std::memcpy(&out[0], bytes.data(), wlen * sizeof(wchar_t));
        return out;
#else
        // Android NDK without iconv: decode the local bytes (treated as UTF-8)
        // and emit one wchar_t per code point (Bionic wchar_t is 32-bit).
        size_t actualSize = (size < 0) ? std::strlen(local) : static_cast<size_t>(size);
        std::wstring out;
        out.reserve(actualSize);
        const unsigned char* p = reinterpret_cast<const unsigned char*>(local);
        size_t i = 0;
        while (i < actualSize) {
            unsigned char c = p[i];
            uint32_t cp = 0;
            size_t need = 0;
            if (c < 0x80) { cp = c; need = 0; }
            else if ((c & 0xE0) == 0xC0) { cp = c & 0x1F; need = 1; }
            else if ((c & 0xF0) == 0xE0) { cp = c & 0x0F; need = 2; }
            else if ((c & 0xF8) == 0xF0) { cp = c & 0x07; need = 3; }
            else { ++i; continue; }
            if (i + need >= actualSize)
                break;
            bool ok = true;
            for (size_t k = 1; k <= need; ++k) {
                unsigned char cc = p[i + k];
                if ((cc & 0xC0) != 0x80) { ok = false; break; }
                cp = (cp << 6) | (cc & 0x3F);
            }
            if (!ok) { ++i; continue; }
            i += need + 1;
            if (cp > 0x10FFFF || (cp >= 0xD800 && cp <= 0xDFFF))
                continue;
            out += static_cast<wchar_t>(cp);
        }
        return out;
#endif
    }

    std::wstring LocalToUnicode(const std::string& local)
    {
        return LocalToUnicode(local.c_str(), static_cast<int>(local.size()));
    }

    // ------------------------------------------------------------------
    // Unicode (wchar_t) validity
    // ------------------------------------------------------------------
    bool IsValidUnicode(const wchar_t* s, size_t len)
    {
        if (s == nullptr)
            return false;
        // On Windows wchar_t is UTF-16, so surrogate pairing matters.
        // On Linux/macOS wchar_t is UTF-32, so there are no surrogates and
        // each element must just be a valid code point.
        for (size_t i = 0; i < len; ++i) {
            unsigned int c = static_cast<unsigned int>(s[i]);
            if (sizeof(wchar_t) >= 4) {
                if (c > 0x10FFFF)
                    return false;
                if (c >= 0xD800 && c <= 0xDFFF)
                    return false;
            }
            else {
                if (c >= 0xD800 && c <= 0xDBFF) {
                    // High surrogate must be followed by low surrogate.
                    if (i + 1 >= len)
                        return false;
                    unsigned int next = static_cast<unsigned int>(s[i + 1]);
                    if (next < 0xDC00 || next > 0xDFFF)
                        return false;
                    ++i;
                }
                else if (c >= 0xDC00 && c <= 0xDFFF) {
                    return false;
                }
            }
        }
        return true;
    }

    bool IsValidUnicode(const std::wstring& s)
    {
        return IsValidUnicode(s.c_str(), s.size());
    }

    // ------------------------------------------------------------------
    // Auto-detect conversions
    // ------------------------------------------------------------------
    std::string AutoToLocal(const wchar_t* s, size_t len)
    {
        if (s == nullptr)
            return std::string();
        if (IsValidUnicode(s, len))
            return UnicodeToLocal(s, static_cast<int>(len));
#if defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
        int mblen = ::WideCharToMultiByte(CP_ACP, 0, s, static_cast<int>(len), nullptr, 0, nullptr, nullptr);
        if (mblen <= 0)
            return std::string();
        std::string result(static_cast<size_t>(mblen), '\0');
        ::WideCharToMultiByte(CP_ACP, 0, s, static_cast<int>(len), &result[0], mblen, nullptr, nullptr);
        return result;
#else
        // Non-Windows: UnicodeToLocal already handles invalid units (either via
        // iconv or via the UTF-8 fallback), so just delegate.
        return UnicodeToLocal(s, static_cast<int>(len));
#endif
    }

    std::string AutoToLocal(const std::wstring& s)
    {
        return AutoToLocal(s.c_str(), s.size());
    }

    std::string AutoToLocal(const std::string& s)
    {
        return AutoToLocal(s.c_str(), s.size());
    }

    std::string AutoToLocal(const char* s, size_t len)
    {
        // Delegate to the Unicode-aware version (handles BOM + UTF-16/32 + UTF-8).
        return AutoToLocalWithUnicode(s, len);
    }

    // ------------------------------------------------------------------
    // Unicode-bytes (UTF-16/UTF-32) detection and conversion
    // ------------------------------------------------------------------
    bool IsUnicodeEncoding(const char* s, size_t len)
    {
        if (s == nullptr || len < 2)
            return false;
        size_t bomLength = 0;
        UnicodeEnc enc = DetectBomEncoding(s, len, bomLength);
        if (enc != ENC_UNKNOWN)
            return true;
        // No BOM: only try to guess UTF-16 LE/BE using a strict heuristic
        // so that Local/UTF-8 content is not misclassified.
        return GuessUtf16NoBom(s, len) != ENC_UNKNOWN;
    }

    bool IsUnicodeEncoding(const std::string& s)
    {
        return IsUnicodeEncoding(s.c_str(), s.size());
    }

    std::string UnicodeBytesToLocal(const char* unicodeBytes, size_t len)
    {
        if (unicodeBytes == nullptr || len == 0)
            return std::string();
        // Step 1: detect encoding and skip BOM.
        size_t bomLength = 0;
        UnicodeEnc enc = DetectBomEncoding(unicodeBytes, len, bomLength);
        const char* content = unicodeBytes + bomLength;
        size_t contentLen = len - bomLength;
        if (enc == ENC_UNKNOWN) {
            // No BOM, try heuristic (UTF-16 LE/BE only).
            enc = GuessUtf16NoBom(unicodeBytes, len);
            content = unicodeBytes;
            contentLen = len;
        }
        if (enc == ENC_UNKNOWN)
            return std::string(unicodeBytes, len);
        // Step 2: convert to UTF-8.
        std::string utf8;
        switch (enc) {
            case ENC_UTF16_LE: utf8 = Utf16BytesToUtf8(content, contentLen, false); break;
            case ENC_UTF16_BE: utf8 = Utf16BytesToUtf8(content, contentLen, true);  break;
            case ENC_UTF32_LE: utf8 = Utf32BytesToUtf8(content, contentLen, false); break;
            case ENC_UTF32_BE: utf8 = Utf32BytesToUtf8(content, contentLen, true);  break;
            default: return std::string(unicodeBytes, len);
        }
        // Step 3: convert UTF-8 to Local.
        return Utf8ToLocal(utf8.c_str(), static_cast<int>(utf8.size()));
    }

    std::string UnicodeBytesToLocal(const std::string& unicodeBytes)
    {
        return UnicodeBytesToLocal(unicodeBytes.c_str(), unicodeBytes.size());
    }

    std::string AutoToLocalWithUnicode(const char* s, size_t len)
    {
        if (s == nullptr)
            return std::string();
        // Order matters:
        // 1) Detect UTF-16/UTF-32 by BOM or strict heuristic first.
        // 2) Then treat remaining data as UTF-8 if valid (Utf8ToLocal itself
        //    handles an optional UTF-8 BOM).
        // 3) Otherwise return bytes as-is (already local encoding).
        if (IsUnicodeEncoding(s, len))
            return UnicodeBytesToLocal(s, len);
        if (IsValidUtf8(s, len))
            return Utf8ToLocal(s, static_cast<int>(len));
        return std::string(s, len);
    }

    std::string AutoToLocalWithUnicode(const std::string& s)
    {
        return AutoToLocalWithUnicode(s.c_str(), s.size());
    }
}
