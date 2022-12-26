QT       += core gui widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about.cpp \
    AddSongToLibrary.cpp \
    foundsongswindow.cpp \
    helppage.cpp \
    main.cpp \
    mainwindow.cpp \
    musiclibrary.cpp \
    songsearcherwindow.cpp

HEADERS += \
    about.h \
    AddSongToLibrary.h \
    foundsongswindow.h \
    helppage.h \
    mainwindow.h \
    musiclibrary.h \
    songsearcherwindow.h

FORMS += \
    about.ui \
    AddSongToLibrary.ui \
    foundsongswindow.ui \
    helppage.ui \
    mainwindow.ui \
    musiclibrary.ui \
    songsearcherwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
