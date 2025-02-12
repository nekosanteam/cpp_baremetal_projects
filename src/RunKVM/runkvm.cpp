

#include <cstdint>
#include <cstdio>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include <linux/kvm.h>

using std::printf;
using std::uint32_t;
using std::uint64_t;
using std::uintptr_t;
using std::size_t;

int kvm_main(uintptr_t start_addr, size_t rom_size, size_t ram_size)
{
	int kvmfd;
	int vmfd;
	int vcpufd;

	void* vmmem;

	kvmfd = open("/dev/kvm", O_RDWR);
	if (kvmfd < 0) {
		perror("open_kvm");
		return 1;
	}

	vmfd = ioctl(kvmfd, KVM_CREATE_VM, 0);
	if (vmfd < 0) {
		perror("ioctl(KVM_CREATE_VM)");
		return 1;
	}

	vmmem = mmap(NULL, rom_size, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS|MAP_NORESERVE, -1, 0);
	if (vmmem == nullptr) {
		perror("mmap()");
		return 1;
	}
	// copy ROM data to mem.

	struct kvm_userspace_memory_region region = {
		.guest_phys_addr = 0,
		.memory_size = (unsigned long long)ram_size,
		.userspace_addr = (unsigned long long)rom_size
	};
	ioctl(vmfd, KVM_SET_USER_MEMORY_REGION, &region);

	vcpufd = ioctl(vmfd, KVM_CREATE_VCPU, 0);
	size_t mmap_size = ioctl(kvmfd, KVM_GET_VCPU_MMAP_SIZE, NULL);

	struct kvm_run* run = mmap(NULL, mmap_size, PROT_READ|PROT_WRITE, MAP_SHARED, vcpufd, 0);
	
	struct kvm_sregs sregs;
	ioctl(vcpufd, KVM_GET_SREGS, &sregs);
	sregs.cs.base = 0;
	sregs.cs.selector = 0;
	ioctl(vcpufd, KVM_SET_SREGS, &sregs);

	struct kvm_regs regs = {
		.rip = 0x0,
		.rflags = 0x02,
	};
	ioctl(vcpufd, KVM_SET_REGS, &regs);

	unsigned int done = 0;
	while (!done) {
		ioctl(vcpufd, KVM_RUN, NULL);

		switch (run->exit_reason) {
		case KVM_EXIT_HLT:
			done = 1;
			break;
		case KVM_EXIT_IO:
			if ((run->io.port == 0x01) && (run->io.direction == KVM_EXIT_IO_OUT)) {
				putchar(*(char*)((unsigned char*)run + run->io.data_offset));
			}
			break;
		default:
			break;
		}
	}

	return 0;
}
