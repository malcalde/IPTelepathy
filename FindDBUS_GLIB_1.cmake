include(LibFindMacros)

# Dependencies
# libfind_package(TELEPATHY telepathy-glib)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(DBUS_GLIB_1_PKGCONF dbus-glib-1)

# Include dir
find_path(DBUS_GLIB_1_INCLUDE_DIRS
  NAMES dbus.h dbus/dbus.h
  PATHS ${DBUS_GLIB_1_PKGCONF_INCLUDE_DIRS}
)

# Finally the library itself
find_library(DBUS_GLIB_1_LIBRARY
  NAMES dbus-1
  PATHS ${DBUS_GLIB_1_PKGCONF_LIBRARY_DIRS}
)

if(DBUS_GLIB_1_INCLUDE_DIRS AND DBUS_GLIB_1_LIBRARY)
    set(DBUS_GLIB_1_FOUND TRUE)  
    set(DBUS_GLIB_1_LIBRARY_DIRS "/usr/lib/i386-linux-gnu")
else(DBUS_GLIB_1_INCLUDE_DIRS AND DBUS_GLIB_1_LIBRARY)
    set(DBUS_GLIB_1_FOUND FALSE)
endif(DBUS_GLIB_1_INCLUDE_DIRS AND DBUS_GLIB_1_LIBRARY)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(DBUS_GLIB_1_PROCESS_INCLUDES DBUS_GLIB_1_INCLUDE_DIR)
set(DBUS_GLIB_1_PROCESS_LIBS DBUS_GLIB_1_LIBRARY)
set(DBUS_GLIB_1_LIBRARIES ${DBUS_GLIB_1_LIBRARY})
