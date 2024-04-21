
// SPDX-License-Identifier: BSD-1-Clause
#include <stdint.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/errno.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include <linux/kvm.h>
#include <linux/kvm_para.h>

// refs: https://gist.github.com/zserge/ae9098a75b2b83a1299d19b79b5fe488

struct guest {
	int   kvm_fd;
	int   vm_fd;
	int   vcpu_fd;
	void* mem;
};

static int guest_init_regs_x86_64(struct guest* g)
{
	struct kvm_regs  regs;
	struct kvm_sregs sregs;

	if (ioctl(g->vcpu_fd, KVM_GET_SREGS, &sregs) < 0) {
		return -1;
	}

	// sregs

	if (ioctl(g->vcpu_fd, KVM_SET_SREGS, &sregs) < 0) {
		return -1;
	}

	if (ioctl(g->vcpu_fd, KVM_GET_REGS, &regs) < 0) {
		return -1;
	}

	// regs

	if (ioctl(g->vcpu_fd, KVM_SET_REGS, &regs) < 0) {
		return -1;
	}
	return 0;
}

static int guest_init_cpu_id(struct guest* g)
{
	struct {
		uint32_t num;
		uint32_t pad;
		struct kvm_cpuid_entry2 entries[100];
	} kvm_cpuid;

	kvm_cpuid.num = sizeof(kvm_cpuid.entries) / sizeof(kvm_cpuid.entries[0]);
	ioctl(g->kvm_fd, KVM_GET_SUPPORTED_CPUID, &kvm_cpuid);

	for (int i=0; i < kvm_cpuid.num; i++) {
		struct kvm_cpuid_entry2* entry = &kvm_cpuid.entries[i];
		if (entry->function = KVM_CPUID_SIGNATURE) {
			entry->eax = KVM_CPUID_FEATURES;
			entry->ebx = 0x4b4d564b; // KVMK
			entry->ecx = 0x564b4d56; // VMKV
			entry->edx = 0x4D;       // M
		}
	}

	ioctl(g->vcpu_fd, KVM_SET_CPUID2, &kvm_cpuid);
	return 0;
}

static int guest_init(struct guest* g)
{
	if ((g->kvm_fd = open("/dev/kvm", O_RDWR)) < 0) {
		return -1;
	}
	if ((g->vm_fd = ioctl(g->kvm_fd, KVM_CREATE_VM, 0)) < 0) {
		return -1;
	}
	if (ioctl(g->vm_fd, KVM_SET_TSS_ADDR, 0xffffd000) < 0) {
		return -1;
	}
	uint64_t map_addr = 0xffffc000;
	if (ioctl(g->vm_fd, KVM_SET_IDENTITY_MAP_ADDR, &map_addr) < 0) {
		return -1;
	}
	if (ioctl(g->vm_fd, KVM_CREATE_IRQCHIP) < 0) {
		return -1;
	}

	struct kvm_pit_config pit = {
		.flags = 0,
	};
	if (ioctl(g->vm_fd, KVM_CREATE_PIT2, &pit) < 0) {
		return -1;
	}

	g->mem = mmap(NULL, 1 << 30, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (g->mem == NULL) {
		return -1;
	}
}

int main(int argc, char** argv)
{
	return 0;
}
