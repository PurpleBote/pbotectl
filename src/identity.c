/*
 * identity.c: code to handle identity related commands
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
#include "identity.h"

static struct subcmd_struct identity_subcmds[] = {
  { "help", subcmd_identity_help },
  { "show", subcmd_identity_show },
  { "count", subcmd_identity_count },
};

MAKE_FIND_SUBCOMMAND(cmd_identity, identity_subcmds)

int
subcmd_identity_help (int argc, const char **argv, const char *prefix)
{
  /*char buffer[DEFAULT_BUFFER_SIZE];*/
  int exit_status = 0;

  /* ToDo: */
  printf (_("identity help\n"));

  return exit_status;
}

int
subcmd_identity_show (int argc, const char **argv, const char *prefix)
{
  /*char buffer[DEFAULT_BUFFER_SIZE];*/
  int exit_status = 0;

  /* ToDo: */
  printf (_("identity show\n"));

  return exit_status;
}

int
subcmd_identity_count(int argc, const char **argv, const char *prefix)
{
  char buffer[DEFAULT_BUFFER_SIZE];
  int exit_status = 0;

  char cmd_str[] = IDENTITY_COMMAND_PREFIX;
  strcat (cmd_str, IDENTITY_COMMAND_PARAM_COUNT); /* ToDo */

  make_request (cmd_str, buffer);

  if (!*buffer)
    {
      printf (_("Empty response from server\n"));
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
  cJSON *identity_json = cJSON_GetObjectItemCaseSensitive (result_json, "identity");
  cJSON *count_json = cJSON_GetObjectItemCaseSensitive (identity_json, "count");

  if (!cJSON_IsNumber (count_json))
    {
      exit_status = 1;
      return exit_status;
    }

  printf (_("Identities:\t%d\n"), count_json->valueint);

  return exit_status;
}
