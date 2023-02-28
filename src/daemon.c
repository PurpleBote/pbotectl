/*
 * daemon.c: code to handle daemon related commands
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
#include "daemon.h"
#include "gettext.h"
#include "jsonrpc.h"

static struct subcmd_struct daemon_subcmds[] = {
  { "help", subcmd_daemon_help },
  { "show", subcmd_daemon_show },
  { "uptime", subcmd_daemon_uptime },
};

MAKE_FIND_SUBCOMMAND(cmd_daemon, daemon_subcmds)

int
subcmd_daemon_help (int argc, const char **argv, const char *prefix)
{
  int exit_status = 0;

  /* ToDo: */
  printf (_("daemon help\n"));

  return exit_status;
}

int
subcmd_daemon_show (int argc, const char **argv, const char *prefix)
{
  char buffer[DEFAULT_BUFFER_SIZE];
  int exit_status = 0, seconds = 0, minutes = 0, hours = 0, days = 0;
  char *req, *is_json;
  cJSON *o_json, *params, *param_subcmd, *result_json, *daemon_json, *uptime_json, *bytes_json, *recv_json, *sent_json;

  params = cJSON_CreateObject();
  param_subcmd = cJSON_CreateString(DAEMON_COMMAND_PARAM_SHOW);
  cJSON_AddItemToObject(params, "subcommand", param_subcmd);

  (void) create_request_str(DAEMON_COMMAND_PREFIX, params, &req);
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
      return exit_status;
    }

  result_json = cJSON_GetObjectItemCaseSensitive (o_json, "result");
  daemon_json = cJSON_GetObjectItemCaseSensitive (result_json, "daemon");
  uptime_json = cJSON_GetObjectItemCaseSensitive (daemon_json, "uptime");
  bytes_json = cJSON_GetObjectItemCaseSensitive (daemon_json, "bytes");
  recv_json = cJSON_GetObjectItemCaseSensitive (bytes_json, "recived");
  sent_json = cJSON_GetObjectItemCaseSensitive (bytes_json, "sent");

  if (!cJSON_IsNumber (uptime_json) ||
      !cJSON_IsNumber (recv_json)||
      !cJSON_IsNumber (sent_json))
    {
      exit_status = 1;
      return exit_status;
    }

  days = uptime_json->valueint / 86400;
  hours = (uptime_json->valueint % 86400) / 3600;
  minutes = (uptime_json->valueint / 60) % 60;
  seconds = uptime_json->valueint % 60;

  printf (_("Daemon:\n"));
  printf (_("\tUptime:\t%d day, %d:%02d:%02d\n\n"), days, hours, minutes, seconds);
  printf (_("\tRecv:\t%s\n"), bs2l(recv_json->valueint));
  printf (_("\tSent:\t%s\n"), bs2l(sent_json->valueint));

  return exit_status;
}

int
subcmd_daemon_uptime (int argc, const char **argv, const char *prefix)
{
  char buffer[DEFAULT_BUFFER_SIZE];
  int exit_status = 0, seconds, minutes, hours, days;
  char *req, *is_json;
  cJSON *params, *param_subcmd, *o_json, *result_json, *daemon_json, *uptime_json;

  params = cJSON_CreateObject();
  param_subcmd = cJSON_CreateString(DAEMON_COMMAND_PARAM_UPTIME);
  cJSON_AddItemToObject(params, "subcommand", param_subcmd);

  (void) create_request_str(DAEMON_COMMAND_PREFIX, params, &req);
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

  o_json = cJSON_Parse(buffer);

  is_json = getenv (PBOTECTL_USE_JSON_OUTPUT_ENVIRONMENT);
  if (is_json)
    {
      printf ("%s\n", cJSON_Print(o_json));
      cJSON_Delete (o_json);
      return exit_status;
    }

  result_json = cJSON_GetObjectItemCaseSensitive(o_json, "result");
  daemon_json = cJSON_GetObjectItemCaseSensitive(result_json, "daemon");
  uptime_json = cJSON_GetObjectItemCaseSensitive(daemon_json, "uptime");

  if (!cJSON_IsNumber(uptime_json))
    {
      exit_status = 1;
      cJSON_Delete (o_json);
      return exit_status;
    }

  days = uptime_json->valueint / 86400;
  hours = (uptime_json->valueint % 86400) / 3600;
  minutes = (uptime_json->valueint / 60) % 60;
  seconds = uptime_json->valueint % 60;
  printf (P_("%d day, %d:%02d:%02d\n",
             "%d days, %d:%02d:%02d\n", days), days, hours, minutes, seconds);

  cJSON_Delete (o_json);
  return exit_status;
}
