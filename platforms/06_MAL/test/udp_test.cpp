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

#include <array>
#include <cstddef>
#include <cstdint>

namespace bm {
namespace work {

struct udp4writer;
struct udp4reader;
struct udp6writer;
struct udp6reader;

class udp4 {
public:
	using Address = std::uint32_t;
	using Port    = std::uint16_t;

	constexpr static Address ANY_ADDRESS { 0 };
	constexpr static Port    ANY_PORT { 0 };

	bool sendto(std::uint8_t* buf, std::size_t size, Address addr, Port port, udp4writer* writer);
	bool recvfrom(std::uint8_t* buf, std::size_t& size, Address& addr, Port port, udp4reader* reader);
};

class udp6 {
public:
	using Address = std::array<std::uint16_t, 8>;
	using Port    = std::uint16_t;

	constexpr static Address ANY_ADDRESS { 0 };
	constexpr static Port    ANY_PORT { 0 };

	bool sendto(std::uint8_t* buf, std::size_t size, Address addr, Port port, udp6writer* writer);
	bool recvfrom(std::uint8_t* buf, std::size_t& size, Address& addr, Port port, udp6reader* reader);
};

struct tcp4writer;
struct tcp4reader;
struct tcp6writer;
struct tcp6reader;

class tcp4 {
public:
	using Address = std::uint32_t;
	using Port    = std::uint16_t;

	constexpr static Address ANY_ADDRESS { 0 };
	constexpr static Port    ANY_PORT { 0 };

	bool send(std::uint8_t* buf, std::size_t size, tcp4writer* writer);
	bool recv(std::uint8_t* buf, std::size_t& size, tcp4reader* reader);
};

class tcp6 {
public:
	using Address = std::array<std::uint16_t, 8>;
	using Port    = std::uint16_t;

	constexpr static Address ANY_ADDRESS { 0 };
	constexpr static Port    ANY_PORT { 0 };

	bool send(std::uint8_t* buf, std::size_t size, tcp6writer* writer);
	bool recv(std::uint8_t* buf, std::size_t& size, tcp6reader* reader);
};

} // namespace work
} // namespace bm

// *.cpp
#include <cstring>
#include <vector>

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace bm {
namespace work {

using std::array;
using std::memset;
using std::size_t;
using std::uint32_t;
using std::uint8_t;

struct udp4writer {
	int sock;
};

struct udp4reader {
	int sock;
};

bool udp4::sendto(uint8_t* buf, size_t size, Address addr, Port port, udp4writer* writer)
{
	int                sock = writer->sock;
	struct sockaddr_in dst;
	int                ret;

	memset(&dst, 0, sizeof(dst));
	dst.sin_family      = AF_INET;
	dst.sin_addr.s_addr = htonl(addr);
	dst.sin_port        = htons(port);
	if ((ret = ::sendto(sock, buf, size, 0, (struct sockaddr*)&dst, sizeof(dst))) != size) {
	}
	return true;
}

bool udp4::recvfrom(uint8_t* buf, size_t& size, Address& addr, Port port, udp4reader* reader)
{
	int                sock = reader->sock;
	struct sockaddr_in src;
	struct sockaddr_in wai;
	socklen_t          src_len;
	size_t             ret;

	memset(&wai, 0, sizeof(wai));
	memset(&src, 0, sizeof(src));
	wai.sin_family      = AF_INET;
	wai.sin_addr.s_addr = INADDR_ANY;
	wai.sin_port        = htons(port);
	bind(sock, (struct sockaddr*)&wai, sizeof(wai));

	src_len = sizeof(src);
	ret     = ::recvfrom(sock, buf, size, 0, (struct sockaddr*)&src, &src_len);
	addr    = ntohl(src.sin_addr.s_addr);
	port    = ntohs(src.sin_port);
	size    = ret;

	return true;
}

struct udp6writer {
	int sock;
};

struct udp6reader {
	int sock;
};

} // namespace work
} // namespace bm

#include <cstdio>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

namespace m = bm::work;
using std::printf;
using std::strcpy;
using std::strlen;

