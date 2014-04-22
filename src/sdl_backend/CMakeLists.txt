#find_package (PkgConfig)

#set (SDL_BOUNCY_REQUIRED
     #sdl2
     #SDL2_image
     #SDL2_mixer
     #SDL2_ttf
     #sigc++-2.0
    #)

#pkg_check_modules(SDL_BOUNCY REQUIRED ${SDL_BOUNCY_REQUIRED})

set (SDL_BACKEND_SRC
     Color.cpp
     Entity.cpp
     EntityCreator.cpp
     EntityHashTable.cpp
     EntityLayer.cpp
     MainLoop.cpp
     GraphicsRenderer.cpp
     Point.cpp
     Rect.cpp
     RenderableGeometry.cpp
     SDLTimer.cpp
     Size.cpp
     StringTexture.cpp
     StringTextureCreator.cpp
     Timer.cpp
     World.cpp
    )

set (SDL_BACKEND_HDR
     Color.h
     Entity.h
     EntityCreator.h
     EntityHashTable.h
     EntityLayer.h
     MainLoop.h
     GraphicsRenderer.h
     Rect.h
     RenderableGeometry.h
     Renderable.h
     SDLTimer.h
     Size.h
     StringTexture.h
     StringTextureCreator.h
     StringTextureData.h
     Timer.h
     World.h
    )

#include_directories(${BLOCKS_SOURCE_DIR}/src)

include_directories(${SDL_BOUNCY_INCLUDE_DIRS} ${CMAKE_BINARY_DIR})

add_library (sdl_backend ${SDL_BACKEND_SRC} ${SDL_BACKEND_HDR})
target_link_libraries (sdl_backend)
#install (TARGETS ../bouncy-ball DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
