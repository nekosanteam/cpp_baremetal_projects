/* SPDX-License-Identifier: MIT-0 */

#include <linux/module.h>

#include <fcntl.h>

static const struct vm_operations_struct mmap_peek_ops = {
	.access = generic_access_phys
};

/* /dev/peek_wb (Write Back) */
static int mmap_peek_wb(struct file* file, struct vm_area_struct* vm)
{
	// vm->vm_page_prot は変更しない(Write-Backに指定)

}

/* /dev/peek_wt (Write Through) */
static int mmap_peek_wt(struct file* file, struct vm_area_struct* vm)
{
	return -EINVAL;
}

/* /dev/peek_wc (Write Combined) */
static int mmap_peek_wc(struct file* file, struct vm_area_struct* vm)
{
	vm->vm_page_prot = pgprot_writecombine(vm->vm_page_prot);
	vm->vm_ops = &mmap_peek_ops;
}

/* /dev/peek_sg (Store/Gather) */
static int mmap_peek_sg(struct file* file, struct vm_area_struct* vm)
{
	vm->vm_ops = &mmap_peek_ops;
	return -EINVAL;
}

/* /dev/peek_sb (Store Buffer [Buffered]) */
static int mmap_peek_sb(struct file* file, struct vm_area_struct* vm)
{
	vm->vm_page_prot = pgprot_device(vm->vm_page_prot);
	vm->vm_ops = &mmap_peek_ops;

}

/* /dev/peek_so (Strongly-Ordered) */
static int mmap_peek_so(struct file* file, struct vm_area_struct* vm)
{
	vm->vm_page_prot = pgprot_noncached(vm->vm_page_prot);
	vm->vm_ops = &mmap_peek_ops;

}

static int open_peek(struct inode* inode, struct file* file)
{
	return 0;
}

static const struct file_operations peek_wb_fops = {
	.mmap = mmap_peek_wb,
	.open = open_peek,
};

static const struct file_operations peek_wt_fops = {
	.mmap = mmap_peek_wt,
	.open = open_peek,
};

static const struct file_operations peek_wc_fops = {
	.mmap = mmap_peek_wc,
	.open = open_peek,
};

static const struct file_operations peek_sg_fops = {
	.mmap = mmap_peek_sg,
	.open = open_peek,
};

static const struct file_operations peek_sb_fops = {
	.mmap = mmap_peek_sb,
	.open = open_peek,
};

static const struct file_operations peek_so_fops = {
	.mmap = mmap_peek_so,
	.open = open_peek,
};

MODULE_LICENSE("GPLv2");

static int peek_init(void)
{
	return 0;
}

static void peek_exit(void)
{
	return;
}

module_init(peek_init);
module_exit(peek_exit);
