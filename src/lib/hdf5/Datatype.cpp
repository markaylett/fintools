/*
 * Fintech Tools.
 * Copyright (C) 2016 Swirly Cloud Limited.
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program; if
 * not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */
#include <ft/hdf5/Datatype.hpp>

#include <ft/hdf5/Exception.hpp>

namespace ft {
namespace hdf5 {

Datatype createStringType(size_t size)
{
  Datatype type{H5Tcopy(H5T_C_S1)};
  if (!type || H5Tset_size(*type, size) < 0) {
    throw Exception{};
  }
  return type;
}

} // hdf5
} // ft
