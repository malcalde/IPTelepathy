FIND_PATH(P4H_INCLUDE_DIR
  NAMES P4H.h
  HINTS
  PATH_SUFFIXES include
  PATHS
  /usr
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