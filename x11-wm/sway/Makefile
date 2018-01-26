# Created by: Johannes Lundberg <johalun0@gmail.com>
# $FreeBSD$

PORTNAME=	sway
DISTVERSION=	0.15
CATEGORIES=	x11-wm

MAINTAINER=	johalun0@gmail.com
COMMENT=	i3-compatible Wayland compositor

LICENSE=	MIT
LICENSE_FILES=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	a2x:textproc/asciidoc \
		wlc>=0.0.10:x11-toolkits/wlc
LIB_DEPENDS=	libwlc.so:x11-toolkits/wlc \
		libwayland-server.so:graphics/wayland \
		libepoll-shim.so:devel/libepoll-shim \
		libpcre.so:devel/pcre \
		libjson-c.so:devel/json-c \
		libxkbcommon.so:x11/libxkbcommon \
		libdbus-1.so:devel/dbus \
		libinput.so:x11/libinput \
		libMagickCore-6.so:graphics/ImageMagick \
		libavutil.so:multimedia/ffmpeg

USES=		cmake:outsource gettext-runtime gnome pathfix pkgconfig

USE_GNOME=	cairo pango gdkpixbuf2

USE_GITHUB=	yes
GH_ACCOUNT=	swaywm

OPTIONS_SUB=	yes
OPTIONS_DEFINE=	SUID
OPTIONS_DEFAULT=SUID
SUID_DESC=	Install sway binary with setuid bit set

.include <bsd.port.mk>
