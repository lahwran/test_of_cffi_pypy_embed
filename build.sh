#!/bin/bash

source ve/bin/activate
mkdir lib/
mkdir build/
python py/build.py
gcc src/main.c -Iinclude -o derp -Llib -lmy_plugin
cp ~/CachedDownloads/pypy-c-jit-82316-4c30448f0457-osx64/bin/libpypy-c.dylib lib/
cp ~/CachedDownloads/pypy-c-jit-82316-4c30448f0457-osx64/lib* lib/ -r
DYLD_LIBRARY_PATH="$DYLD_LIBRARY_PATH:$PWD/lib" ./derp
