/*
 * jsonrpc.c: code with JSON-RPC stuff
 * Copyright (C) 2022-2023, PurpleBote Team
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

#include "gettext.h"
#include "jsonrpc.h"
#include "util.h"

char *
get_4XX_error (int code)
{
  switch (code)
  {
    case (404):
      return _("Not found");
    default:
      return _("Unknown error code");
  }
}

char *
get_error_message (int code)
{
  int prefix = code / 100;
  switch (prefix)
  {
    case (4):
      return get_4XX_error (code);
    default:
      return _("Unknown error code");
  }
}

int
check_json_error (char *buffer)
{
  cJSON *o_json, *json_result, *json_error, *json_error_code;
  const char *error_ptr;

#if DEBUG_MODE
  printf("Response: %s\n", buffer);
#endif

  o_json = cJSON_Parse (buffer);

  if (o_json == NULL)
    {
      error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
          fprintf(stderr, _("Error before: %s\n"), error_ptr);
        }
      return JSON_MALFORMED;
    }

  json_result = cJSON_GetObjectItemCaseSensitive (o_json, "result");
  json_error = cJSON_GetObjectItemCaseSensitive (o_json, "error");

  if (cJSON_IsNull (json_result) && !cJSON_IsNull (json_error))
    {
      json_error_code = cJSON_GetObjectItemCaseSensitive (json_error, "code");
      /*cJSON *json_error_message = cJSON_GetObjectItemCaseSensitive (json_error, "message");*/

      printf (_("Error, code: %3d, message: %s\n"),
              json_error_code->valueint,
              get_error_message (json_error_code->valueint));
      cJSON_Delete (o_json);
      return JSON_IS_ERROR;
    }

  if (cJSON_IsNull (json_result) && cJSON_IsNull (json_error))
    {
      cJSON_Delete (o_json);
      return JSON_MALFORMED;
    }
  if (!cJSON_IsNull (json_result) && !cJSON_IsNull (json_error))
    {
      cJSON_Delete (o_json);
      return JSON_MALFORMED;
    }

  cJSON_Delete (o_json);

  return JSON_OK;
}

int
create_request_str (char *cmd, cJSON *params, char **buf)
{
  cJSON *req, *req_ver, *req_id, *jcmd;
#if DEBUG_MODE
  char *string;
#endif

  req = cJSON_CreateObject();

  req_ver = cJSON_CreateString("2.0");
  cJSON_AddItemToObject(req, "jsonrpc", req_ver);

  req_id = cJSON_CreateNumber(0);
  cJSON_AddItemToObject(req, "id", req_id);

  jcmd = cJSON_CreateString(cmd);
  cJSON_AddItemToObject(req, "method", jcmd);

  cJSON_AddItemToObject(req, "params", params);

#if DEBUG_MODE
  string = cJSON_Print(req);
  printf ("%s\n", string);
#endif

  *buf = cJSON_PrintUnformatted(req);

  cJSON_Delete (req);
  return 0;
}
