# Fintech Tools.
# Copyright (C) 2016 Swirly Cloud Limited.
#
# This program is free software; you can redistribute it and/or modify it under the terms of the
# GNU General Public License as published by the Free Software Foundation; either version 2 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with this program; if
# not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
# 02110-1301, USA.

file(GLOB hdf5_SOURCES "*.cpp")

add_library(hdf5_static STATIC ${hdf5_SOURCES})
set_target_properties(hdf5_static PROPERTIES OUTPUT_NAME ft_hdf5)
target_link_libraries(hdf5_static)
install(TARGETS hdf5_static DESTINATION lib)

if(ENABLE_SHARED_LIBS)
  add_library(hdf5_shared SHARED ${hdf5_SOURCES})
  set_target_properties(hdf5_shared PROPERTIES OUTPUT_NAME ft_hdf5)
  target_link_libraries(hdf5_shared)
  install(TARGETS hdf5_shared DESTINATION lib)
endif()
