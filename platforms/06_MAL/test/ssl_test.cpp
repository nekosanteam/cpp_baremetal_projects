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

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>


#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#pragma warning(disable:4996)
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#define SOCKET int
#define SD_BOTH SHUT_WR
#endif

#include <openssl/ssl.h>
#include <openssl/err.h>

#define CA_BUNDLE_FILE ""

using std::string;
using std::memset;

int main(int argc, char** argv)
{
    const string target("nekosan-team.jp");

#ifdef WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        return 0;
    }
#endif

    SSL* ssl_;
    SSL_CTX* ctx_;

    SSL_library_init();
    SSL_load_error_strings();

    const SSL_METHOD* method = SSLv23_method();
    ctx_ = SSL_CTX_new(method);
    SSL_CTX_set_min_proto_version(ctx_, TLS1_1_VERSION);

    int r = SSL_CTX_load_verify_locations(ctx_, CA_BUNDLE_FILE, nullptr);
    if (r == 0) {
        return -1;
    }

    int error = 0;
    struct hostent* hp;
    struct sockaddr_in addr;
    int socket_;

    if ((hp = gethostbyname(target.c_str())) == 0) {
        return -1;
    }
    memset(&addr, 0, sizeof(addr));
    addr.sin_addr = *(struct in_addr*)hp->h_addr_list[0];
    addr.sin_family = AF_INET;
    addr.sin_port = htons(443);

    socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socket_ < 0) {
        return -1;
    }
    int flag = 1;
    setsockopt(socket_, IPPROTO_TCP, TCP_NODELAY, (char*)&flag, sizeof(flag));
    if (connect(socket_, (struct sockaddr*)&addr, sizeof(addr)) != 0) {
        return -1;
    }
    ssl_ = SSL_new(ctx_);
    SSL_set_fd(ssl_, socket_);

    if (SSL_connect(ssl_) <= 0) {
        // error.
        error = SSL_get_error(ssl_, 0);
    }



}
