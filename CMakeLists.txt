# Copyright (C) 2007-2009 LuaDist.
# Submitted by David Manura
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the COPYRIGHT file distributed with LuaDist.
# Please note that the package source code is licensed under its own license.

project(gslshell C)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
INCLUDE(dist.cmake)

# Library
set(LUAGSL_SRCS
  math-types.c
  matrix.c
  nlinfit_helper.c
  fdfsolver.c
  nlinfit.c
  lua-utils.c
  linalg.c
  integ.c
  ode_solver.c
  ode.c
  lua-gsl.c
)

# Complex support if Lua LNUM patch installed (lualnum).
include(CheckSymbolExists)
check_symbol_exists(LNUM_COMPLEX ${LUA_INCLUDE_DIR}/luaconf.h HAVE_LNUM_COMPLEX)
if (HAVE_LNUM_COMPLEX)
  list(APPEND LUAGSL_SRCS cmatrix.c cnlinfit.c code.c fft.c)
  add_definitions(--std=c99 -DLNUM_COMPLEX) # complex.h support
endif (HAVE_LNUM_COMPLEX)

# readline like support for Lua shell
FIND_PATH(READLINE_INCLUDE_DIR readline/readline.h)
FIND_LIBRARY(READLINE_LIBRARY NAMES readline)
IF ( READLINE_LIBRARY )
  INCLUDE_DIRECTORIES ( ${READLINE_INCLUDE_DIR} )
  ADD_DEFINITIONS ( -DLUA_USE_READLINE )
  SET ( MYLUA_LIBS ${MYLUA_LIBS} ${READLINE_LIBRARY} )
ENDIF ( )
INCLUDE(FindCurses)
IF ( CURSES_LIBRARY )
  INCLUDE_DIRECTORIES ( ${CURSES_INCLUDE_DIR} )
  SET ( MYLUA_LIBS ${MYLUA_LIBS} ${CURSES_LIBRARY} )
ENDIF ( )

# Find gsl
find_library(GSL_LIBRARY NAMES gsl)
find_library(GSLCBLAS_LIBRARY NAMES gslcblas)

add_lua_module(gsl ${LUAGSL_SRCS})
set_property(TARGET gsl APPEND PROPERTY COMPILE_DEFINITIONS "USE_SEPARATE_NAMESPACE")
target_link_libraries(gsl ${GSL_LIBRARY} ${GSLCBLAS_LIBRARY})

add_executable(gsl-shell gsl-shell.c ${LUAGSL_SRCS})
target_link_libraries(gsl-shell ${LUA_LIBRARY} ${MYLUA_LIBS} ${GSL_LIBRARY} ${GSLCBLAS_LIBRARY})

install(TARGETS gsl DESTINATION ${INSTALL_CMOD})
install(FILES igsl.lua integ.lua DESTINATION ${INSTALL_LMOD})
install(TARGETS gsl-shell RUNTIME DESTINATION ${INSTALL_BIN})
install(FILES
  tests/ex-linalg.lua
  tests/mexp.lua
  tests/ode-test.lua
  tests/ode-example-qdho.lua
  tests/matrix-op.lua
  tests/nlinfit-test.lua
  DESTINATION ${INSTALL_TEST})
install(FILES INSTALL LICENSE README DESTINATION ${INSTALL_DATA})
install(FILES
  doc/source/acknowledgments.rst
  doc/source/conf.py
  doc/source/email-gslshell.png
  doc/source/fft.rst
  doc/source/index.rst
  doc/source/integ.rst
  doc/source/intro.rst
  doc/source/linalg.rst
  doc/source/matrices.rst
  doc/source/news.rst
  doc/source/nlinfit.rst
  doc/source/ode.rst
  DESTINATION ${INSTALL_DOC})
install(FILES
  examples/legendre-pol.lua
  examples/nlinfit.lua
  examples/ode-example.lua
  DESTINATION ${INSTALL_EXAMPLE})
