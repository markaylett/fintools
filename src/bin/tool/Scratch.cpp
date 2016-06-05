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
#include <ft/hdf5/File.hpp>

#include <H5Epublic.h>

#include <exception>
#include <iostream>

using namespace ft;
using namespace std;

int main(int argc, char* argv[])
{
  int ret = 1;
  try {
    // Suppress error logging.
    H5Eset_auto2(H5E_DEFAULT, nullptr, nullptr);
    auto file = createHdf5File("scratch.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    ret = 0;
  } catch (const exception& e) {
    cerr << "exception: " << e.what() << endl;
  }
  return ret;
}
