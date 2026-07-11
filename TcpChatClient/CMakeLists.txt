cmake_minimum_required(VERSION 3.19)
project(TcpChatClient LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Network Widgets)

qt_standard_project_setup()

qt_add_executable(TcpChatClient
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

)

target_link_libraries(TcpChatClient
    PRIVATE
        Qt::Core
        Qt::Network
        Qt::Widgets
)

install(TARGETS TcpChatClient
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET TcpChatClient
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
