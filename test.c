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

#include <stdio.h>
#include "gf256.h"


/* test functions prototypes */
/* ------------------------- */
void test_degree();
void test_mult();
void test_brute_invert();
void test_div();

/* test routine */
/* ------------ */
int main()
{
    test_degree();

    test_mult();

    test_brute_invert();

    test_div();

    return(0);
}


/* test functions */
/* -------------- */
void test_degree()
{
    uint8_t polyA = 0x1C;    /* degree 4  */
    uint32_t polyB = 0x110E; /* degree 12 */
    uint8_t pass =0;
    uint8_t fail = 0;

    if (get_degree((uint32_t)polyA) != 4 )
    {
        fail ++;
        printf("\n[error] : %u instead of 4\n", get_degree((uint32_t)polyA));
    }
    else
    {
        pass ++;
    }

    if (get_degree(polyB) != 12 )
    {
        fail ++;
        printf("\n[error] : %u instead of 12\n", get_degree(polyB));
    }
    else
    {
        pass ++;
    }

    printf("\n test_degree : %u PASS - %u FAIL\n", pass, fail );
}


void test_mult()
{
    uint8_t pass =0;
    uint8_t fail = 0;

    uint8_t polyA = 0x1C;    /* X⁴ + X³ + X² */
    uint8_t polyB = 0x03;    /* X + 1 */
    uint8_t polyAB = 0x24;   /* X⁵ + X² */

    if (mult_poly(polyA, polyB) != polyAB)
    {
        fail++;
        printf("\n[error] : %x instead of %x\n", mult_poly(polyA, polyB), polyAB);
    }
    else
    {
        pass++;
    }

    polyB = 0x01; /* 1 */
    polyAB = polyA;

    if (mult_poly(polyA, polyB) != polyAB)
    {
        fail++;
        printf("\n[error] : %x instead of %x\n", mult_poly(polyA, polyB), polyAB);
    }
    else
    {
        pass++;
    }    

    polyB = 0x02; /* X */
    polyAB = 0x38;

    if (mult_poly(polyA, polyB) != polyAB)
    {
        fail++;
        printf("\n[error] : %x instead of %x\n", mult_poly(polyA, polyB), polyAB);
    }
    else
    {
        pass++;
    }    

    polyA = 0xC2; /* X⁷ + X⁶ + X */
    polyB = 0x2F; /* X⁵ + X³ + X² + X + 1 = invert(polyA) */
    polyAB = 0x01;

    if (mult_poly(polyA, polyB) != polyAB)
    {
        fail++;
        printf("\n[error] : %x instead of %x\n", mult_poly(polyA, polyB), polyAB);
    }
    else
    {
        pass++;
    }   

    polyA = 0b010010;
    polyB = 0b111111;
    polyAB = 0b10100011;

    if (mult_poly(polyA, polyB) != polyAB)
    {
        fail++;
        printf("\n[error] : %x instead of %x\n", mult_poly(polyA, polyB), polyAB);
    }
    else
    {
        pass++;
    }   

    polyA = 255;
    polyB = 10;
    polyAB = 0b01011100;

    if (mult_poly(polyA, polyB) != polyAB)
    {
        fail++;
        printf("\n[error] : %x instead of %x\n", mult_poly(polyA, polyB), polyAB);
    }
    else
    {
        pass++;
    }   

    polyA = 128;
    polyB = 64;
    polyAB = 0b01001101;

    if (mult_poly(polyA, polyB) != polyAB)
    {
        fail++;
        printf("\n[error] : %x instead of %x\n", mult_poly(polyA, polyB), polyAB);
    }
    else
    {
        pass++;
    }

    polyA = 64;
    polyB = 128;
    polyAB = 0b01001101;

    if (mult_poly(polyA, polyB) != polyAB)
    {
        fail++;
        printf("\n[error] : %x instead of %x\n", mult_poly(polyA, polyB), polyAB);
    }
    else
    {
        pass++;
    }

    polyA = 44;
    polyB = 201;
    polyAB = 0b01010011;

    if (mult_poly(polyA, polyB) != polyAB)
    {
        fail++;
        printf("\n[error] : %x instead of %x\n", mult_poly(polyA, polyB), polyAB);
    }
    else
    {
        pass++;
    }

    polyA = 255;
    polyB = 255;
    polyAB = 0b00010011;

    if (mult_poly(polyA, polyB) != polyAB)
    {
        fail++;
        printf("\n[error] : %x instead of %x\n", mult_poly(polyA, polyB), polyAB);
    }
    else
    {
        pass++;
    }    

    polyA = 200;
    polyB = 100;
    polyAB = 0b10110101;

    if (mult_poly(polyA, polyB) != polyAB)
    {
        fail++;
        printf("\n[error] : %x instead of %x\n", mult_poly(polyA, polyB), polyAB);
    }
    else
    {
        pass++;
    }    

    polyA = 91;
    polyB = 15;
    polyAB = 0b01110100;

    if (mult_poly(polyA, polyB) != polyAB)
    {
        fail++;
        printf("\n[error] : %x instead of %x\n", mult_poly(polyA, polyB), polyAB);
    }
    else
    {
        pass++;
    }    


    polyA = 15;
    polyB = 91;
    polyAB = 0b01110100;

    if (mult_poly(polyA, polyB) != polyAB)
    {
        fail++;
        printf("\n[error] : %x instead of %x\n", mult_poly(polyA, polyB), polyAB);
    }
    else
    {
        pass++;
    }    


    printf("\n test_mult : %u PASS - %u FAIL\n", pass, fail );    
}

