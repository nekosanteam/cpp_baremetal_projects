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

	bool sendto(std::uint8_t* buf, std::size_t size, Address addr, Port port, udp4writer* writer);
	bool recvfrom(std::uint8_t* buf, std::size_t& size, Address& addr, Port port, udp4reader* reader);
};

class udp6 {
public:
	using Address = std::array<std::uint16_t, 8>;
	using Port    = std::uint16_t;

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

	bool send(std::uint8_t* buf, std::size_t size, tcp4writer* writer);
	bool recv(std::uint8_t* buf, std::size_t& size, tcp4reader* reader);
};

class tcp6 {
public:
	using Address = std::array<std::uint16_t, 8>;
	using Port    = std::uint16_t;

	bool send(std::uint8_t* buf, std::size_t size, tcp6writer* writer);
	bool recv(std::uint8_t* buf, std::size_t& size, tcp6reader* reader);
};

}
}

// *.cpp
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

namespace bm {
namespace work {

using std::size_t;
using std::uint8_t;
using std::uint32_t;
using std::array;
using std::memset;

struct udp4writer {
    int sock;
};

struct udp4reader {
    int sock;
};

bool udp4::sendto(uint8_t* buf, size_t size, Address addr, Port port, udp4writer* writer)
{
    int sock = writer->sock;
    struct sockaddr_in dst;
    int ret;

    memset(&dst, 0, sizeof(dst));
    dst.sin_family = AF_INET;
    dst.sin_addr.s_addr = htonl(addr);
    dst.sin_port        = htons(port);
    if ((ret = ::sendto(sock, buf, size, 0, (struct sockaddr*)&dst, sizeof(dst))) != size){

    }
    return true;
}

bool udp4::recvfrom(uint8_t* buf, size_t& size, Address& addr, Port port, udp4reader* reader)
{
    int sock = reader->sock;
    struct sockaddr_in src;
    struct sockaddr_in wai;
    socklen_t src_len;
    size_t ret;

    memset(&wai, 0, sizeof(wai));
    memset(&src, 0, sizeof(src));
    wai.sin_family = AF_INET;
    wai.sin_addr.s_addr = INADDR_ANY;
    wai.sin_port = htons(port);
    bind(sock, (struct sockaddr*)&wai, sizeof(wai));

    src_len = sizeof(src);
    ret = ::recvfrom(sock, buf, size, 0, (struct sockaddr*)&src, &src_len);
    addr = ntohl(src.sin_addr.s_addr);
    port = ntohs(src.sin_port);
    size = ret;

    return true;
}

struct udp6writer {
    int sock;
};

struct udp6reader {
    int sock;
};



}
}

#include <cstdio>

namespace m = bm::work;
using std::strcpy;
using std::strlen;
using std::printf;

int main(int argc, char** argv)
{
    if (argc > 1) {
        if (argv[1][0] == 's') {
            m::udp4 s;
            m::udp4writer p;
            uint8_t buf[128];
            size_t size;

            p.sock = socket(PF_INET, SOCK_DGRAM, 0);
            strcpy((char*)&buf[0], "send");
            size = strlen((char*)&buf[0]);
            s.sendto(&buf[0], size, 0x7F000001u, 5001, &p);
            printf("s: %s\n", &buf[0]);
        }
        else if (argv[1][0] == 'r') {
            m::udp4 r;
            m::udp4reader p;
            uint8_t buf[128];
            size_t size;
            m::udp4::Address addr;

            p.sock = socket(PF_INET, SOCK_DGRAM, 0);
            size = sizeof(buf);
            r.recvfrom(&buf[0], size, addr, 5001, &p);
            printf("r: %s\n", &buf[0]);
        }
    }
    return 0;
}
