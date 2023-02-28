QT += core gui widgets remoteobjects

TEMPLATE = lib
DEFINES += LIBBMS_LIBRARY

LIB_NAME = bms
LIB_VERSION = 0.0.1

conandeploy.CONFIG += recursive
QMAKE_EXTRA_TARGETS += conandeploy

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
include(common/common.pri)

SOURCES += \

HEADERS += \
    libbms_global.h

REPC_REPLICA = $$PWD/service.rep

install_headers.files = $$HEADERS

include(../conan/conan.pri)


