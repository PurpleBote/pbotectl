/*
 * identity.h: interfaces to identity related commands
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

#ifndef PBOTECTL_IDENTITY_H
#define PBOTECTL_IDENTITY_H

#define IDENTITY_COMMAND_PREFIX "identity"

#define IDENTITY_COMMAND_PARAM_COUNT "count"
#define IDENTITY_COMMAND_PARAM_SHOW "show"

#define ECDH256_ECDSA256_ID 2
#define ECDH256_ECDSA256_NAME "ECDH-256 / ECDSA-256"
#define ECDH256_ECDSA256_NAME_FULL "ECDH-256 / ECDSA-256 / AES-256 / SHA-256"

#define ECDH521_ECDSA521_ID 3
#define ECDH521_ECDSA521_NAME "ECDH-521 / ECDSA-521"
#define ECDH521_ECDSA521_NAME_FULL "ECDH-521 / ECDSA-521 / AES-256 / SHA-512"

#define X25519_ED25519_ID 5
#define X25519_ED25519_NAME "X25519 / ED25519"
#define X25519_ED25519_NAME_FULL "X25519 / ED25519 / AES-256 / SHA-512"

int subcmd_identity_help (int argc, const char **argv, const char *prefix);
int subcmd_identity_show (int argc, const char **argv, const char *prefix);
int subcmd_identity_count(int argc, const char **argv, const char *prefix);

char * identity_type_to_str(int type);

#endif /* PBOTECTL_IDENTITY_H */
