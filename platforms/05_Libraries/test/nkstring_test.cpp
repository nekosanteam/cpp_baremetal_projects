/* SPDX-License-Identifier: BSD-1-Clause */
/*
 * Copyright 2023,2024 nekosanteam <1688092+nekosanteam@users.noreply.github.com>. All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted
 * provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions
 *    and the following disclaimer.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS
 * AND CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "nkstring.h"

#include <cstdio>
#include <cstring>
#include <array>

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
    BYTES_EQUAL('2', dst[11]);
    BYTES_EQUAL(0, dst[12]);
    BYTES_EQUAL(0xc3, dst[13]);
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

TEST(StringTest, TestStrCpyCpp01)
{
    const char *pSrc = "test01";
    char pDst[12];

    nk::strcpy(pDst, pSrc);
    BYTES_EQUAL('1', pDst[5]);
    BYTES_EQUAL('\0', pDst[6]);
}

TEST(StringTest, TestStrCpyCpp02)
{
    const char *pSrc = "test02";
    std::array<char,12> pDst;

    nk::strcpy(pDst, pSrc);
    BYTES_EQUAL('2', pDst[5]);
    BYTES_EQUAL('\0', pDst[6]);
}

TEST(StringTest, TestNStrCpyCpp01)
{
    const char *pSrc = "test01";
    char pDst[12];

    nk::strncpy(pDst, pSrc);
    BYTES_EQUAL('1', pDst[5]);
    BYTES_EQUAL('\0', pDst[6]);
    BYTES_EQUAL('\0', pDst[11]);
}

TEST(StringTest, TestStrNCpyCpp02)
{
    const char *pSrc = "test02";
    std::array<char,12> pDst;

    nk::strncpy(pDst, pSrc);
    BYTES_EQUAL('2', pDst[5]);
    BYTES_EQUAL('\0', pDst[6]);
    BYTES_EQUAL('\0', pDst[11]);
}

TEST(StringTest, TestStrCatCpp01)
{
    const char *pSrc = "test01";
    const char *pApp = "test02";
    std::array<char,14> pDst {};

    nk::strcpy(pDst, pSrc);
    nk::strcat(pDst, pApp);
    BYTES_EQUAL('1', pDst[5]);
    BYTES_EQUAL('2', pDst[11]);
    BYTES_EQUAL('\0', pDst[12]);
    BYTES_EQUAL('\0', pDst[13]);
}

TEST(StringTest, TestStrNCatCpp01)
{
    const char *pSrc = "test01";
    const char *pApp = "test02";
    std::array<char,14> pDst {};

    nk::strcpy(pDst, pSrc);
    nk::strncat(pDst, pApp, 5);
    BYTES_EQUAL('1', pDst[5]);
    BYTES_EQUAL('0', pDst[10]);
    BYTES_EQUAL('\0', pDst[11]);
    BYTES_EQUAL('\0', pDst[13]);
}

int main(int argc, char** argv)
{
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
