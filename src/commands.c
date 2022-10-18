/*
 * commands.c: code of available commands
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

#include <stdio.h>

#include "commands.h"

struct subcmd_struct *
get_subcommand (const char *s, struct subcmd_struct subcmds[], size_t len)
{
  unsigned long i;
  for (i = 0; i < len; i++)
    {
      struct subcmd_struct *p = subcmds + i;
      if (!strcmp (s, p->subcmd))
        return p;
    }
  return NULL;
}

int
is_subcommand (const char *s, struct subcmd_struct subcmds[], size_t len)
{
  return !!get_subcommand (s, subcmds, len);
}

int
run_subcommand (struct subcmd_struct *p, int argc, const char **argv)
{
  int status;
  const char *prefix;
  prefix = NULL;

  status = p->fn (argc, argv, prefix);

  if (status)
    return status;

  return EXIT_SUCCESS;
}

int
handle_subcommand (int argc, const char **argv, struct subcmd_struct subcmds[], size_t len)
{
  const char *subcmd;
  struct subcmd_struct *command;

  subcmd = argv[0];

  command = get_subcommand (subcmd, subcmds, len);
  if (command)
    return (run_subcommand (command, argc, argv));
  else
    {
      printf (_("Unknown command or parameter: %s\n\n"), subcmd);
      command = get_subcommand ("help", subcmds, len);
      return (run_subcommand (command, argc, argv));
    }
}
