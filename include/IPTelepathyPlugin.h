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


#ifndef IPTELEPATHYPLUGIN_H
#define IPTELEPATHYPLUGIN_H

#include "P4H.h"
#include "IPTelepathyPluginPrerequisites.h"

/**
 * @addtogroup P4H
 * @{
 */

/** Play for health namespace */
namespace P4H {
	/** P4H Integration telepathy framework plugin */
    class IPTelepathyPlugin : public Plugin 
    {
      public:
		/** Default constructor */  
        IPTelepathyPlugin();
		/** Virtual destructor */
		virtual ~IPTelepathyPlugin();

		/** return (unique) plugin name */
        virtual const String& getName() const;

		/** Plugin lifecycle: install */
        virtual bool onInstall();

		/** Plugin lifecycle: initialise */
        virtual bool onInitialise();
		
		/** Plugin lifecycle: re-entry install */
        virtual bool onReInitialise();

		/** Plugin lifecycle: shutdown */
        virtual bool onShutdown();

		/** Plugin lifecycle: uninstall */
        virtual bool onUninstall();

		/** Plugin lifecycle: execute */
        virtual bool onExecute();

		/** Plugin lifecycle: pause */
        virtual bool onPause();

		/** Render loop callback */
        void onFrameCallback(Event * event);
		
	protected:
		/** Plugin dependencies controller */
		PluginPtr mDepPlugin; 
    };//end-class IPTelepathylugin
    
} //end-namespace

/** @} End doxygen group P4H */

#endif // IPTELEPATHYPLUGIN_H
