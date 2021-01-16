/* 
* MIT License

* Copyright (c) 2021 Frédéric Ruellé

* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:

* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.

* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE. 
*/
#ifndef GF256_H
#define GF256_H

#include <stdint.h>

#define NB_ELEM_GF256 (256U) /* number of elements in GF(256) */
#define AES_IRREDUCE_POLY (0x011B) /* X⁸ + X⁴ + X³ + X + 1 */
#define AES_IRREDUCE_DEGREE (8U)
#define DEGREE_GF256 (7U) /* in GF(256), the maximum degree is 7 otherwise a reduction by AES_IRREDUCE_POLY is required */
#define MULT_NEUTRAL_ELT (1U) /* the neutral element for the multiplication */

/* Function returning the degree of a polynom (can be out of GF(256)) */
uint8_t get_degree(uint32_t polynom);

/* Add polynoms in GF(256) */
uint8_t add_poly(uint8_t polyA, uint8_t polyB);

/* Multiply polynoms in GF(256) so do a reduction if needed */
uint8_t mult_poly(uint8_t polyA, uint8_t polyB);

/* Brute force inversion of a polynomial */
uint8_t brute_invert_poly(uint8_t poly);

/* Divide polynoms in GF(256) : polyA / polyB */
uint8_t div_poly(uint8_t polyA, uint8_t polyB);

#endif /* GF256_H */