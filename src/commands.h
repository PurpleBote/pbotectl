/*
 * commands.h: interfaces of available commands
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

#ifndef PBOTECTL_COMMANDS_H
#define PBOTECTL_COMMANDS_H

#include <stdlib.h>
#include <string.h>

#include "gettext.h"
#include "util.h"

#define DEFAULT_BUFFER_SIZE 8192

#define MAKE_FIND_SUBCOMMAND(CMD_NAME, SUBCMD_NAME) \
int \
CMD_NAME (int argc, const char **argv, const char *prefix) \
{ \
  const char *subcmd; \
  int exit_status = 0; \
  /* For skipping command name */ \
  argc--;\
  argv++;\
  /* Try to find subcommand */ \
  subcmd = argv[0]; \
  if (!subcmd) \
    exit_status = 1; \
  else \
    exit_status = handle_subcommand (argc, argv, SUBCMD_NAME, \
                                     ARRAY_SIZE (SUBCMD_NAME)); \
  return exit_status; \
}

void make_request (const char *request, char *buffer);

int cmd_help (int argc, const char **argv, const char *prefix);
/* cmd_version defined in version.h */

int cmd_show (int argc, const char **argv, const char *prefix);
/*int cmd_status (int argc, const char **argv, const char *prefix); */

/* mail commands */
/*
int cmd_mail (int argc, const char **argv, const char *prefix);
int cmd_task (int argc, const char **argv, const char *prefix);
int cmd_alias (int argc, const char **argv, const char *prefix);
*/

/* bote commands */
int cmd_daemon (int argc, const char **argv, const char *prefix);
int cmd_identity (int argc, const char **argv, const char *prefix);
int cmd_node (int argc, const char **argv, const char *prefix);
int cmd_peer (int argc, const char **argv, const char *prefix);
int cmd_storage (int argc, const char **argv, const char *prefix);

/* Subcommands */
struct subcmd_struct
{
  const char *subcmd;
  int (*fn) (int, const char **, const char *);
};

struct subcmd_struct *
get_subcommand (const char *s, struct subcmd_struct subcmds[], size_t len);
int is_subcommand (const char *s, struct subcmd_struct subcmds[], size_t len);

int run_subcommand (struct subcmd_struct *p, int argc, const char **argv);

int handle_subcommand (int argc, const char **argv, struct subcmd_struct subcmds[], size_t len);

/*
struct subcmd_struct * get_subcommand (const char *s);
int is_subcommand (const char *s);
int run_subcommand (struct subcmd_struct *p, int argc, const char **argv);
int handle_subcommand (int argc, const char **argv);
*/

#endif /* PBOTECTL_COMMANDS_H */
