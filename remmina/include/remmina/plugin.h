/*
 * Remmina - The GTK+ Remote Desktop Client
 * Copyright (C) 2010 Vic Lee 
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, 
 * Boston, MA 02111-1307, USA.
 */

#ifndef __REMMINA_PLUGIN_H__
#define __REMMINA_PLUGIN_H__

#include <remmina/types.h>

G_BEGIN_DECLS

typedef struct _RemminaProtocolPlugin
{
    gchar *protocol;
    gchar *description;
    gchar *icon_name;
    gchar *icon_name_ssh;
    gchar *avahi_service_type;
    const RemminaProtocolSetting *basic_settings;
    const RemminaProtocolSetting *advanced_settings;
    RemminaProtocolSSHSetting ssh_setting;

    void (* init) (RemminaProtocolWidget *gp);
    gboolean (* open_connection) (RemminaProtocolWidget *gp);
    gboolean (* close_connection) (RemminaProtocolWidget *gp);
    gpointer (* query_feature) (RemminaProtocolWidget *gp, RemminaProtocolFeature feature);
    void (* call_feature) (RemminaProtocolWidget *gp, RemminaProtocolFeature feature, const gpointer data);
} RemminaProtocolPlugin;

/* Plugin Service is a struct containing a list of function pointers,
 * which is passed from Remmina main program to the plugin module
 * through the plugin entry function remmina_plugin_entry() */
typedef struct _RemminaPluginService
{
    gboolean     (* register_protocol_plugin)            (RemminaProtocolPlugin *plugin);

    gint         (* protocol_plugin_get_width)           (RemminaProtocolWidget *gp);
    void         (* protocol_plugin_set_width)           (RemminaProtocolWidget *gp, gint width);
    gint         (* protocol_plugin_get_height)          (RemminaProtocolWidget *gp);
    void         (* protocol_plugin_set_height)          (RemminaProtocolWidget *gp, gint height);
    gboolean     (* protocol_plugin_get_scale)           (RemminaProtocolWidget *gp);
    void         (* protocol_plugin_set_scale)           (RemminaProtocolWidget *gp, gboolean scale);
    gboolean     (* protocol_plugin_get_expand)          (RemminaProtocolWidget *gp);
    void         (* protocol_plugin_set_expand)          (RemminaProtocolWidget *gp, gboolean expand);
    gboolean     (* protocol_plugin_has_error)           (RemminaProtocolWidget *gp);
    void         (* protocol_plugin_set_error)           (RemminaProtocolWidget *gp, const gchar *fmt, ...);
    gboolean     (* protocol_plugin_is_closed)           (RemminaProtocolWidget *gp);
    RemminaFile* (* protocol_plugin_get_file)            (RemminaProtocolWidget *gp);
    GPtrArray*   (* protocol_plugin_get_printers)        (RemminaProtocolWidget *gp);
    void         (* protocol_plugin_emit_signal)         (RemminaProtocolWidget *gp, const gchar *signal_name);
    gchar*       (* protocol_plugin_start_direct_tunnel) (RemminaProtocolWidget *gp, gint default_port);
    gboolean     (* protocol_plugin_start_xport_tunnel)  (RemminaProtocolWidget *gp, gint display, RemminaXPortTunnelInitFunc init_func);
    gboolean     (* protocol_plugin_close_connection)    (RemminaProtocolWidget *gp);
    gint         (* protocol_plugin_init_authpwd)        (RemminaProtocolWidget *gp, RemminaAuthpwdType authpwd_type);
    gint         (* protocol_plugin_init_authuserpwd)    (RemminaProtocolWidget *gp);
    gchar*       (* protocol_plugin_init_get_username)   (RemminaProtocolWidget *gp);
    gchar*       (* protocol_plugin_init_get_password)   (RemminaProtocolWidget *gp);
    gint         (* protocol_plugin_init_authx509)       (RemminaProtocolWidget *gp);
    gchar*       (* protocol_plugin_init_get_cacert)     (RemminaProtocolWidget *gp);
    gchar*       (* protocol_plugin_init_get_cacrl)      (RemminaProtocolWidget *gp);
    gchar*       (* protocol_plugin_init_get_clientcert) (RemminaProtocolWidget *gp);
    gchar*       (* protocol_plugin_init_get_clientkey)  (RemminaProtocolWidget *gp);
    void         (* protocol_plugin_init_save_cred)      (RemminaProtocolWidget *gp);
    void         (* protocol_plugin_init_show_listen)    (RemminaProtocolWidget *gp, gint port);
    void         (* protocol_plugin_init_show_retry)     (RemminaProtocolWidget *gp);
    gboolean     (* protocol_plugin_ssh_exec)            (RemminaProtocolWidget *gp, const gchar *fmt, ...);
    void         (* protocol_plugin_chat_open)           (RemminaProtocolWidget *gp, const gchar *name,
                                                          void(*on_send)(RemminaProtocolWidget *gp, const gchar *text),
                                                          void(*on_destroy)(RemminaProtocolWidget *gp));
    void         (* protocol_plugin_chat_close)          (RemminaProtocolWidget *gp);
    void         (* protocol_plugin_chat_receive)        (RemminaProtocolWidget *gp, const gchar *text);

    gint         (* pref_get_scale_quality)              (void);
    gint         (* pref_get_sshtunnel_port)             (void);
    guint        (* pref_keymap_get_keyval)              (const gchar *keymap, guint keyval);
} RemminaPluginService;

/* "Prototype" of the plugin entry function */
typedef gboolean (*RemminaPluginEntryFunc) (RemminaPluginService *service);

G_END_DECLS

#endif /* __REMMINA_PLUGIN_H__ */
