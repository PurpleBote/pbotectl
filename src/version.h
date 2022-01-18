/*
 * version.h: code with version related variables and commands
 * Copyright (C) 2019-2022 polistern
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

#ifndef PBOTECTL_VERSION_H__
#define PBOTECTL_VERSION_H__

#include <stdio.h>

#include "commands.h"

#define CODENAME "Plus Bote Control Tool"

#define STRINGIZE(x) #x
#define MAKE_VERSION(a, b, c) STRINGIZE (a) "." STRINGIZE (b) "." STRINGIZE (c)

#define PBOTECTL_VERSION_MAJOR 0
#define PBOTECTL_VERSION_MINOR 1
#define PBOTECTL_VERSION_MICRO 0

#define PBOTECTL_VERSION                                                      \
  MAKE_VERSION (PBOTECTL_VERSION_MAJOR, PBOTECTL_VERSION_MINOR,               \
                PBOTECTL_VERSION_MICRO)
#define VERSION PBOTECTL_VERSION

static inline int
cmd_version (int argc, const char **argv, const char *prefix)
{
  printf ("%s, version %s\n", CODENAME, VERSION);
  return 0;
}

#endif // PBOTECTL_VERSION_H__