void test_brute_invert()
{
    uint8_t pass =0;
    uint8_t fail = 0;

    uint8_t poly = 0xC2; /* X⁷ + X⁶ + X */
    uint8_t inv_poly = 0x2F;

    if (brute_invert_poly(poly) != inv_poly)
    {
        fail++;
        printf("\n[error] : %x instead of %x\n", brute_invert_poly(poly), inv_poly);
    }
    else
    {
        pass++;
    }   

    printf("\n test_brute_invert : %u PASS - %u FAIL\n", pass, fail );     
}

void test_div()
{
    uint8_t pass =0;
    uint8_t fail = 0;

    uint8_t polyA = 0x06;    /* X² + X */
    uint8_t polyB = 0x03;    /* X + 1 */
    uint8_t polyAdivB = 0x02; /* X */

    if (div_poly(polyA, polyB) != polyAdivB)
    {
        fail++;
        printf("\n[error] : %x instead of %x\n", div_poly(polyA, polyB), polyAdivB);
    }
    else
    {
        pass++;
    }

    polyB = polyA;
    polyAdivB = 1;

    if (div_poly(polyA, polyB) != polyAdivB)
    {
        fail++;
        printf("\n[error] : %x instead of %x\n", div_poly(polyA, polyB), polyAdivB);
    }
    else
    {
        pass++;
    }

    polyA = 0x1B;    
    polyB = 0x05;    
    polyAdivB = 0x07;

    if (div_poly(polyA, polyB) != polyAdivB)
    {
        fail++;
        printf("\n[error] : %x instead of %x\n", div_poly(polyA, polyB), polyAdivB);
    }
    else
    {
        pass++;
    }

    polyA = 255;    
    polyB = 128;    
    polyAdivB = 0b01111111;

    if (div_poly(polyA, polyB) != polyAdivB)
    {
        fail++;
        printf("\n[error] : %x instead of %x\n", div_poly(polyA, polyB), polyAdivB);
    }
    else
    {
        pass++;
    }

    polyA = 104;    
    polyB = 32;    
    polyAdivB = 0b11001000;

    if (div_poly(polyA, polyB) != polyAdivB)
    {
        fail++;
        printf("\n[error] : %x instead of %x\n", div_poly(polyA, polyB), polyAdivB);
    }
    else
    {
        pass++;
    }

    polyA = 200;    
    polyB = 100;    
    polyAdivB = 0b00000010;

    if (div_poly(polyA, polyB) != polyAdivB)
    {
        fail++;
        printf("\n[error] : %x instead of %x\n", div_poly(polyA, polyB), polyAdivB);
    }
    else
    {
        pass++;
    }

    polyA = 12;
    polyB = 100;    
    polyAdivB = 0b01000001;

    if (div_poly(polyA, polyB) != polyAdivB)
    {
        fail++;
        printf("\n[error] : %x instead of %x\n", div_poly(polyA, polyB), polyAdivB);
    }
    else
    {
        pass++;
    }


    printf("\n test_div : %u PASS - %u FAIL\n", pass, fail );
}
