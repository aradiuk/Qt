cmake_minimum_required(VERSION 3.16)

project(TvRemoteControl VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.10)

# Content of downloaded design from Figma to Qt or similar
if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/importedcontent/CMakeLists.txt")
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/importedcontent)
endif()

qt_add_executable(appTvRemoteControl
    main.cpp
)

qt_add_qml_module(appTvRemoteControl
    URI TvRemoteControl
    QML_FILES
        Main.qml
        RESOURCES images/cast_connected.svg images/cast_white.svg images/closed_caption.svg images/closed_caption_white.svg images/fast_forward.svg images/fast_rewind.svg images/hdr_on.svg images/hdr_on_white.svg images/mic.svg images/mic_white.svg images/minus.svg images/play_pause.svg images/plus.svg images/power.svg images/settings.svg images/speaker.svg images/speaker_muted.svg images/speaker_muted_white.svg images/volume_down.svg images/volume_up.svg
        RESOURCES fonts/Silkscreen/Silkscreen-Bold.ttf fonts/Silkscreen/Silkscreen-Regular.ttf
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appTvRemoteControl PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appTvRemoteControl
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appTvRemoteControl
    PRIVATE Qt6::Quick
)

install(TARGETS appTvRemoteControl
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
