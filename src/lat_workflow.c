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

#include <string.h>
#include <stdlib.h>

#include "lat_workflow.h"
#include "lat_debug.h"

int
lat_workflow_static_placement_noop (char    *f_in,
                                    int     *n_out,
                                    char    ***f_out)
{
    char *f;
    char **a;

    if (f_in == NULL || f_out == NULL) {
        LAT_ERR_MSG (("Invalid parameter(s)"));
        return LAT_BAD_PARAM;
    }

    a           = (char**)malloc (sizeof (char**));
    *n_out      = 1;
    f           = strdup (f_in);
    a[0]        = f;
    *f_out      = a;

    return LAT_SUCCESS;
}
