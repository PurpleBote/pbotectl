/*
 * request.c: code to make request to socket
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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _WIN32 /* not _WIN32 */
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include <linux/limits.h>
#else /* _WIN32 */
/* NOOP */
#endif /* not _WIN32 */

#include "commands.h"
#include "util.h"

#define DEFAULT_SOCKET_PATH "/run/pboted/pboted.sock"
#define DEFAULT_HOST "127.0.0.1"
#define DEFAULT_PORT 5055

#ifndef _WIN32
#define INVALID_SOCKET -1
#endif

static void
set_socket_path (char *socket_path)
{
  char *env_val = getenv (PBOTECTL_SOCKET_PATH_ENVIRONMENT);
  if (env_val)
    {
#if DEBUG_MODE
      printf ("Got socket path override: %s\n", env_val);
#endif
      strcpy (socket_path, env_val);
    }
  else
    {
#if DEBUG_MODE
      printf ("Use default socket path: %s\n", DEFAULT_SOCKET_PATH);
#endif
      strcpy (socket_path, DEFAULT_SOCKET_PATH);
    }
}

static void
set_host_addr (char *host, int *port)
{
  char *host_env_val = getenv (PBOTECTL_DAEMON_HOST_ENVIRONMENT);
  if (host_env_val)
    {
#if DEBUG_MODE
      printf ("Got host override: %s\n", host_env_val);
#endif
      strcpy (host, host_env_val);
    }
  else
    {
#if DEBUG_MODE
      printf ("Use default host: %s\n", DEFAULT_HOST);
#endif
      strcpy (host, DEFAULT_HOST);
    }

  char *port_env_val = getenv (PBOTECTL_DAEMON_PORT_ENVIRONMENT);
  if (port_env_val)
    {
      sscanf(port_env_val, "%d", port);
#if DEBUG_MODE
      printf ("Got port override: %s\n", port_env_val);
#endif
    }
  else
    {
#if DEBUG_MODE
      printf ("Use default port: %d\n", DEFAULT_PORT);
#endif
      *port = DEFAULT_PORT;
    }
}

void
make_request (const char *request, char *buffer)
{
  /* Socket stuff */
  char socket_path[PATH_MAX];
  struct sockaddr_un sock_addr;
  /* TCP stuff */
  char host_ip[50]; /* Taken with a margin for IPv6 in future */
  int host_port = 0;
  struct sockaddr_in host_addr;
  /* For both */
  int data_socket;
  int ret;

  /* check what we need to use to connect */
  char *is_socket = getenv (PBOTECTL_CONNECT_USE_SOCKET);

  /* If booth socket and host:port not set - try default host and port*/
  if (!is_socket)
    {
      is_socket = malloc (1);
      *is_socket = '0';
    }

#if DEBUG_MODE
  printf ("make_request: is socket: %s\n", *is_socket - '0' ? "true" : "false");
#endif

  if (*is_socket - '0')
    {
      set_socket_path (socket_path);
      if (!file_exists (socket_path))
        {
          printf (_("make_request: Socket file not exists: %s\n"),
                  socket_path);
          return;
        }
      data_socket = socket (AF_UNIX, SOCK_STREAM, 0);
      if (data_socket == -1)
        {
          printf (_("make_request: Socket create error: %s\n"),
                  strerror (errno));
          return;
        }

      memset (&sock_addr, 0, sizeof (sock_addr));

      sock_addr.sun_family = AF_UNIX;
      strncpy (sock_addr.sun_path, socket_path, sizeof (sock_addr.sun_path) - 1);

      ret = connect (data_socket, (const struct sockaddr *)&sock_addr, sizeof (sock_addr));
    }
  else
    {
      set_host_addr (&host_ip[0], &host_port);
      data_socket = socket(AF_INET, SOCK_STREAM, 0);
      if (data_socket == -1)
        {
          printf (_("make_request: Socket create error: %s\n"),
                  strerror (errno));
          return;
        }

      memset (&host_addr, 0, sizeof (host_addr));

      host_addr.sin_family = AF_INET;
      host_addr.sin_addr.s_addr = inet_addr(host_ip);
      host_addr.sin_port = htons(host_port);
      ret = connect (data_socket, (const struct sockaddr *)&host_addr, sizeof (host_addr));
    }

  if (ret == INVALID_SOCKET)
    {
      printf (_("make_request: Socket connect error: %s\n"),
              strerror (errno));
      return;
    }

  ret = write (data_socket, request, strlen (request));

  if (ret == -1)
    {
      printf (_("make_request: Write error to socket: %s\n"),
              strerror (errno));
    }

  ret = read (data_socket, buffer, DEFAULT_BUFFER_SIZE);
  if (ret == -1)
    {
      printf (_("make_request: Read error from socket: %s\n"),
              strerror (errno));
      return;
    }

  buffer[DEFAULT_BUFFER_SIZE - 1] = 0;
  /*printf (_("make_request: response: %s\n"), buffer);*/

  close (data_socket);
}
