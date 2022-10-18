/*
 * show.h: interfaces to show related commands
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

#ifndef PBOTECTL_SHOW_H
#define PBOTECTL_SHOW_H

#define SHOW_COMMAND_PREFIX_ALL      "all."
#define SHOW_COMMAND_PREFIX_DAEMON   "daemon."
#define SHOW_COMMAND_PREFIX_IDENTITY "identity."
#define SHOW_COMMAND_PREFIX_NODE     "node."
#define SHOW_COMMAND_PREFIX_PEER     "peer."
#define SHOW_COMMAND_PREFIX_STORAGE  "storage."
#define SHOW_COMMAND_POSTFIX         "show"

int subcmd_show_help (int argc, const char **argv, const char *prefix);
int subcmd_show_all (int argc, const char **argv, const char *prefix);

#endif /* PBOTECTL_SHOW_H */
