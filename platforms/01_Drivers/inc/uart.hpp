#pragma once
/**
 * @file uart.hpp
 * 
 */
#include <cstddef>
#include <cstdint>
#include <string>

namespace nk {
namespace work {

class UART {
public:
	UART();
	virtual ~UART();
	virtual void init();
	virtual void put(char c);
	virtual void put(const char* str);

//	virtual int gets();
//	virtual int sets();
};

} // namespace work
} // namespace nk
