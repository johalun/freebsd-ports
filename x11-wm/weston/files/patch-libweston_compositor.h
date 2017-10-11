--- libweston/compositor.h.orig	2017-02-07 22:58:35 UTC
+++ libweston/compositor.h
@@ -1619,6 +1619,7 @@ weston_compositor_create(struct wl_displ
 enum weston_compositor_backend {
 	WESTON_BACKEND_DRM,
 	WESTON_BACKEND_FBDEV,
+	WESTON_BACKEND_SCFB,
 	WESTON_BACKEND_HEADLESS,
 	WESTON_BACKEND_RDP,
 	WESTON_BACKEND_WAYLAND,
