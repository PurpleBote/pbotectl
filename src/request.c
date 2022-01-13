/*
 * request.c: code to make request ro socket
 * Copyright (C) 2019-2022 polistern
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
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "commands.h"
#include "util.h"

#define DEFAULT_SOCKET_PATH "/run/pboted/pboted.sock"

void
make_request (const char *request, char *response)
{
  struct sockaddr_un addr;
  int ret;
  int data_socket;

  data_socket = socket (AF_UNIX, SOCK_STREAM, 0);
  if (data_socket == -1)
    {
      fprintf (stderr, "make_request: Socket create error: %s\n",
               strerror (errno));
      exit (EXIT_FAILURE);
    }

  memset (&addr, 0, sizeof (addr));

  addr.sun_family = AF_UNIX;
  strncpy (addr.sun_path, DEFAULT_SOCKET_PATH, sizeof (addr.sun_path) - 1);

  ret = connect (data_socket, (const struct sockaddr *)&addr, sizeof (addr));
  if (ret == -1)
    {
      fprintf (stderr, "make_request: Socket connect error: %s\n",
               strerror (errno));
      exit (EXIT_FAILURE);
    }

  ret = write (data_socket, request, ARRAY_SIZE (request));

  if (ret == -1)
    {
      fprintf (stderr, "make_request: Write error to socket: %s\n",
               strerror (errno));
    }

  ret = read (data_socket, response, sizeof (response));
  if (ret == -1)
    {
      fprintf (stderr, "make_request: Read error from socket: %s\n",
               strerror (errno));
      exit (EXIT_FAILURE);
    }

  response[sizeof (response) - 1] = 0;
  printf ("make_request: response: %s\n", response);

  close (data_socket);
}
