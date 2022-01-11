/**
 * Copyright (c) 2019-2022 polistern
 */

#ifndef GIT_COMPAT_UTIL_H
#define GIT_COMPAT_UTIL_H

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

#define EXIT_SUCCESS 0

//#define RUN_SETUP      (1<<0)
//#define NEED_WORK_TREE (1<<3)

static inline int skip_prefix(const char *str, const char *prefix, const char **out) {
  do {
    if (!*prefix) {
      *out = str;
      return 1;
    }
  } while (*str++ == *prefix++);
  return 0;
}

#endif
