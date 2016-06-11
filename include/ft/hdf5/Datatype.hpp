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
#ifndef FT_HDF5_DATATYPE_HPP
#define FT_HDF5_DATATYPE_HPP

#include <ft/util/Defs.hpp>
#include <ft/util/UniqueHandle.hpp>

#include <H5Ppublic.h>

namespace ft {
namespace hdf5 {

struct DatatypePolicy {
  using HandleType = hid_t;
  static constexpr HandleType Invalid{H5I_INVALID_HID};
  static void close(HandleType handle) noexcept { H5Tclose(handle); }
};

using Datatype = UniqueHandle<DatatypePolicy>;

FT_API Datatype createStringType(size_t size);

} // hdf5
} // ft

#endif // FT_HDF5_DATATYPE_HPP
