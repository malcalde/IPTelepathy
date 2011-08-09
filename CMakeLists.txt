project(IPTelepathy)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
INCLUDE(CheckIncludeFileCXX)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR})

################# Configuración del proyecto
set(CMAKE_INSTALL_PREFIX "/usr")
set(CMAKE_BUILD_TYPE "debug")
set(CMAKE_C_FLAGS "-g -pg")

set(DST_INCLUDE_DIR "include/p4h")
set(DST_SHARE_DIR "share/p4h")
set(DST_CONFIG_DIR "etc/p4h")

################# Configuración de los modos
add_definitions(-DOGRE_GCC_VISIBILITY)

if(CMAKE_BUILD_TYPE)
  string(TOLOWER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_TOLOWER)

  if(CMAKE_BUILD_TYPE_TOLOWER STREQUAL debug)
    add_definitions(-D_DEBUG  -DDEBUG -g -Wall )	
  endif(CMAKE_BUILD_TYPE_TOLOWER STREQUAL debug)

  if(CMAKE_BUILD_TYPE_TOLOWER STREQUAL release)
    add_definitions(-DNDEBUG)	
  endif(CMAKE_BUILD_TYPE_TOLOWER STREQUAL release)
endif(CMAKE_BUILD_TYPE)

################# Busqueda de librerias
include (CheckIncludeFileCXX)

if(UNIX)
	find_package(PkgConfig REQUIRED)
	PKG_CHECK_MODULES(OGRE REQUIRED OGRE)
	find_library(CEGUIOGRE_LIBRARIES NAMES CEGUIOgreRenderer)
	find_library(BOOSTTHREAD_LIBRARIES NAMES boost_thread-mt)
	
	find_package(P4H REQUIRED)
    find_package(TELEPATHY REQUIRED)
    find_package(GLIB_2_0 REQUIRED)
    find_package(DBUS_GLIB_1 REQUIRED)
endif(UNIX)


