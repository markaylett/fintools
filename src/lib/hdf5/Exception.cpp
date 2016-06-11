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
#include <ft/hdf5/Exception.hpp>

#include <H5Epublic.h>

using namespace std;

namespace ft {
namespace hdf5 {
namespace {
herr_t setError(unsigned n, const H5E_error2_t* errDesc, void* clientData) noexcept
{
  auto* buf = static_cast<char*>(clientData);
  strncpy(buf, errDesc->desc, MaxErrMsg);
  buf[MaxErrMsg] = '\0';
  return 0;
}
} // anonymous

Exception::Exception() noexcept
{
  // FIXME: is this the best approach? Is it thread-safe?
  hid_t stack{H5Eget_current_stack()};
  // Pop all but inner-most frame, i.e., the root cause.
  H5Epop(stack, H5Eget_num(stack) - 1);
  // Get inner-most error message.
  H5Ewalk2(stack, H5E_WALK_DOWNWARD, setError, what_);
  // Free stack.
  H5Eclose_stack(stack);
}

Exception::~Exception() noexcept = default;

const char* Exception::what() const noexcept
{
  return what_;
}

} // hdf5
} // ft
