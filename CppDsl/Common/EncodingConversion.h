#ifndef ENCODING_CONVERSION_H_20260425
#define ENCODING_CONVERSION_H_20260425

#include <string>

namespace Utility
{
    // Convert UTF-8 encoded string to the local console encoding.
    // On Windows, converts to the current ANSI code page (CP_ACP) so that
    // printf/std::cout can display non-ASCII characters correctly in the
    // default console. On non-Windows platforms, converts via iconv from
    // UTF-8 to the current locale's CODESET (nl_langinfo(CODESET)).
    std::string Utf8ToLocal(const char* utf8, int size = -1);
    std::string Utf8ToLocal(const std::string& utf8);

    // Convert local console encoding string to UTF-8 encoding.
    // On Windows, converts from the current ANSI code page (CP_ACP) to UTF-8.
    // On non-Windows platforms, converts via iconv from the current locale's
    // CODESET to UTF-8.
    std::string LocalToUtf8(const char* local, int size = -1);
    std::string LocalToUtf8(const std::string& local);

    // Validate whether the given byte sequence is well-formed UTF-8.
    bool IsValidUtf8(const char* s, size_t len);
    bool IsValidUtf8(const std::string& s);

    // Auto-detect: if input is valid UTF-8 convert to local ANSI,
    // otherwise return the bytes unchanged.
    std::string AutoToLocal(const char* s, size_t len);
    std::string AutoToLocal(const std::string& s);
    
    // Auto-detect: if input is valid Unicode (UTF-16) convert to local ANSI,
    // otherwise return converted bytes.
    std::string AutoToLocal(const wchar_t* s, size_t len);
    std::string AutoToLocal(const std::wstring& s);

    // Convert UTF-16 (wchar_t) encoded string to the local console encoding.
    // On Windows, converts from UTF-16 to the current ANSI code page (CP_ACP).
    // On non-Windows platforms, converts via iconv from WCHAR_T (native
    // wchar_t width and endianness) to the current locale's CODESET.
    std::string UnicodeToLocal(const wchar_t* unicode, int size = -1);
    std::string UnicodeToLocal(const std::wstring& unicode);

    // Convert local console encoding string to UTF-16 (wchar_t) encoding.
    // On Windows, converts from the current ANSI code page (CP_ACP) to UTF-16.
    // On non-Windows platforms, converts via iconv from the current locale's
    // CODESET to WCHAR_T (native wchar_t width and endianness).
    std::wstring LocalToUnicode(const char* local, int size = -1);
    std::wstring LocalToUnicode(const std::string& local);

    // Validate whether the given wide character sequence is well-formed UTF-16.
    bool IsValidUnicode(const wchar_t* s, size_t len);
    bool IsValidUnicode(const std::wstring& s);

    // Detect if the given byte sequence represents Unicode encoding (UTF-16/UTF-32)
    // with or without BOM (Byte Order Mark).
    bool IsUnicodeEncoding(const char* s, size_t len);
    bool IsUnicodeEncoding(const std::string& s);

    // Convert Unicode-encoded byte sequence (UTF-16/UTF-32) to local console encoding.
    // Automatically detects BOM and encoding type (UTF-16LE, UTF-16BE, UTF-32LE, UTF-32BE).
    std::string UnicodeBytesToLocal(const char* unicodeBytes, size_t len);
    std::string UnicodeBytesToLocal(const std::string& unicodeBytes);

    // Auto-detect: if input is valid Unicode bytes (UTF-16/UTF-32) convert to local,
    // otherwise return the bytes unchanged.
    std::string AutoToLocalWithUnicode(const char* s, size_t len);
    std::string AutoToLocalWithUnicode(const std::string& s);
}

#endif // ENCODING_CONVERSION_H_20260425
