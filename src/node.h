/*
 * node.h: interfaces to node related commands
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

#ifndef PBOTECTL_NODE_H
#define PBOTECTL_NODE_H

#define NODE_COMMAND_PREFIX "node."

#define NODE_COMMAND_PARAM_SHOW  "show"
#define NODE_COMMAND_PARAM_COUNT "count"
#define NODE_COMMAND_PARAM_STATS "stats"

int subcmd_node_help (int argc, const char **argv, const char *prefix);
int subcmd_node_show (int argc, const char **argv, const char *prefix);
int subcmd_node_count (int argc, const char **argv, const char *prefix);
int subcmd_node_stats (int argc, const char **argv, const char *prefix);

#endif /* PBOTECTL_NODE_H */
