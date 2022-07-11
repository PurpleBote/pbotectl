/*
 * storage.c: code to handle storage related commands
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
#include "storage.h"

static struct subcmd_struct daemon_subcmds[] = {
  { "help", subcmd_storage_help },
  { "show", subcmd_storage_show },
  { "used", subcmd_storage_used },
  { "clean", subcmd_storage_clean },
};

int
cmd_storage (int argc, const char **argv, const char *prefix)
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
    exit_status = handle_subcommand (argc, argv, daemon_subcmds,
                                     ARRAY_SIZE (daemon_subcmds));

  return exit_status;
}

int
subcmd_storage_help (int argc, const char **argv, const char *prefix)
{
  int exit_status = 0;

  // ToDo:
  printf ("storage help\n");

  return exit_status;
}

int
subcmd_storage_show (int argc, const char **argv, const char *prefix)
{
  char buffer[DEFAULT_BUFFER_SIZE];
  int exit_status = 0;

  char cmd_str[] = STORAGE_COMMAND_PREFIX;
  strcat (cmd_str, STORAGE_COMMAND_PARAM_SHOW); // ToDo

  make_request (cmd_str, buffer);

  if (!buffer)
    {
      printf ("Empty response from server\n");
      exit_status = 1;
    }

  cJSON *o_json = cJSON_Parse (buffer);

  char * is_json = getenv (PBOTECTL_USE_JSON_OUTPUT_ENVIRONMENT);
  if (is_json)
    {
      printf ("%s\n", cJSON_Print (o_json));
      return exit_status;
    }

  cJSON *result_json = cJSON_GetObjectItemCaseSensitive (o_json, "result");
  cJSON *storage_json = cJSON_GetObjectItemCaseSensitive (result_json, "storage");
  cJSON *used_json = cJSON_GetObjectItemCaseSensitive (storage_json, "used");

  if (!cJSON_IsNumber (used_json))
    {
      exit_status = 1;
      return exit_status;
    }

  printf ("Used:\t%f\n", used_json->valuedouble );

  return exit_status;
}

int
subcmd_storage_used (int argc, const char **argv, const char *prefix)
{
  char buffer[DEFAULT_BUFFER_SIZE];
  int exit_status = 0;

  char cmd_str[] = STORAGE_COMMAND_PREFIX;
  strcat (cmd_str, STORAGE_COMMAND_PARAM_USED); // ToDo

  make_request (cmd_str, buffer);

  if (!buffer)
    {
      printf ("Empty response from server\n");
      exit_status = 1;
    }

  cJSON *o_json = cJSON_Parse (buffer);

  char * is_json = getenv (PBOTECTL_USE_JSON_OUTPUT_ENVIRONMENT);
  if (is_json)
    {
      printf ("%s\n", cJSON_Print (o_json));
      return exit_status;
    }

  cJSON *result_json = cJSON_GetObjectItemCaseSensitive (o_json, "result");
  cJSON *storage_json = cJSON_GetObjectItemCaseSensitive (result_json, "storage");
  cJSON *used_json = cJSON_GetObjectItemCaseSensitive (storage_json, "used");

  if (!cJSON_IsNumber (used_json))
    {
      exit_status = 1;
      return exit_status;
    }

  printf ("Used:\t%f\n", used_json->valuedouble );

  return exit_status;
}

int
subcmd_storage_clean (int argc, const char **argv, const char *prefix)
{
  int exit_status = 0;

  // ToDo:
  printf ("storage clean\n");

  return exit_status;
}
