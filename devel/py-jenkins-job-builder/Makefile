# Created by: Li-Wen Hsu <lwhsu@FreeBSD.org>
# $FreeBSD$

PORTNAME=	jenkins-job-builder
PORTVERSION=	2.0.0
CATEGORIES=	devel python
MASTER_SITES=	CHEESESHOP
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	lwhsu@FreeBSD.org
COMMENT=	Manage Jenkins jobs with YAML

LICENSE=	APACHE20
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	${PKGNAMEPREFIX}pbr>0:devel/py-pbr@${FLAVOR}
RUN_DEPENDS=	${PKGNAMEPREFIX}yaml>0:devel/py-yaml@${FLAVOR} \
		${PKGNAMEPREFIX}pbr>0:devel/py-pbr@${FLAVOR} \
		${PKGNAMEPREFIX}six>0:devel/py-six@${FLAVOR} \
		${PKGNAMEPREFIX}stevedore>0:devel/py-stevedore@${FLAVOR} \
		${PKGNAMEPREFIX}python-jenkins>0:devel/py-python-jenkins@${FLAVOR} \
		${PKGNAMEPREFIX}fasteners>0:devel/py-fasteners@${FLAVOR} \
		${PKGNAMEPREFIX}Jinja2>0:devel/py-Jinja2@${FLAVOR}

USES=		python
USE_PYTHON=	autoplist distutils

.include <bsd.port.mk>
