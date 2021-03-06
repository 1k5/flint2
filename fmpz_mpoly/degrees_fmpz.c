/*
    Copyright (C) 2017 Daniel Schultz

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "fmpz_mpoly.h"


void fmpz_mpoly_degrees_fmpz(fmpz ** degs, const fmpz_mpoly_t poly,
                                                    const fmpz_mpoly_ctx_t ctx)
{
    mpoly_degrees_pfmpz(degs, poly->exps, poly->length, poly->bits, ctx->minfo);
}
