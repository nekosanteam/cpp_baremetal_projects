/* SPDX-License-Identifier: MIT-0 */
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
