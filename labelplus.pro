TEMPLATE = app
LIBS +=

CONFIG += c++11

#
# imgui
#
INCLUDEPATH += 3rdparty/imgui
SOURCES += \
    3rdparty/imgui/imgui_draw.cpp \
    3rdparty/imgui/imgui.cpp \
    3rdparty/imgui/imgui_demo.cpp

#
# imgui-addons, from addons_examples.pro
#
DEFINES += \
    IMIMPL_SHADER_NONE \
    IMGUI_USE_SDL2_BINDING
INCLUDEPATH += \
    3rdparty/sdl2/inc \
    3rdparty/sdl2/inc/SDL2 \
    3rdparty/sdl2/prebuilds/linux_x64
LIBS += -L3rdparty/sdl2/prebuilds/linux_x64 -l:libSDL2.a -pthread -ldl


#
# app
#
SOURCES += \
    src/main.cpp \
    src/gui.cpp \
    src/imgui_helpers.cpp

HEADERS += \
    src/gui.h
