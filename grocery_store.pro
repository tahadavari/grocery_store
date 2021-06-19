QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    deleteproduct.cpp \
    editproduct.cpp \
    editprofile.cpp \
    grouping.cpp \
    main.cpp \
    mainwindow.cpp \
    newproduct.cpp \
    product.cpp \
    singup.cpp \
    user.cpp \
    userinformation.cpp

HEADERS += \
    admin.h \
    deleteproduct.h \
    editproduct.h \
    editprofile.h \
    grouping.h \
    mainwindow.h \
    newproduct.h \
    product.h \
    singup.h \
    user.h \
    userinformation.h

FORMS += \
    admin.ui \
    deleteproduct.ui \
    editproduct.ui \
    editprofile.ui \
    grouping.ui \
    mainwindow.ui \
    newproduct.ui \
    product.ui \
    singup.ui \
    user.ui \
    userinformation.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc
