QT       += core gui sql remoteobjects network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#include(../common/common.pri)
#INCLUDEPATH += $$PWD/../c
#CONAN_INSTALL += bms/0.0.1

conanupload.CONFIG += recursive
QMAKE_EXTRA_TARGETS += conanupload


#include(../conan/conan.pri)
include(../lib/common/common.pri)


#QMAKE_SUBSTITUTES += dllfile

SOURCES += \
    adddialog.cpp \
    administratorinterface.cpp \
    dishesedict.cpp \
    dishwidget.cpp \
    getneworder.cpp \
    loginwidget.cpp \
    main.cpp \
    admini.cpp \
    orderlist.cpp \
    registwidget.cpp \
    reportwidget.cpp \
    setcostdialog.cpp

HEADERS += \
    adddialog.h \
    admini.h \
    administratorinterface.h \
    dishesedict.h \
    dishwidget.h \
    getneworder.h \
    loginwidget.h \
    orderlist.h \
    registwidget.h \
    reportwidget.h \
    setcostdialog.h

FORMS += \
    adddialog.ui \
    admini.ui \
    administratorinterface.ui \
    dishesedict.ui \
    dishwidget.ui \
    loginwidget.ui \
    orderlist.ui \
    registwidget.ui \
    reportwidget.ui \
    setcostdialog.ui

REPC_REPLICA = $$PWD/../service.rep
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

