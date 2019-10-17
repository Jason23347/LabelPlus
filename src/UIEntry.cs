
using ImGuiNET;

namespace LabelPlus
{
    static class UIEntry {
        static bool _showAnotherWindow;

        static void ShowMainMenuBar()
        {
            if (ImGui.BeginMainMenuBar())
            {
                if (ImGui.BeginMenu("File"))
                {
                    ImGui.MenuItem("Open Project", "CTRL+O");
                    ImGui.MenuItem("Reload Project", "CTRL+R");
                    ImGui.MenuItem("Close Project");
                    ImGui.Separator();
                    ImGui.MenuItem("Exit", "ALT+F4");
                    ImGui.EndMenu();
                }
                if (ImGui.BeginMenu("Edit"))
                {
                    if (ImGui.MenuItem("Undo", "CTRL+Z")) {}
                    if (ImGui.MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
                    ImGui.Separator();
                    if (ImGui.MenuItem("Cut", "CTRL+X")) {}
                    if (ImGui.MenuItem("Copy", "CTRL+C")) {}
                    if (ImGui.MenuItem("Paste", "CTRL+V")) {}
                    ImGui.EndMenu();
                }
                if (ImGui.BeginMenu("Help"))
                {
                    if (ImGui.MenuItem("Online Documentation")) {}
                    if (ImGui.MenuItem("Video Tutorial")) {}
                    if (ImGui.MenuItem("Keyboard Shortcuts Reference")) {}
                    ImGui.Separator();
                    if (ImGui.MenuItem("About")) {}
                    ImGui.EndMenu();
                }
                ImGui.EndMainMenuBar();
            }
        }

        static void ShowMainToolBar()
        {
            ImGui.PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
            if (ImGui.BeginToolbar("main_toolbar", ImVec2(1, menu_height), toolbar_size))
            {
                foreach (auto* action in m_toolbar_actions)
                {
                    action->toolbarButton();
                }
            }
            ImGui.EndToolbar();
            ImGui.PopStyleVar();
        }

        public static void Draw()
        {
            ImGui.Begin("Another Window", ref _showAnotherWindow);
            ImGui.Text("Hello from another window!");
            if (ImGui.Button("Close Me"))
                _showAnotherWindow = false;
            ImGui.End();

            ShowMainMenuBar();
            ShowMainToolBar();

            ImGui.ShowDemoWindow();
        }
    }
}