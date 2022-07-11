/*
 * commands.h: interfaces of available commands
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

#ifndef PBOTECTL_COMMANDS_H
#define PBOTECTL_COMMANDS_H

#include <stdlib.h>
#include <string.h>

#include "util.h"

#define DEFAULT_BUFFER_SIZE 8192

void make_request (const char *request, char *buffer);

int cmd_help (int argc, const char **argv, const char *prefix);
// cmd_version defined in version.h

int cmd_show (int argc, const char **argv, const char *prefix);
//int cmd_status (int argc, const char **argv, const char *prefix);

/// mail command
//int cmd_mail (int argc, const char **argv, const char *prefix);
//int cmd_task (int argc, const char **argv, const char *prefix);
//int cmd_alias (int argc, const char **argv, const char *prefix);

/// bote commands
int cmd_daemon (int argc, const char **argv, const char *prefix);
int cmd_identity (int argc, const char **argv, const char *prefix);
int cmd_node (int argc, const char **argv, const char *prefix);
int cmd_peer (int argc, const char **argv, const char *prefix);
int cmd_storage (int argc, const char **argv, const char *prefix);

/// Subcommands

struct subcmd_struct
{
  const char *subcmd;
  int (*fn) (int, const char **, const char *);
};

static inline struct subcmd_struct *
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

static inline int
is_subcommand (const char *s, struct subcmd_struct subcmds[], size_t len)
{
  return !!get_subcommand (s, subcmds, len);
}

static inline int
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

static inline int
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
      printf ("Unknown command or parameter: %s\n\n", subcmd);
      command = get_subcommand ("help", subcmds, len);
      return (run_subcommand (command, argc, argv));
    }
}

//struct subcmd_struct * get_subcommand (const char *s);
//int is_subcommand (const char *s);
//int run_subcommand (struct subcmd_struct *p, int argc, const char **argv);
//int handle_subcommand (int argc, const char **argv);

#endif // PBOTECTL_COMMANDS_H
