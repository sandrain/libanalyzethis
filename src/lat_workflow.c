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
#include "lat_workflow.h"

int
lat_workflow_static_placement_noop (char *f_in,
                                    char **f_out)
{
    if (f_in == NULL || f_out == NULL) {
        fprintf (stderr,
                 "[%s:%d] ERROR: Invalid parameter(s)\n",
                 __func__, __LINE__);
        return LAT_BAD_PARAM;
    }

    *f_out = strdup (f_in);

    return LAT_SUCCESS;
}
