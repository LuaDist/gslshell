
/* fdfsolver.h
 * 
 * Copyright (C) 2009 Francesco Abbate
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef FDFSOLVER_H
#define FDFSOLVER_H

#include <lua.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_multifit_nlin.h>

#include "defs.h"

struct fit_data {
  lua_State *L;
  gsl_vector *x;
  gsl_vector *j_raw;
  size_t n;
};

struct fdfsolver {
  gsl_multifit_fdfsolver *base;
  gsl_multifit_function_fdf fdf[1];
  struct fit_data fit_data[1];
  int base_type;
};

extern int                fdfsolver_dealloc    (lua_State *L);
extern struct fdfsolver * check_fdfsolver      (lua_State *L, int index);
extern struct fdfsolver * push_new_fdfsolver   (lua_State *L, 
						size_t n, size_t p);

extern char const * const fdfsolver_mt_name;
extern const struct luaL_Reg fdfsolver_methods[];

#endif
