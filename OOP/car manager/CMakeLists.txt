cmake_minimum_required(VERSION 3.26)
project(car_manager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt@5")


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(car_manager main.cpp
        domain.h
        service.h
        repository.h
        gui.h
        domain.cpp
        service.cpp
        repository.cpp
        gui.cpp
        repository.cpp)
target_link_libraries(car_manager
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

