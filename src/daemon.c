/*
 * daemon.c: code to handle daemon related commands
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
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "commands.h"
#include "daemon.h"

static const char     *sizes[]   = { "EiB", "PiB", "TiB", "GiB", "MiB", "KiB", "B" };
static const uint64_t  exbibytes = 1024ULL * 1024ULL * 1024ULL *
                                   1024ULL * 1024ULL * 1024ULL;

static struct subcmd_struct daemon_subcmds[] = {
  { "help", subcmd_daemon_help },
  { "show", subcmd_daemon_show },
  { "uptime", subcmd_daemon_uptime },
};

char *
bs2l(uint64_t size)
{   
  char * result = (char *) malloc(sizeof(char) * 20);
  uint64_t multiplier = exbibytes;
  int i;

  for (i = 0; i < ARRAY_SIZE(sizes); i++, multiplier /= 1024)
    {   
      if (size < multiplier)
        continue;
      if (size % multiplier == 0)
        sprintf(result, "%" PRIu64 " %s", size / multiplier, sizes[i]);
      else
        sprintf(result, "%.1f %s", (float) size / multiplier, sizes[i]);
      return result;
    }

  strcpy(result, "0");
  return result;
}

int
cmd_daemon (int argc, const char **argv, const char *prefix)
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
subcmd_daemon_help (int argc, const char **argv, const char *prefix)
{
  int exit_status = 0;

  // ToDo:
  printf ("daemon help\n");

  return exit_status;
}

int
subcmd_daemon_show (int argc, const char **argv, const char *prefix)
{
  char buffer[DEFAULT_BUFFER_SIZE];
  int exit_status = 0;

  char cmd_str[] = DAEMON_COMMAND_PREFIX;
  strcat (cmd_str, DAEMON_COMMAND_PARAM_UPTIME); // ToDo

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
  printf ("Uptime:\t%d day(s), %d:%02d:%02d\n\n", days, hours, minutes, seconds);
  printf ("Recv:\t%s\n", bs2l(recv_json->valueint));
  printf ("Sent:\t%s\n", bs2l(sent_json->valueint));

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
  printf ("%d day(s), %d:%02d:%02d\n", days, hours, minutes, seconds);

  return exit_status;
}
