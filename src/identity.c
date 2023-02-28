/*
 * identity.c: code to handle identity related commands
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
  int exit_status = EXIT_SUCCESS;

  /* ToDo: */
  printf (_("identity help\n"));

  return exit_status;
}

int
subcmd_identity_show (int argc, const char **argv, const char *prefix)
{
  char buffer[DEFAULT_BUFFER_SIZE];
  int exit_status = EXIT_SUCCESS;
  char *req, *is_json, *type_str;
  cJSON *o_json, *params, *param_subcmd, *result_json, *identities_json;
  const cJSON *identity_json = NULL;
  cJSON *i_name, *i_address, *i_hash, *i_type;

  params = cJSON_CreateObject(); /* Cleaned inside create_request_str() */
  param_subcmd = cJSON_CreateString(IDENTITY_COMMAND_PARAM_SHOW);
  cJSON_AddItemToObject(params, "subcommand", param_subcmd);

  (void) create_request_str(IDENTITY_COMMAND_PREFIX, params, &req);
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
  identities_json = cJSON_GetObjectItemCaseSensitive (result_json, "identity");

  printf (_("Identities:\n"));

  cJSON_ArrayForEach(identity_json, identities_json)
  {
    i_name = cJSON_GetObjectItemCaseSensitive(identity_json, "name");
    i_address = cJSON_GetObjectItemCaseSensitive(identity_json, "address");
    i_hash = cJSON_GetObjectItemCaseSensitive(identity_json, "hash");
    i_type = cJSON_GetObjectItemCaseSensitive(identity_json, "type");
    if (!cJSON_IsNumber (i_type) || !cJSON_IsString (i_name) ||
        !cJSON_IsString (i_address) || !cJSON_IsString (i_hash))
      {
        exit_status = EXIT_ERROR;
        cJSON_Delete (o_json);
        return exit_status;
      }
    printf (_("\tName:\t%s\n"), i_name->valuestring);
    printf (_("\tMail:\tb64.%s\n"), i_address->valuestring);
    printf (_("\tHash:\t%s\n"), i_hash->valuestring);
    type_str = identity_type_to_str(i_type->valueint);
    printf (_("\tType:\t%s\n\n"), type_str);
  }

  cJSON_Delete (o_json);
  return exit_status;
}

int
subcmd_identity_count(int argc, const char **argv, const char *prefix)
{
  char buffer[DEFAULT_BUFFER_SIZE];
  int exit_status = EXIT_SUCCESS;
  char *req, *json_output;
  cJSON *params, *param_subcmd, *o_json, *result_json, *identity_json, *count_json;

  params = cJSON_CreateObject();
  param_subcmd = cJSON_CreateString(IDENTITY_COMMAND_PARAM_COUNT);
  cJSON_AddItemToObject(params, "subcommand", param_subcmd);
  
  (void) create_request_str(IDENTITY_COMMAND_PREFIX, params, &req);
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

  json_output = getenv (PBOTECTL_USE_JSON_OUTPUT_ENVIRONMENT);
  if (json_output)
    {
      printf ("%s\n", cJSON_Print (o_json));
      cJSON_Delete (o_json);
      return exit_status;
    }

  result_json = cJSON_GetObjectItemCaseSensitive (o_json, "result");
  identity_json = cJSON_GetObjectItemCaseSensitive (result_json, "identity");
  count_json = cJSON_GetObjectItemCaseSensitive (identity_json, "count");

  if (!cJSON_IsNumber (count_json))
    {
      exit_status = EXIT_ERROR;
      cJSON_Delete (o_json);
      return exit_status;
    }

  printf (_("Identities:\n"));
  printf (_("\tCount:\t%d\n"), count_json->valueint);

  cJSON_Delete (o_json);
  return exit_status;
}

char *
identity_type_to_str(int type)
{
  switch(type)
    {
      case ECDH256_ECDSA256_ID:
        return ECDH256_ECDSA256_NAME;
      case ECDH521_ECDSA521_ID:
        return ECDH521_ECDSA521_NAME;
      case X25519_ED25519_ID:
        return X25519_ED25519_NAME;
      default:
        return "UNKNOWN";
    }
}
