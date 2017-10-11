--- clients/desktop-shell.c.orig	2017-01-19 01:41:20 UTC
+++ clients/desktop-shell.c
@@ -41,6 +41,7 @@
 #include <ctype.h>
 #include <time.h>
 #include <assert.h>
+#include <signal.h>
 
 #include <wayland-client.h>
 #include "window.h"
@@ -50,6 +51,8 @@
 #include "shared/xalloc.h"
 #include "shared/zalloc.h"
 
+#define program_invocation_short_name getprogname()
+
 #include "weston-desktop-shell-client-protocol.h"
 
 #define DEFAULT_CLOCK_FORMAT CLOCK_FORMAT_MINUTES
