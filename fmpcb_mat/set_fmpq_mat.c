/*=============================================================================

    This file is part of ARB.

    ARB is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    ARB is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ARB; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2012 Fredrik Johansson

******************************************************************************/

#include "fmpcb_mat.h"

void
fmpcb_mat_set_fmpq_mat(fmpcb_mat_t dest, const fmpq_mat_t src, long prec)
{
    long i, j;

    if (fmpcb_mat_ncols(dest) != 0)
    {
        for (i = 0; i < fmpcb_mat_nrows(dest); i++)
            for (j = 0; j < fmpcb_mat_ncols(dest); j++)
                fmpcb_set_fmpq(fmpcb_mat_entry(dest, i, j),
                    fmpq_mat_entry(src, i, j), prec);
    }
}
