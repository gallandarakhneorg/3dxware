/*
 * Copyright (c) 2008-2009 Stéphane GALLAND <galland@arakhne.org>
 *
 * This file is part of ASMD.
 *
 * ASMD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ASMD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with ASMD.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef __DEBUG_H__
#  define __DEBUG_H__

#  ifdef DEBUG
#    include <stdio.h>
#    define dbg(__v__) { fprintf(stderr, "[%s:%d] " __v__ "\n", __FILE__, __LINE__); }
#    define dbg1(__v__,__a__) { fprintf(stderr, "[%s:%d] " __v__ "\n", __FILE__, __LINE__, (__a__)); }
#    define dbg2(__v__,__a__,__b__) { fprintf(stderr, "[%s:%d] " __v__ "\n", __FILE__, __LINE__, (__a__), (__b__)); }
#    define dbg3(__v__,__a__,__b__,__c__) { fprintf(stderr, "[%s:%d] " __v__ "\n", __FILE__, __LINE__, (__a__), (__b__),(__c__)); }
#  else
#    define dbg(__v__) {}
#    define dbg1(__v__,__a__) {}
#    define dbg2(__v__,__a__,__b__) {}
#    define dbg3(__v__,__a__,__b__,__c__) {}
#  endif

#endif // __DEBUG_H__

