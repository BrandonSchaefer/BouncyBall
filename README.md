BouncyBall
==========

Dependencies:

    libsdl2-dev
    libsdl2-image-dev
    libsdl2-mixer-dev
    libsdl2-ttf-dev
    libsigc++-2.0-dev

Compiling:

    mkdir build
    cd build
    cmake .. [-DCMAKE_INSTALL_PREFIX=<path>]
    make -j4
    make install
