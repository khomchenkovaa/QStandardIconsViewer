#-------------------------------------------------
#
# Project created by QtCreator 2019-04-10T16:20:44
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QStandardIcons
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

include(qfonticon/qfonticon.pri)

SOURCES += \
        iconfonttab.cpp \
        iconlisttab.cpp \
        iconmimetab.cpp \
        iconthemetab.cpp \
        infodlgmbox.cpp \
        main.cpp \
        standardiconswidget.cpp \
        standardpixmaptab.cpp

HEADERS += \
        iconfonttab.h \
        iconlisttab.h \
        iconmimetab.h \
        iconthemetab.h \
        infodlgmbox.h \
        standardiconswidget.h \
        standardpixmaptab.h

FORMS += \
    infodlgmbox.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qStaddardIcons.qrc

