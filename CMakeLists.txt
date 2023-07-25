cmake_minimum_required(VERSION 3.23)
project(audio_and_video_Qt)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_OSX_ARCHITECTURES x86_64)

set(CMAKE_PREFIX_PATH "/Users/gasoline/Qt5.12.12/5.12.12/clang_64/lib/cmake")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        MultimediaWidgets
        REQUIRED)

add_executable(audio_and_video_Qt main.cpp)
target_link_libraries(audio_and_video_Qt
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Multimedia
        Qt5::MultimediaWidgets
        )

