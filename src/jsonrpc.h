/*
 * jsonrpc.h: code with JSON-RPC stuff
 * Copyright (C) 2022-2023, PurpleBote Team
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

#ifndef PBOTECTL_JSONRPC_H
#define PBOTECTL_JSONRPC_H

#include "cJSON.h"

#define JSON_MALFORMED (-2)
#define JSON_IS_ERROR (-1)
#define JSON_OK 0

enum jvalue_type
{
  jtype_string,
  jtype_int
};

typedef struct jrpc_param
{
  int type;
  char* name;
  char* svalue;
  int ivalue;
} jrpc_param;

char * get_4XX_error (int code);

char * get_error_message (int code);

int check_json_error (char *buffer);

int create_request_str (char *cmd, cJSON *params, char **req);

#endif /* PBOTECTL_JSONRPC_H */
