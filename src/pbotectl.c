/*
 * pbotectl.c: CLI utility for Plus Bote Daemon
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
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "gettext.h"
#include "util.h"
#include "version.h"

struct cmd_struct
{
  const char *cmd;
  int (*fn) (int, const char **, const char *);
};

static struct cmd_struct commands[] = {
  { "help", cmd_help },
  { "version", cmd_version },
  /* Overview */
  { "show", cmd_show },
  /* ToDo: { "status", cmd_status },*/
  /* Detailed */
  { "daemon", cmd_daemon },
  { "identity", cmd_identity },
  /* ToDo: { "mail", cmd_mail },*/
  { "node", cmd_node },
  { "peer", cmd_peer },
  { "storage", cmd_storage },
};

const char * const env_var[]
= {
   PBOTECTL_USE_JSON_OUTPUT_ENVIRONMENT,
   PBOTECTL_CONNECT_USE_SOCKET,
   PBOTECTL_SOCKET_PATH_ENVIRONMENT,
   PBOTECTL_DAEMON_HOST_ENVIRONMENT,
   PBOTECTL_DAEMON_PORT_ENVIRONMENT,
   NULL
};

static struct cmd_struct *
get_command (const char *s)
{
  unsigned long i;
  for (i = 0; i < ARRAY_SIZE (commands); i++)
    {
      struct cmd_struct *p = commands + i;
      if (!strcmp (s, p->cmd))
        return p;
    }
  return NULL;
}

int
is_command (const char *s)
{
  return !!get_command (s);
}

static int
/*run_command (struct cmd_struct *p, int argc, const char **argv)*/
run_command (struct cmd_struct *p, int argc, char **argv)
{
  int status;
  const char *prefix;
  prefix = NULL;

  status = p->fn (argc, argv, prefix);

  if (status)
    return status;

  return EXIT_SUCCESS;
}

static int
/*handle_options (const char ***argv, int *argc, int *envchanged, int *need_help)*/
handle_options (char ***argv, int *argc, int *envchanged, int *need_help)
{
  /*const char **orig_argv = *argv;*/
  char **orig_argv = *argv;

  if (0 == strcmp((*argv)[0], "-h"))
    {
      char *str = "--help";
      (*argv)[0] = (char *)malloc(strlen(str));
      strcpy((*argv)[0], str);
    }

  if (0 == strcmp((*argv)[0], "-v"))
    {
      char *str = "--version";
      (*argv)[0] = (char *)malloc(strlen(str));
      strcpy((*argv)[0], str);
    }
  
  /* Check if first parameter is command */
  if (is_command ((*argv)[0]))
    return 0;
  
  while (*argc > 0)
    {
      const char *cmd = (*argv)[0];

      /* If we still get command */
      if (cmd[0] != '-')
        break;

      if (0 == strcmp(cmd, "--help") || 0 == strcmp(cmd, "--version"))
        break;

      if (0 == strcmp(cmd, "-j") || 0 == strcmp(cmd, "--json"))
        {
          setenv (PBOTECTL_USE_JSON_OUTPUT_ENVIRONMENT, "1", 1);
          if (envchanged)
            *envchanged = 1;
        }
      else if (0 == strcmp (cmd, "-s") || 0 == strcmp (cmd, "--socket"))
        {
          setenv (PBOTECTL_CONNECT_USE_SOCKET, "1", 1);

          if (envchanged)
            *envchanged = 1;
          
          (*argv)++;
          (*argc)--;
          break;
        }
      else if (skip_prefix (cmd, "--socket=", &cmd))
        {
          setenv (PBOTECTL_CONNECT_USE_SOCKET, "1", 1);
          setenv (PBOTECTL_SOCKET_PATH_ENVIRONMENT, cmd, 1);
          
          if (envchanged)
            *envchanged = 1;
        }
      else if (0 == strcmp (cmd, "-t") || 0 == strcmp (cmd, "--tcp"))
        {
          setenv (PBOTECTL_CONNECT_USE_SOCKET, "0", 1);
          
          if (envchanged)
            *envchanged = 1;
          
          (*argv)++;
          (*argc)--;
          break;
        }
      else if (skip_prefix (cmd, "--host=", &cmd))
        {
          setenv (PBOTECTL_CONNECT_USE_SOCKET, "0", 1);
          setenv (PBOTECTL_DAEMON_HOST_ENVIRONMENT, cmd, 1);
          
          if (envchanged)
            *envchanged = 1;
        }
      else if (skip_prefix (cmd, "--port=", &cmd))
        {
          setenv (PBOTECTL_CONNECT_USE_SOCKET, "0", 1);
          setenv (PBOTECTL_DAEMON_PORT_ENVIRONMENT, cmd, 1);
          
          if (envchanged)
            *envchanged = 1;
        }
      else
        {
          fprintf (stderr, _("unknown option: %s\n"), cmd);
          *need_help = 1;
          break;
        }
      
      (*argv)++;
      (*argc)--;
    }
  
  return (*argv) - orig_argv;
}

static void
/*handle_command (int argc, const char **argv)*/
handle_command (int argc, char **argv)
{
  const char *cmd;
  struct cmd_struct *command;

  cmd = argv[0];

  command = get_command (cmd);
  if (command)
    exit (run_command (command, argc, argv));
  else
    {
      printf (_("Unknown command or parameter: %s\n\n"), cmd);
      command = get_command ("help");
      exit (run_command (command, argc, argv));
    }
}

int
main (int argc, char *argv[])
{
  const char *cmd;
  int need_help = 0;

  /* For skipping bin name */
  argc--;
  argv++;

#if DEBUG_MODE
  printf ("argc:    %d\n", argc);
  if (argc > 0)
    {
      int i = 0;
      for (i = 0; i < argc; i++)
        {
          printf ("argv[%d]: %s\n", i, argv[i]);
        }
    }
#endif

  /*setlocale (LC_ALL, "");*/
  setlocale (LC_CTYPE, "");
  /*setlocale (LC_CTYPE, "C");*/
  setlocale (LC_MESSAGES, "");
#ifndef _WIN32
  bindtextdomain (PACKAGE, "/usr/share/locale");
#endif
  textdomain (PACKAGE);

  handle_options (&argv, &argc, NULL, &need_help);

  if (need_help)
    argv[0] = "help";

  if (argc > 0)
    {
      /* Translate --help and --version into commands */
      skip_prefix (argv[0], "--", &argv[0]);
    }
  else
    {
      /* The user didn't specify a command; give them help */
      fprintf (stderr, _("no command given\n\n"));
      argv[0] = "help";
    }

  cmd = argv[0];

  if (!cmd)
    argv[0] = cmd = "help";
#if DEBUG_MODE
  printf ("cmd: %s\n", cmd);

  int i = 0;
  while (env_var[i])
    {
      char *value = getenv (env_var[i]);
      if (value)
        printf("%s: %s\n", env_var[i], value);
      else
        printf("%s: NULL\n", env_var[i]);
      i++;
    }
#endif

  handle_command (argc, argv);

  return EXIT_SUCCESS;
}
