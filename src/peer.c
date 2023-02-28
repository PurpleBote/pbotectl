/*
 * peer.c: code to handle peer related commands
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

  printf (_("Avaliable commands:\n"));
  printf (_("  help      Show this message\n"));
  printf (_("  show      List peers\n"));
  printf (_("  count     Show total and good\n"));
  printf (_("  stats     Show detailed info\n"));
  printf ("\n");

  return exit_status;
}

int
subcmd_peer_show (int argc, const char **argv, const char *prefix)
{
  char *buffer = (char *) malloc (DEFAULT_BUFFER_SIZE);
  int exit_status = 0;
  char *req, *is_json;
  cJSON *params, *param_subcmd, *o_json, *result_json, *peers_json, *count_json, *total_json, *good_json;

  params = cJSON_CreateObject();
  param_subcmd = cJSON_CreateString(PEER_COMMAND_PARAM_SHOW);
  cJSON_AddItemToObject(params, "subcommand", param_subcmd);
  
  (void) create_request_str(PEER_COMMAND_PREFIX, params, &req);
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
  peers_json = cJSON_GetObjectItemCaseSensitive (result_json, "peers");
  count_json = cJSON_GetObjectItemCaseSensitive (peers_json, "count");
  total_json = cJSON_GetObjectItemCaseSensitive (count_json, "total");
  good_json = cJSON_GetObjectItemCaseSensitive (count_json, "good");

  if (!cJSON_IsNumber (total_json) || !cJSON_IsNumber (good_json))
    {
      printf (_("Malformed response\n"));
      exit_status = 1;
      free (buffer);
      cJSON_Delete (o_json);
      return exit_status;
    }

  printf (_("Peers:\n"));
  printf (_("\tTotal:\t%d\n"), total_json->valueint);
  printf (_("\tGood:\t%d\n"), good_json->valueint);

  free (buffer);
  cJSON_Delete (o_json);

  return exit_status;
}

int
subcmd_peer_count (int argc, const char **argv, const char *prefix)
{
  char *buffer = (char *) malloc (DEFAULT_BUFFER_SIZE);
  int exit_status = 0;
  char *req, *is_json;
  cJSON *params, *param_subcmd, *o_json, *result_json, *peers_json, *count_json, *total_json, *good_json;

  params = cJSON_CreateObject();
  param_subcmd = cJSON_CreateString(PEER_COMMAND_PARAM_COUNT);
  cJSON_AddItemToObject(params, "subcommand", param_subcmd);

  (void) create_request_str(PEER_COMMAND_PREFIX, params, &req);
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
  printf ("%s\n", buffer);

  is_json = getenv (PBOTECTL_USE_JSON_OUTPUT_ENVIRONMENT);
  if (is_json)
    {
      printf ("%s\n", cJSON_Print (o_json));
      free (buffer);
      cJSON_Delete (o_json);
      return exit_status;
    }

  result_json = cJSON_GetObjectItemCaseSensitive (o_json, "result");
  peers_json = cJSON_GetObjectItemCaseSensitive (result_json, "peers");
  count_json = cJSON_GetObjectItemCaseSensitive (peers_json, "count");
  total_json = cJSON_GetObjectItemCaseSensitive (count_json, "total");
  good_json = cJSON_GetObjectItemCaseSensitive (count_json, "good");

  if (!cJSON_IsNumber (total_json) || !cJSON_IsNumber (good_json))
    {
      printf (_("Malformed response\n"));
      exit_status = 1;
      free (buffer);
      cJSON_Delete (o_json);
      return exit_status;
    }

  printf (_("Peers:\n"));
  printf (_("\tTotal:\t%d\n"), total_json->valueint);
  printf (_("\tGood:\t%d\n"), good_json->valueint);

  free (buffer);
  cJSON_Delete (o_json);

  return exit_status;
}

int
subcmd_peer_stats (int argc, const char **argv, const char *prefix)
{
  char *buffer = (char *) malloc (DEFAULT_BUFFER_SIZE);
  int exit_status = 0;
  char *req;
  cJSON *params, *param_subcmd;

  params = cJSON_CreateObject();
  param_subcmd = cJSON_CreateString(PEER_COMMAND_PARAM_STATS);
  cJSON_AddItemToObject(params, "subcommand", param_subcmd);
  
  (void) create_request_str(PEER_COMMAND_PREFIX, params, &req);
#if DEBUG_MODE
  printf (_("Formated request: %s\n"), req);
  fflush(stdout);
#endif

  make_request (req, buffer);

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

  free (buffer);

  return exit_status;
}
