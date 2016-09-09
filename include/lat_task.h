/* vim: set softtabstop=4:shiftwidth=4:expandtab */

/*
 * Copyright (c) 2015-2016  UT-Battelle, LLC
 *                          All rights reserved.
 *
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 * $HEADER$
 *
 */

#ifndef LAT_TASK_H
#define LAT_TASK_H

#include <lat_file.h>

#define MAX_INPUT_FILES (1024)

typedef struct lat_task_s {
    char        *name;
    ssize_t     num_input_files;
    lat_file_t  input_files[1024];
} lat_task_t;

#endif /* LAT_TASK_H */
