cmake_minimum_required(VERSION 3.19)
project(SecurityPanel LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(SecurityPanel
    WIN32 MACOSX_BUNDLE
    main.cpp
    dialog.cpp
    dialog.h
    dialog.ui
)

target_link_libraries(SecurityPanel
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS SecurityPanel
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET SecurityPanel
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
