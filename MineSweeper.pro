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

INCLUDEPATH += $$PWD/Headers/

SOURCES += \
	Sources/Dialogs/About.cpp \
	Sources/Dialogs/Custom.cpp \
	Sources/Dialogs/Record.cpp \
	Sources/Dialogs/Success.cpp \
	Sources/Graphics.cpp \
	Sources/Main.cpp \
	Sources/MainWindow.cpp \
	Sources/Games/MainGame.cpp

HEADERS += \
	Headers/Dialogs/About.h \
	Headers/Dialogs/Custom.h \
	Headers/Dialogs/Record.h \
	Headers/Dialogs/Success.h \
	Headers/Graphics.h \
	Headers/MainWindow.h \
	Headers/Games/MainGame.h

FORMS += \
	Forms/Dialogs/About.ui \
	Forms/Dialogs/Custom.ui \
	Forms/Dialogs/Record.ui \
	Forms/Dialogs/Success.ui \
	Forms/MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources/Resources.qrc

RC_ICONS = Resources/Images/icon.ico
