QT       += core gui remoteobjects network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
include(../common/common.pri)
SOURCES += \
    adddishesdialog.cpp \
    administratorinterface.cpp \
    dishesedict.cpp \
    dishwidget.cpp \
    getneworder.cpp \
    main.cpp \
    admini.cpp \
    orderlist.cpp

HEADERS += \
    adddishesdialog.h \
    admini.h \
    administratorinterface.h \
    dishesedict.h \
    dishwidget.h \
    getneworder.h \
    orderlist.h

FORMS += \
    adddishesdialog.ui \
    admini.ui \
    administratorinterface.ui \
    dishesedict.ui \
    dishwidget.ui \
    orderlist.ui

REPC_REPLICA = $$PWD/../service.rep
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
