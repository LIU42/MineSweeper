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

SOURCES += \
	Sources/Dialogs/about.cpp \
	Sources/Dialogs/custom.cpp \
	Sources/Dialogs/record.cpp \
	Sources/Dialogs/success.cpp \
	Sources/graphics.cpp \
	Sources/main.cpp \
	Sources/mainwindow.cpp \
	Sources/Models/minesweeper.cpp

HEADERS += \
	Sources/Dialogs/about.h \
	Sources/Dialogs/custom.h \
	Sources/Dialogs/record.h \
	Sources/Dialogs/success.h \
	Sources/graphics.h \
	Sources/mainwindow.h \
	Sources/Models/minesweeper.h

FORMS += \
	Forms/Dialogs/about.ui \
	Forms/Dialogs/custom.ui \
	Forms/Dialogs/record.ui \
	Forms/Dialogs/success.ui \
	Forms/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources/resource.qrc

RC_ICONS = Resources/Images/icon.ico
