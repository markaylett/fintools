#!/bin/sh
set -e
format=${CLANG_FORMAT:-clang-format}
find include src test \( -name "*.[ch]pp" \) -exec $format -i --style=file {} \;
