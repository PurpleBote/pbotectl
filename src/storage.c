/**
 * Copyright (c) 2019-2022 polistern
 */

#include <stdio.h>

#include "commands.h"

#define STORAGE_COMMAND_PREFIX "storage"
#define STORAGE_COMMAND_PARAM_USED "used"

int cmd_storage(int argc, const char **argv, const char *prefix) {
  char buffer[DEFAULT_BUFFER_SIZE];
  int exit_status = 0;

  // ToDo: parse and concat request
  make_request("storage.used", buffer);

  if (buffer)
    printf("%s\n", buffer);
  else {
    printf("Empty response from server\n");
    exit_status = 1;
  }

  return exit_status;
}
