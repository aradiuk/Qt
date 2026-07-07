cmake_minimum_required(VERSION 3.19)
project(RichTextEditor LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
set(CMAKE_AUTORCC ON)

qt_standard_project_setup()

qt_add_executable(RichTextEditor
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    resources.qrc
    finddialog.h finddialog.cpp finddialog.ui
    replacedialog.h replacedialog.cpp replacedialog.ui
)

target_link_libraries(RichTextEditor
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS RichTextEditor
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET RichTextEditor
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
