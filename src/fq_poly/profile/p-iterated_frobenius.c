/*
    Copyright (C) 2013 Mike Hansen

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include "flint.h"
#include "ulong_extras.h"
#include "fmpz.h"
#include "fq.h"
#include "fq_mat.h"
#include "fq_poly.h"

#ifdef T
#undef T
#endif

#define T fq
#define CAP_T FQ
#include "fq_poly_templates/profile/p-iterated_frobenius.c"
#undef CAP_T
#undef T
