--- mod_scgi.c.orig	2009-11-21 23:02:06 UTC
+++ mod_scgi.c
@@ -135,16 +135,16 @@ static int scgi_map_location(request_rec
     return DECLINED;
 }
 
-static void log_err(const char *file, int line, request_rec *r,
+static void log_err(const char *file, int line, int index, request_rec *r,
                     apr_status_t status, const char *msg)
 {
-    ap_log_rerror(file, line, APLOG_ERR, status, r, "scgi: %s", msg);
+    ap_log_rerror(file, line, index, APLOG_ERR, status, r, "scgi: %s", msg);
 }
 
-static void log_debug(const char *file, int line, request_rec *r, const
+static void log_debug(const char *file, int line, int index, request_rec *r, const
                       char *msg)
 {
-    ap_log_rerror(file, line, APLOG_DEBUG, APR_SUCCESS, r, msg);
+    ap_log_rerror(file, line, index, APLOG_DEBUG, APR_SUCCESS, r, "%s", msg);
 }
 
 static char *http2env(apr_pool_t *p, const char *name)
@@ -312,7 +312,7 @@ send_headers(request_rec *r, struct sock
     int i;
     apr_status_t rv = 0;
     apr_port_t  port = 0;
-    GET_PORT(port, r->connection->remote_addr);
+    GET_PORT(port, r->useragent_addr);
 
     log_debug(APLOG_MARK,r, "sending headers");
     t = apr_table_make(r->pool, 40);
@@ -324,14 +324,14 @@ send_headers(request_rec *r, struct sock
 	    buf = "0";
     add_header(t, "CONTENT_LENGTH",  buf);
     add_header(t, "SCGI", SCGI_PROTOCOL_VERSION);
-    add_header(t, "SERVER_SOFTWARE", ap_get_server_version());
+    add_header(t, "SERVER_SOFTWARE", ap_get_server_banner());
     add_header(t, "SERVER_PROTOCOL", r->protocol);
     add_header(t, "SERVER_NAME", ap_get_server_name(r));
     add_header(t, "SERVER_ADMIN", r->server->server_admin);
     add_header(t, "SERVER_ADDR", r->connection->local_ip);
     add_header(t, "SERVER_PORT", apr_psprintf(r->pool, "%u",
                                               ap_get_server_port(r)));
-    add_header(t, "REMOTE_ADDR", r->connection->remote_ip);
+    add_header(t, "REMOTE_ADDR", r->useragent_ip);
     add_header(t, "REMOTE_PORT", apr_psprintf(r->pool, "%d", port));
     add_header(t, "REMOTE_USER", r->user);
     add_header(t, "REQUEST_METHOD", r->method);
