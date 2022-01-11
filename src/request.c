/**
 * Copyright (c) 2019-2022 polistern
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

void make_request(const char *request, char *response) {
  struct sockaddr_un addr;
  int ret;
  int data_socket;

  data_socket = socket(AF_UNIX, SOCK_STREAM, 0);
  if (data_socket == -1) {
    fprintf(stderr, "make_request: Socket create error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  memset(&addr, 0, sizeof(addr));

  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, DEFAULT_SOCKET_PATH, sizeof(addr.sun_path) - 1);

  ret = connect(data_socket, (const struct sockaddr *) &addr, sizeof(addr));
  if (ret == -1) {
    fprintf(stderr, "make_request: Socket connect error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  ret = write(data_socket, request, ARRAY_SIZE(request));

  if (ret == -1) {
    fprintf(stderr, "make_request: Write error to socket: %s\n", strerror(errno));
  }

  ret = read(data_socket, response, sizeof(response));
  if (ret == -1) {
    fprintf(stderr, "make_request: Read error from socket: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  response[sizeof(response) - 1] = 0;
  printf("make_request: response: %s\n", response);

  close(data_socket);
}
