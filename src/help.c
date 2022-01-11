/**
 * Copyright (c) 2019-2022 polistern
 */

#include <stdio.h>

#include "commands.h"

const char usage_string[] = (
  "Usage:\tpbotectl [-s <socket_path>] <command> [<args>]\n"
  "\n"
  "Avaliable commands:\n"
  "\n"
  "basic information\n"
  "   version\tDisplay information about pbotectl version\n"
  "   help\t\tDisplay help information about pbotectl (this message)\n"
  "   \t\tor can be a part of other commands\n"
  "\n"
  "examine the pboted state (can be a part of other commands)\n"
  "   show\t\tShow various types of objects\n"
  "   status\tShow the status of various tasks\n"
  "\n"
  "work with mail related\n"
  "   mail\t\tWork with mail\n"
  "   alias\tWork with aliases (address book)\n"
  "\n"
  "work with Bote configuration\n"
  "   storage\tWork with DHT storage\n"
  "   peer\t\tWork with relay peers\n"
  "   node\t\tWork with usual nodes\n"
  "\n"
  );

int cmd_help(int argc, const char **argv, const char *prefix) {
  int exit_status = 0;

  // If no more params we show basic usage
  printf(usage_string);
  // ToDo: check another params like commands and params

  return exit_status;
}
