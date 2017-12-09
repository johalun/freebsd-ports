# Created by: Johannes Lundberg <johalun0@gmail.com>
# $FreeBSD$

PORTNAME=	sway
PORTVERSION=0.15
CATEGORIES=	wayland

MAINTAINER=	x11@FreeBSD.org
COMMENT=	i3-compatible Wayland compositor.

LICENSE=	MIT
LICENSE_FILES=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	a2x:textproc/asciidoc
LIB_DEPENDS=	libwlc.so:x11-toolkits/wlc \
				libwayland-server.so:graphics/wayland \
				libepoll-shim.so:devel/libepoll-shim \
				libpcre.so:devel/pcre \
				libjson-c.so:devel/json-c \
				libxkbcommon.so:x11/libxkbcommon \
				libdbus-1.so:devel/dbus \
				libinput.so:x11/libinput

# For image capture
#		libMagickCore-6.so:graphics/ImageMagick
# For video capture
#		libavutil.so:multimedia/ffmpeg

USE_GITHUB=	yes
GH_ACCOUNT=	swaywm
GH_TAGNAME=	0.15-rc3

USES=		cmake:outsource gettext-runtime gnome pathfix pkgconfig
USE_GNOME=	cairo pango gdkpixbuf2
USE_GCC=	any

OPTIONS_SUB=	yes
OPTIONS_DEFINE=	SUID
OPTIONS_DEFAULT=SUID
SUID_DESC=	Install sway binary with setuid bit set

.include <bsd.port.mk>
