cmake_minimum_required(VERSION 2.8.3)
set (CMAKE_AUTOMOC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)
project(sara_ui)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS roscpp)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)


catkin_package()

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(${catkin_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})

## Add qt5 UI wrapper
qt5_wrap_ui(MainWindow_UI ui/mainwindow.ui)

add_executable(test_log
  tests/logs.cpp)

add_executable(test_subscribe
  tests/subscribe.cpp)

add_executable(test_list
  tests/list_topic.cpp)

add_executable(sara_ui
    src/main.cpp
    src/mainwindow.cpp
    src/cthreadtopicssubscriber.cpp
    ${MainWindow_UI})
qt5_use_modules(sara_ui Widgets)

## Specify libraries to link a library or executable target against
target_link_libraries(test_log ${catkin_LIBRARIES})
target_link_libraries(test_subscribe ${catkin_LIBRARIES})
target_link_libraries(test_list ${catkin_LIBRARIES})
target_link_libraries(sara_ui ${catkin_LIBRARIES} Qt5::Widgets)
