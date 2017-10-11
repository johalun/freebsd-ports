--- compositor/main.c.orig	2017-02-14 20:59:07 UTC
+++ compositor/main.c
@@ -41,7 +41,9 @@
 #include <sys/socket.h>
 #include <libinput.h>
 #include <sys/time.h>
-#include <linux/limits.h>
+/* #include <linux/limits.h> */
+#include <limits.h>
+#define PATH_MAX _POSIX_PATH_MAX
 
 #ifdef HAVE_LIBUNWIND
 #define UNW_LOCAL_ONLY
@@ -61,6 +63,7 @@
 #include "compositor-headless.h"
 #include "compositor-rdp.h"
 #include "compositor-fbdev.h"
+#include "compositor-scfb.h"
 #include "compositor-x11.h"
 #include "compositor-wayland.h"
 #include "windowed-output-api.h"
@@ -538,6 +541,9 @@ usage(int error_code)
 #if defined(BUILD_FBDEV_COMPOSITOR)
 			"\t\t\t\tfbdev-backend.so\n"
 #endif
+#if defined(BUILD_SCFB_COMPOSITOR)
+			"\t\t\t\tscfb-backend.so\n"
+#endif
 #if defined(BUILD_HEADLESS_COMPOSITOR)
 			"\t\t\t\theadless-backend.so\n"
 #endif
@@ -577,6 +583,14 @@ usage(int error_code)
 		"\n");
 #endif
 
+#if defined(BUILD_SCFB_COMPOSITOR)
+	fprintf(stderr,
+		"Options for scfb-backend.so:\n\n"
+		"  --tty=TTY\t\tThe tty to use\n"
+		"  --device=DEVICE\tThe framebuffer device to use\n"
+		"\n");
+#endif
+
 #if defined(BUILD_HEADLESS_COMPOSITOR)
 	fprintf(stderr,
 		"Options for headless-backend.so:\n\n"
@@ -680,9 +694,9 @@ clock_name(clockid_t clk_id)
 	static const char *names[] = {
 		[CLOCK_REALTIME] =		"CLOCK_REALTIME",
 		[CLOCK_MONOTONIC] =		"CLOCK_MONOTONIC",
-		[CLOCK_MONOTONIC_RAW] =		"CLOCK_MONOTONIC_RAW",
-		[CLOCK_REALTIME_COARSE] =	"CLOCK_REALTIME_COARSE",
-		[CLOCK_MONOTONIC_COARSE] =	"CLOCK_MONOTONIC_COARSE",
+		/* [CLOCK_MONOTONIC_RAW] =		"CLOCK_MONOTONIC_RAW", */
+		/* [CLOCK_REALTIME_COARSE] =	"CLOCK_REALTIME_COARSE", */
+		/* [CLOCK_MONOTONIC_COARSE] =	"CLOCK_MONOTONIC_COARSE", */
 #ifdef CLOCK_BOOTTIME
 		[CLOCK_BOOTTIME] =		"CLOCK_BOOTTIME",
 #endif
@@ -1577,6 +1591,57 @@ load_x11_backend(struct weston_composito
 }
 
 static void
+scfb_backend_output_configure(struct wl_listener *listener, void *data)
+{
+	struct weston_output *output = data;
+	struct weston_config *wc = wet_get_config(output->compositor);
+	struct weston_config_section *section;
+
+	section = weston_config_get_section(wc, "output", "name", "scfb");
+
+	wet_output_set_transform(output, section, WL_OUTPUT_TRANSFORM_NORMAL, UINT32_MAX);
+	weston_output_set_scale(output, 1);
+
+	weston_output_enable(output);
+}
+
+static int
+load_scfb_backend(struct weston_compositor *c,
+				  int *argc, char **argv, struct weston_config *wc)
+{
+	struct weston_scfb_backend_config config = {{ 0, }};
+	int ret = 0;
+
+	const struct weston_option scfb_options[] = {
+		{ WESTON_OPTION_INTEGER, "tty", 0, &config.tty },
+		{ WESTON_OPTION_STRING, "device", 0, &config.device },
+	};
+
+	parse_options(scfb_options, ARRAY_LENGTH(scfb_options), argc, argv);
+
+	if (!config.device)
+		config.device = strdup("/dev/ttyv1");
+
+	config.base.struct_version = WESTON_SCFB_BACKEND_CONFIG_VERSION;
+	config.base.struct_size = sizeof(struct weston_scfb_backend_config);
+	config.configure_device = configure_input_device;
+
+	/* load the actual wayland backend and configure it */
+	ret = weston_compositor_load_backend(c, WESTON_BACKEND_SCFB,
+					     &config.base);
+
+	if (ret < 0)
+		goto out;
+
+	wet_set_pending_output_handler(c, scfb_backend_output_configure);
+
+out:
+	free(config.device);
+	return ret;
+
+}
+
+static void
 wayland_backend_output_configure_hotplug(struct wl_listener *listener, void *data)
 {
 	struct weston_output *output = data;
@@ -1722,6 +1787,8 @@ load_backend(struct weston_compositor *c
 		return load_rdp_backend(compositor, argc, argv, config);
 	else if (strstr(backend, "fbdev-backend.so"))
 		return load_fbdev_backend(compositor, argc, argv, config);
+	else if (strstr(backend, "scfb-backend.so"))
+		return load_scfb_backend(compositor, argc, argv, config);
 	else if (strstr(backend, "drm-backend.so"))
 		return load_drm_backend(compositor, argc, argv, config);
 	else if (strstr(backend, "x11-backend.so"))
