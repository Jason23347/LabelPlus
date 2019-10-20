TEMPLATE = lib
TARGET = imgui-qt3d
BINDIR = $$OUT_PWD/../../bin
DESTDIR = $$BINDIR

CONFIG += staticlib
QT += 3dcore 3drender 3dinput 3dlogic 3danimation

INCLUDEPATH += ../imgui

DEFINES += "IMGUI_USER_CONFIG=\"qt-imconfig.h\""

SOURCES += \
    ../imgui/imgui.cpp \
    ../imgui/imgui_draw.cpp \
    ../imgui/imgui_demo.cpp \
    imguimanager.cpp \
    imguiqt3dwindow.cpp

HEADERS += \
    imguimanager.h \
    imguiqt3dwindow.h
