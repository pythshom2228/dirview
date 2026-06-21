QT += widgets

CONFIG += c++17

TARGET = dirview

DESTDIR = $$PWD/build

OBJECTS_DIR = $$DESTDIR/obj
MOC_DIR = $$DESTDIR/moc
RCC_DIR = $$DESTDIR/rcc
UI_DIR = $$DESTDIR/ui

SOURCES += \
    src/main.cpp \
    src/MainWindow.cpp \
    src/FileSystemModel.cpp

HEADERS += \
    src/MainWindow.h \
    src/FileSystemModel.h