/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  MiguelAlcalde <malcalde@ibit.org>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef IPTELEPATHYPLUGINPREREQUISITES_H
#define IPTELEPATHYPLUGINPREREQUISITES_H

#include "OgrePrerequisites.h"
#include "Ogre.h"
#include "P4H.h"

#if (OGRE_PLATFORM == OGRE_PLATFORM_WIN32) && !defined(OGRE_STATIC_LIB)
#   ifdef IPTESTPLUGIN_EXPORTS
#       define _IPTelepathyPluginExport __declspec(dllexport)
#   else
#       if defined( __MINGW32__ )
#           define _IPTelepathyPluginExport
#       else
#    		define _IPTelepathyPluginExport __declspec(dllimport)
#       endif
#   endif
#elif defined ( OGRE_GCC_VISIBILITY )
#    define _IPTelepathyPluginExport  __attribute__ ((visibility("default")))
#else
#   define _IPTelepathyPluginExport
#endif

#endif // IPTELEPATHYPLUGINPREREQUISITES_H
