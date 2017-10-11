--- clients/terminal.c.orig	2016-11-21 17:00:30 UTC
+++ clients/terminal.c
@@ -32,7 +32,11 @@
 #include <unistd.h>
 #include <math.h>
 #include <time.h>
-#include <pty.h>
+/* #include <pty.h> */
+#include <sys/types.h>
+#include <sys/ioctl.h>
+#include <termios.h>
+#include <libutil.h>
 #include <ctype.h>
 #include <cairo.h>
 #include <sys/epoll.h>
@@ -3075,7 +3079,7 @@ int main(int argc, char *argv[])
 
 	option_shell = getenv("SHELL");
 	if (!option_shell)
-		option_shell = "/bin/bash";
+		option_shell = "/bin/sh";
 
 	config_file = weston_config_get_name_from_env();
 	config = weston_config_parse(config_file);
