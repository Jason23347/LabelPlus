#ifndef GUI_H
#define GUI_H

#include <imgui.h>

#include <QObject>

class ImguiManager;

class Gui : public QObject
{
    Q_OBJECT
public:
    void frame();

private:
    ImguiManager *m_manager = nullptr;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    void showDebugWindow();
    void showMainMenuBar();
    void showMainToolBar();
    void showWorkspace();
    void showStatusBar();
};


#endif
