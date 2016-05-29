Fintech Tools
=============

Environment Variables
---------------------

This guide may refer to the following environment variables:

- `FINTOOLS_BUILD` - build directory;
- `FINTOOLS_HOME` - installation directory;
- `FINTOOLS_SOURCE` - source directory.

It is recommended that you also modify your environment, so that the binaries installed under
`FINTOOLS_HOME` can be located at runtime:

    PATH=$PATH:$FINTOOLS_HOME/bin; export PATH
    LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$FINTOOLS_HOME/lib; export LD_LIBRARY_PATH

Dependencies
------------

To build Fintools from source, you will need:

- [CMake] - for Makefile generation;
- [GCC] or [Clang] - with support for C++14;
- [Boost] - for additional library dependencies.

Build from Source
-----------------

The following sections assume that `FINTOOLS_SOURCE` is equal to `SOURCE_DIR/fintools`, and that
`FINTOOLS_BUILD` is equal to `BUILD_DIR/fintools`.

### Download ###

Clone the project from the [master repository](http://github.com/swirlycloud/fintools) or your own
personal fork:

    $ cd $SOURCE_DIR
    $ git clone https://github.com/swirlycloud/fintools.git fintools

The `SOURCE_DIR/fintools` directory should now contain the source.

A [Zip archive](https://github.com/swirlycloud/fintools/archive/master.zip) can also be download as
an alternative.

### Configure ###

Configure using `cmake` as follows from the build directory:

    $ cd $BUILD_DIR
    $ mkdir -p fintools
    $ cd fintools
    $ cmake $SOURCE_DIR/fintools -DCMAKE_INSTALL_PREFIX=$FINTOOLS_HOME

This step will produce Unix Makefiles by default. The build-type and compiler can be set using the
following options:

    $ cmake $SOURCE_DIR/fintools -G "Unix Makefiles" \
        -DCMAKE_BUILD_TYPE=RELEASE \
        -DCMAKE_INSTALL_PREFIX=$FINTOOLS_HOME \
        -DCMAKE_C_COMPILER=gcc \
        -DCMAKE_CXX_COMPILER=g++

Build times can be reduced during development by disabling shared libraries and compiler
optimisations:

    $ cmake $SOURCE_DIR/fintools -G "Unix Makefiles" \
        -DCMAKE_BUILD_TYPE=DEBUG \
        -DENABLE_SHARED_LIBS=OFF

Note that both shared and static libraries are built by default.

Architecture-specific optimisation flags can be specified for release builds:

    $ cmake $SOURCE_DIR/fintools -G "Unix Makefiles" \
      -DCMAKE_BUILD_TYPE=RELEASE \
      -DCMAKE_C_FLAGS_RELEASE="-march=native -O3" \
      -DCMAKE_CXX_FLAGS_RELEASE="-march=native -O3"

See [CMake Documentation](https://cmake.org/documentation) for further information.

### Make ###

Compile the code in the build directory using the `make` command:

    $ cd $BUILD_DIR/fintools
    $ make

### Install ###

Install to `CMAKE_INSTALL_PREFIX`:

    $ make install

[Boost]: http://www.boost.org/
[Clang]: http://clang.llvm.org/
[CMake]: http://www.cmake.org/
[GCC]: http://gcc.gnu.org/
