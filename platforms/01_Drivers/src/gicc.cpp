/**
 * @file gicc.cpp
 *
 */
#include "gicc.hpp"
#include "mmio.hpp"

#include <array>
#include <cstddef>
#include <cstdint>

// GICv2
// ref: https://developer.arm.com/documentation/ihi0048/bb/
// GICv3
// ref: https://developer.arm.com/documentation/ihi0069/h/
// GIC-400
// ref: https://developer.arm.com/documentation/ddi0471/b/
// GIC-500
// ref: https://developer.arm.com/documentation/ddi0516/e/
// GIC-500 Errata
// ref: https://developer.arm.com/documentation/102018/0109/

namespace nk {
namespace work {

class RegisterTable {
public:
	using Addr   = std::uintptr_t;
	using Offset = Addr;

	static inline std::uint32_t read32(Addr reg)
	{
		return *(reinterpret_cast<volatile std::uint32_t*>(reg));
	}

	static inline std::uint64_t read64(Addr reg)
	{
		std::uint64_t val;
		val = static_cast<std::uint64_t>(*(reinterpret_cast<volatile std::uint32_t*>(reg)));
		val |= (static_cast<std::uint64_t>(*(reinterpret_cast<volatile std::uint32_t*>(reg + 4))) << 32);
		return val;
	}

	static inline std::uint32_t write32(Addr reg, std::uint32_t val)
	{
		*(reinterpret_cast<volatile std::uint32_t*>(reg)) = val;
		return *(reinterpret_cast<volatile std::uint32_t*>(reg));
	}

	static inline void write32(Addr reg, std::uint32_t val1, std::uint32_t val2)
	{
		*(reinterpret_cast<volatile std::uint32_t*>(reg))     = val1;
		*(reinterpret_cast<volatile std::uint32_t*>(reg + 4)) = val2;
		return;
	}

	static inline std::uint64_t write64(Addr reg, std::uint64_t val)
	{
		*(reinterpret_cast<volatile std::uint32_t*>(reg))     = static_cast<std::uint32_t>(val & 0xFFFFFFFFu);
		*(reinterpret_cast<volatile std::uint32_t*>(reg + 4)) = static_cast<std::uint32_t>((val >> 32) & 0xFFFFFFFFu);
		return read64(reg);
	}

	static inline std::uint32_t clear32(Addr reg, std::uint32_t bitP)
	{
		std::uint32_t val = read32(reg);
		return write32(reg, (val & (~bitP)));
	}

	static inline std::uint64_t clear64(Addr reg, std::uint64_t bitP)
	{
		std::uint64_t val = read64(reg);
		return write64(reg, (val & (~bitP)));
	}
};

class GICD_ : public RegisterTable {
public:
	using RegisterTable::Addr;
	using RegisterTable::Offset;

