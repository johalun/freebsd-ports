# $FreeBSD$

PORTNAME=	btpd
PORTVERSION=	0.16
PORTREVISION=	2
CATEGORIES=	net-p2p
MASTER_SITES=	GHC

MAINTAINER=	ports@FreeBSD.org
COMMENT=	Bittorrent client consisting of a daemon and client commands

LICENSE=	BSD2CLAUSE BSD3CLAUSE
LICENSE_COMB=	multi

USE_GITHUB=	yes

USES=		autoreconf ssl
GNU_CONFIGURE=	yes
CONFIGURE_ARGS+=	--with-openssl=${OPENSSLBASE}

OPTIONS_DEFINE=	DOCS

post-install-DOCS-on:
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/README ${STAGEDIR}${DOCSDIR}

.include <bsd.port.mk>
