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

#ifndef __LAT_DEBUG_H
#define __LAT_DEBUG_H

#include <stdlib.h>
#include <stdio.h>

#define LAT_DEBUG 1

char *lat_varg_to_str (const char *fmt, ...);

#if LAT_DEBUG == 1
#define LAT_ERR_MSG(a) do {                                                             \
    char *__s = NULL;                                                                   \
    __s = lat_varg_to_str a;                                                            \
    if (__s == NULL)                                                                    \
        fprintf (stderr, "ERROR: Invalid string in LAT_FATAL\n");                       \
    else {                                                                              \
        fprintf (stderr, "[%s:%d:%s] ERROR: %s", __FILE__, __LINE__, __func__, __s);    \
        free (__s);                                                                     \
    }                                                                                   \
} while (0)
#else
#define LAT_ERR_MSG (a) do {} while(0)
#endif /* LAT_ERR_MSG */

#define LAT_FATAL(rc,a) do {    \
    LAT_ERR_MSG (a);            \
    return rc;                  \
} while(0)                      

#if LAT_DEBUG == 1
#define LAT_INFO(a) do {                                                                \
    char *__s = NULL;                                                                   \
    __s = lat_varg_to_str a;                                                            \
    if (__s == NULL)                                                                    \
        fprintf (stderr, "ERROR: Invalid string in LAT_FATAL\n");                       \
    else                                                                                \
        fprintf (stdout, "[%s:%d:%s] INFO: %s", __FILE__, __LINE__, __func__, __s);     \
        free (__s);                                                                     \
    }                                                                                   \
} while (0)
#else
#define LAT_INFO (a) do {} while(0)
#endif /* LAT_INFO */

#if LAT_DEBUG == 1
#define LAT_WARN(a) do {                                                                \
    char *__s = NULL;                                                                   \
    __s = lat_varg_to_str a;                                                            \
    if (__s == NULL)                                                                    \
        fprintf (stderr, "ERROR: Invalid string in LAT_FATAL\n");                       \
    else                                                                                \
        fprintf (stdout, "[%s:%d:%s] WARN: %s", __FILE__, __LINE__, __func__, __s);     \
        free (__s);                                                                     \
    }                                                                                   \
} while (0)
#else
#define LAT_WARNL (a) do {} while(0)
#endif /* LAT_WARN */

#endif /* __LAT_DEBUG_H */
