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
#ifndef FT_UTIL_UNIQUEHANDLE_HPP
#define FT_UTIL_UNIQUEHANDLE_HPP

#include <utility> // swap()

#include <unistd.h> // close()

namespace ft {

/**
 * UniqueHandle manages unique ownership of file, socket, and other descriptors in the same way that
 * unique_ptr does for pointer types.
 */
template <typename HandlePolicyT>
class UniqueHandle {
 public:
  using HandleType = typename HandlePolicyT::HandleType;
  static constexpr HandleType Invalid{HandlePolicyT::Invalid};

  explicit UniqueHandle(HandleType handle = Invalid) noexcept : handle_{handle} {}
  ~UniqueHandle() noexcept
  {
    if (handle_ != Invalid) {
      HandlePolicyT::close(handle_);
    }
  }

  // Copy.
  UniqueHandle(const UniqueHandle&) = delete;
  UniqueHandle& operator=(const UniqueHandle&) = delete;

  // Move.
  UniqueHandle(UniqueHandle&& rhs) noexcept : handle_{rhs.release()} {}
  UniqueHandle& operator=(UniqueHandle&& rhs) noexcept
  {
    reset(rhs.release());
    return *this;
  }
  HandleType get() const noexcept { return handle_; }
  HandleType operator*() const noexcept { return handle_; }
  explicit operator bool() const noexcept { return handle_ != Invalid; }

  HandleType release() noexcept
  {
    HandleType handle{handle_};
    handle_ = Invalid;
    return handle;
  }
  void reset(HandleType handle = Invalid) noexcept
  {
    std::swap(handle_, handle);
    if (handle != Invalid) {
      HandlePolicyT::close(handle);
    }
  }
  void swap(UniqueHandle& rhs) noexcept { std::swap(handle_, rhs.handle_); }

 private:
  HandleType handle_{Invalid};
};

// FIXME: consider moving this into separate file.
struct PosixFilePolicy {
  using HandleType = int;
  static constexpr HandleType Invalid{-1};
  static void close(HandleType handle) noexcept { ::close(handle); }
};

using PosixFile = UniqueHandle<PosixFilePolicy>;

} // ft

#endif // FT_UTIL_UNIQUEHANDLE_HPP
