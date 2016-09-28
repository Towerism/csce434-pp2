# csce434-pp3
## Building and testing
To build
```
$ make
```

To test
```
$ make test
```

## CMake build system
I decided I didn't like all the files being in the top-level project directory, nor
did I like the ast files being scrunched up into a few separate files. I
switched to the CMake build system to solve both of these complaints elegantly.
As a bonus, CMake automatically takes care of header dependencies.

I kept a Makefile in the root project directory that interfaces with the CMake
build system, so one can simply call `make` without worrying about the CMake
build system. Plus the root Makefile will copy the generated `dcc` executable
from the build tree into the top-level directory.

## General design
The scope analysis phase occurs in two phases. First the symbol table is built.
Each node that worries about declarations or statements has its own local symbol
table. The root symbol table is exposed as a static variable in program which
allows lower nodes to make queries about the classes and interfaces declared in
the program. In this stage, redefinitions and virtual function signature
mismatches are caught. The rest of scope analysis occurs in the second pass,
including parent class signature mismatches, parent class variable
redefinitions, and missing types.

## Virtual function and super class separation
My initial design did both virtual function and super class signature
mismatch checking in the second pass. This caused problems though as `bad6.decaf`
would like virtual function signature mismatch checking to be done before super
class checking happens. Thus I moved the virtual function checking into the
first pass, but kept super class checking in the second pass.
