#!/bin/sh

gccwflags="-Wall -Wextra -pedantic"
gccflags="-O3 -ansi $gccwflags"
sourcefilesi="../smpi/vm.c"
sourcefilesc="smpc/smpc.c"

buildfolder="smpc_unix"

if which gcc >/dev/null; then
  echo GCC is installed
else
  echo Please have GCC installed
  exit 1
fi

rm -rf $buildfolder && # remove previous build
mkdir $buildfolder &&

cd $buildfolder &&

# Build SMP Bytecode Interpreter

gcc $gccflags -c $sourcefilesi &&
gcc -s -shared -fPIC -static *.o -o libsmpi.so &&

gcc $gccflags -c smpi.c &&
gcc -s smpi.o -o smpi -static -L$PWD -lsmpi -Wl,-rpath,'$ORIGIN' &&

rm -f *.o &&

# Build SMP Compiler

cd .. &&

echo Build successful
