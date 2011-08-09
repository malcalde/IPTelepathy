include(LibFindMacros)

# Dependencies
# libfind_package(TELEPATHY telepathy-glib)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(TELEPATHY_PKGCONF telepathy-glib)

# Include dir
find_path(TELEPATHY_INCLUDE_DIRS
  NAMES telepathy-glib.h telepathy-glib/telepathy-glib.h
  PATHS ${TELEPATHY_PKGCONF_INCLUDE_DIRS}
)

# Finally the library itself
find_library(TELEPATHY_LIBRARY
  NAMES telepathy-glib
  PATHS ${TELEPATHY_PKGCONF_LIBRARY_DIRS}
)

if(TELEPATHY_INCLUDE_DIRS AND TELEPATHY_LIBRARY)
    set(TELEPATHY_FOUND TRUE)  
    set(TELEPATHY_LIBRARY_DIRS "/usr/lib/i386-linux-gnu")
else(TELEPATHY_INCLUDE_DIRS AND TELEPATHY_LIBRARY)
    set(TELEPATHY_FOUND FALSE)
endif(TELEPATHY_INCLUDE_DIRS AND TELEPATHY_LIBRARY)


# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(TELEPATHY_PROCESS_INCLUDES TELEPATHY_INCLUDE_DIR)
set(TELEPATHY_PROCESS_LIBS TELEPATHY_LIBRARY)
set(TELEPATHY_LIBRARIES ${TELEPATHY_LIBRARY})