################# Entorno del proyecto
# ------------------------- Begin Generic CMake Variable Logging ------------------
# if you are building in-source, this is the same as CMAKE_SOURCE_DIR, otherwise 
# this is the top level directory of your build tree 
MESSAGE( STATUS "CMAKE_BINARY_DIR:         " ${CMAKE_BINARY_DIR} )
# if you are building in-source, this is the same as CMAKE_CURRENT_SOURCE_DIR, otherwise this 
# is the directory where the compiled or generated files from the current CMakeLists.txt will go to 
MESSAGE( STATUS "CMAKE_CURRENT_BINARY_DIR: " ${CMAKE_CURRENT_BINARY_DIR} )
# this is the directory, from which cmake was started, i.e. the top level source directory 
MESSAGE( STATUS "CMAKE_SOURCE_DIR:         " ${CMAKE_SOURCE_DIR} )
# this is the directory where the currently processed CMakeLists.txt is located in 
MESSAGE( STATUS "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR} )
# contains the full path to the top level directory of your build tree 
MESSAGE( STATUS "PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR} )
# contains the full path to the root of your project source directory,
# i.e. to the nearest directory where CMakeLists.txt contains the PROJECT() command 
MESSAGE( STATUS "PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR} )
# set this variable to specify a common place where CMake should put all executable files
# (instead of CMAKE_CURRENT_BINARY_DIR)
MESSAGE( STATUS "EXECUTABLE_OUTPUT_PATH: " ${EXECUTABLE_OUTPUT_PATH} )
# set this variable to specify a common place where CMake should put all libraries 
# (instead of CMAKE_CURRENT_BINARY_DIR)
MESSAGE( STATUS "LIBRARY_OUTPUT_PATH:     " ${LIBRARY_OUTPUT_PATH} )
# tell CMake to search first in directories listed in CMAKE_MODULE_PATH
# when you use FIND_PACKAGE() or INCLUDE()
MESSAGE( STATUS "CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH} )
# this is the complete path of the cmake which runs currently (e.g. /usr/local/bin/cmake) 
MESSAGE( STATUS "CMAKE_COMMAND: " ${CMAKE_COMMAND} )
# this is the CMake installation directory 
MESSAGE( STATUS "CMAKE_ROOT: " ${CMAKE_ROOT} )
# this is the filename including the complete path of the file where this variable is used. 
MESSAGE( STATUS "CMAKE_CURRENT_LIST_FILE: " ${CMAKE_CURRENT_LIST_FILE} )
# this is linenumber where the variable is used
MESSAGE( STATUS "CMAKE_CURRENT_LIST_LINE: " ${CMAKE_CURRENT_LIST_LINE} )
# this is used when searching for include files e.g. using the FIND_PATH() command.
MESSAGE( STATUS "CMAKE_INCLUDE_PATH: " ${CMAKE_INCLUDE_PATH} )
# this is used when searching for libraries e.g. using the FIND_LIBRARY() command.
MESSAGE( STATUS "CMAKE_LIBRARY_PATH: " ${CMAKE_LIBRARY_PATH} )
# the complete system name, e.g. "Linux-2.4.22", "FreeBSD-5.4-RELEASE" or "Windows 5.1" 
MESSAGE( STATUS "CMAKE_SYSTEM: " ${CMAKE_SYSTEM} )
# the short system name, e.g. "Linux", "FreeBSD" or "Windows"
MESSAGE( STATUS "CMAKE_SYSTEM_NAME: " ${CMAKE_SYSTEM_NAME} )
# only the version part of CMAKE_SYSTEM 
MESSAGE( STATUS "CMAKE_SYSTEM_VERSION: " ${CMAKE_SYSTEM_VERSION} )
# the processor name (e.g. "Intel(R) Pentium(R) M processor 2.00GHz") 
MESSAGE( STATUS "CMAKE_SYSTEM_PROCESSOR: " ${CMAKE_SYSTEM_PROCESSOR} )
# is TRUE on all UNIX-like OS's, including Apple OS X and CygWin
MESSAGE( STATUS "UNIX: " ${UNIX} )
# is TRUE on Windows, including CygWin 
MESSAGE( STATUS "WIN32: " ${WIN32} )
# is TRUE on Apple OS X
MESSAGE( STATUS "APPLE: " ${APPLE} )
# is TRUE when using the MinGW compiler in Windows
MESSAGE( STATUS "MINGW: " ${MINGW} )
# is TRUE on Windows when using the CygWin version of cmake
MESSAGE( STATUS "CYGWIN: " ${CYGWIN} )
# is TRUE on Windows when using a Borland compiler 
MESSAGE( STATUS "BORLAND: " ${BORLAND} )
# Microsoft compiler 
MESSAGE( STATUS "MSVC: " ${MSVC} )
MESSAGE( STATUS "MSVC_IDE: " ${MSVC_IDE} )
MESSAGE( STATUS "MSVC60: " ${MSVC60} )
MESSAGE( STATUS "MSVC70: " ${MSVC70} )
MESSAGE( STATUS "MSVC71: " ${MSVC71} )
MESSAGE( STATUS "MSVC80: " ${MSVC80} )
MESSAGE( STATUS "CMAKE_COMPILER_2005: " ${CMAKE_COMPILER_2005} )
# set this to true if you don't want to rebuild the object files if the rules have changed, 
# but not the actual source files or headers (e.g. if you changed the some compiler switches) 
MESSAGE( STATUS "CMAKE_SKIP_RULE_DEPENDENCY: " ${CMAKE_SKIP_RULE_DEPENDENCY} )
# since CMake 2.1 the install rule depends on all, i.e. everything will be built before installing. 
# If you don't like this, set this one to true.
MESSAGE( STATUS "CMAKE_SKIP_INSTALL_ALL_DEPENDENCY: " ${CMAKE_SKIP_INSTALL_ALL_DEPENDENCY} )
# If set, runtime paths are not added when using shared libraries. Default it is set to OFF
MESSAGE( STATUS "CMAKE_SKIP_RPATH: " ${CMAKE_SKIP_RPATH} )
# set this to true if you are using makefiles and want to see the full compile and link 
# commands instead of only the shortened ones 
MESSAGE( STATUS "CMAKE_VERBOSE_MAKEFILE: " ${CMAKE_VERBOSE_MAKEFILE} )
# this will cause CMake to not put in the rules that re-run CMake. This might be useful if 
# you want to use the generated build files on another machine. 
MESSAGE( STATUS "CMAKE_SUPPRESS_REGENERATION: " ${CMAKE_SUPPRESS_REGENERATION} )
# the compiler flags for compiling C sources 
MESSAGE( STATUS "CMAKE_C_FLAGS: " ${CMAKE_C_FLAGS} )
# the compiler flags for compiling C++ sources
MESSAGE( STATUS "CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS} )
# Choose the type of build.  Example: SET(CMAKE_BUILD_TYPE Debug) 
MESSAGE( STATUS "CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE} )
# if this is set to ON, then all libraries are built as shared libraries by default.
MESSAGE( STATUS "BUILD_SHARED_LIBS: " ${BUILD_SHARED_LIBS} )
# the compiler used for C files 
MESSAGE( STATUS "CMAKE_C_COMPILER: " ${CMAKE_C_COMPILER} )
# the compiler used for C++ files 
MESSAGE( STATUS "CMAKE_CXX_COMPILER: " ${CMAKE_CXX_COMPILER} )
# if the compiler is a variant of gcc, this should be set to 1 
MESSAGE( STATUS "CMAKE_COMPILER_IS_GNUCC: " ${CMAKE_COMPILER_IS_GNUCC} )
# if the compiler is a variant of g++, this should be set to 1 
MESSAGE( STATUS "CMAKE_COMPILER_IS_GNUCXX : " ${CMAKE_COMPILER_IS_GNUCXX} )
# the tools for creating libraries 
MESSAGE( STATUS "CMAKE_AR: " ${CMAKE_AR} )
MESSAGE( STATUS "CMAKE_RANLIB: " ${CMAKE_RANLIB} )
# Modules search path 
MESSAGE( STATUS "CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH})

#P4H variables
MESSAGE( STATUS "P4H_INCLUDE_DIR: " ${P4H_INCLUDE_DIR})
MESSAGE( STATUS "P4H_LIBRARY: " ${P4H_LIBRARIES})

#TELEPATHY variables
MESSAGE( STATUS "TELEPATHY_INCLUDE_DIR: " ${TELEPATHY_INCLUDE_DIRS})
MESSAGE( STATUS "TELEPATHY_LIBRARY: " ${TELEPATHY_LIBRARIES})
MESSAGE( STATUS "GLIB2_INCLUDE_DIR: " ${GLIB_2_0_INCLUDE_DIRS})
MESSAGE( STATUS "GLIB2_LIBRARY: " ${GLIB_2_0_LIBRARIES})
MESSAGE( STATUS "GLIB2_AUX_INCLUDE_DIR:" ${GLIB_2_0_LINUX_INCLUDE_DIRS})
MESSAGE( STATUS "DBUS_GLIB_1_INCLUDE_DIR: " ${DBUS_GLIB_1_INCLUDE_DIRS})
MESSAGE( STATUS "DBUS_GLIB_1_LIBRARY: " ${DBUS_GLIB_1_LIBRARIES})

    
# ------------------------- End of Generic CMake Variable Logging -----------

################# Configuración proyecto
aux_source_directory(src SOURCE_FILES)

include_directories(
	${P4H_INCLUDE_DIRS}
	${OGRE_INCLUDE_DIRS}
	${TELEPATHY_INCLUDE_DIRS}
    ${GLIB_2_0_INCLUDE_DIRS}
    ${DBUS_GLIB_1_INCLUDE_DIRS}
    ${GLIB_2_0_LINUX_INCLUDE_DIRS}
	include
)

link_directories(${OGRE_LIBRARY_DIRS}
                 ${TELEPATHY_LIBRARY_DIRS} 
                 ${DBUS_GLIB_1_LIBRARY_DIRS}) 

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} 
	${P4H_LIBRARIES}
	${OGRE_LIBRARIES}
	${BOOSTTHREAD_LIBRARIES}
	${CEGUIOGRE_LIBRARIES}
	${TELEPATHY_LIBRARIES}
    ${GLIB_2_0_LIBRARIES}
    ${DBUS_GLIB_1_LIBRARIES}
)

set_property(TARGET ${PROJECT_NAME} PROPERTY SOVERSION 0.0.1)

################ Preparando las carpetas para la ejecución

execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink 
  ${CMAKE_CURRENT_SOURCE_DIR}/res
  ${CMAKE_CURRENT_BINARY_DIR}/res
)
# execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink 
#   ${CMAKE_CURRENT_SOURCE_DIR}/media
#   ${CMAKE_CURRENT_BINARY_DIR}/media
# )
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink 
  ${CMAKE_CURRENT_SOURCE_DIR}/debian
  ${CMAKE_CURRENT_BINARY_DIR}/debian
)

################# Instalación

install(
  DIRECTORY include/
  DESTINATION ${DST_INCLUDE_DIR}/${PROJECT_NAME}
  FILES_MATCHING PATTERN "*.h"
  PATTERN ".git" EXCLUDE
)

install(
  TARGETS ${PROJECT_NAME} 
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib${LIB_SUFFIX}
  ARCHIVE DESTINATION lib${LIB_SUFFIX}
)

install(
  DIRECTORY res
  DESTINATION ${DST_SHARE_DIR}/${PROJECT_NAME}
  PATTERN ".git" EXCLUDE
)

install(
  DIRECTORY media
  DESTINATION ${DST_SHARE_DIR}/${PROJECT_NAME}
  PATTERN ".git" EXCLUDE
)

