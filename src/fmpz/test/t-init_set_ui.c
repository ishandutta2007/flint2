/*
    Copyright (C) 2011 Sebastian Pancratz

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "flint.h"
#include "ulong_extras.h"
#include "fmpz.h"

int
main(void)
{
    int i, result;
    FLINT_TEST_INIT(state);

    flint_printf("init_set_ui....");
    fflush(stdout);

    for (i = 0; i < 10000 * flint_test_multiplier(); i++)
    {
        fmpz_t a, b;
        ulong x = n_randtest(state);

        fmpz_init(a);
        fmpz_set_ui(a, x);
        fmpz_init_set_ui(b, x);

        result = fmpz_equal(a, b) && _fmpz_is_canonical(b);
        if (!result)
        {
            flint_printf("FAIL:\n\n");
            flint_printf("a = "), fmpz_print(a), flint_printf("\n");
            flint_printf("b = "), fmpz_print(b), flint_printf("\n");
            flint_printf("x = %wu\n", x);
            fflush(stdout);
            flint_abort();
        }

        fmpz_clear(a);
        fmpz_clear(b);
    }

    FLINT_TEST_CLEANUP(state);

    flint_printf("PASS\n");
    return 0;
}
