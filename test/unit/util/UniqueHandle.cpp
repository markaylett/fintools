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
#include <ft/util/UniqueHandle.hpp>

#include <boost/test/unit_test.hpp>

using namespace ft;
using namespace std;

namespace {

int closed{0};

struct TestPolicy {
  using HandleType = int;
  static constexpr HandleType Invalid{-1};
  static void close(HandleType handle) noexcept { ++closed; }
};

using TestHandle = UniqueHandle<TestPolicy>;

} // anonymous

BOOST_AUTO_TEST_SUITE(UniqueHandleSuite)

BOOST_AUTO_TEST_CASE(InvalidConstructCase)
{
  closed = 0;
  {
    TestHandle h;
    BOOST_CHECK_EQUAL(h.get(), -1);
    BOOST_CHECK_EQUAL(*h, -1);
    BOOST_CHECK(!h);
  }
  BOOST_CHECK_EQUAL(closed, 0);
}

BOOST_AUTO_TEST_CASE(ValidConstructCase)
{
  closed = 0;
  {
    TestHandle h{1};
    BOOST_CHECK_EQUAL(h.get(), 1);
    BOOST_CHECK_EQUAL(*h, 1);
    BOOST_CHECK(h);
  }
  BOOST_CHECK_EQUAL(closed, 1);
}

BOOST_AUTO_TEST_CASE(ReleaseCase)
{
  closed = 0;
  {
    TestHandle h{1};
    BOOST_CHECK(h);
    BOOST_CHECK_EQUAL(h.release(), 1);
  }
  BOOST_CHECK_EQUAL(closed, 0);
}

BOOST_AUTO_TEST_CASE(ResetCase)
{
  closed = 0;
  {
    TestHandle h{1};
    BOOST_CHECK(h);
    h.reset();
    BOOST_CHECK(!h);
    BOOST_CHECK_EQUAL(closed, 1);
  }
  BOOST_CHECK_EQUAL(closed, 1);
}

BOOST_AUTO_TEST_CASE(MoveConstructCase)
{
  closed = 0;
  {
    TestHandle h1{1};
    BOOST_CHECK(h1);
    {
      TestHandle h2{move(h1)};
      BOOST_CHECK(!h1);
      BOOST_CHECK(h2);
      BOOST_CHECK_EQUAL(closed, 0);
    }
    BOOST_CHECK_EQUAL(closed, 1);
  }
  BOOST_CHECK_EQUAL(closed, 1);
}

BOOST_AUTO_TEST_CASE(MoveAssignCase)
{
  closed = 0;
  {
    TestHandle h1;
    BOOST_CHECK(!h1);
    {
      TestHandle h2{1};
      BOOST_CHECK(h2);

      h1 = move(h2);
      BOOST_CHECK(h1);
      BOOST_CHECK(!h2);

      BOOST_CHECK_EQUAL(closed, 0);
    }
    BOOST_CHECK_EQUAL(closed, 0);
  }
  BOOST_CHECK_EQUAL(closed, 1);
}

BOOST_AUTO_TEST_SUITE_END()
