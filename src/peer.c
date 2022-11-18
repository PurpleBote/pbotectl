/*
 * peer.c: code to handle peer related commands
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
#include "gettext.h"
#include "peer.h"

static struct subcmd_struct peer_subcommands[] = {
  { "help", subcmd_peer_help },
  { "show", subcmd_peer_show },
  { "count", subcmd_peer_count },
  { "stats", subcmd_peer_stats },
};

MAKE_FIND_SUBCOMMAND(cmd_peer, peer_subcommands)

int
subcmd_peer_help (int argc, const char **argv, const char *prefix)
{
  int exit_status = 0;

  /* ToDo: */
  printf (_("peer help\n"));

  return exit_status;
}

int
subcmd_peer_show (int argc, const char **argv, const char *prefix)
{
  /*char buffer[DEFAULT_BUFFER_SIZE];*/
  int exit_status = 0;

  char cmd_str[] = PEER_COMMAND_PREFIX;
  strcat (cmd_str, PEER_COMMAND_PARAM_SHOW); /* ToDo */

  /* ToDo: */
  printf (_("peer show\n"));

  return exit_status;
}

int
subcmd_peer_count (int argc, const char **argv, const char *prefix)
{
  char buffer[DEFAULT_BUFFER_SIZE];
  int exit_status = 0;

  char cmd_str[] = PEER_COMMAND_PREFIX;
  strcat (cmd_str, PEER_COMMAND_PARAM_COUNT);

  make_request (cmd_str, buffer);

  if (!*buffer)
    {
      printf (_("Empty response from server\n"));
      exit_status = 1;
    }

  cJSON *o_json = cJSON_Parse(buffer);

  char * is_json = getenv (PBOTECTL_USE_JSON_OUTPUT_ENVIRONMENT);
  if (is_json)
    {
      printf ("%s\n", cJSON_Print(o_json));
      return exit_status;
    }

  cJSON *result_json = cJSON_GetObjectItemCaseSensitive(o_json, "result");
  cJSON *peers_json = cJSON_GetObjectItemCaseSensitive(result_json, "peers");
  cJSON *count_json = cJSON_GetObjectItemCaseSensitive(peers_json, "count");
  cJSON *total_json = cJSON_GetObjectItemCaseSensitive(count_json, "total");
  cJSON *good_json = cJSON_GetObjectItemCaseSensitive(count_json, "good");

  if (!cJSON_IsNumber(total_json) || !cJSON_IsNumber(good_json))
    {
      exit_status = 1;
      return exit_status;
    }

  printf (_("Total:\t%d\n"), total_json->valueint);
  printf (_("Good:\t%d\n"), good_json->valueint);

  return exit_status;
}

int
subcmd_peer_stats (int argc, const char **argv, const char *prefix)
{
  char buffer[DEFAULT_BUFFER_SIZE];
  int exit_status = 0;

  char cmd_str[] = PEER_COMMAND_PREFIX;
  strcat (cmd_str, PEER_COMMAND_PARAM_STATS);

  make_request (cmd_str, buffer);

  if (!*buffer)
    {
      printf (_("Empty response from server\n"));
      exit_status = 1;
    }

  return exit_status;
}
