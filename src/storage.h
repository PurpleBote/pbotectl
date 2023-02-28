/*
 * storage.h: interfaces to storage related commands
 * Copyright (C) 2022-2023, PurpleBote Team
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

#ifndef PBOTECTL_STORAGE_H
#define PBOTECTL_STORAGE_H

#define STORAGE_COMMAND_PREFIX "storage"

#define STORAGE_COMMAND_PARAM_CLEAN "clean"
#define STORAGE_COMMAND_PARAM_SHOW  "show"
#define STORAGE_COMMAND_PARAM_USED  "used"

int subcmd_storage_help (int argc, const char **argv, const char *prefix);
int subcmd_storage_show (int argc, const char **argv, const char *prefix);
int subcmd_storage_used (int argc, const char **argv, const char *prefix);
int subcmd_storage_clean (int argc, const char **argv, const char *prefix);

#endif /* PBOTECTL_STORAGE_H */
