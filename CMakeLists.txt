# Copyright (C) 2007-2009 LuaDist.
# Created by Peter Drahoš
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the COPYRIGHT file distributed with LuaDist.
# Please note that the package source code is licensed under its own license.

PROJECT(lrandom C)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
INCLUDE(dist.cmake)

ADD_LUA_MODULE(random lrandom.c random.def)
ADD_LUA_TEST(test.lua)

INSTALL(TARGETS random DESTINATION ${INSTALL_CMOD})
INSTALL(FILES README DESTINATION ${INSTALL_DATA})
INSTALL(FILES test.lua DESTINATION ${INSTALL_TEST})
