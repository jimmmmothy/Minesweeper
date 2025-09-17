cmake_minimum_required(VERSION 3.16)

# Project name and C++ standard
project(Minesweeper LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Instruct CMake to run uic automatically when needed.
set(CMAKE_AUTOUIC ON)

# Find Qt5 files
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Svg REQUIRED)

set(SOURCES board.cpp main.cpp gamewindow.cpp qextendedbutton.cpp)
set(HEADERS board.h gamewindow.h qextendedbutton.h)
set(UI gamewindow.ui)
set(RESOURCES textures.qrc)

# Generate UI and resource files
qt_wrap_ui(UI_HEADERS ${FORMS})
qt_add_resources(RESOURCE_SOURCES ${RESOURCES})

# Define executable
add_executable(Minesweeper
    ${SOURCES}
    ${HEADERS}
    ${UI_HEADERS}
    ${RESOURCE_SOURCES}
)

# Link with Qt modules
target_link_libraries(Minesweeper PRIVATE
    Qt5::Widgets
    Qt5::Svg
)

# Install rules (similar to your .pro file)
if(QNX)
    set(INSTALL_PATH /tmp/${PROJECT_NAME}/bin)
elseif(UNIX AND NOT ANDROID)
    set(INSTALL_PATH /opt/${PROJECT_NAME}/bin)
else()
    set(INSTALL_PATH bin)
endif()

install(TARGETS Minesweeper DESTINATION ${INSTALL_PATH})
