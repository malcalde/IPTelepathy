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


#include "IPTelepathyPlugin.h"
#include "P4HPlugin.h"
#include "P4HEventManager.h"
#include "P4HTools.h"

namespace P4H 
{
    const String sPluginName = "IPTelepathyPlugin";

    //---------------------------------------------------------------------
    IPTelepathyPlugin::IPTelepathyPlugin()
    {
    }
    //---------------------------------------------------------------------
    const String& IPTelepathyPlugin::getName() const
    {
      return sPluginName;
    }
    //---------------------------------------------------------------------
    bool IPTelepathyPlugin::onInstall()
    {
        P4H_LOG( String("*-*-*-*-*-*IPTelepathyPlugin: install"));

        return true;
    }
    //---------------------------------------------------------------------
    bool IPTelepathyPlugin::onInitialise()
    {
        P4H_LOG( "*-*-*-*-*-*IPTelepathyPlugin: initialise");

        EventManager::getSingleton().addCallback( 
            "IPFrameEvent", 
            CallbackInfo(
                this, 
                CallbackInfo::EventCallback(this, &IPTelepathyPlugin::onFrameCallback)
            )
        );

        return true;
    }
    //---------------------------------------------------------------------
    bool IPTelepathyPlugin::onReInitialise()
    {
        P4H_LOG( "*-*-*-*-*-*IPTelepathyPlugin: reinitialise");

        return true;
    }
    //---------------------------------------------------------------------
    bool IPTelepathyPlugin::onShutdown()
    {
        //shutdown called - unregister stuff here

        P4H_LOG( "*-*-*-*-*-*IPTelepathyPlugin: shutdown");

        return true;
    }
    //---------------------------------------------------------------------
    bool IPTelepathyPlugin::onUninstall()
    {
        //uninstall called - delete stuff here

        P4H_LOG( "*-*-*-*-*-*IPTelepathyPlugin: uninstall");

        return true;
    }
    //---------------------------------------------------------------------
    bool IPTelepathyPlugin::onExecute()
    {
        P4H_LOG( "*-*-*-*-*-*IPTelepathyPlugin: Execute");

        return true;
    }
    //---------------------------------------------------------------------
    bool IPTelepathyPlugin::onPause()
    {
        P4H_LOG( "*-*-*-*-*-*IPTelepathyPlugin: pause" );

        return true;
    }
    //---------------------------------------------------------------------
    void IPTelepathyPlugin::onFrameCallback(Event * event)
    {
        IPFrameEvent* frameEvent = static_cast<IPFrameEvent*> (event);

        P4H_LOG( String("*-*-*-*-*-*IPTelepathyPlugin: onFrameCallback") + stringify(frameEvent->timeSinceLastFrame) );
    }

}

