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

#include "lat_workflow.h"

int
lat_workflow_static_placement_noop (FILE *f_in,
                                    FILE **f_out)
{
    f_out = &f_in;

    return LAT_SUCCESS;
}
