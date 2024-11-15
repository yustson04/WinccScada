Header file location
Project folder->library

Install C Debugger
    Link: msys2.org
1. Install UCRT    
2. Install mingw-64 GCC (GNU Compiler Collection )
    $ pacman -S mingw-w64-ucrt-x86_64-gcc
3. Install toolchain
    pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
