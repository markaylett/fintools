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
#ifndef FT_HDF5_EXCEPTION_HPP
#define FT_HDF5_EXCEPTION_HPP

#include <ft/util/Defs.hpp>

#include <cstddef> // size_t
#include <cstring> // strcpy()
#include <exception>

namespace ft {
namespace hdf5 {

/**
 * Maximum error message length.
 */
constexpr std::size_t MaxErrMsg{255};

class FT_API Exception : public std::exception {
 public:
  Exception() noexcept;

  ~Exception() noexcept override;

  // Copy.
  Exception(const Exception& rhs) noexcept { *this = rhs; }
  Exception& operator=(const Exception& rhs) noexcept
  {
    std::strcpy(what_, rhs.what_);
    return *this;
  }

  // Move.
  Exception(Exception&&) noexcept = default;
  Exception& operator=(Exception&&) noexcept = default;

  const char* what() const noexcept override;

 private:
  char what_[MaxErrMsg + 1];
};

} // hdf5
} // ft

#endif // FT_HDF5_EXCEPTION_HPP
