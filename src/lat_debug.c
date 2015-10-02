/* vim: set softtabstop=4:shiftwidth=4:expandtab */

/*
 * Copyright (c) 2015       UT-Battelle, LLC
 *                          All rights reserved.
 *
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 * $HEADER$
 *
 */

#include <stdarg.h>
#include <stdio.h>

#include "lat_debug.h"

char *lat_varg_to_str (const char *fmt, ...) {
    va_list arglist;
    int     n       = -1;
    char    *str    = NULL;

    va_start (arglist, fmt);
    /* FIXME we should be able to call vasprintf directly but for some reason
       it does not work so i call directly the opal version (OPAL is supposed
       to deal with portability issues of these functions) */
    n = vasprintf (&str, fmt, arglist);
    va_end (arglist);

    if (n == -1) {
        fprintf (stderr, "Fatal error in varg_to_str\n");
        return NULL;
    } else {
        return str;
    }
}

