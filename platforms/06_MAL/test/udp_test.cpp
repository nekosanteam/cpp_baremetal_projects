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
	bool recvfrom(Address& addr, Port& port, std::uint8_t* buf, std::size_t size, udp4reader& reader);
};

class udp6 {
public:
	using Address = std::array<std::uint16_t, 8>;
	using Port    = std::uint16_t;

	bool sendto(std::uint8_t* buf, std::size_t size, Address addr, Port port, udp6writer* writer);
	bool recvfrom(std::uint8_t* buf, std::size_t size, Address& addr, Port& port, udp6reader& reader);
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
	bool recv(std::uint8_t* buf, std::size_t size, tcp4reader& reader);
};

class tcp6 {
public:
	using Address = std::array<std::uint16_t, 8>;
	using Port    = std::uint16_t;

	bool send(std::uint8_t* buf, std::size_t size, tcp6writer* writer);
	bool recv(std::uint8_t* buf, std::size_t size, tcp6reader& reader);
};

}
}

// *.cpp
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace bm {
namespace work {

using std::size_t;
using std::uint8_t;
using std::array;

struct udp4writer {
    int sock;
};

struct udp4reader {
    int sock;
};

bool udp4::sendto(uint8_t* buf, size_t size, Address addr, Port port, udp4writer* writer)
{
    int sock = writer->sock;
    int ret;

    if ((ret = ::sendto(sock, buf, size, &addr)) ) {

    }
}

bool udp4::recvfrom(uint8_t* buf, size_t size, Address& addr, Port& port)
{

}

struct udp6writer {
    int sock;
};

struct udp6reader {
    int sock;
};



}
}
