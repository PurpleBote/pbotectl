/*
 * util.h: code with usefull functions and constants
 * Copyright (C) 2022, PurpleBote Team
 * Copyright (C) 2019-2022, polistern
 * 
 * This file is part of pbotectl.
 *
 * pbotectl is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * pbotectl is distributed in the hope that it will be useful,but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with pbotectl. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef PBOTECTL_UTIL_H
#define PBOTECTL_UTIL_H

#include <inttypes.h>

#define ARRAY_SIZE(x) (sizeof (x) / sizeof (x[0]))

#define EXIT_SUCCESS 0

#define PBOTECTL_USE_JSON_OUTPUT_ENVIRONMENT "PBOTECTL_USE_JSON_OUTPUT"
/* Connection type */
#define PBOTECTL_CONNECT_USE_SOCKET "PBOTECTL_USE_SOCKET"
/* For connection to daemon socket locally */
#define PBOTECTL_SOCKET_PATH_ENVIRONMENT "PBOTECTL_SOCKET_PATH"
/* or remote */
#define PBOTECTL_DAEMON_HOST_ENVIRONMENT "PBOTECTL_DAEMON_HOST"
#define PBOTECTL_DAEMON_PORT_ENVIRONMENT "PBOTECTL_DAEMON_PORT"

/*#define RUN_SETUP      (1<<0)*/
/*#define NEED_WORK_TREE (1<<3)*/

int skip_prefix (const char *str, const char *prefix, const char **out);

int file_exists (const char *filename);

static const char     *sizes[]   = { "EiB", "PiB", "TiB", "GiB", "MiB", "KiB", "B" };
static const uint64_t  exbibytes = 1024ULL * 1024ULL * 1024ULL *
                                   1024ULL * 1024ULL * 1024ULL;

char * bs2l (uint64_t size);

#endif /* PBOTECTL_UTIL_H */
