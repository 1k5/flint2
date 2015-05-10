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

    Copyright (C) 2011 Fredrik Johansson

******************************************************************************/

#ifndef FMPZ_FACTOR_H
#define FMPZ_FACTOR_H

#include <gmp.h>
#include "flint.h"

#ifdef __cplusplus
 extern "C" {
#endif

typedef struct
{
    int sign;
    fmpz * p;
    ulong * exp;
    slong alloc;
    slong num;
} fmpz_factor_struct;

typedef fmpz_factor_struct fmpz_factor_t[1];


/* Utility functions *********************************************************/

FLINT_DLL void fmpz_factor_init(fmpz_factor_t factor);

FLINT_DLL void fmpz_factor_clear(fmpz_factor_t factor);

FLINT_DLL void fmpz_factor_print(const fmpz_factor_t factor);

FLINT_DLL void _fmpz_factor_fit_length(fmpz_factor_t factor, slong len);

FLINT_DLL void _fmpz_factor_append_ui(fmpz_factor_t factor, mp_limb_t p, ulong exp);

FLINT_DLL void _fmpz_factor_append(fmpz_factor_t factor, fmpz_t p, ulong exp);

FLINT_DLL void _fmpz_factor_set_length(fmpz_factor_t factor, slong newlen);

/* Factoring *****************************************************************/

FLINT_DLL void _fmpz_factor_extend_factor_ui(fmpz_factor_t factor, mp_limb_t n);

FLINT_DLL int fmpz_factor_trial_range(fmpz_factor_t factor, const fmpz_t n,
                                       ulong start, ulong num_primes);

FLINT_DLL void fmpz_factor(fmpz_factor_t factor, const fmpz_t n);

FLINT_DLL void fmpz_factor_si(fmpz_factor_t factor, slong n);

FLINT_DLL int fmpz_factor_pp1(fmpz_t factor, const fmpz_t n, 
                                       ulong B1, ulong B2_sqrt, ulong c);

FLINT_DLL int fmpz_factor_pollard_rho_ac(fmpz_t p_factor, const fmpz_t n, 
                                         const fmpz_t ai, const fmpz_t xi, 
                                         mp_limb_t max_iters);

FLINT_DLL int fmpz_factor_pollard_rho(fmpz_t p_factor, flint_rand_t state, 
                                      const fmpz_t n, mp_limb_t max_tries, 
                                      mp_limb_t max_iters);

/* Expansion *****************************************************************/

FLINT_DLL void fmpz_factor_expand_iterative(fmpz_t n, const fmpz_factor_t factor);

FLINT_DLL void fmpz_factor_expand_multiexp(fmpz_t n, const fmpz_factor_t factor);

FLINT_DLL void fmpz_factor_expand(fmpz_t n, const fmpz_factor_t factor);

/* Multiplicative functions **************************************************/

FLINT_DLL void fmpz_factor_euler_phi(fmpz_t res, const fmpz_factor_t fac);

FLINT_DLL int fmpz_factor_moebius_mu(const fmpz_factor_t fac);

FLINT_DLL void fmpz_factor_divisor_sigma(fmpz_t res, const fmpz_factor_t fac, ulong k);

#ifdef __cplusplus
}
#endif

#endif
