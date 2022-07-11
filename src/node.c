/*
 * node.c: code to handle node related commands
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

#include <cjson/cJSON.h>
#include <stdio.h>

#include "commands.h"
#include "node.h"

static struct subcmd_struct node_subcommands[] = {
  { "help", subcmd_node_help },
  { "show", subcmd_node_show },
  { "count", subcmd_node_count },
  { "stats", subcmd_node_stats },
};

int
cmd_node (int argc, const char **argv, const char *prefix)
{
  const char *subcmd;
  int exit_status = 0;

  // For skipping command name
  argc--;
  argv++;

  // Try to find subcommand
  subcmd = argv[0];

  if (!subcmd)
    exit_status = 1;
  else
    exit_status = handle_subcommand (argc, argv, node_subcommands,
                                     ARRAY_SIZE (node_subcommands));

  return exit_status;
}

int
subcmd_node_help (int argc, const char **argv, const char *prefix)
{
  int exit_status = 0;

  // ToDo:
  printf ("node help\n");

  return exit_status;
}

int
subcmd_node_show (int argc, const char **argv, const char *prefix)
{
  int exit_status = 0;

  // ToDo:
  printf ("node show\n");

  return exit_status;
}

int
subcmd_node_count (int argc, const char **argv, const char *prefix)
{
  char buffer[DEFAULT_BUFFER_SIZE];
  int exit_status = 0;

  char cmd_str[] = NODE_COMMAND_PREFIX;
  strcat (cmd_str, NODE_COMMAND_PARAM_COUNT);

  make_request (cmd_str, buffer);

  if (!buffer)
    {
      printf ("Empty response from server\n");
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
  cJSON *peers_json = cJSON_GetObjectItemCaseSensitive(result_json, "nodes");
  cJSON *count_json = cJSON_GetObjectItemCaseSensitive(peers_json, "count");
  cJSON *total_json = cJSON_GetObjectItemCaseSensitive(count_json, "total");
  cJSON *unlocked_json = cJSON_GetObjectItemCaseSensitive(count_json, "unlocked");

  if (!cJSON_IsNumber(total_json) || !cJSON_IsNumber(unlocked_json))
    {
      exit_status = 1;
      return exit_status;
    }

  printf ("Total:\t\t%d\n", total_json->valueint);
  printf ("Unlocked:\t%d\n", unlocked_json->valueint);

  return exit_status;
}

int
subcmd_node_stats (int argc, const char **argv, const char *prefix)
{
  int exit_status = 0;

  // ToDo:
  printf ("node stats\n");

  return exit_status;
}
