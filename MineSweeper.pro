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

INCLUDEPATH += $$PWD/include/

SOURCES += \
	src/cores/block.cpp \
	src/views/dialogs/aboutdialog.cpp \
	src/views/dialogs/customdialog.cpp \
	src/views/dialogs/recorddialog.cpp \
	src/views/dialogs/successdialog.cpp \
	src/views/widgets/scenewidget.cpp \
	src/main.cpp \
	src/views/mainwindow.cpp \
	src/cores/controller.cpp \
	src/commons/resources.cpp

HEADERS += \
	include/cores/block.h \
	include/views/dialogs/aboutdialog.h \
	include/views/dialogs/customdialog.h \
	include/views/dialogs/recorddialog.h \
	include/views/dialogs/successdialog.h \
	include/views/widgets/scenewidget.h \
	include/views/mainwindow.h \
	include/cores/controller.h \
	include/commons/resources.h \
	include/commons/constants.h

FORMS += \
	ui/dialogs/aboutdialog.ui \
	ui/dialogs/customdialog.ui \
	ui/dialogs/recorddialog.ui \
	ui/dialogs/successdialog.ui \
	ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res/resources.qrc

RC_ICONS = res/images/icon.ico
