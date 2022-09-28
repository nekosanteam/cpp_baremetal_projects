#include "nkstring.h"
#include <cstdio>
#include <cstring>

#include <CppUTest/CommandLineTestRunner.h>

TEST_GROUP(StringTest)
{
    nk_char dst[32];
    nk_char src[32];

    TEST_SETUP()
    {
        std::memset(dst, 0xc3, 32);
        std::memset(src, 0xc9, 32);
    }

    TEST_TEARDOWN() {}
};

TEST(StringTest, TestStrNLenS)
{
    UNSIGNED_LONGS_EQUAL(0, nk_strnlen_s(NULL, 2));
    UNSIGNED_LONGS_EQUAL(0, nk_strnlen_s("", 2));
    UNSIGNED_LONGS_EQUAL(1, nk_strnlen_s("1", 2));
    UNSIGNED_LONGS_EQUAL(2, nk_strnlen_s("12", 2));
    UNSIGNED_LONGS_EQUAL(2, nk_strnlen_s("123", 2));
}

TEST(StringTest, TestStrLen)
{
    UNSIGNED_LONGS_EQUAL(0, nk_strlen(""));
    UNSIGNED_LONGS_EQUAL(1, nk_strlen("1"));
    UNSIGNED_LONGS_EQUAL(2, nk_strlen("12"));
}

TEST(StringTest, TestStrCpy)
{
    nk_char org[] = "test01";

    nk_strcpy(src, org);
    nk_strcpy(dst, src);
    STRCMP_EQUAL(org, dst);
    BYTES_EQUAL(0, dst[6]);
}

TEST(StringTest, TestStrNCpy)
{
    nk_char org[] = "test02";

    nk_strncpy(dst, org, 8);
    STRCMP_EQUAL("test02", dst);
    BYTES_EQUAL(0, dst[7]);
}

TEST(StringTest, TestStrCat)
{
    nk_strcpy(dst, "test01");
    nk_strcat(dst, "test02");
    STRCMP_EQUAL("test01test02", dst);
    BYTES_EQUAL(0, dst[12]);
}

TEST(StringTest, TestStrNCat01)
{
    nk_strcpy(dst, "test01");
    nk_strncat(dst, "test02", 7);
    STRCMP_EQUAL("test01test02", dst);
    BYTES_EQUAL(0, dst[12]);
    BYTES_EQUAL(0, dst[13]);
    BYTES_EQUAL(0xc3, dst[14]);
}

TEST(StringTest, TestStrNCat02)
{
    nk_strcpy(dst, "test01");
    nk_strncat(dst, "test02", 5);
    STRCMP_EQUAL("test01test0", dst);
    BYTES_EQUAL(0, dst[11]);
    BYTES_EQUAL(0xc3, dst[12]);
}

TEST(StringTest, TestStrCmp)
{
    LONGS_EQUAL(0, nk_strcmp("aa", "aa"));
    LONGS_EQUAL(-1, nk_strcmp("aa", "ab"));
    LONGS_EQUAL(std::strcmp("aaa", "aa"), nk_strcmp("aaa", "aa"));
    //LONGS_EQUAL(1, nk_strcmp("aaa", "aa"));
}

TEST(StringTest, TestStrNCmp)
{
    LONGS_EQUAL(0, nk_strncmp("aab", "aac", 2));
    LONGS_EQUAL(-1, nk_strncmp("aa", "ab", 3));
    LONGS_EQUAL(1, nk_strncmp("aaa", "aa", 3));
}

TEST(StringTest, TestStrChr)
{
    nk_char org[] = "abcdgfgf";

    STRCMP_EQUAL("fgf", nk_strchr(org, 'f'));
    POINTERS_EQUAL(NULL, nk_strchr(org, 'i'));
    BYTES_EQUAL(0, *nk_strchr(org, '\0'));
}

TEST(StringTest, TestStrRChr)
{
    nk_char org[] = "abcdgfgf";

    STRCMP_EQUAL("gf", nk_strrchr(org, 'g'));
    POINTERS_EQUAL(NULL, nk_strrchr(org, 'i'));
    BYTES_EQUAL(0, *nk_strrchr(org, '\0'));
}

TEST(StringTest, TestMemChr)
{
    dst[3] = static_cast<nk_char>(0x7c);

    POINTERS_EQUAL(dst + 3, nk_memchr(dst, 0x7c, 4));
}

TEST(StringTest, TestMemCmp)
{
    for (int i=0; i<4; i++) {
        src[i] = static_cast<nk_char>(0x79);
        dst[i] = static_cast<nk_char>(0x79);
    }
    LONGS_EQUAL(0, nk_memcmp(src, dst, 4));
    LONGS_EQUAL(1, nk_memcmp(src, dst, 5));
    LONGS_EQUAL(-1, nk_memcmp(dst, src, 6));    
}

TEST(StringTest, TestMemSet)
{
    nk_memset(src, 0x75, 5);
    nk_memset(dst, 0x75, 5);
    LONGS_EQUAL(0, nk_memcmp(dst, src, 5));
    LONGS_EQUAL(1, nk_memcmp(src, dst, 6));
    LONGS_EQUAL(-1, nk_memcmp(dst, src, 6));
}

TEST(StringTest, TestMemCpy)
{
    nk_memcpy(dst, src, 6);
    LONGS_EQUAL(0, nk_memcmp(dst, src, 6));
    LONGS_EQUAL(1, nk_memcmp(src, dst, 7));
    LONGS_EQUAL(-1, nk_memcmp(dst, src, 7));
}

TEST(StringTest, TestMemMove)
{
    nk_memmove(dst, src, 7);
    LONGS_EQUAL(0, nk_memcmp(dst, src, 7));
    LONGS_EQUAL(1, nk_memcmp(src, dst, 8));
    LONGS_EQUAL(-1, nk_memcmp(dst, src, 8));
}

int main(int argc, char** argv)
{
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
