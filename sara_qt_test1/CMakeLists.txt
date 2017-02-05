cmake_minimum_required(VERSION 2.8.3)
set (CMAKE_AUTOMOC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)
project(Sara_QT_Test1)

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
qt5_wrap_ui(MainWindow_UI src/mainwindow.ui)

add_executable(simulate_log
  src/logs.cpp)

add_executable(subscriber
  src/subscribe.cpp)

add_executable(list_topics
  src/list_topic.cpp)

add_executable(sara_qt_window
    src/main.cpp
    src/mainwindow.cpp
    ${MainWindow_UI})
qt5_use_modules(sara_qt_window Widgets)

## Specify libraries to link a library or executable target against
target_link_libraries(sara_qt_window ${catkin_LIBRARIES} Qt5::Widgets)
target_link_libraries(simulate_log ${catkin_LIBRARIES})
target_link_libraries(subscriber ${catkin_LIBRARIES})
target_link_libraries(list_topics ${catkin_LIBRARIES})
