/*
 * help.c: code to view help messages
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

const char usage_string[]
    = ("Usage: pbotectl [-s | --socket=PATH] [-j | --json] <command> [<args>]\n"
       "\n"
       "   -s, --socket=PATH\tSet custom path to socket\n"
       "   -j, --json\t\tEnables output formatting to JSON\n"
       "\n"
       "Avaliable commands:\n"
       "\n"
       "basic information\n"
       "   version\t\tDisplay information about pbotectl version\n"
       "   help\t\t\tDisplay help information about pbotectl (this message)\n"
       "   \t\t\tor can be a part of other commands\n"
       "\n"
       "examine the pboted state (can be a part of other commands)\n"
       "   show\t\t\tShow various types of objects\n"
       "   status\t\tShow the status of various tasks\n"
       "\n"
       //"work with mail related entities\n"
       // ToDo: "   mail\t\t\tList, compose, send mail\n"
       // ToDo: "   task\t\t\tGet status and run Bote tasks (e.g. recieve/send mail tasks)\n"
       // ToDo: "   alias\t\tList, add, edit, remove aliases (address book)\n"
       //"\n"
       "work with Bote daemon\n"
       "   daemon\t\tShow runtime variables (e.g. uptime, transferred data size)\n"
       "   identity\t\tShow, create, modify, remove, update Bote identities\n"
       "   storage\t\tShow DHT storage usage and update limit\n"
       "   peer\t\t\tList, add, remove, update relay peers\n"
       "   node\t\t\tList, add, remove, update DHT nodes\n"
       "\n");

int
cmd_help (int argc, const char **argv, const char *prefix)
{
  int exit_status = 0;

  // If no more params we show basic usage
  printf (usage_string);
  // ToDo: check another params like commands and params

  return exit_status;
}
