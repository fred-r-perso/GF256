#include <stdio.h>
#include "gf256.h"

uint8_t do_reduction(uint32_t big_poly);
uint32_t mult_poly_no_reduc(uint32_t polyA, uint32_t polyB);

/* local macros and defines */
/* ------------------------ */
#define TRACE_ON 0
#define LOG(fmt, ...) do { if (TRACE_ON) printf(fmt, __VA_ARGS__); } while(0)

/* exported functions */
/* ------------------ */

uint8_t get_degree(uint32_t polynom)
{
    uint8_t degree = 0;

    /* initialisation : get rid of degree 0 coefficient */
    polynom = polynom >> 1;

    /* If polynom is not 0 then there is at least one coefficient being 1 */
    while (polynom != 0)
    {
        degree += 1;
        polynom = polynom >> 1;
    }

    return(degree);
}


uint8_t add_poly(uint8_t polyA, uint8_t polyB)
{
    /* The coefficients are in GF(2) so the addition is a XOR for each degree (no carry) */
    return (polyA ^ polyB);
}


uint8_t mult_poly(uint8_t polyA, uint8_t polyB)
{
    uint8_t loop = 0;
    uint32_t multi = 0;
    uint32_t res = 0;

    /* Take each coefficient of polyA */
    for (loop=0; loop <= get_degree(polyA); loop++)
    {
        /* polyB is shifted by the position of the coefficient of polyA we consider */
        multi = polyB << loop;

        /* take the coefficient of polyA (from lowest to highest) and multiply the shifted polyB by it */
        multi = multi * (polyA>>loop & 0x01); /* we get a polynom : polyB * current coeff of A */

        /* we do the addition of the polynoms : what we had before + the new polynom */
        res = res ^ multi; /* the degree can go beyond 7 (out of GF(256)) hence doing XOR directly */
    }

    /* Do a reduction if temp is not in GF(256) */
    LOG("\n [mult_poly] degree res : %u\n", get_degree(res));
    if (get_degree(res)>DEGREE_GF256)
    {
        res = do_reduction(res);

    }
    
    return(res);
}


uint8_t brute_invert_poly(uint8_t poly)
{
    /* Loop on all elements of GF(256) except 0 until poly * element = 1 mod AES_IRREDUCE_POLY */
    uint32_t loop = 0;
    uint8_t res = 0;

    while ( (loop < NB_ELEM_GF256 - 1) && (res != MULT_NEUTRAL_ELT) )
    {
        loop ++; /* skip 0 which cannot be inverted */
        res = mult_poly(loop, poly);
        LOG("\n [brute_invert_poly] %x = %x * %x\n", res, loop, poly);
    }

    return(loop);
}


/* private function(s) */
/* ------------------- */

uint32_t mult_poly_no_reduc(uint32_t polyA, uint32_t polyB)
{
    uint8_t loop = 0;
    uint32_t multi = 0;
    uint32_t res = 0;

    /* Take each coefficient of polyA */
    for (loop=0; loop <= get_degree(polyA); loop++)
    {
        /* polyB is shifted by the position of the coefficient of polyA we consider */
        multi = polyB << loop;

        /* take the coefficient of polyA (from lowest to highest) and multiply the shifted polyB by it */
        multi = multi * (polyA>>loop & 0x01); /* we get a polynom : polyB * current coeff of A */

        /* we do the addition of the polynoms : what we had before + the new polynom */
        res = res ^ multi; /* the degree can go beyond 7 (out of GF(256)) hence doing XOR directly */
    }

    LOG("\n [mult_poly_no_reduc] degree res : %u\n", get_degree(res));

    return(res);
}

uint8_t do_reduction(uint32_t big_poly)
{
    uint8_t big_degree = get_degree(big_poly);
    uint8_t delta_degree = 0; /* power of X to multiply the AES_IRREDUCE_POLY */
    uint32_t poly_quotient = 0; /* the polynom to multiply AES_IRREDUCE_POLY */
    uint32_t substract = 0;  /* the polynom AES_IRREDUCE_POLY * temp */
    uint32_t res = big_poly;

    while(big_degree > DEGREE_GF256)
    {
        delta_degree = big_degree - AES_IRREDUCE_DEGREE;
        poly_quotient = (1<<delta_degree); /* the polynom in the quotient is X power delta */
        substract = mult_poly_no_reduc(AES_IRREDUCE_POLY, poly_quotient);
        LOG("\n[do_reduction] delta_degree = %u - poly_quotient is: %x - substract is: %x\n", delta_degree, poly_quotient, substract);
        res = res ^ substract; /* the rest : + is equivalent to - in GF(2) and is XOR */
        big_degree = get_degree(res);
        LOG("\n[do_reduction] res_degree = %u\n", big_degree);
    }

    return(res);
}