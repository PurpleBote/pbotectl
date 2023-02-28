/*
 * util.c: code with usefull functions and constants
 * Copyright (C) 2022-2023, PurpleBote Team
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

#ifndef WIN32
#include <sys/stat.h>
#endif

#include "util.h"
#include "version.h"

int
skip_prefix (const char *str, const char *prefix, const char **out)
{
  do
    {
      if (!*prefix)
        {
          *out = str;
          return 1;
        }
    } while (*str++ == *prefix++);
  return 0;
}

int
file_exists (const char *filename)
{
  struct stat buffer;
  return stat (filename, &buffer) == 0 ? 1 : 0;
}

char *
bs2l (uint64_t size)
{
  const char *sizes[] = { "EiB", "PiB", "TiB", "GiB", "MiB", "KiB", "B" };
  char * result = (char *) malloc(sizeof(char) * 20);
  uint64_t multiplier = exbibytes;
  int i;

  for (i = 0; i < ARRAY_SIZE(sizes); i++, multiplier /= 1024)
    {   
      if (size < multiplier)
        continue;
      if (size % multiplier == 0)
        sprintf(result, "%" PRIu64 " %s", size / multiplier, sizes[i]);
      else
        sprintf(result, "%.1f %s", (float) size / multiplier, sizes[i]);
      return result;
    }

  strcpy(result, "0");
  return result;
}

int
cmd_version (int argc, const char **argv, const char *prefix)
{
  printf (_("%s, version %s\n"), CODENAME, VERSION);
  return 0;
}
