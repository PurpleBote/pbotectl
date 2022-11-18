/*
 * show.c: code to handle show command
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
#include <string.h>

#include "cJSON.h"

#include "commands.h"
#include "daemon.h"
#include "identity.h"
#include "node.h"
#include "peer.h"
#include "show.h"
#include "storage.h"

static struct subcmd_struct show_subcmds[] = {
  { "help", subcmd_daemon_help },
  { "all", subcmd_show_all },
  { "daemon", subcmd_daemon_show },
  { "identity", subcmd_identity_show },
  { "node", subcmd_node_show },
  { "peer", subcmd_peer_show },
  { "storage", subcmd_storage_show },
};

MAKE_FIND_SUBCOMMAND(cmd_show, show_subcmds)

int
subcmd_show_help (int argc, const char **argv, const char *prefix)
{
  int exit_status = 0;

  /* ToDo: */
  printf (_("show help\n"));

  return exit_status;
}

int
subcmd_show_all (int argc, const char **argv, const char *prefix)
{
  int exit_status = 0;

  char * is_json = getenv (PBOTECTL_USE_JSON_OUTPUT_ENVIRONMENT);
  if (is_json)
    {
      char buffer[DEFAULT_BUFFER_SIZE];
      char cmd_str[] = SHOW_COMMAND_PREFIX_ALL;
      strcat (cmd_str, SHOW_COMMAND_POSTFIX);

      make_request (cmd_str, buffer);

      if (!*buffer)
        {
          printf (_("Empty response from server\n"));
          exit_status = 1;
        }

      cJSON *o_json = cJSON_Parse (buffer);

      printf ("%s\n", cJSON_Print (o_json));

      return exit_status;
    }

  /* For skipping help and all */
  int i;
  for (i = 2; i < ARRAY_SIZE (show_subcmds); i++)
    {
      struct subcmd_struct *p = show_subcmds + i;
      printf ("%s\n", p->subcmd);
      exit_status = run_subcommand (p, argc, argv);
      printf ("\n");

      if (exit_status != 0)
        return exit_status;
    }

  return exit_status;
}
