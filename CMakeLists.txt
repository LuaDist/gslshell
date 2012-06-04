# Copyright (C) 2007-2012 LuaDist.
# Created by David Manura, Peter Drahoš
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the COPYRIGHT file distributed with LuaDist.
# Please note that the package source code is licensed under its own license.

project ( gslshell C )
cmake_minimum_required ( VERSION 2.8 )
include ( cmake/dist.cmake )
include ( lua )

# Library
set ( LUAGSL_SRCS math-types.c matrix.c nlinfit_helper.c fdfsolver.c nlinfit.c lua-utils.c 
  linalg.c integ.c ode_solver.c ode.c lua-gsl.c )

# Complex support if Lua LNUM patch installed (lualnum).
include ( CheckSymbolExists )
check_symbol_exists ( LNUM_COMPLEX ${LUA_INCLUDE_DIR}/luaconf.h HAVE_LNUM_COMPLEX )
if ( HAVE_LNUM_COMPLEX )
  list ( APPEND LUAGSL_SRCS cmatrix.c cnlinfit.c code.c fft.c )
  add_definitions ( --std=c99 -DLNUM_COMPLEX )
  # complex.h support
endif ( HAVE_LNUM_COMPLEX )

# readline like support for Lua shell
find_path ( READLINE_INCLUDE_DIR readline/readline.h )
find_library ( READLINE_LIBRARY NAMES readline )
if ( READLINE_LIBRARY )
  include_directories ( ${READLINE_INCLUDE_DIR} )
  add_definitions ( -DLUA_USE_READLINE )
  set ( MYLUA_LIBS ${MYLUA_LIBS} ${READLINE_LIBRARY} )
endif ( )
include ( FindCurses )
if ( CURSES_LIBRARY )
  include_directories ( ${CURSES_INCLUDE_DIR} )
  set ( MYLUA_LIBS ${MYLUA_LIBS} ${CURSES_LIBRARY} )
endif ( )

# Find gsl
find_library ( GSL_LIBRARY NAMES gsl )
find_library ( GSLCBLAS_LIBRARY NAMES gslcblas )

install_lua_module ( gsl ${LUAGSL_SRCS} LINK ${GSL_LIBRARY} ${GSLCBLAS_LIBRARY} )
set_property ( TARGET gsl APPEND PROPERTY COMPILE_DEFINITIONS "USE_SEPARATE_NAMESPACE" )

add_executable ( gsl-shell gsl-shell.c ${LUAGSL_SRCS} )
target_link_libraries ( gsl-shell ${LUA_LIBRARY} ${MYLUA_LIBS} ${GSL_LIBRARY} ${GSLCBLAS_LIBRARY} )

install_executable ( gsl-shell )
install_lua_module ( igsl igsl.lua )
install_lua_module ( integ integ.lua )
install_test ( tests/ex-linalg.lua tests/mexp.lua tests/ode-test.lua tests/ode-example-qdho.lua 
  tests/matrix-op.lua tests/nlinfit-test.lua )
install_data ( LICENSE README )
install_doc ( doc/source/acknowledgments.rst doc/source/conf.py doc/source/email-gslshell.png 
  doc/source/fft.rst doc/source/index.rst doc/source/integ.rst doc/source/intro.rst 
  doc/source/linalg.rst doc/source/matrices.rst doc/source/news.rst doc/source/nlinfit.rst 
  doc/source/ode.rst )
install_example ( examples/legendre-pol.lua examples/nlinfit.lua examples/ode-example.lua )
