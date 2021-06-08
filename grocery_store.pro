QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    grouping.cpp \
    main.cpp \
    mainwindow.cpp \
    newproduct.cpp \
    singup.cpp \
    user.cpp

HEADERS += \
    admin.h \
    grouping.h \
    mainwindow.h \
    newproduct.h \
    singup.h \
    user.h

FORMS += \
    admin.ui \
    grouping.ui \
    mainwindow.ui \
    newproduct.ui \
    singup.ui \
    user.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc
