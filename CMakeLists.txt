cmake_minimum_required(VERSION 3.16)

project(HealthNotifier VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Multimedia)

qt_standard_project_setup()
set(CMAKE_AUTORCC ON)

set(PROJECT_SOURCES
    main.cpp
    wstart.cpp
    wstart.h
    wstart.ui
    rec.qrc
)

if(WIN32)
    # Equivalent of qmake's RC_ICONS
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/icon.rc"
        "IDI_ICON1 ICON \"${CMAKE_CURRENT_SOURCE_DIR}/data/icon.ico\"\n")
    list(APPEND PROJECT_SOURCES "${CMAKE_CURRENT_BINARY_DIR}/icon.rc")
endif()

qt_add_executable(HealthNotifier ${PROJECT_SOURCES})

set_target_properties(HealthNotifier PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

target_link_libraries(HealthNotifier PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Multimedia
)

include(GNUInstallDirs)
install(TARGETS HealthNotifier
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
