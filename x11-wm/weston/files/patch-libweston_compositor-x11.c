--- libweston/compositor-x11.c.orig	2017-01-19 01:41:20 UTC
+++ libweston/compositor-x11.c
@@ -37,6 +37,7 @@
 #include <errno.h>
 #include <sys/time.h>
 #include <sys/shm.h>
+#include <sys/stat.h>
 #include <linux/input.h>
 
 #include <xcb/xcb.h>
