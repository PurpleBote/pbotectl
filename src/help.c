/*
 * help.c: code to view help messages
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

#include "commands.h"
#include "gettext.h"

const char usage_string[]
    = ("Usage: pbotectl [OPTION...] COMMAND [OPTION...]"
       /*"-h | -v |\n"
       "    [[-s | --socket] | --socket=PATH] |\n"
       "    [[-H | --host] | --host=<host> -p <port>]\n"
       "    [-j | --json] <command> [<args>]\n"*/
       "\n"
       "General options:\n"
       "    -h, --help\t\tShow help information about pbotectl (this message)\n"
       "    -v, --version\tShow information about pbotectl version\n"
       "  Connect options:\n"
       "    -s, --socket\tFlag to force use socket with defaults\n"
       "        --socket=PATH\tSet custom path to socket\n"
       "    OR\n"
       "    -t, --tcp\t\tFlag to force use host:port with defaults\n"
       "        --host=ADDRESS\tSet pboted address\n"
       "        --port=PORT\tSet pboted control port\n"
       "  Formatting options:\n"
       "    -j, --json\t\tEnables output formatting to JSON\n"
       "\n"
       "Avaliable commands:\n"
       "\n"
       " Basic information\n"
       "   help\t\t\tShow help information about pbotectl (this message)\n"
       "   version\t\tShow information about pbotectl version\n"
       "   \t\t\tor can be a part of other commands\n"
       "\n"
       " Examine the pboted state (can be a part of other commands)\n"
       "   show\t\t\tShow various types of objects\n"
       "   status\t\tShow the status of various tasks\n"
       "\n"
       /*"work with mail related entities\n"*/
       /* ToDo: "   mail\t\t\tList, compose, send mail\n"*/
       /* ToDo: "   task\t\t\tGet status and run Bote tasks (e.g. recieve/send mail tasks)\n"*/
       /* ToDo: "   alias\t\tList, add, edit, remove aliases (address book)\n"*/
       /*"\n"*/
       " Work with Bote daemon\n"
       "   daemon\t\tShow runtime variables (e.g. uptime, transferred data size)\n"
       "   identity\t\tShow, create, modify, remove, update Bote identities\n"
       "   storage\t\tShow DHT storage usage and update limit\n"
       "   node\t\t\tList, add, remove, update DHT nodes\n"
       "   peer\t\t\tList, add, remove, update relay peers\n"
       "\n"
       "Report bugs to polistern@i2pmail.org\n");

int
cmd_help (int argc, const char **argv, const char *prefix)
{
  int exit_status = 0;

  /* If no more params we show basic usage */
  printf (usage_string);
  /* ToDo: check another params like commands and params */

  return exit_status;
}
