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

#include <telepathy-glib/telepathy-glib.h>

#include "IPTelepathyPlugin.h"
#include "P4HPlugin.h"
#include "P4HEventManager.h"
#include "P4HTools.h"

using namespace P4H;

const String sPluginName = "IPTelepathy";

static GMainLoop* tp_loop = NULL;
static TpDBusDaemon* tp_bus= NULL;
static TpConnection* tp_conn = NULL;

//---------------------------------------------------------------------------
// Telepathy funcions (implementation)
//---------------------------------------------------------------------------
static void tp_connection_ready (
    TpConnectionManager   *cm,
    const GError      *in_error,
    gpointer       user_data,
    GObject       *weak_obj
);

static void tp_got_connection_managers (
    TpConnectionManager    * const * cms,
    gsize           ncms,
    const GError       *error,
    gpointer        user_data,
    GObject        *weak_object
);

//---------------------------------------------------------------------------
// IPTelepathyPlugin methods
//---------------------------------------------------------------------------
IPTelepathyPlugin::IPTelepathyPlugin()
{
}
//---------------------------------------------------------------------------
const String& IPTelepathyPlugin::getName() const
{
    return sPluginName;
}
//---------------------------------------------------------------------------
bool IPTelepathyPlugin::onInstall()
{
    P4H_LOG( String("*-*-*-*-*-*IPTelepathyPlugin: install"));

    return true;
}
//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
bool IPTelepathyPlugin::onReInitialise()
{
    P4H_LOG( "*-*-*-*-*-*IPTelepathyPlugin: reinitialise");

    return true;
}
//---------------------------------------------------------------------------
bool IPTelepathyPlugin::onShutdown()
{
    //shutdown called - unregister stuff here

    P4H_LOG( "*-*-*-*-*-*IPTelepathyPlugin: shutdown");

    return true;
}
//---------------------------------------------------------------------------
bool IPTelepathyPlugin::onUninstall()
{
    //uninstall called - delete stuff here

    P4H_LOG( "*-*-*-*-*-*IPTelepathyPlugin: uninstall");

    return true;
}
//---------------------------------------------------------------------------
bool IPTelepathyPlugin::onExecute()
{
    P4H_LOG( "*-*-*-*-*-*IPTelepathyPlugin: Execute");

    //TODO (malcalde@ibit.org) De momento meto todo el codigo aqui a la espera de investigar posibilidades 
    // de Boost::StateChart + Boost:Thread patterns
    GError *error = NULL;
    g_type_init ();
    
    /* create a main loop */
    tp_loop = g_main_loop_new (NULL, FALSE);

    /* acquire a connection to the D-Bus daemon */
    tp_bus = tp_dbus_daemon_dup(&error);
    if (tp_bus == NULL)
        g_error ("%s", error->message);
    
    /* Let's get a list of the connection managers */
    tp_list_connection_managers (tp_bus, tp_got_connection_managers,
            NULL, NULL, NULL);
    
//     /* we want to request the gabble CM */
//     TpConnectionManager *cm = tp_connection_manager_new (tp_bus,"idle", NULL, &error);
//     
//     if (error) g_error ("%s", error->message);

//     tp_connection_manager_call_when_ready (cm, 
//                                            tp_connection_ready,
//                                            argv, NULL, NULL);

    g_main_loop_run (tp_loop);
    g_object_unref (tp_bus);
        
    return true;
}
//---------------------------------------------------------------------------
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

//---------------------------------------------------------------------------
// Telepathy funcions (implementation)
//---------------------------------------------------------------------------
static void tp_connection_ready (
    TpConnectionManager   *cm,
    const GError      *in_error,
    gpointer       user_data,
    GObject       *weak_obj
)
{
    g_print (" > cm_ready\n");

//     if (in_error) g_error ("%s", in_error->message);
// 
//     /* request a new connection */
//     GHashTable *parameters = tp_asv_new (
//             "account", G_TYPE_STRING, "miguel.wasabi@gmail.com",
//             "password", G_TYPE_STRING, "Seed2tha",
//             NULL);
// 
//     tp_cli_connection_manager_call_request_connection (cm, -1,
//             "jabber",
//             parameters,
//             request_connection_cb,
//             NULL, NULL, NULL);
// 
//     g_hash_table_destroy (parameters);

}
//---------------------------------------------------------------------------
static void tp_got_connection_managers (
    TpConnectionManager    * const * cms,
    gsize           ncms,
    const GError       *error,
    gpointer        user_data,
    GObject        *weak_object
)
{
    g_print (" > got_connection_managers\n");

    /* From the documentation:
     *  tp_list_connection_managers() will wait for each
     *  TpConnectionManager to become ready, so all connection managers
     *  passed to callback will be ready */

    int i;
    for (i = 0; i < ncms; i++)
    {
        TpConnectionManager *cm = cms[i];

        if (!tp_connection_manager_is_ready (cm))
        {
            /* this should never happen, unless there is an
             * error */
            g_print ("CM not ready!\n");
            continue;
        }

        g_print (" - %s\n", cm->name);

        /* get the protocols */
        const TpConnectionManagerProtocol * const *iter;
        for (iter = cm->protocols; iter && *iter; iter++)
        {
            const TpConnectionManagerProtocol *prot = *iter;
            g_print ("   . %s\n", prot->name);
        }
    }
}

