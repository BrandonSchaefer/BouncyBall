find_package (PkgConfig)

set (SDL_BOUNCY_REQUIRED
     sdl2
     SDL2_image
     SDL2_mixer
     SDL2_ttf
     sigc++-2.0
    )

pkg_check_modules(SDL_BOUNCY REQUIRED ${SDL_BOUNCY_REQUIRED})

set (SDL_BOUNCY_SRC
     Ball.cpp
     BouncyBallMain.cpp
     BouncyGameData.cpp
     Button.cpp
     LosingScreen.cpp
     Main.cpp
     PauseMenu.cpp
     Paddle.cpp
     PaddleAI.cpp
     Score.cpp
     TitleScreen.cpp
    )

set (SDL_BOUNCY_HDR
     Ball.h
     BouncyBallMain.h
     BouncyGameData.h
     Button.h
     LosingScreen.h
     Main.h
     PauseMenu.h
     Paddle.h
     PaddleAI.h
     Score.h
     TitleScreen.h
    )

add_subdirectory(sdl_backend)

add_executable(../bouncy-ball ${SDL_BOUNCY_SRC} ${SDL_BOUNCY_HDR})

include_directories(${SDL_BOUNCY_INCLUDE_DIRS} ${CMAKE_BINARY_DIR} ${SDL_BOUNCY_SOURCE_DIR}/src)
link_directories(${SDL_BOUNCY_LIBRARY_DIRS})

target_link_libraries (../bouncy-ball sdl_backend ${SDL_BOUNCY_LIBRARIES})

install (TARGETS ../bouncy-ball DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
