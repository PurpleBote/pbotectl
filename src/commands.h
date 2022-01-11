/**
 * Copyright (c) 2019-2022 polistern
 */

#ifndef COMMANDS_H
#define COMMANDS_H

#define DEFAULT_BUFFER_SIZE 8192

void make_request(const char *request, char *response);

int cmd_help(int argc, const char **argv, const char *prefix);
int cmd_show(int argc, const char **argv, const char *prefix);
int cmd_storage(int argc, const char **argv, const char *prefix);
// cmd_version defined in version.h

#endif
