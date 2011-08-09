FIND_PATH(P4H_INCLUDE_DIRS
  NAMES P4H.h
  HINTS
  PATH_SUFFIXES p4h p4h/P4HCore 
  PATHS
  /usr
  /usr/include
  /usr/local
  /home/malcalde/Projects/rehab8/playforhealth/P4HCore
)

FIND_LIBRARY(P4H_LIBRARY 
  NAMES P4HCore
  HINTS
  PATH_SUFFIXES lib lib/i386-linux-gnu P4HCore P4HGames P4HInput
  PATHS
  /usr/local
  /usr
  /home/malcalde/Projects/rehab8/playforhealth/build
)

set(P4H_PROCESS_INCLUDES P4H_INCLUDE_DIRS)
set(P4H_PROCESS_LIBS P4H_LIBRARY)
set(P4H_LIBRARIES ${P4H_LIBRARY})