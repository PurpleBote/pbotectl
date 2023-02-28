/*
 * help.c: code to view help messages
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
#include "gettext.h"

int
cmd_help (int argc, const char **argv, const char *prefix)
{
  /* ToDo: check another params like commands and params? */
  int exit_status = 0;

  /* If no more params we show basic usage */
  printf (_("Usage: pbotectl [OPTION...] COMMAND [COMMAND OPTION...]"));
  /*"-h | -v |\n"
  "    [[-s | --socket] | --socket=PATH] |\n"
  "    [[-H | --host] | --host=<host> -p <port>]\n"
  "    [-j | --json] <command> [<args>]\n"*/
  printf ("\n");
  printf (_("General options:\n"));
  printf (_("\
    -h, --help          Show help information about pbotectl (this message)\n"));
  printf (_("\
    -v, --version       Show information about pbotectl version\n"));
  printf (_("Connect options:\n"));
  printf (_("\
    -s, --socket        Flag to force use socket with defaults\n"));
  printf (_("\
        --socket=PATH   Set custom path to socket\n"));
  printf (_("  OR\n"));
  printf (_("\
    -t, --tcp           Flag to force use TCP with defaults\n"));
  printf (_("\
        --host=ADDRESS  Set pboted address\n"));
  printf (_("\
        --port=PORT     Set pboted control port\n"));
  printf (_("Formatting options:\n"));
  printf (_("\
    -j, --json          Enables output formatting to JSON\n"));
  printf ("\n");
  printf (_("Avaliable commands:\n"));
  printf (_("Basic information\n"));
  printf (_("\
    help                Show help information about pbotectl (this message)\n"));
  printf (_("\
    version             Show information about pbotectl version\n"));
  printf (_("\
                        or can be a part of other commands\n"));
  printf ("\n");
  printf (_("Examine daemon state (can be a part of other commands)\n"));
  printf (_("\
    show                Show various types of objects\n"));
  printf (_("\
    status              Show the status of various tasks\n"));
  printf ("\n");
  /* ToDo:
  printf (_("Mail related\n"));
  printf (_("\
    mail                List, compose, send mail\n"));
  printf (_("\
    task                Get status and run Bote tasks\n\
                        (e.g. recieve/send mail tasks)\n"));
  printf (_("\
    alias               List, add, edit, remove aliases (address book)\n"));
  printf ("\n");
  */
  printf (_("Work with daemon\n"));
  printf (_("\
    daemon              Show runtime variables (e.g. uptime, transferred data size)\n"));
  printf (_("\
    identity            Show, create, modify, remove, update Bote identities\n"));
  printf (_("\
    storage             Show DHT storage usage and update limit\n"));
  printf (_("\
    node                List, add, remove, update DHT nodes\n"));
  printf (_("\
    peer                List, add, remove, update relay peers\n"));
  printf ("\n");
  printf (_("Report bugs to <%s>\n"), "polistern@i2pmail.org");

  return exit_status;
}
