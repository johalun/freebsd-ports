--- libweston/launcher-weston-launch.c.orig	2017-02-14 20:59:07 UTC
+++ libweston/launcher-weston-launch.c
@@ -40,19 +40,29 @@
 #include <sys/ioctl.h>
 #include <fcntl.h>
 #include <unistd.h>
-#include <linux/vt.h>
-#include <linux/kd.h>
-#include <linux/major.h>
+
+#include <termios.h>
+#include <sys/consio.h>
+#include <sys/kbio.h>
+#define TTY_BASENAME    "/dev/ttyv"
+#define TTY_0           "/dev/ttyv0"
+
+/* #include <linux/kd.h> */
+/* #include <linux/major.h> */
+/* #include <linux/vt.h> */
+/* #define TTY_BASENAME "/dev/tty" */
+/* #define TTY_0        "/dev/tty0" */
+
 
 #include "compositor.h"
 #include "weston-launch.h"
 #include "launcher-impl.h"
 
-#define DRM_MAJOR 226
+/* #define DRM_MAJOR 226 */
 
-#ifndef KDSKBMUTE
-#define KDSKBMUTE	0x4B51
-#endif
+/* #ifndef KDSKBMUTE */
+/* #define KDSKBMUTE	0x4B51 */
+/* #endif */
 
 #ifdef HAVE_LIBDRM
 
@@ -151,22 +161,35 @@ launcher_weston_launch_open(struct westo
 static void
 launcher_weston_launch_close(struct weston_launcher *launcher_base, int fd)
 {
+	weston_log("%s: fd %d\n",__func__,fd);
 	close(fd);
 }
 
 static void
 launcher_weston_launch_restore(struct weston_launcher *launcher_base)
 {
+	weston_log("%s\n",__func__);
 	struct launcher_weston_launch *launcher = wl_container_of(launcher_base, launcher, base);
 	struct vt_mode mode = { 0 };
 
-	if (ioctl(launcher->tty, KDSKBMUTE, 0) &&
+	if (/*ioctl(launcher->tty, KDSKBMUTE, 0) &&*/
 	    ioctl(launcher->tty, KDSKBMODE, launcher->kb_mode))
 		weston_log("failed to restore kb mode: %m\n");
 
 	if (ioctl(launcher->tty, KDSETMODE, KD_TEXT))
 		weston_log("failed to set KD_TEXT mode on tty: %m\n");
 
+	/* Restore sane mode */
+	struct termios tios;
+	if (tcgetattr(launcher->tty, &tios)) {
+		weston_log("Failed to get terminal attribute\n");
+	} else {
+		cfmakesane(&tios);
+		if (tcsetattr(launcher->tty, TCSAFLUSH, &tios)) {
+			weston_log("Failed to set terminal attribute\n");
+		}
+	}
+
 	/* We have to drop master before we switch the VT back in
 	 * VT_AUTO, so we don't risk switching to a VT with another
 	 * display server, that will then fail to set drm master. */
@@ -243,7 +266,9 @@ launcher_weston_launch_connect(struct we
 		/* We don't get a chance to read out the original kb
 		 * mode for the tty, so just hard code K_UNICODE here
 		 * in case we have to clean if weston-launch dies. */
-		launcher->kb_mode = K_UNICODE;
+
+		launcher->kb_mode = K_XLATE;
+		/* launcher->kb_mode = K_UNICODE; */
 
 		loop = wl_display_get_event_loop(compositor->wl_display);
 		launcher->source = wl_event_loop_add_fd(loop, launcher->fd,
