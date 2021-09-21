#include "nkstring.h"
#include <cstdio>

#include <CppUTest/CommandLineTestRunner.h>

TEST_GROUP(StringTest)
{
    char dst[32];
    char src[32];

    TEST_SETUP()
    {
        memset(dst, 0xc3, 32);
        memset(src, 0xc9, 32);
    }

    TEST_TEARDOWN() {}
};

TEST(StringTest, TestStrCpy)
{
    char org[] = "test01";

    nk_strcpy(src, org);
    nk_strcpy(dst, src);
    STRCMP_EQUAL(org, dst);
    BYTES_EQUAL(0, dst[6]);
}

TEST(StringTest, TestStrNCpy)
{
    char org[] = "test02";

    nk_strncpy(dst, org, 8);
    STRCMP_EQUAL("test02", dst);
    BYTES_EQUAL(0, dst[7]);
}

TEST(StringTest, TestStrLen)
{
    UNSIGNED_LONGS_EQUAL(0, nk_strlen(""));
    UNSIGNED_LONGS_EQUAL(1, nk_strlen("1"));
    UNSIGNED_LONGS_EQUAL(2, nk_strlen("12"));
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
    LONGS_EQUAL(1, nk_strcmp("aaa", "aa"));
}

TEST(StringTest, TestStrNCmp)
{
    LONGS_EQUAL(0, nk_strncmp("aab", "aac", 2));
    LONGS_EQUAL(-1, nk_strncmp("aa", "ab", 3));
    LONGS_EQUAL(1, nk_strncmp("aaa", "aa", 3));
}

TEST(StringTest, TestStrChr)
{
    char org[] = "abcdgfgf";

    STRCMP_EQUAL("fgf", nk_strchr(org, 'f'));
    POINTERS_EQUAL(NULL, nk_strchr(org, 'i'));
    BYTES_EQUAL(0, *nk_strchr(org, '\0'));
}

TEST(StringTest, TestStrRChr)
{
    char org[] = "abcdgfgf";

    STRCMP_EQUAL("gf", nk_strrchr(org, 'g'));
    POINTERS_EQUAL(NULL, nk_strrchr(org, 'i'));
    BYTES_EQUAL(0, *nk_strrchr(org, '\0'));
}

int main(int argc, char** argv)
{
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
