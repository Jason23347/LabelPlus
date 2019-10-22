TEMPLATE = app
LIBS +=

QT += 3dcore 3drender 3dinput 3dlogic 3danimation 3dextras

# imgui
INCLUDEPATH += 3rdparty/imgui-qt3d 3rdparty/imgui

#3rdparty/imgui/imgui_widgets.cpp \
SOURCES += \
    3rdparty/imgui/imgui_draw.cpp \
    3rdparty/imgui/imgui.cpp \
    3rdparty/imgui/imgui_demo.cpp \
    3rdparty/imgui-qt3d/imguimanager.cpp \
    3rdparty/imgui-qt3d/imguiqt3dwindow.cpp

HEADERS += \
    3rdparty/imgui-qt3d/imguimanager.h \
    3rdparty/imgui-qt3d/imguiqt3dwindow.h

# app
SOURCES += \
    src/main.cpp \
    src/gui.cpp

HEADERS += \
    src/gui.h
