cmake_minimum_required(VERSION 3.14)

project(TTS VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        qml.qrc
        Menu.h
        Menu.cpp
        Handler.h
        Handler.cpp
        Worker.h
        Worker.cpp
        Wav.cpp
        Wav.h
        DataBase.h
        DataBase.cpp
        TextData.h
        TextData.cpp
)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "C:/Users/Admin/Desktop/APP")
endif()

set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/appicon.rc")

add_executable(TTS WIN32
  ${PROJECT_SOURCES}
  ${APP_ICON_RESOURCE_WINDOWS}
)

target_link_libraries(TTS
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)


# bangvv version1
