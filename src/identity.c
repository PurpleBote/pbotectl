/*
 * identity.c: code to handle identity related commands
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

#include <stdio.h>

#include "commands.h"

#define IDENTITY_COMMAND_PREFIX "identity"
#define IDENTITY_COMMAND_PARAM_COUNT "count"

int
cmd_identity (int argc, const char **argv, const char *prefix)
{
  char buffer[DEFAULT_BUFFER_SIZE];
  int exit_status = 0;

  // ToDo: parse and concat request
  make_request ("identity.count", buffer);

  if (buffer)
    printf ("%s\n", buffer);
  else
    {
      printf ("Empty response from server\n");
      exit_status = 1;
    }

  return exit_status;
}
