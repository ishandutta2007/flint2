/*
    Copyright (C) 2010 Sebastian Pancratz
    Copyright (C) 2013 Qingwen GUAN

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

/* try to get fdopen declared */
#if defined __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif

#include <sys/types.h>
#if (!defined (__WIN32) || defined(__CYGWIN__)) && !defined(_MSC_VER)
#include <unistd.h>
#endif


#include "flint.h"
#include "fmpz.h"

#if (!defined (__WIN32) || defined(__CYGWIN__)) && !defined(_MSC_VER)

int main(void)
{
    int i, j, n = 10000, result;

    FILE *in, *out;
    int fd[2];
    pid_t childpid;

    FLINT_TEST_INIT(state);

    printf("out_raw/inp_raw....");
    fflush(stdout);

    /* Randomise n integers, write to and read from a pipe */
    {
        fmpz *a;

        a = flint_calloc(n, sizeof(fmpz));
        for (i = 0; i < n; i++)
            fmpz_randtest(a + i, state, 200);

        if (pipe(fd))
        {
            printf("FAIL:\n");
            printf("Failed to set-up the pipe.\n");
            fflush(stdout);
            flint_abort();
        }

        if((childpid = fork()) == -1)
        {
            printf("FAIL:\n");
            printf("Failed to fork the process.\n");
            fflush(stdout);
            flint_abort();
        }

        if(childpid == 0)  /* Child process */
        {
            size_t r;

            close(fd[0]);
            out = fdopen(fd[1], "w");
            if (out == NULL)
            {
                printf("FAIL:\n");
                printf("Could not open output file at the pipe.\n");
                fflush(stdout);
                flint_abort();
            }

            for (j = 0; j < n; j++)
            {
                r = fmpz_out_raw(out, a + j);

                if (r <= 0)
                {
                    printf("FAIL:\n");
                    printf("Write error.\n");
                    fflush(stdout);
                    flint_abort();
                }
            }

            fclose(out);
            for (i = 0; i < n; ++i)
                fmpz_clear(a + i);
            flint_free(a);
            return 0;
        }
        else  /* Parent process */
        {
            size_t r;
            fmpz_t t;

            close(fd[1]);
            in = fdopen(fd[0], "r");
            if (in == NULL)
            {
                printf("FAIL:\n");
                printf("Could not open input file at the pipe.\n");
                fflush(stdout);
                flint_abort();
            }

            fmpz_init(t);

            i = 0;
            while ( (r = fmpz_inp_raw(t, in)) != 0 )
            {
                result = fmpz_equal(t, a + i) && _fmpz_is_canonical(t);
                if (!result)
                {
                    printf("FAIL:\n");
                    printf("a[i] = "), fmpz_print(a + i), printf("\n");
                    printf("t    = "), fmpz_print(t), printf("\n");
                    fflush(stdout);
                    flint_abort();
                }

                ++i;
            }

            fmpz_clear(t);
            fclose(in);
        }

        if (i != n)
        {
            printf("FAIL:\n");
            printf("Only %d out of %d objects were processed.\n", i, n);
            fflush(stdout);
            flint_abort();
        }

        for (i = 0; i < n; i++)
            fmpz_clear(a + i);
        flint_free(a);
    }

    /* Write bad data to a pipe and read it */
    /* Not necessary */

    FLINT_TEST_CLEANUP(state);

    printf("PASS\n");
    return 0;
}

#else

int main(void)
{
    printf("out_raw/ inp_raw....");
    fflush(stdout);
    printf("SKIPPED\n");
    return 0;
}

#endif
