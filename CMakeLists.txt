cmake_minimum_required(VERSION 3.5)
set (CMAKE_AUTOMOC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)
project(sara_ui)


set(THREADS_PREFER_PTHREAD_FLAG ON)

## Find catkin macros and libraries
find_package(Threads REQUIRED)
find_package(catkin REQUIRED COMPONENTS roscpp)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(message_generation REQUIRED
	CATKIN_DEPENDS message_runtime
)

add_message_files(
  FILES
  sara_launch.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

set(CMAKE_CXX_STANDARD 11)

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

add_executable(sara_ui_helper
  src/helper.cpp
  src/helper_funct.cpp)

add_executable(sara_ui
    src/main.cpp
    src/mainwindow.cpp
    src/CThreadDiagnostics.cpp
    src/CScenarios.cpp
    src/CScenario.cpp
    src/helper_funct.cpp
    ${MainWindow_UI})
qt5_use_modules(sara_ui Widgets)

## For support Yaml CPP
target_link_libraries(${PROJECT_NAME} yaml-cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(test_log ${catkin_LIBRARIES})
target_link_libraries(test_subscribe ${catkin_LIBRARIES})
target_link_libraries(test_list ${catkin_LIBRARIES})
target_link_libraries(sara_ui ${catkin_LIBRARIES} Qt5::Widgets)
target_link_libraries(sara_ui_helper ${catkin_LIBRARIES} Threads::Threads)
