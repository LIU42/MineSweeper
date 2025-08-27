QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/sources/

SOURCES += \
	sources/cores/framework.cpp \
	sources/cores/unit.cpp \
	sources/main.cpp \
	sources/utils/resources.cpp \
	sources/views/aboutdialog.cpp \
	sources/views/customdialog.cpp \
	sources/views/rankdialog.cpp \
	sources/views/successdialog.cpp \
	sources/views/mainwindow.cpp \
	sources/views/scenewidget.cpp

HEADERS += \
	sources/cores/framework.h \
	sources/cores/unit.h \
	sources/utils/constants.h \
	sources/utils/resources.h \
	sources/views/aboutdialog.h \
	sources/views/customdialog.h \
	sources/views/rankdialog.h \
	sources/views/successdialog.h \
	sources/views/mainwindow.h \
	sources/views/scenewidget.h

FORMS += \
	forms/aboutdialog.ui \
	forms/customdialog.ui \
	forms/rankdialog.ui \
	forms/successdialog.ui \
	forms/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc

RC_ICONS = resources/images/icon.ico
