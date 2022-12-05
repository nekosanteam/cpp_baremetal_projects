// SPDX-License-Identifier: CC0-1.0
/**
 * @file nkqueue.h
 *
 */
#ifndef NKQUEUE_H_
#define NKQUEUE_H_

#ifdef __cplusplus
#include <cstddef>
#include <cstdint>
using std::size_t;
#else
#include <stddef.h>
#include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct nkring {
	unsigned int num;
	void*        desc;
	void*        avail;
	void*        used;
};

struct nkqueue;

void   nkring_init(struct nkring* nr, unsigned int num, unsigned int align);
size_t nkring_size(unsigned int num, unsigned int align);
int    nkring_need(struct nkring* nr);

int   nkqueue_create(struct nkqueue* nq);
int   nkqueue_add_buffer(struct nkqueue* nq, void* buf, size_t size);
void* nkqueue_get_buffer(struct nkqueue* nq);
void* nkqueue_get_available_buffer(struct nkqueue* nq);
void* nkqueue_add_consumed_buffer(struct nkqueue* nq);
void  nkqueue_kick(struct nkqueue* nq);

#ifdef __cplusplus
}
#endif

#endif // NKQUEUE_H_
