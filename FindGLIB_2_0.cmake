include(LibFindMacros)

# Dependencies
# libfind_package(TELEPATHY telepathy-glib)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(GLIB_PKGCONF glib-2.0)

MESSAGE( STATUS "GLIB:" ${GLIB_PKGCONF_INCLUDE_DIRS})
MESSAGE( STATUS "GLIB:" ${GLIB_PKGCONF_LIBRARY_DIRS})

find_path(GLIB_2_0_INCLUDE_DIRS
 NAMES glib.h 
 PATHS ${GLIB_PKGCONF_INCLUDE_DIRS}
)

find_path(GLIB_2_0_LINUX_INCLUDE_DIRS
 names glibconfig.h
 PATHS ${GLIB_PKGCONF_INCLUDE_DIRS}
)

# Finally the library itself
find_library(GLIB_2_0_LIBRARY
  NAMES glib-2.0
  PATHS ${GLIB_PKGCONF_LIBRARY_DIRS}
)

if(GLIB_2_0_INCLUDE_DIRS AND GLIB_2_0_LIBRARY)
    set(GLIB_2_0_FOUND TRUE)  
    set(GLIB_2_0_LIBRARY_DIRS)
else(GLIB_2_0_INCLUDE_DIRS AND GLIB_2_0_LIBRARY)
    set(GLIB_2_0_FOUND FALSE)
endif(GLIB_2_0_INCLUDE_DIRS AND GLIB_2_0_LIBRARY)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(GLIB_2_0_PROCESS_INCLUDES GLIB_INCLUDE_DIR GLIB_2_0_LINUX_INCLUDE_DIRS)
set(GLIB_2_0_PROCESS_LIBS GLIB_LIBRARY)
set(GLIB_2_0_LIBRARIES ${GLIB_2_0_LIBRARY})

MESSAGE( STATUS "GLIB(.h):" ${GLIB_2_0_INCLUDE_DIRS})
MESSAGE( STATUS "GLIB(.h):" ${GLIB_2_0_LINUX_INCLUDE_DIRS})
MESSAGE( STATUS "GLIB(.so):" ${GLIB_2_0_LIBRARY})
 