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

INCLUDEPATH += $$PWD/headers/

SOURCES += \
	sources/cores/framework.cpp \
	sources/cores/unit.cpp \
	sources/main.cpp \
	sources/utils/resources.cpp \
	sources/views/dialogs/aboutdialog.cpp \
	sources/views/dialogs/customdialog.cpp \
	sources/views/dialogs/rankdialog.cpp \
	sources/views/dialogs/successdialog.cpp \
	sources/views/mainwindow.cpp \
	sources/views/widgets/scenewidget.cpp

HEADERS += \
	headers/cores/framework.h \
	headers/cores/unit.h \
	headers/utils/constants.h \
	headers/utils/resources.h \
	headers/views/dialogs/aboutdialog.h \
	headers/views/dialogs/customdialog.h \
	headers/views/dialogs/rankdialog.h \
	headers/views/dialogs/successdialog.h \
	headers/views/mainwindow.h \
	headers/views/widgets/scenewidget.h

FORMS += \
	forms/dialogs/aboutdialog.ui \
	forms/dialogs/customdialog.ui \
	forms/dialogs/rankdialog.ui \
	forms/dialogs/successdialog.ui \
	forms/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc

RC_ICONS = resources/images/icon.ico
