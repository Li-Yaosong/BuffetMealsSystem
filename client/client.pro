QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    administratorinterface.cpp \
    clientapp.cpp \
    clientinterface.cpp \
    login.cpp \
    main.cpp \
    client.cpp \
    orderlist.cpp

HEADERS += \
    administratorinterface.h \
    client.h \
    clientapp.h \
    clientinterface.h \
    login.h \
    orderlist.h

FORMS += \
    administratorinterface.ui \
    client.ui \
    clientapp.ui \
    clientinterface.ui \
    login.ui \
    orderlist.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target