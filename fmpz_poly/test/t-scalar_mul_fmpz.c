/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

   Copyright (C) 2009 William Hart

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_poly.h"
#include "ulong_extras.h"

int
main(void)
{
    int i, result;
    printf("scalar_mul_fmpz....");
    fflush(stdout);

    fmpz_poly_randinit();

    // check aliasing of a and b
    for (i = 0; i < 10000; i++)
    {
        fmpz_poly_t a, b;
        fmpz_t n;
        fmpz_init(n);
        fmpz_randtest(n, 200);

        fmpz_poly_init(a);
        fmpz_poly_init(b);
        fmpz_poly_randtest(a, n_randint(100), n_randint(200));

        fmpz_poly_scalar_mul_fmpz(b, a, n);
        fmpz_poly_scalar_mul_fmpz(a, a, n);

        result = (fmpz_poly_equal(a, b));
        if (!result)
        {
            printf("FAIL:\n");
            fmpz_poly_print(a), printf("\n\n");
            fmpz_poly_print(b), printf("\n\n");
            abort();
        }

        fmpz_clear(n);
        fmpz_poly_clear(a);
        fmpz_poly_clear(b);
    }

    // compare with fmpz_poly_scalar_mul_si
    for (i = 0; i < 10000; i++)
    {
        fmpz_poly_t a, b;
        fmpz_t n1;
        long n;
        fmpz_init(n1);
        n = (long) n_randbits(FLINT_BITS - 1);
        if (n_randint(2))
            n = -n;
        fmpz_set_si(n1, n);

        fmpz_poly_init(a);
        fmpz_poly_init(b);
        fmpz_poly_randtest(a, n_randint(100), n_randint(200));

        fmpz_poly_scalar_mul_fmpz(b, a, n1);
        fmpz_poly_scalar_mul_si(a, a, n);

        result = (fmpz_poly_equal(a, b));
        if (!result)
        {
            printf("FAIL:\n");
            fmpz_poly_print(a), printf("\n\n");
            fmpz_poly_print(b), printf("\n\n");
            abort();
        }

        fmpz_clear(n1);
        fmpz_poly_clear(a);
        fmpz_poly_clear(b);
    }

    fmpz_poly_randclear();
    _fmpz_cleanup();
    printf("PASS\n");
    return 0;
}
