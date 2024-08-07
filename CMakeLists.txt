# minimum require
# cmake_minimum_required (VERSION 3.8.1)

# global solution
# project(qtimgui_sln)

# goto subs
# add_subdirectory(examples)
# add_subdirectory(src)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5 COMPONENTS Core Quick Gui Widgets REQUIRED)

# message(CMAKE_SOURCE_DIR===${CMAKE_SOURCE_DIR})

file(GLOB SRCS "*.cpp")
add_library(qtImgui SHARED ${SRCS})

target_link_libraries(qtImgui PUBLIC 
  Qt5::Widgets
  Imguis
)

if(BUILD_EXAMPLE)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR})
  add_subdirectory(examples)
endif()
