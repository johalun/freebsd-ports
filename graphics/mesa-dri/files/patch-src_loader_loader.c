--- src/loader/loader.c.orig	2017-10-17 15:43:46.347084000 +0200
+++ src/loader/loader.c	2017-10-17 15:45:45.664816000 +0200
@@ -260,8 +260,10 @@
       return -1;
    }
 
-   *maj = major(buf.st_rdev);
-   *min = minor(buf.st_rdev);
+   // Major/minor irrelevant on FreeBSD
+   // Cause bug on post-ino64 where major = inode number of device
+   *maj = 0;
+   *min = 0;
 
    return 0;
 }
