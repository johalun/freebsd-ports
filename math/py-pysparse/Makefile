# Created by: Yuri Victorovich <yuri@rawbw.com>
# $FreeBSD$

PORTNAME=	pysparse
PORTVERSION=	1.3
PORTREVISION=	3
CATEGORIES=	math python
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	yuri@rawbw.com
COMMENT=	Fast sparse matrix library for Python

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	${PYTHON_PKGNAMEPREFIX}numpy>=1.2,1:math/py-numpy@${FLAVOR}
RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}numpy>=1.2,1:math/py-numpy@${FLAVOR}
LIB_DEPENDS=	liblapack.so:math/lapack \
		libblas.so:math/blas \
		libopenblas.so:math/openblas \
		libcblas.so:math/cblas

USE_GITHUB=	yes
GH_ACCOUNT=	PythonOptimizers
GH_TAGNAME=	f8430bd

LDFLAGS+=	-shared  # Workaround for an obscure bug in py-numpy, see https://github.com/numpy/numpy/issues/7779

USES=		fortran python:2.7 # fortran is needed for the correct build flags passed to py-numpy extension build process
USE_PYTHON=	distutils autoplist

.include <bsd.port.mk>
