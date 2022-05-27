#include "DslUtility.h"

namespace DslFileReadWrite
{
    int stringCompare(const void* a, const void* b)
    {
        const char* stra = *static_cast<const char* const*>(a);
        const char* strb = *static_cast<const char* const*>(b);
        if (nullptr == stra && nullptr == strb)
            return 0;
        else if (nullptr == stra)
            return -1;
        else if (nullptr == strb)
            return 1;

        size_t lena = strlen(stra);
        size_t lenb = strlen(strb);
        if (lena < lenb)
            return -1;
        else if (lena > lenb)
            return 1;
        else
            return strcmp(stra, strb);
    }
    void writeInt(char* s, int& pos, int val)
    {
        unsigned int v = val;
        s[pos++] = (char)(v & 0xff);
        s[pos++] = (char)((v & 0xff00) >> 8);
        s[pos++] = (char)((v & 0xff0000) >> 16);
        s[pos++] = (char)((v & 0xff000000) >> 24);
    }
    void write7BitEncodedInt(char* s, int& pos, int val)
    {
        unsigned int num;
        for (num = (unsigned int)val; num >= 128; num >>= 7) {
            s[pos++] = (char)(num | 0x80);
        }
        s[pos++] = (char)num;
    }
    int readInt(const char* bytes, int size, int pos)
    {
        if (0 != bytes && pos >= 0 && pos + 3 < size) {
            unsigned char b1 = bytes[pos];
            unsigned char b2 = bytes[pos + 1];
            unsigned char b3 = bytes[pos + 2];
            unsigned char b4 = bytes[pos + 3];
            return b1 | (b2 << 8) | (b3 << 16) | (b4 << 24);
        }
        else {
            return -1;
        }
    }
    int read7BitEncodedInt(const char* bytes, int size, int pos, int& byteCount)
    {
        int num = -1;
        byteCount = 0;
        if (0 != bytes && pos < size) {
            int bitCount = 0;
            unsigned char b;
            num = 0;
            do {
                if (bitCount == 35) {
                    num = -1;
                    break;
                }
                b = bytes[pos++];
                num |= (b & 0x7F) << bitCount;
                bitCount += 7;
            }
            while (pos < size && (b & 0x80) != 0);
            byteCount = bitCount / 7;
        }
        return num;
    }

    char readByte(const char* bytes, int size, int curCodeIndex)
    {
        if (curCodeIndex < size)
            return bytes[curCodeIndex];
        else
            return 0;
    }
    const char* readIdentifier(const char** identifiers, int idCount, int curIdIndex)
    {
        if (curIdIndex < idCount)
            return identifiers[curIdIndex];
        else
            return 0;
    }
    const std::string& readIdentifier(const std::string* identifiers, int idCount, int curIdIndex)
    {
        if (curIdIndex < idCount)
            return identifiers[curIdIndex];
        else
            return DslData::ISyntaxComponent::EmptyString();
    }
    void WriteIndent(FILE* fp, int indent)
    {
        for (int i = 0; i < indent; ++i) {
            fwrite("\t", 1, 1, fp);
        }
    }
    void WriteId(FILE* fp, const char* str, int indent)
    {
        WriteIndent(fp, indent);
        fprintf(fp, "%s", str);
    }
    void WriteString(FILE* fp, const char* str, int indent, const char* beginDelim, const char* endDelim)
    {
        const char* escapeChars = "\\\"'";
        WriteIndent(fp, indent);
        fwrite(beginDelim, strlen(beginDelim), 1, fp);
        const char* p = str;
        size_t len = strlen(p);
        while (*p) {
            size_t n = strcspn(p, escapeChars);
            if (n < len) {
                fwrite(p, 1, n, fp);
                fwrite("\\", 1, 1, fp);
                fwrite(p + n, 1, 1, fp);
                p += n + 1;
                len = strlen(p);
            }
            else {
                fwrite(p, 1, len, fp);
                break;
            }
        }
        fwrite(endDelim, strlen(endDelim), 1, fp);
    }

}
