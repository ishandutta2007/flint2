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

    Copyright (C) 2014 Fredrik Johansson

******************************************************************************/

#include "acb_poly.h"

void _acb_poly_acb_invpow_cpx(acb_ptr res, const acb_t N, const acb_t c, long trunc, long prec)
{
    long i;
    acb_t logN;

    acb_init(logN);
    acb_log(logN, N, prec);
    acb_mul(res + 0, logN, c, prec);
    acb_neg(res + 0, res + 0);
    acb_exp(res + 0, res + 0, prec);

    for (i = 1; i < trunc; i++)
    {
        acb_mul(res + i, res + i - 1, logN, prec);
        acb_div_si(res + i, res + i, -i, prec);
    }

    acb_clear(logN);
}

void
_acb_poly_powsum_series_naive(acb_ptr z,
    const acb_t s, const acb_t a, const acb_t q, long n, long len, long prec)
{
    long k, i;
    int q_one;
    acb_t ak, logak, t, qpow;

    acb_init(ak);
    acb_init(logak);
    acb_init(t);
    acb_init(qpow);

    _acb_vec_zero(z, len);
    acb_one(qpow);

    q_one = acb_is_one(q);

    for (k = 0; k < n; k++)
    {
        acb_add_ui(ak, a, k, prec);

        if (len == 1)
        {
            acb_neg(t, s);
            acb_pow(t, ak, t, prec);
        }
        else
        {
            acb_log(logak, ak, prec);
            acb_mul(t, logak, s, prec);
            acb_neg(t, t);
            acb_exp(t, t, prec);
        }

        if (!q_one)
        {
            acb_mul(t, t, qpow, prec);
            if (k < n - 1)
                acb_mul(qpow, qpow, q, prec);
        }

        acb_add(z, z, t, prec);

        for (i = 1; i < len; i++)
        {
            acb_mul(t, t, logak, prec);
            acb_div_si(t, t, -i, prec);
            acb_add(z + i, z + i, t, prec);
        }
    }

    acb_clear(ak);
    acb_clear(logak);
    acb_clear(t);
    acb_clear(qpow);
}

