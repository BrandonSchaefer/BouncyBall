configure_file(bouncy-ball.desktop.in ${CMAKE_CURRENT_BINARY_DIR}/bouncy-ball.desktop @ONLY)
configure_file(bouncy-ball.svg ${CMAKE_CURRENT_BINARY_DIR}/bouncy-ball.svg @ONLY)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/bouncy-ball.desktop
        DESTINATION ${CMAKE_INSTALL_PREFIX}/share/applications
       )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/bouncy-ball.svg
        DESTINATION ${CMAKE_INSTALL_PREFIX}/share/icons/hicolor/scalable/apps
       )
