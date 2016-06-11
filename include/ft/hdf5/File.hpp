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
#ifndef FT_HDF5_FILE_HPP
#define FT_HDF5_FILE_HPP

#include <ft/util/Defs.hpp>
#include <ft/util/UniqueHandle.hpp>

#include <H5Ppublic.h>

namespace ft {

struct Hdf5FilePolicy {
  using HandleType = hid_t;
  static constexpr HandleType Invalid{H5I_INVALID_HID};
  static void close(HandleType handle) noexcept { H5Fclose(handle); }
};

using Hdf5File = UniqueHandle<Hdf5FilePolicy>;

FT_API Hdf5File createHdf5File(const char* name, unsigned flags, hid_t createId = H5P_DEFAULT,
                               hid_t accessId = H5P_DEFAULT);

} // ft

#endif // FT_HDF5_FILE_HPP
