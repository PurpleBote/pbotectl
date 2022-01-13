/*
 * pbotectl.c: CLI utility for Plus Bote daemon
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
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "util.h"
#include "version.h"

struct cmd_struct
{
  const char *cmd;
  int (*fn) (int, const char **, const char *);
};

static struct cmd_struct commands[] = {
  { "help", cmd_help },
  { "show", cmd_show },
  { "storage", cmd_storage },
  { "version", cmd_version },
};

static struct cmd_struct *
get_command (const char *s)
{
  unsigned long i;
  for (i = 0; i < ARRAY_SIZE (commands); i++)
    {
      struct cmd_struct *p = commands + i;
      if (!strcmp (s, p->cmd))
        return p;
    }
  return NULL;
}

int
is_command (const char *s)
{
  return !!get_command (s);
}

static int
run_command (struct cmd_struct *p, int argc, const char **argv)
{
  int status;
  const char *prefix;
  prefix = NULL;

  status = p->fn (argc, argv, prefix);

  if (status)
    return status;

  return EXIT_SUCCESS;
}

static void
handle_command (int argc, const char **argv)
{
  const char *cmd;
  struct cmd_struct *command;

  cmd = argv[0];

  command = get_command (cmd);
  if (command)
    exit (run_command (command, argc, argv));
  else
    {
      printf ("Unknown command\n\n");
      command = get_command ("hel");
      exit (run_command (command, argc, argv));
    }
}

int
main (int argc, char *argv[])
{
  const char *cmd;
  // int done_help = 0;

  // For skipping bin name
  argc--;
  argv++;

  printf ("argc:    %d\n", argc);
  printf ("argv[0]: %s\n", argv[0]);

  cmd = argv[0];

  if (!cmd)
    argv[0] = cmd = "help";

  printf ("cmd: %s\n", cmd);

  handle_command (argc, argv);

  return EXIT_SUCCESS;
}
