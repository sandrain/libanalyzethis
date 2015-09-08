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

#include "lat_constants.h"
#include "lat_debug.h"
#include "lat_inifile_parser.h"

int
main (int argc, char **argv)
{
    int             rc;
    char            *test_inifile = "test_inifile.conf";
    ssize_t         n_blocks;
    lat_iniconfig_t *config;

    rc = lat_parse_inifile (test_inifile, &config);
    if (rc != LAT_SUCCESS)
        LAT_FATAL (LAT_ERROR, ("lat_parse_ini_file() failed"));

    lat_display_iniconfig (config);
}
