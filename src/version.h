/**
 * Copyright (c) 2019-2022 polistern
 */

#ifndef PBOTECTL_VERSION_H__
#define PBOTECTL_VERSION_H__

#include "commands.h"

#define CODENAME "Plus Bote Control Tool"

#define STRINGIZE(x) #x
#define MAKE_VERSION(a, b, c) STRINGIZE(a) "." STRINGIZE(b) "." STRINGIZE(c)

#define PBOTECTL_VERSION_MAJOR 0
#define PBOTECTL_VERSION_MINOR 0
#define PBOTECTL_VERSION_MICRO 1

#define PBOTECTL_VERSION MAKE_VERSION(PBOTECTL_VERSION_MAJOR, PBOTECTL_VERSION_MINOR, PBOTECTL_VERSION_MICRO)
#define VERSION PBOTECTL_VERSION

static inline int cmd_version(int argc, const char **argv, const char *prefix) {
  printf("%s, version %s\n", CODENAME, VERSION);
  return 0;
}

#endif // PBOTECTL_VERSION_H__
