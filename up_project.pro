QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    menu_widget.cpp \
    settings_widget.cpp \
    start_widget.cpp \
    songlistwidget.cpp \
    songinfowidget.cpp \
    songselectmenu.cpp \
    songinfo.cpp \
    scoreswidget.cpp \
    gameplaywidget.cpp

HEADERS += \
    mainwindow.h \
    menu_widget.h \
    settings_widget.h \
    start_widget.h \
    mainwindow.h \
    songlistwidget.h \
    songinfowidget.h \
    songselectmenu.h \
    songinfo.h \
    scoreswidget.h \
    gameplaywidget.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