	const static Offset CTLR        = 0x0000;
	const static Offset IIDR        = 0x0008;
	const static Offset IGROUPR0    = 0x0080;
	const static Offset ISENABLER0  = 0x0100;
	const static Offset ICENABLER0  = 0x0180;
	const static Offset ISPENDR0    = 0x0200;
	const static Offset ICPENDR0    = 0x0280;
	const static Offset ISACTIVER0  = 0x0300;
	const static Offset ICACTIVER0  = 0x0380;
	const static Offset IPRIORITYR0 = 0x0400;
	const static Offset ITARGETSR0  = 0x0800;
	const static Offset ICFGR0      = 0x0C00;
	const static Offset IGRPMODR0   = 0x0D00;
	const static Offset NSACR0      = 0x0E00;
	const static Offset SGIR        = 0x0F00;
	const static Offset CPENDSGIR0  = 0x0F10;
	const static Offset SPENDSGIR0  = 0x0F20;
	const static Offset INMIR0      = 0x0F80;
	const static Offset IROUTER0    = 0x6000;
};

using MMIO::Register;
using MMIO::Register64;
using MMIO::RegisterArray;
using MMIO::RegisterArray64;

namespace devkit {
constexpr MMIO::PhyAddr GIC_ADDR { 0xffc00000 };
constexpr MMIO::PhyAddr GICD_OFFSET { 0x1000 };
constexpr MMIO::PhyAddr GICC_OFFSET { 0x2000 };
using GIC_BASE  = MMIO::PhyBase<GIC_ADDR>;
using GICD_BASE = MMIO::PhyBase<GIC_ADDR + GICD_OFFSET>;
using GICC_BASE = MMIO::PhyBase<GIC_ADDR + GICC_OFFSET>;
} // namespace devkit
namespace qemu {
constexpr MMIO::PhyAddr GICD_ADDR { 0x08000000 };
constexpr MMIO::PhyAddr GICC_ADDR { 0x08010000 };
using GICD_BASE = MMIO::PhyBase<GICD_ADDR>;
using GICC_BASE = MMIO::PhyBase<GICC_ADDR>;
} // namespace qemu

using qemu::GICC_BASE;
using qemu::GICD_BASE;

// GICD Registers. (Distributor)
constexpr Register<GICD_BASE, 0x0000> GICD_CTLR {};  ///< Distributor control register.
constexpr Register<GICD_BASE, 0x0004> GICD_TYPER {}; ///< Interrupt control type register.
constexpr Register<GICD_BASE, 0x0008> GICD_IIDR {};  ///< Distributor Implementer Identification Register.
namespace gic_v3 {
constexpr Register<GICD_BASE, 0x0040> GICD_SETSPI_NSR {}; // GICv3
constexpr Register<GICD_BASE, 0x0048> GICD_CLRSPI_NSR {}; // GICv3
constexpr Register<GICD_BASE, 0x0050> GICD_SETSPI_SR {};  // GICv3
constexpr Register<GICD_BASE, 0x0058> GICD_CLRSPI_SR {};  // GICv3
} // namespace gic_v3
constexpr RegisterArray<GICD_BASE, 0x0080, 32>  GICD_IGROUPn {};
constexpr RegisterArray<GICD_BASE, 0x0100, 32>  GICD_ISENABLERn {};
constexpr RegisterArray<GICD_BASE, 0x0180, 32>  GICD_ICENABLERn {};
constexpr RegisterArray<GICD_BASE, 0x0200, 32>  GICD_ISPENDRn {};
constexpr RegisterArray<GICD_BASE, 0x0280, 32>  GICD_ICPENDRn {};
constexpr RegisterArray<GICD_BASE, 0x0300, 32>  GICD_ISACTIVERn {};
constexpr RegisterArray<GICD_BASE, 0x0380, 32>  GICD_ICACTIVERn {};
constexpr RegisterArray<GICD_BASE, 0x0400, 256> GICD_IPRIORITYRn {};
constexpr RegisterArray<GICD_BASE, 0x0800, 256> GICD_ITARGETSRn {};
constexpr RegisterArray<GICD_BASE, 0x0C00, 256> GICD_ICFGRn {};
namespace gic_v2 {
constexpr Register<GICD_BASE, 0x0D00>          GICD_PPISR {};  // GICv2 only.
constexpr RegisterArray<GICD_BASE, 0x0D04, 15> GICD_SPISRn {}; // GICv2 only.
} // namespace gic_v2
namespace gic_v3 {
constexpr RegisterArray<GICD_BASE, 0x0D00, 32> GICD_IGRPMODRn {}; // GICv3 only.
constexpr RegisterArray<GICD_BASE, 0x0E04, 64> GICD_NCACRn {};    // GICv3 only.
} // namespace gic_v3
constexpr Register<GICD_BASE, 0x0F00>         GICD_SGIR {};
constexpr RegisterArray<GICD_BASE, 0x0F10, 4> GICD_CPENDSGIRn {};
constexpr RegisterArray<GICD_BASE, 0x0F20, 4> GICD_SPENDSGIRn {};
namespace gic_v2 {
constexpr Register<GICD_BASE, 0x0FD0> GICD_PIDR4 {};
constexpr Register<GICD_BASE, 0x0FD4> GICD_PIDR5 {};
constexpr Register<GICD_BASE, 0x0FD8> GICD_PIDR6 {};
constexpr Register<GICD_BASE, 0x0FDC> GICD_PIDR7 {};
constexpr Register<GICD_BASE, 0x0FE0> GICD_PIDR0 {};
constexpr Register<GICD_BASE, 0x0FE4> GICD_PIDR1 {};
constexpr Register<GICD_BASE, 0x0FE8> GICD_PIDR2 {};
constexpr Register<GICD_BASE, 0x0FEC> GICD_PIDR3 {};
constexpr Register<GICD_BASE, 0x0FF0> GICD_CIDR0 {};
constexpr Register<GICD_BASE, 0x0FF4> GICD_CIDR1 {};
constexpr Register<GICD_BASE, 0x0FF8> GICD_CIDR2 {};
constexpr Register<GICD_BASE, 0x0FFC> GICD_CIDR3 {};
} // namespace gic_v2
namespace gic_v3 {
constexpr RegisterArray64<GICD_BASE, 0x6000, 960> GICD_IROUTER {};  // GICv3 only.
constexpr Register<GICD_BASE, 0xC000>             GICD_ESTATUSR {}; // GICv3 only.
constexpr Register<GICD_BASE, 0xC004>             GICD_ERRTESTR {}; // GICv3 only.
constexpr RegisterArray<GICD_BASE, 0xC084, 30>    GICD_SPISR {};    // GICv3 only.
} // namespace gic_v3
namespace gic_v3 {
constexpr Register<GICD_BASE, 0xFFD0> GICD_PIDR4 {};
constexpr Register<GICD_BASE, 0xFFD4> GICD_PIDR5 {};
constexpr Register<GICD_BASE, 0xFFD8> GICD_PIDR6 {};
constexpr Register<GICD_BASE, 0xFFDC> GICD_PIDR7 {};
constexpr Register<GICD_BASE, 0xFFE0> GICD_PIDR0 {};
constexpr Register<GICD_BASE, 0xFFE4> GICD_PIDR1 {};
constexpr Register<GICD_BASE, 0xFFE8> GICD_PIDR2 {};
constexpr Register<GICD_BASE, 0xFFEC> GICD_PIDR3 {};
constexpr Register<GICD_BASE, 0xFFF0> GICD_CIDR0 {};
constexpr Register<GICD_BASE, 0xFFF4> GICD_CIDR1 {};
constexpr Register<GICD_BASE, 0xFFF8> GICD_CIDR2 {};
constexpr Register<GICD_BASE, 0xFFFC> GICD_CIDR3 {};
} // namespace gic_v3

// GICC Registers (GICv2)
constexpr Register<GICC_BASE, 0x0000> GICC_CTLR {}; //<
constexpr Register<GICC_BASE, 0x0004> GICC_PMR {};
constexpr Register<GICC_BASE, 0x0008> GICC_BPR {};
constexpr Register<GICC_BASE, 0x000C> GICC_IAR {};
constexpr Register<GICC_BASE, 0x0010> GICC_EOIR {};
constexpr Register<GICC_BASE, 0x0014> GICC_RPR {};
constexpr Register<GICC_BASE, 0x0018> GICC_HPPIR {};
constexpr Register<GICC_BASE, 0x001C> GICC_ABPR {};
constexpr Register<GICC_BASE, 0x0020> GICC_AIAR {};
constexpr Register<GICC_BASE, 0x0024> GICC_AEOIR {};
constexpr Register<GICC_BASE, 0x0028> GICC_AHPPIR {};
constexpr Register<GICC_BASE, 0x00D0> GICC_APR0 {};
constexpr Register<GICC_BASE, 0x00E0> GICC_NSAPR0 {};
constexpr Register<GICC_BASE, 0x00FC> GICC_IIDR {};
constexpr Register<GICC_BASE, 0x1000> GICC_DIR {};

void GICD::init()
{
	uint32_t reg = GICD_IIDR.get();
	GICD_IIDR.set(reg);
}

void GICD::enable(int intno)
{
	(void)intno;
}

void GICD::disable(int intno)
{
	(void)intno;
}

void GICC::init() { }

void GICC::enable() { }

void GICC::disable() { }

} // namespace work
} // namespace bm
