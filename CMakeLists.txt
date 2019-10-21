cmake_minimum_required(VERSION 3.1.3)
project(PulseViewTrunk LANGUAGES CXX VERSION 1.1.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Boost "1.53" COMPONENTS filesystem serialization system REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Concurrent REQUIRED)
find_package(Qt5Qml REQUIRED)
find_package(Qt5Svg REQUIRED)
find_package(Qt5UiTools REQUIRED)
find_package(Qt5Xml REQUIRED)

include(GNUInstallDirs)

find_library(GLIB_LIBRARIES glib-2.0)
find_library(GLIBMM_LIBRARIES NAMES glibmm-2.4 glibmm-2.44)
find_library(SIGCPP_LIBRARIES sigc-2.4)
find_library(LIBSIGROK_LIBRARIES sigrok)
find_library(LIBSIGROKCXX_LIBRARIES sigrokcxx)
find_library(LIBSIGROK_DECODE_LIBRARIES sigrokdecode)

find_package(PkgConfig)
pkg_check_modules(PYTHON REQUIRED python3)
pkg_check_modules(GLIB REQUIRED glib-2.0)
pkg_check_modules(GLIBMM REQUIRED glibmm-2.4)
pkg_check_modules(SIGCPP REQUIRED sigc++-2.0)
pkg_check_modules(LIBSIGROK REQUIRED libsigrok)
pkg_check_modules(LIBSIGROKCXX REQUIRED libsigrokcxx)
pkg_check_modules(LIBSIGROK_DECODE REQUIRED libsigrokdecode)

FILE(GLOB SRC_LIST src/*.cpp
                   src/*.h
                   src/detail/*.cpp
                   src/detail/*.h)

FILE(GLOB PULSEVIEW pulseview/pv/*.cpp
                pulseview/pv/*.hpp
                pulseview/pv/*/*.cpp
                pulseview/pv/*/*.hpp
                pulseview/pv/*/*/*.cpp
                pulseview/pv/*/*/*.hpp)

FILE(GLOB UI_FILES ui/*.ui) # TODO: add pulseview UI files here
qt5_wrap_ui(PROJECT_UI ${UI_FILES})

add_definitions(-DQT_NO_KEYWORDS)
add_definitions(-D__STDC_LIMIT_MACROS)
add_definitions(-Wall -Wextra)
add_definitions(-std=c++11)
add_definitions(-DBOOST_MATH_DISABLE_FLOAT128=1)
add_definitions(-DENABLE_DECODE)

configure_file (
	${CMAKE_CURRENT_SOURCE_DIR}/pulseview/config.h.in
	${PROJECT_BINARY_DIR}/config.h
)

add_executable(${PROJECT_NAME}
        ${SRC_LIST}
        ${PROJECT_UI}
        ${PULSEVIEW}
)

target_include_directories(${PROJECT_NAME}
        PRIVATE
                # pulseview
                ${CMAKE_CURRENT_SOURCE_DIR}/pulseview/pv
                ${CMAKE_CURRENT_SOURCE_DIR}/pulseview/pv/binding
                ${CMAKE_CURRENT_SOURCE_DIR}/pulseview/pv/data
                ${CMAKE_CURRENT_SOURCE_DIR}/pulseview/pv/devices
                ${CMAKE_CURRENT_SOURCE_DIR}/pulseview/pv/dialogs
                ${CMAKE_CURRENT_SOURCE_DIR}/pulseview/pv/popups
                ${CMAKE_CURRENT_SOURCE_DIR}/pulseview/pv/prop
                ${CMAKE_CURRENT_SOURCE_DIR}/pulseview/pv/toolbars
                ${CMAKE_CURRENT_SOURCE_DIR}/pulseview/pv/views
                ${CMAKE_CURRENT_SOURCE_DIR}/pulseview/pv/widgets
                ${CMAKE_CURRENT_SOURCE_DIR}/pulseview/pv/data/decode
                ${CMAKE_CURRENT_SOURCE_DIR}/pulseview/pv/views/trace
                ${CMAKE_CURRENT_SOURCE_DIR}/pulseview

                ${PROJECT_BINARY_DIR}

                # project
                ${CMAKE_CURRENT_SOURCE_DIR}/src

                # 3rd party
                ${Qt5Widgets_INCLUDE_DIRS}
                ${Qt5Concurrent_INCLUDE_DIRS}
                ${Qt5Qml_INCLUDE_DIRS}
                ${Qt5UiTools_INCLUDE_DIRS}
                ${Qt5Svg_INCLUDE_DIRS}
		${Qt5Xml_INCLUDE_DIRS}
                ${LIBSIGROK_DECODE_INCLUDE_DIRS}
                ${LIBSIGROKCXX_INCLUDE_DIRS}
                ${LIBSIGROK_INCLUDE_DIRS}
                ${GLIB_INCLUDE_DIRS}
                ${GLIBCONFIG_INCLUDE_DIRS}
                ${GLIBMM_INCLUDE_DIRS}
                ${GLIBMMCONFIG_INCLUDE_DIRS}
                ${SIGCPP_INCLUDE_DIRS}
                ${SIGCPPCONFIG_INCLUDE_DIRS}
)

link_directories(
        ${Boost_LIBRARY_DIRS}
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
                ${Qt5Widgets_LIBRARIES}
                ${Qt5Concurrent_LIBRARIES}
                ${Qt5Qml_LIBRARIES}
                ${Qt5UiTools_LIBRARIES}
                ${Qt5Svg_LIBRARIES}
                ${Qt5Xml_LIBRARIES}
                ${PYTHON_LIBRARIES}
                ${LIBSIGROK_LIBRARIES}
                ${LIBSIGROKCXX_LIBRARIES}
                ${LIBSIGROK_DECODE_LIBRARIES}
                ${GLIBMM_LIBRARIES}
                ${SIGCPP_LIBRARIES}
                ${GLIB_LIBRARIES}
                ${Boost_LIBRARIES}
)

if (NOT WIN32)
	find_library(PTHREAD_LIBRARIES pthread)
	if (PTHREAD_LIBRARIES)
                target_link_libraries(${PROJECT_NAME} PRIVATE ${PTHREAD_LIBRARIES})
	else()
		message(FATAL_ERROR "pthread libraries not found!")
	endif()
endif()