void print_v4addr(sockaddr* addr, size_t len)
{
	// https://man7.org/linux/man-pages/man7/ip.7.html
	sockaddr_in* rp = (sockaddr_in*)addr;
	uint32_t     nt = ntohl(rp->sin_addr.s_addr);
	printf("v4 addr %08x ", nt); // uint32_t.
	for (int i = 0; i < 4; i++) {
		printf("%d.", (uint8_t)(nt >> ((3 - i) * 8)));
	}
}

void print_v6addr(sockaddr* addr, size_t len)
{
	// https://man7.org/linux/man-pages/man7/ipv6.7.html
	sockaddr_in6* rp = (sockaddr_in6*)addr;

	printf("v6 addr ");
	for (int i = 0; i < 8; i++) {
		printf("%02x%02x:", rp->sin6_addr.s6_addr[i * 2], rp->sin6_addr.s6_addr[i * 2 + 1]);
	}
}

int main(int argc, char** argv)
{
	/*
	    std::string str;
	    printf("std::string size = %d\n", sizeof(str)); // 32 (amd64 linux)
	    std::vector<std::uint32_t> vec;
	    printf("std::vector size = %d\n", sizeof(vec)); // 24 (amd64 linux)
	    std::forward_list<std::uint32_t> flst;
	    printf("std::forward_list size = %d\n", sizeof(flst)); // 8 (amd64 linux)
	    std::list<std::uint32_t> lst;
	    printf("std::list   size = %d\n", sizeof(lst)); // 24 (amd64 linux)
	    std::queue<std::uint32_t> que;
	    printf("std::queue  size = %d\n", sizeof(que)); // 80 (amd64 linux)
	    std::deque<std::uint32_t> deq;
	    printf("std::deque  size = %d\n", sizeof(deq)); // 80 (amd64 linux)
	    std::map<std::string, std::string> map;
	    printf("std::map    size = %d\n", sizeof(map)); // 48 (amd64 linux)
	    std::map<std::uint8_t, std::uint8_t> map2;
	    printf("std::map(int) size = %d\n", sizeof(map2)); // 48 (amd64 linux)
	    std::set<std::string> set;
	    printf("std::set    size = %d\n", sizeof(set)); // 48 (amd64 linux)
	*/
	if (argc > 1) {
		if (argv[1][0] == 's') {
			m::udp4       s;
			m::udp4writer p;

			uint8_t buf[128];
			size_t  size;

			p.sock = socket(PF_INET, SOCK_DGRAM, 0);
			strcpy((char*)&buf[0], "send");
			size = strlen((char*)&buf[0]);
			s.sendto(&buf[0], size, 0x7F000001u, 5001, &p);
			printf("s: %s\n", &buf[0]);
		}
		else if (argv[1][0] == 'r') {
			m::udp4          r;
			m::udp4reader    p;
			m::udp4::Address addr;

			uint8_t buf[128];
			size_t  size;

			p.sock = socket(PF_INET, SOCK_DGRAM, 0);
			size   = sizeof(buf);
			r.recvfrom(&buf[0], size, addr, 5001, &p);
			printf("r: %s\n", &buf[0]);
		}
		else if (argv[1][0] == 'a') {
			struct addrinfo  hints;
			struct addrinfo* results;

			int r;

			memset(&hints, 0, sizeof(hints));
			hints.ai_family   = AF_UNSPEC;
			hints.ai_socktype = SOCK_DGRAM;
			hints.ai_flags    = 0;
			hints.ai_protocol = 0;
			if (argc > 2) {
				r = getaddrinfo(argv[2], "4000", &hints, &results);
				if (r) {
					perror("getaddrinfo");
					exit(EXIT_FAILURE);
				}
				for (struct addrinfo* rp = results; rp != NULL; rp = rp->ai_next) {
					printf("family: %d ", rp->ai_family);
					if (rp->ai_family == AF_INET) {
						print_v4addr(rp->ai_addr, rp->ai_addrlen);
					}
					else if (rp->ai_family == AF_INET6) {
						print_v6addr(rp->ai_addr, rp->ai_addrlen);
					}
					printf("\n");
				}
				freeaddrinfo(results);
			}
		}
	}
	return 0;
}
