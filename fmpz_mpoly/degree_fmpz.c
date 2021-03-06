/*
    Copyright (C) 2017 Daniel Schultz

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "fmpz_mpoly.h"


void fmpz_mpoly_degree_fmpz(fmpz_t deg, const fmpz_mpoly_t poly, slong var,
                                                    const fmpz_mpoly_ctx_t ctx)
{
    slong i;
    fmpz * new_degs;
    TMP_INIT;

    TMP_START;
    new_degs = (fmpz *) TMP_ALLOC(ctx->minfo->nvars*sizeof(fmpz));
    for (i = 0; i < ctx->minfo->nvars; i++)
        fmpz_init(new_degs + i);

    mpoly_degrees_ffmpz(new_degs, poly->exps, poly->length, poly->bits, ctx->minfo);

    for (i = 0; i < ctx->minfo->nvars; i++)
    {
        if (i == var)
            fmpz_swap(new_degs + i, deg);
        fmpz_clear(new_degs + i);
    }

    TMP_END;
}
