/*
 * daemon.c: code to handle daemon related commands
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

#include "cjson/cJSON.h"

#include "commands.h"
#include "daemon.h"
#include "gettext.h"

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
  int exit_status = 0;

  char cmd_str[] = DAEMON_COMMAND_PREFIX;
  strcat (cmd_str, DAEMON_COMMAND_PARAM_UPTIME); /* ToDo */

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
  cJSON *daemon_json = cJSON_GetObjectItemCaseSensitive (result_json, "daemon");
  cJSON *uptime_json = cJSON_GetObjectItemCaseSensitive (daemon_json, "uptime");
  cJSON *bytes_json = cJSON_GetObjectItemCaseSensitive (daemon_json, "bytes");
  cJSON *recv_json = cJSON_GetObjectItemCaseSensitive (bytes_json, "recived");
  cJSON *sent_json = cJSON_GetObjectItemCaseSensitive (bytes_json, "sent");

  if (!cJSON_IsNumber (uptime_json) ||
      !cJSON_IsNumber (recv_json)||
      !cJSON_IsNumber (sent_json))
    {
      exit_status = 1;
      return exit_status;
    }

  int seconds, minutes, hours, days;
  days = uptime_json->valueint / 86400;
  hours = (uptime_json->valueint % 86400) / 3600;
  minutes = (uptime_json->valueint / 60) % 60;
  seconds = uptime_json->valueint % 60;
  printf (_("Uptime:\t%d day, %d:%02d:%02d\n\n"), days, hours, minutes, seconds);
  printf (_("Recv:\t%s\n"), bs2l(recv_json->valueint));
  printf (_("Sent:\t%s\n"), bs2l(sent_json->valueint));

  return exit_status;
}

int
subcmd_daemon_uptime (int argc, const char **argv, const char *prefix)
{
  char buffer[DEFAULT_BUFFER_SIZE];
  int exit_status = 0;

  char cmd_str[] = DAEMON_COMMAND_PREFIX;
  strcat (cmd_str, DAEMON_COMMAND_PARAM_UPTIME);

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
  cJSON *daemon_json = cJSON_GetObjectItemCaseSensitive(result_json, "daemon");
  cJSON *uptime_json = cJSON_GetObjectItemCaseSensitive(daemon_json, "uptime");

  if (!cJSON_IsNumber(uptime_json))
    {
      exit_status = 1;
      return exit_status;
    }

  int seconds, minutes, hours, days;
  days = uptime_json->valueint / 86400;
  hours = (uptime_json->valueint % 86400) / 3600;
  minutes = (uptime_json->valueint / 60) % 60;
  seconds = uptime_json->valueint % 60;
  printf (_("%d day, %d:%02d:%02d\n"), days, hours, minutes, seconds);

  return exit_status;
}
