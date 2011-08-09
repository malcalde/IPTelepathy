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

#include <boost/thread/thread.hpp>
#include <telepathy-glib/telepathy-glib.h>

#include "P4HPlugin.h"
#include "P4HEventManager.h"
#include "P4HTools.h"

#include "IPTelepathyPlugin.h"

using namespace P4H;

const String sPluginName = "IPTelepathy";

static GMainLoop* tp_loop = NULL;
static TpDBusDaemon* tp_bus= NULL;
static TpConnection* tp_conn = NULL;
static GError *g_error = NULL;

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

struct _threadLoop
{
    void operator()()
    {
        if (!tp_loop)
        {
            P4H_LOG("[IPTelepathyPlugin - _threadLoop] Starting telepathy loop");
            g_main_loop_run (tp_loop);
        }
        else
            P4H_LOG("[IPTelepathyPlugin - _threadLoop] No DBUS conection!.");
    }
} threadLoop;

//---------------------------------------------------------------------------
// IPTelepathyPlugin methods
//---------------------------------------------------------------------------
IPTelepathyPlugin::IPTelepathyPlugin()
{
}
//---------------------------------------------------------------------------
IPTelepathyPlugin::~IPTelepathyPlugin()
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

    g_type_init();
    
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

    /* create a main loop */
    tp_loop = g_main_loop_new(NULL, FALSE);
    
    /* acquire a connection to the D-Bus daemon */
    tp_bus = tp_dbus_daemon_dup(&g_error);
    if (tp_bus == NULL)
    {
        P4H_LOG("[IPTelepathyPlugin::initialise]{ERROR} " + String(g_error->message));
        return false;
    }
    
    return true;
}
//---------------------------------------------------------------------------
bool IPTelepathyPlugin::onReInitialise()
{
    P4H_LOG( "*-*-*-*-*-*IPTelepathyPlugin: reinitialise");

    /* re-create a main loop */
    if (! tp_loop)
        tp_loop = g_main_loop_new(NULL, FALSE);
    return true;
}
//---------------------------------------------------------------------------
bool IPTelepathyPlugin::onShutdown()
{
    //shutdown called - unregister stuff here

    P4H_LOG( "*-*-*-*-*-*IPTelepathyPlugin: shutdown");

    //Cerramos conexion
    if (tp_conn)
        tp_cli_connection_call_disconnect (tp_conn, -1, NULL, NULL, NULL, NULL);
    
    //Release D-BUS connection
    g_object_unref(tp_bus);
    
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

    /* Let's get a list of the connection managers */
    tp_list_connection_managers (tp_bus, tp_got_connection_managers,
            NULL, NULL, NULL);
   
    boost::thread thrd(threadLoop);
        
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

