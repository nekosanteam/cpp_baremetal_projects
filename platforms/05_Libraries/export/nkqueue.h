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

#ifndef NKQUEUE_H_
#define NKQUEUE_H_
/**
 * @file nkqueue.h
 *
 */

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
