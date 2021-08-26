#include "gicc.hpp"
#include "mmio.hpp"

#include <array>
#include <cstddef>
#include <cstdint>

// GIC-400
// ref: https://developer.arm.com/documentation/ddi0471/b/
// GIC-500
// ref: https://developer.arm.com/documentation/ddi0516/e/

namespace work {

using MMIO::Register;
using MMIO::Register64;
using MMIO::RegisterArray;
using MMIO::RegisterArray64;

constexpr MMIO::PhyAddr GIC_BASE = 0xffc00000;
constexpr MMIO::PhyAddr GICD_BASE = GIC_BASE + 0x1000;
constexpr MMIO::PhyAddr GICC_BASE = GIC_BASE + 0x2000;

// GICD Registers.
constexpr Register<GICD_BASE, 0x0000> GICD_CTLR{};
constexpr Register<GICD_BASE, 0x0004> GICD_TYPER{};
constexpr Register<GICD_BASE, 0x0008> GICD_IIDR{};
constexpr Register<GICD_BASE, 0x0040> GICD_SETSPI_NSR{}; // GICv3
constexpr Register<GICD_BASE, 0x0048> GICD_CLRSPI_NSR{}; // GICv3
constexpr Register<GICD_BASE, 0x0050> GICD_SETSPI_SR{};  // GICv3
constexpr Register<GICD_BASE, 0x0058> GICD_CLRSPI_SR{};  // GICv3
constexpr RegisterArray<GICD_BASE, 0x0080, 32> GICD_IGROUPn{};
constexpr RegisterArray<GICD_BASE, 0x0100, 32> GICD_ISENABLERn{};
constexpr RegisterArray<GICD_BASE, 0x0180, 32> GICD_ICENABLERn{};
constexpr RegisterArray<GICD_BASE, 0x0200, 32> GICD_ISPENDRn{};
constexpr RegisterArray<GICD_BASE, 0x0280, 32> GICD_ICPENDRn{};
constexpr RegisterArray<GICD_BASE, 0x0300, 32> GICD_ISACTIVERn{};
constexpr RegisterArray<GICD_BASE, 0x0380, 32> GICD_ICACTIVERn{};
constexpr RegisterArray<GICD_BASE, 0x0400, 256> GICD_IPRIORITYRn{};
constexpr RegisterArray<GICD_BASE, 0x0800, 256> GICD_ITARGETSRn{};
constexpr RegisterArray<GICD_BASE, 0x0C00, 256> GICD_ICFGRn{};
constexpr Register<GICD_BASE, 0x0D00> GICD_PPISR{};              // GICv2 only.
constexpr RegisterArray<GICD_BASE, 0x0D04, 15> GICD_SPISRn{};    // GICv2 only.
constexpr RegisterArray<GICD_BASE, 0x0D00, 32> GICD_IGRPMODRn{}; // GICv3 only.
constexpr RegisterArray<GICD_BASE, 0x0E04, 64> GICD_NCACRn{};    // GICv3 only.
constexpr Register<GICD_BASE, 0x0F00> GICD_SGIR{};
constexpr RegisterArray<GICD_BASE, 0x0F10, 4> GICD_CPENDSGIRn{};
constexpr RegisterArray<GICD_BASE, 0x0F20, 4> GICD_SPENDSGIRn{};
namespace v2 {
constexpr Register<GICD_BASE, 0x0FD0> GICD_PIDR4{};
constexpr Register<GICD_BASE, 0x0FD4> GICD_PIDR5{};
constexpr Register<GICD_BASE, 0x0FD8> GICD_PIDR6{};
constexpr Register<GICD_BASE, 0x0FDC> GICD_PIDR7{};
constexpr Register<GICD_BASE, 0x0FE0> GICD_PIDR0{};
constexpr Register<GICD_BASE, 0x0FE4> GICD_PIDR1{};
constexpr Register<GICD_BASE, 0x0FE8> GICD_PIDR2{};
constexpr Register<GICD_BASE, 0x0FEC> GICD_PIDR3{};
constexpr Register<GICD_BASE, 0x0FF0> GICD_CIDR0{};
constexpr Register<GICD_BASE, 0x0FF4> GICD_CIDR1{};
constexpr Register<GICD_BASE, 0x0FF8> GICD_CIDR2{};
constexpr Register<GICD_BASE, 0x0FFC> GICD_CIDR3{};
} // namespace v2
constexpr RegisterArray64<GICD_BASE, 0x6000, 960> GICD_IROUTER{}; // GICv3 only.
constexpr Register<GICD_BASE, 0xC000> GICD_ESTATUSR{};            // GICv3 only.
constexpr Register<GICD_BASE, 0xC004> GICD_ERRTESTR{};            // GICv3 only.
constexpr RegisterArray<GICD_BASE, 0xC084, 30> GICD_SPISR{};      // GICv3 only.
namespace v3 {
constexpr Register<GICD_BASE, 0xFFD0> GICD_PIDR4{};
constexpr Register<GICD_BASE, 0xFFD4> GICD_PIDR5{};
constexpr Register<GICD_BASE, 0xFFD8> GICD_PIDR6{};
constexpr Register<GICD_BASE, 0xFFDC> GICD_PIDR7{};
constexpr Register<GICD_BASE, 0xFFE0> GICD_PIDR0{};
constexpr Register<GICD_BASE, 0xFFE4> GICD_PIDR1{};
constexpr Register<GICD_BASE, 0xFFE8> GICD_PIDR2{};
constexpr Register<GICD_BASE, 0xFFEC> GICD_PIDR3{};
constexpr Register<GICD_BASE, 0xFFF0> GICD_CIDR0{};
constexpr Register<GICD_BASE, 0xFFF4> GICD_CIDR1{};
constexpr Register<GICD_BASE, 0xFFF8> GICD_CIDR2{};
constexpr Register<GICD_BASE, 0xFFFC> GICD_CIDR3{};
} // namespace v3

// GICC Registers (GICv2)
constexpr Register<GICC_BASE, 0x0000> GICC_CTLR{};
constexpr Register<GICC_BASE, 0x0004> GICC_PMR{};
constexpr Register<GICC_BASE, 0x0008> GICC_BPR{};
constexpr Register<GICC_BASE, 0x000C> GICC_IAR{};
constexpr Register<GICC_BASE, 0x0010> GICC_EOIR{};
constexpr Register<GICC_BASE, 0x0014> GICC_RPR{};
constexpr Register<GICC_BASE, 0x0018> GICC_HPPIR{};
constexpr Register<GICC_BASE, 0x001C> GICC_ABPR{};
constexpr Register<GICC_BASE, 0x0020> GICC_AIAR{};
constexpr Register<GICC_BASE, 0x0024> GICC_AEOIR{};
constexpr Register<GICC_BASE, 0x0028> GICC_AHPPIR{};
constexpr Register<GICC_BASE, 0x00D0> GICC_APR0{};
constexpr Register<GICC_BASE, 0x00E0> GICC_NSAPR0{};
constexpr Register<GICC_BASE, 0x00FC> GICC_IIDR{};
constexpr Register<GICC_BASE, 0x1000> GICC_DIR{};

void GICD::init() {
}

void GICD::enable(int intno) {
}

void GICD::disable(int intno) {
}

void GICC::init() {
}

void GICC::enable() {
}

void GICC::disable() {
}

} // namespace work
