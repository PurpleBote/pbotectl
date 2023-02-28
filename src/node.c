/*
 * node.c: code to handle node related commands
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

#include <stdio.h>
#include <string.h>

#include "commands.h"
#include "gettext.h"
#include "jsonrpc.h"
#include "node.h"

static struct subcmd_struct node_subcommands[] = {
  { "help", subcmd_node_help },
  { "show", subcmd_node_show },
  { "count", subcmd_node_count },
  { "stats", subcmd_node_stats },
};

MAKE_FIND_SUBCOMMAND(cmd_node, node_subcommands)

int
subcmd_node_help (int argc, const char **argv, const char *prefix)
{
  int exit_status = 0;

  /* ToDo: */
  printf (_("node help\n"));

  return exit_status;
}

int
subcmd_node_show (int argc, const char **argv, const char *prefix)
{
  char *buffer = (char *) malloc (DEFAULT_BUFFER_SIZE);
  int exit_status = 0;
  char *req, *is_json;
  cJSON *params, *param_subcmd, *o_json, *result_json, *nodes_json, *count_json, *total_json, *unlocked_json;

  params = cJSON_CreateObject();
  param_subcmd = cJSON_CreateString(NODE_COMMAND_PARAM_SHOW);
  cJSON_AddItemToObject(params, "subcommand", param_subcmd);
  
  (void) create_request_str(NODE_COMMAND_PREFIX, params, &req);
#if DEBUG_MODE
  printf (_("Formated request: %s\n"), req);
  fflush(stdout);
#endif

  make_request (req, buffer);
  free (req);

  if (!*buffer)
    {
      printf (_("Empty response from server\n"));
      exit_status = 1;
      free (buffer);
      return exit_status;
    }

  exit_status = check_json_error (buffer);
  if (exit_status == JSON_IS_ERROR) /* If we got error in response */
    {
      free (buffer);
      return exit_status;
    }
  else if (exit_status == JSON_MALFORMED)
    {
      printf (_("Malformed response\n"));
      return exit_status;
    }

  o_json = cJSON_Parse (buffer);

  is_json = getenv (PBOTECTL_USE_JSON_OUTPUT_ENVIRONMENT);
  if (is_json)
    {
      printf ("%s\n", cJSON_Print (o_json));
      free (buffer);
      cJSON_Delete (o_json);
      return exit_status;
    }

  result_json = cJSON_GetObjectItemCaseSensitive (o_json, "result");
  nodes_json = cJSON_GetObjectItemCaseSensitive (result_json, "nodes");
  count_json = cJSON_GetObjectItemCaseSensitive (nodes_json, "count");
  total_json = cJSON_GetObjectItemCaseSensitive (count_json, "total");
  unlocked_json = cJSON_GetObjectItemCaseSensitive (count_json, "unlocked");

  if (!cJSON_IsNumber (total_json) || !cJSON_IsNumber (unlocked_json))
    {
      printf (_("Malformed response\n"));
      exit_status = 1;
      free (buffer);
      cJSON_Delete (o_json);
      return exit_status;
    }

  printf (_("Nodes:\n"));
  printf (_("\tTotal:\t\t%d\n"), total_json->valueint);
  printf (_("\tUnlocked:\t%d\n"), unlocked_json->valueint);

  free (buffer);
  cJSON_Delete (o_json);

  return exit_status;
}

int
subcmd_node_count (int argc, const char **argv, const char *prefix)
{
  char buffer[DEFAULT_BUFFER_SIZE];
  int exit_status = 0;
  char *req, *is_json;
  cJSON *params, *param_subcmd, *o_json, *result_json, *peers_json, *count_json, *total_json, *unlocked_json;

  params = cJSON_CreateObject();
  param_subcmd = cJSON_CreateString(NODE_COMMAND_PARAM_COUNT);
  cJSON_AddItemToObject(params, "subcommand", param_subcmd);
  
  (void) create_request_str(NODE_COMMAND_PREFIX, params, &req);
#if DEBUG_MODE
  printf (_("Formated request: %s\n"), req);
  fflush(stdout);
#endif

  make_request (req, buffer);
  free (req);

  if (!*buffer)
    {
      printf (_("Empty response from server\n"));
      exit_status = 1;
      free (buffer);
      return exit_status;
    }

  exit_status = check_json_error (buffer);
  if (exit_status == JSON_IS_ERROR) /* If we got error in response */
    {
      free (buffer);
      return exit_status;
    }
  else if (exit_status == JSON_MALFORMED)
    {
      printf (_("Malformed response\n"));
      return exit_status;
    }

  o_json = cJSON_Parse(buffer);

  is_json = getenv (PBOTECTL_USE_JSON_OUTPUT_ENVIRONMENT);
  if (is_json)
    {
      printf ("%s\n", cJSON_Print(o_json));
      cJSON_Delete (o_json);
      return exit_status;
    }

  result_json = cJSON_GetObjectItemCaseSensitive(o_json, "result");
  peers_json = cJSON_GetObjectItemCaseSensitive(result_json, "nodes");
  count_json = cJSON_GetObjectItemCaseSensitive(peers_json, "count");
  total_json = cJSON_GetObjectItemCaseSensitive(count_json, "total");
  unlocked_json = cJSON_GetObjectItemCaseSensitive(count_json, "unlocked");

  if (!cJSON_IsNumber(total_json) || !cJSON_IsNumber(unlocked_json))
    {
      exit_status = 1;
      cJSON_Delete (o_json);
      return exit_status;
    }

  printf (_("Nodes:\n"));
  printf (_("\tTotal:\t\t%d\n"), total_json->valueint);
  printf (_("\tUnlocked:\t%d\n"), unlocked_json->valueint);

  cJSON_Delete (o_json);
  return exit_status;
}

int
subcmd_node_stats (int argc, const char **argv, const char *prefix)
{
  int exit_status = 0;

  /* ToDo: */
  printf (_("node stats\n"));

  return exit_status;
}
