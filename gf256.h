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