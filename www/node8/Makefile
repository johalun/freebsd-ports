# $FreeBSD$

PORTNAME=	node
PORTVERSION=	8.9.3
DISTVERSIONPREFIX=	v
CATEGORIES=	www
MASTER_SITES=	http://nodejs.org/dist/v${PORTVERSION}/
PKGNAMESUFFIX=	8

MAINTAINER=	bhughes@FreeBSD.org
COMMENT=	V8 JavaScript for client and server (8.x LTS)

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

OPTIONS_DEFINE=	BUNDLED_SSL DOCS NLS DTRACE
OPTIONS_DEFAULT=DTRACE
OPTIONS_SUB=	yes

OPTIONS_DEFAULT_FreeBSD_10=	BUNDLED_SSL
OPTIONS_DEFAULT+=		${OPTIONS_DEFAULT_${OPSYS}_${OSREL:R}}

.if !exists(/usr/sbin/dtrace)
OPTIONS_EXCLUDE+=	DTRACE
.endif

OPTIONS_EXCLUDE_FreeBSD_10=	DTRACE
OPTIONS_EXCLUDE_aarch64=	DTRACE

BUNDLED_SSL_DESC=		Use node.js's bundled OpenSSL implementation
BUNDLED_SSL_USES_OFF=		ssl
BUNDLED_SSL_CONFIGURE_OFF=	--shared-openssl --openssl-use-def-ca-store
BUNDLED_SSL_RUN_DEPENDS_OFF=	ca_root_nss>=0:security/ca_root_nss

NLS_CONFIGURE_ON=	--with-intl=system-icu
NLS_LIB_DEPENDS=	libicui18n.so:devel/icu

DTRACE_CONFIGURE_ON=	--with-dtrace

USES=		compiler:c++11-lib gmake python:2,build pkgconfig \
		localbase shebangfix

HAS_CONFIGURE=	yes
USE_LDCONFIG=	yes

CONFLICTS_INSTALL=	node[456]-[0-9]* node-[0-9]*

ONLY_FOR_ARCHS=		aarch64 amd64 armv6 armv7 i386

CONFIGURE_ARGS=	--prefix=${PREFIX_RELDEST} \
		--without-npm \
		--shared-cares \
		--shared-libuv \
		--shared-zlib

SHEBANG_FILES=	tools/specialize_node_d.py tools/genv8constants.py

PREFIX_RELDEST=	${PREFIX:S,^${DESTDIR},,}
REINPLACE_ARGS=	-i ''
MAKE_ENV+=	CC.host=${CC} CXX.host=${CXX} LINK.host=${CXX} LINK.target=${CXX}

LIB_DEPENDS+=	libcares.so:dns/c-ares\
		libuv.so:devel/libuv

.include <bsd.port.options.mk>

.if empty(PORT_OPTIONS:MBUNDLED_SSL)

.if ${OPSYS} == FreeBSD && ${OSVERSION} < 1100085 && ${SSL_DEFAULT} == base
IGNORE=		node.js requires openssl 1.0.2, add DEFAULT_VERSIONS+=ssl=openssl to /etc/make.conf or enable BUNDLED_SSL option
.endif

.if !empty(SSL_DEFAULT:Mlibressl*)
IGNORE=		cannot build node.js with LibreSSL. You must enable BUNDLED_SSL
.endif

.endif

.include <bsd.port.pre.mk>

.if ${ARCH} == armv6 || ${ARCH} == armv7
CONFIGURE_ARGS+=--openssl-no-asm
.endif

.if ${COMPILER_TYPE} == gcc
# GCC does not expose std::snprintf() without this define
CXXFLAGS+=	-D_GLIBCXX_USE_C99
.endif

post-patch:
	@${REINPLACE_CMD} -e 's|/usr/local|${LOCALBASE}|' \
		${WRKSRC}/deps/v8/src/v8.gyp

post-configure:
	# Post-process Makefile and *.mk files created by node-gyp and remove
	# all occurrences of -I${LOCALBASE}/include. C*FLAGS include this
	# before all -I../deps/* for bundled code. This can cause build
	# breakages if the dependency is installed in ${LOCALBASE}. The
	# USES+=localbase # above will ensure that we pick up includes for real
	# external dependencies.
	${FIND} ${WRKSRC}/out -type f -print0 \
		| ${XARGS} -0 ${REINPLACE_CMD} -e "s|-I${LOCALBASE}/include||g"

post-install:
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/bin/node

.include <bsd.port.post.mk>
