--- shared/string-helpers.h.orig	2016-11-20 21:46:09 UTC
+++ shared/string-helpers.h
@@ -31,6 +31,7 @@
 #include <stdint.h>
 #include <errno.h>
 #include <assert.h>
+#include <unistd.h>
 
 /* Convert string to integer
  *
