/*
 * gettext.h: libintl.h wrapper
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

#ifndef GETTEXT_H
#define GETTEXT_H

#if defined(_)
#error "namespace conflict: '_' is pre-defined?"
#endif

#include <libintl.h>
#include <locale.h>

#define _(msgid) gettext(msgid)
/*#define N_(msgid) (msgid)*/

#endif /* GETTEXT_H */
