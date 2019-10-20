TEMPLATE = app
TARGET = labelplus
BINDIR = build
DESTDIR = $$BINDIR
LIBS += -L"$$BINDIR" -limgui-qt3d
PRE_TARGETDEPS += $$BINDIR/$${QMAKE_PREFIX_STATICLIB}imgui-qt3d.$${QMAKE_EXTENSION_STATICLIB}

QT += 3dcore 3drender 3dinput 3dlogic 3danimation 3dextras

INCLUDEPATH += 3rdparty/imgui-qt3d 3rdparty/imgui

SOURCES += \
    src/main.cpp \
    src/gui.cpp

HEADERS += \
    src/gui.h
