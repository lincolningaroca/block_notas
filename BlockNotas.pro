#-------------------------------------------------
#
# Project created by QtCreator 2014-04-26T14:20:38
#
#-------------------------------------------------

QT       += core gui printsupport sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG+=c++17
TARGET = BlockNotas
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
include(botan.pri)

SOURCES += main.cpp\
    aboutdialog.cpp \
    mainwindow.cpp \
    frmlogin.cpp \
    frmnuevacuenta.cpp \
    database.cpp \
    simplecrypt.cpp \
#    frmactualizar.cpp \
    frmcambiarclave.cpp \
    frmcodigo.cpp \
    frmdesencriptar.cpp \
    frmregistro.cpp \
    frmdatosregistro.cpp \
    contacto.cpp \
    frmcontactos.cpp \
    frmnuevacategoria.cpp \
    frmrecuperaclave.cpp \
    frmcambiarfrase.cpp \
    frmeditadatos.cpp \
    botan.cpp \
    DuCrypt.cpp \
    frmencripta.cpp \
    frmcaracteres.cpp

HEADERS  += mainwindow.h \
    aboutdialog.h \
    frmlogin.h \
    frmnuevacuenta.h \
    database.h \
    simplecrypt.h \
#    frmactualizar.h \
    frmcambiarclave.h \
    frmcodigo.h \
    frmdesencriptar.h \
    frmregistro.h \
    frmdatosregistro.h \
    contacto.h \
    frmcontactos.h \
    frmnuevacategoria.h \
    frmrecuperaclave.h \
    frmcambiarfrase.h \
    frmeditadatos.h \
    botan.h \
    DuCrypt.h \
    frmencripta.h \
    frmcaracteres.h

FORMS    += mainwindow.ui \
    aboutdialog.ui \
    frmlogin.ui \
    frmnuevacuenta.ui \
#    frmactualizar.ui \
    frmcambiarclave.ui \
    frmcodigo.ui \
    frmdesencriptar.ui \
    frmregistro.ui \
    frmdatosregistro.ui \
    frmcontactos.ui \
    frmnuevacategoria.ui \
    frmrecuperaclave.ui \
    frmcambiarfrase.ui \
    frmeditadatos.ui \
    frmencripta.ui \
    frmcaracteres.ui

RESOURCES += \
    res.qrc
#OTHER_FILES+=app.rc \
#    ../../../Downloads/1401844805_010.png
#RC_FILE=app.rc
RC_ICONS+=appMainIcon.ico
#INCLUDEPATH+="$$_PRO_FILE_PWD_/dialogs"
#LIBS+= -L"$$_PRO_FILE_PWD_/lib" -lqtfindreplacedialog
#QMAKE_CXXFLAGS +=-std=gnu++17



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lqtfindreplacedialog
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lqtfindreplacedialogd
else:unix: LIBS += -L$$PWD/lib/ -lqtfindreplacedialog

INCLUDEPATH += $$PWD/inlcude
DEPENDPATH += $$PWD/inlcude

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/libqtfindreplacedialog.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/libqtfindreplacedialogd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/qtfindreplacedialog.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/qtfindreplacedialogd.lib
else:unix: PRE_TARGETDEPS += $$PWD/lib/libqtfindreplacedialog.a
