/*
 * storage.c: code to handle storage related commands
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

#include "commands.h"
#include "jsonrpc.h"
#include "storage.h"

static struct subcmd_struct storage_subcmds[] = {
  { "help", subcmd_storage_help },
  { "show", subcmd_storage_show },
  { "used", subcmd_storage_used },
  { "clean", subcmd_storage_clean },
};

MAKE_FIND_SUBCOMMAND(cmd_storage, storage_subcmds)

int
subcmd_storage_help (int argc, const char **argv, const char *prefix)
{
  int exit_status = 0;

  printf (_("Avaliable commands:\n"));
  printf (_("  help      Show this message\n"));
  printf (_("  show      Info about storage\n"));
  printf (_("  used      Show storage usage info\n"));
  printf (_("  clean     Trigger storage cleanup\n"));
  printf ("\n");

  return exit_status;
}

int
subcmd_storage_show (int argc, const char **argv, const char *prefix)
{
  char buffer[DEFAULT_BUFFER_SIZE];
  int exit_status = 0;
  char *req, *is_json;
  cJSON *o_json, *params, *param_subcmd, *result_json, *storage_json, *used_json;

  params = cJSON_CreateObject();
  param_subcmd = cJSON_CreateString(STORAGE_COMMAND_PARAM_SHOW);
  cJSON_AddItemToObject(params, "subcommand", param_subcmd);

  (void) create_request_str(STORAGE_COMMAND_PREFIX, params, &req);
#if DEBUG_MODE
  printf (_("Formated request: %s\n"), req);
  fflush (stdout);
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
      cJSON_Delete (o_json);
      return exit_status;
    }

  result_json = cJSON_GetObjectItemCaseSensitive (o_json, "result");
  storage_json = cJSON_GetObjectItemCaseSensitive (result_json, "storage");
  used_json = cJSON_GetObjectItemCaseSensitive (storage_json, "used");

  if (!cJSON_IsNumber (used_json))
    {
      exit_status = 1;
      cJSON_Delete (o_json);
      return exit_status;
    }

  printf (_("Storage:\n"));
  printf (_("\tUsed:\t%f\n"), used_json->valuedouble );

  cJSON_Delete (o_json);
  return exit_status;
}

int
subcmd_storage_used (int argc, const char **argv, const char *prefix)
{
  char buffer[DEFAULT_BUFFER_SIZE];
  int exit_status = 0;
  char *req, *is_json;
  cJSON *o_json, *params, *param_subcmd, *result_json, *storage_json, *used_json;

  params = cJSON_CreateObject();
  param_subcmd = cJSON_CreateString(STORAGE_COMMAND_PARAM_USED);
  cJSON_AddItemToObject(params, "subcommand", param_subcmd);

  (void) create_request_str(STORAGE_COMMAND_PREFIX, params, &req);
#if DEBUG_MODE
  printf (_("Formated request: %s\n"), req);
  fflush (stdout);
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
      cJSON_Delete (o_json);
      return exit_status;
    }

  result_json = cJSON_GetObjectItemCaseSensitive (o_json, "result");
  storage_json = cJSON_GetObjectItemCaseSensitive (result_json, "storage");
  used_json = cJSON_GetObjectItemCaseSensitive (storage_json, "used");

  if (!cJSON_IsNumber (used_json))
    {
      exit_status = 1;
      cJSON_Delete (o_json);
      return exit_status;
    }

  printf (_("Storage:\n"));
  printf (_("\tUsed:\t%f\n"), used_json->valuedouble );

  cJSON_Delete (o_json);
  return exit_status;
}

int
subcmd_storage_clean (int argc, const char **argv, const char *prefix)
{
  int exit_status = 0;

  /* ToDo: show freed space*/
  printf (_("Storage cleanup started\n"));

  return exit_status;
}
