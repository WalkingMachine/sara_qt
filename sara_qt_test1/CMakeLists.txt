cmake_minimum_required(VERSION 2.8.3)
set (CMAKE_AUTOMOC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)
project(Sara_QT_Test1)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)

catkin_package()

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(${catkin_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(Sara_QT_Test1 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Add qt5 UI wrapper
qt5_wrap_ui(MainWindow_UI src/mainwindow.ui)

## Declare a C++ executable
add_executable(sara_qt_window
  src/main.cpp
  src/mainwindow.cpp
  ${MainWindow_UI}
)

qt5_use_modules(sara_qt_window Widgets)

## Specify libraries to link a library or executable target against
target_link_libraries(sara_qt_window ${catkin_LIBRARIES} Qt5::Widgets)
