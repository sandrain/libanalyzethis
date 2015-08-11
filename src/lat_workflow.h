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

#ifndef LAT_WORKFLOW_H
#define LAT_WORKFLOW_H

#include <stdio.h>
#include "lat_constants.h"

/**
 * This is a very basic static placement of a workflow that is there only for
 * testing: it does not actually place any task, just return the workflow file.
 * In other words, it is assumed that the scheduling will be perform at
 * runtime only.
 */
int
lat_workflow_static_placement_noop (FILE *f_in,
                                    FILE **f_out);

#endif /* LAT_WORKFLOW_H */
