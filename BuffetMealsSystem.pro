TEMPLATE = subdirs
conanupload.CONFIG += recursive
QMAKE_EXTRA_TARGETS += conanupload

conandeploy.CONFIG += recursive
QMAKE_EXTRA_TARGETS += conandeploy

SUBDIRS += \
    admini \
    client
