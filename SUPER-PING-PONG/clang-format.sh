#!/bin/bash
set -e

clang-format-5.0 -i -style=file ./Classes/*.h
clang-format-5.0 -i -style=file ./Classes/*.cpp

echo "Done"

