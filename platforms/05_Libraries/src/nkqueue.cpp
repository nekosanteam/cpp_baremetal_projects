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
/**
 * @file nkqueue.cpp
 *
 */

#include "nkqueue.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>

using std::array;
using std::copy_n;

using nkq_size = size_t;

#define UNUSED(v) (void)(v)

struct vring {
	array<uint8_t, 128> ring;
	nkq_size            wp;
	nkq_size            rp;
};

bool is_empty(const struct vring& r)
{
	nkq_size rp = r.rp;
	nkq_size wp = r.wp;

	return (rp == wp);
}

nkq_size ring_size(const struct vring& r)
{
	return (nkq_size)(r.ring.size());
}

nkq_size get_room(const struct vring& r)
{
	nkq_size rp = r.rp;
	nkq_size wp = r.wp;

	if (rp == wp) {
		return ring_size(r);
	}
	if (rp < wp) {
		// assert(((wp - rp) <= r.ring.size()))
		return (ring_size(r) - (wp - rp));
	}
	else {
		// assert(((rp - wp) >= r.ring.size()))
		return ((rp - wp) - ring_size(r));
	}
}

nkq_size recv(struct vring& r, uint8_t* buf, size_t len)
{
	if (is_empty(r)) {
		return 0;
	}

	nkq_size ret;
	if ((ret = (ring_size(r) - get_room(r))) < len) {
		len = ret;
	}

	nkq_size rp = r.rp;
	nkq_size wp = r.wp;

	nkq_size rrp;
	if (rp < ring_size(r)) {
		rrp = rp;
	}
	else {
		rrp = rp - ring_size(r);
	}

	if ((rp + len) < 2 * ring_size(r)) {
		rp = rp + len;
	}
	else {
		// assert(rp >= r.ring.size());
		rp = ((rp - ring_size(r)) + len) - ring_size(r);
	}

	if ((ring_size(r) - rrp) >= len) {
		copy_n(&r.ring[rrp], len, &buf[0]);
	}
	else {
		size_t a = ring_size(r) - rrp;
		size_t b = len - a;
		copy_n(&r.ring[rrp], a, &buf[0]);
		copy_n(&r.ring[0], b, &buf[a]);
	}
	r.rp = rp;

	return len;
}

size_t send(struct vring& r, const uint8_t* buf, size_t len)
{
	size_t ret;

	if ((ret = get_room(r)) < len) {
		len = ret;
		if (len == 0) {
			return 0;
		}
	}

	size_t wp = r.wp;
	size_t rp = r.rp;

	size_t rwp;
	if (wp < ring_size(r)) {
		rwp = wp;
	}
	else {
		rwp = wp - ring_size(r);
	}

	if ((wp + len) < 2 * ring_size(r)) {
		wp = wp + len;
	}
	else {
		// assert(wp >= r.ring.size());
		wp = ((wp - ring_size(r)) + len) - ring_size(r);
	}

	if ((ring_size(r) - rwp) >= len) {
		copy_n(&buf[0], len, &r.ring[rwp]);
	}
	else {
		size_t a = ring_size(r) - rwp;
		;
		size_t b = len - a;
		copy_n(&buf[0], a, &r.ring[rwp]);
		copy_n(&buf[a], b, &r.ring[0]);
	}
	r.wp = wp;

	return len;
}

#include <cstdio>
#include <cstring>

#undef NDEBUG
#include <cassert>

void assert_vring(struct vring& r)
{
	assert(get_room(r) <= r.ring.size());
	assert(r.wp < 2 * r.ring.size());
	assert(r.rp < 2 * r.ring.size());

	if (r.rp == r.wp) {
		// empty(), ok.
		return;
	}
	else if (r.rp < r.wp) {
		assert(((r.wp - r.rp) <= r.ring.size()));
	}
	else { // rp > wp
		assert(((r.rp - r.wp) >= r.ring.size()));
	}
}

void dump_buffer(uint8_t* buf, int len)
{
	for (int i = 0; i < len; i++) {
		std::printf("%02x ", buf[i]);
		if ((i & 0x0F) == 0x0F) {
			std::printf("\n");
		}
	}
	std::printf("\n");
}

void print_vring(struct vring& r)
{
	for (int i = 0; i < 128; i++) {
		std::printf("%02x ", r.ring.at(i));
		if ((i & 0x0F) == 0x0F) {
			std::printf("\n");
		}
	}
	std::printf("wp = %ld\n", r.wp);
	std::printf("rp = %ld\n", r.rp);
	std::printf("empty = %d, get_room = %ld\n", is_empty(r), get_room(r));
	std::printf("\n");
}

extern "C" int nkqueue_test(int argc, char** argv)
{
	struct vring ring { };
	uint8_t      bufA[128];
	uint8_t      bufB[128];
	size_t       r;

	for (int i = 0; i < 128; i++) {
		bufA[i] = (char)i;
		bufB[i] = 0;
	}

	int t0;
	std::printf("t0\n");
	for (size_t i = 0; i < 256; i++) {
		send(ring, bufA, 128);
		assert_vring(ring);
		recv(ring, bufB, 128);
		assert_vring(ring);
		if ((t0 = std::memcmp(bufA, bufB, 128)) != 0) {
			std::printf("memcmp[%d] = %d\n", i, t0);
			print_vring(ring);
			assert_vring(ring);
			return 1;
		}
	}

	int t1;
	std::printf("t1\n");
	for (size_t i = 0; i < 256; i++) {
		send(ring, bufA, 1);
		assert_vring(ring);
		recv(ring, bufB, 1);
		assert_vring(ring);
		if ((t1 = std::memcmp(bufA, bufB, 1)) != 0) {
			std::printf("memcmp[%d] = %d\n", i, t1);
			print_vring(ring);
			assert_vring(ring);
			return 1;
		}
	}

	int t2;
	std::printf("t2\n");
	for (size_t i = 0; i < 256; i++) {
		for (size_t j = 0; j < 128; j++) {
			send(ring, bufA, j + 1);
			assert_vring(ring);
			// print_vring(ring);
			recv(ring, bufB, j + 1);
			assert_vring(ring);
			// print_vring(ring);
			if ((t2 = std::memcmp(bufA, bufB, j + 1)) != 0) {
				dump_buffer(bufB, j + 1);
				std::printf("memcmp[%d, %d] = %d\n", i, j, t2);
				print_vring(ring);
				assert_vring(ring);
				return 1;
			}
			// std::printf("check %4d, %4d, get_room(%4d), rp %4ld, wp %4ld\n", i, j, get_room(ring), ring.rp, ring.wp);
		}
	}

	int t3;
	std::printf("t3\n");
	for (size_t i = 0; i < 256; i++) {
		for (size_t j = 128; j > 0; j--) {
			send(ring, bufA, j);
			assert_vring(ring);
			recv(ring, bufB, j);
			assert_vring(ring);
			if ((t3 = std::memcmp(bufA, bufB, j)) != 0) {
				dump_buffer(bufB, j);
				std::printf("memcmp[%d, %d] = %d\n", i, j, t3);
				print_vring(ring);
				assert_vring(ring);
				return 1;
			}
		}
	}

	std::printf("done\n");
	return 0;
}
