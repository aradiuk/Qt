cmake_minimum_required(VERSION 3.19)
project(TcpChatServer LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Network Widgets)

qt_standard_project_setup()

qt_add_executable(TcpChatServer
    WIN32 MACOSX_BUNDLE
    main.cpp
    dialog.cpp
    dialog.h
    dialog.ui
    server.h server.cpp
)

target_link_libraries(TcpChatServer
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Network
)

install(TARGETS TcpChatServer
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET TcpChatServer
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
