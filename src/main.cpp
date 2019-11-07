#include <QtCore>
#include <imgui.h>


static const char* styleFileName = "./myimgui.style";
static const char* styleFileNamePersistent = "/persistent_folder/myimgui.style";   // Needed by Emscripten only


void InitGL()	// Mandatory
{
    // if (!myImageTextureId2) myImageTextureId2 = ImImpl_LoadTexture("./myNumbersTexture.png");


    const char* pStyleFileName = styleFileName;
    if (!ImGui::LoadStyle(pStyleFileName,ImGui::GetStyle()))   {
        printf("Warning: \"%s\" not present.\n",pStyleFileName);fflush(stdout);
        ImGui::ResetStyle(ImGuiStyle_Gray);
    }

// We might just choose one predefined style:
//ImGui::ResetStyle(ImGuiStyle_Gray,ImGui::GetStyle());

// This is something that does not work properly with all the addons:
//ImGui::GetIO().NavFlags |= ImGuiNavFlags_EnableKeyboard;
}
void ResizeGL(int /*w*/,int /*h*/)	// Mandatory
{

}
void DestroyGL()    // Mandatory
{
    // if (myImageTextureId2) {ImImpl_FreeTexture(myImageTextureId2);}
}

void showDebugWindow()
{
    static float f = 0.0f;

    ImGui::Text("Hello, world!");
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    // ImGui::ColorEdit3("clear color", (float*)&clear_color);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

#include "gui.h"
void DrawGL()	// Mandatory
{
    static Gui gui;
    gui.frame();
    // ImGui::Render();
}

//#   define USE_ADVANCED_SETUP   // in-file definition (see below). For now it just adds custom fonts and different FPS settings (please read below).


// Application code
#ifndef IMGUI_USE_AUTO_BINDING_WINDOWS  // IMGUI_USE_AUTO_ definitions get defined automatically (e.g. do NOT touch them!)
int main(int argc, char** argv)
#else //IMGUI_USE_AUTO_BINDING_WINDOWS
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int iCmdShow)
#endif //IMGUI_USE_AUTO_BINDING_WINDOWS
{

    //#ifdef YES_IMGUIFREETYPE    // Testing only (to remove)
    //ImGuiFreeType::DefaultRasterizationFlags = ImGuiFreeType::Bold|ImGuiFreeType::Oblique;
    //#endif //YES_IMGUIFREETYPE

#   ifndef USE_ADVANCED_SETUP

    //ImImpl_InitParams::DefaultFontSizeOverrideInPixels = 26.f;   // Fast method to override the size of the default font (13.f)

    // Basic
#   ifndef IMGUI_USE_AUTO_BINDING_WINDOWS  // IMGUI_USE_AUTO_ definitions get defined automatically (e.g. do NOT touch them!)
    ImImpl_Main(NULL,argc,argv);
#   else //IMGUI_USE_AUTO_BINDING_WINDOWS
    ImImpl_WinMain(NULL,hInstance,hPrevInstance,lpCmdLine,iCmdShow);
#   endif //IMGUI_USE_AUTO_BINDING_WINDOWS


#   else //USE_ADVANCED_SETUP
    // Advanced
        static const ImWchar ranges[] =
        {
            0x0020, 0x00FF, // Basic Latin + Latin Supplement
            0x20AC, 0x20AC,	// €
            0x2122, 0x2122,	// ™
            0x2196, 0x2196, // ↖
            0x21D6, 0x21D6, // ⇖
            0x2B01, 0x2B01, // ⬁
            0x2B09, 0x2B09, // ⬉
            0x2921, 0x2922, // ⤡ ⤢
            0x263A, 0x263A, // ☺
            0x266A, 0x266A, // ♪
            0
        };
    const float fontSizeInPixels = 18.f;
                                  //-40.f; // If < 0, it's the number of lines that fit the whole screen (but without any kind of vertical spacing)
    ImFontConfig cfg;
#   ifdef IMIMPL_BUILD_SDF
    cfg.OversampleH=cfg.OversampleV=1;    // signed-distance-field fonts work better when these values are equal (default: 3,1 are not equal)
    //ImImpl_SdfShaderSetParams(ImVec4(0.460f,0.365f,0.120f,0.04f));	// (optional) Sets sdf params
#   endif //IMIMPL_BUILD_SDF

    // These lines load an embedded font (with no compression).
    const unsigned char ttfMemory[] =
#   include "./fonts/DejaVuSerifCondensed-Bold.ttf.inl"
//#   include "./fonts/DroidSerif-Bold.ttf.inl"
;   // tip: If you have signed chars (e.g. const char ttfMemory[] = ...) you can still cast ttfMemory as (const unsigned char*) later.

    ImImpl_InitParams gImGuiInitParams(
    -1,-1,NULL,                                                         // optional window width, height, title
    //------------------------------------------------------------------------------------------------------------------------
    NULL,
    //"./fonts/DejaVuSerifCondensed-Bold.ttf",                          // optional custom font from file (main custom font)
    //------------------------------------------------------------------------------------------------------------------------
    //NULL,0,
    (const unsigned char*) ttfMemory,sizeof(ttfMemory)/sizeof(ttfMemory[0]),    // optional custom font from memory (secondary custom font) WARNING (licensing problem): e.g. embedding a GPL font in your code can make your code GPL as well.
    //------------------------------------------------------------------------------------------------------------------------
    fontSizeInPixels,
    &ranges[0],
    &cfg,                                                               // optional ImFontConfig* (useful for merging glyph to the default font, according to ImGui)
    false                                                               // true = addDefaultImGuiFontAsFontZero
    );
    // IMPORTANT: If you need to add more than one TTF file,
    // or you need to load embedded font data encoded with a different ImImpl_InitParams::Compression type,
    // there's a second ctr that takes a ImVector<ImImpl_InitParams::FontData> (see imguibindings.h).
    // For a single compressed font loaded from an extern file, the first constructor should work (the file extension is used to detect the compression type).
    // In all cases, to use compressed/encoded data some additional definitions are necessary (for example: YES_IMGUIBZ2 and/or YES_IMGUISTRINGIFIER and/or IMGUI_USE_ZLIB).

    // Here are some optional tweaking of the desired FPS settings (they can be changed at runtime if necessary, but through some global values defined in imguibindinds.h)
    gImGuiInitParams.gFpsClampInsideImGui = 30.0f;  // Optional Max allowed FPS (!=0, default -1 => unclamped). Useful for editors and to save GPU and CPU power.
    gImGuiInitParams.gFpsDynamicInsideImGui = false; // If true when inside ImGui, the FPS is not constant (at gFpsClampInsideImGui), but goes from a very low minimum value to gFpsClampInsideImGui dynamically. Useful for editors and to save GPU and CPU power.
    gImGuiInitParams.gFpsClampOutsideImGui = 10.f;  // Optional Max allowed FPS (!=0, default -1 => unclamped). Useful for setting a different FPS for your main rendering.

//#   define TEST_IMAGE_GLYPHS    // Experimental (currently it works only with user glyphs from uniformly sized tiles in images (or from a whole image) (good for image icons), but we could extend the code in the future if requested to support font glyphs of different widths)
#   ifdef TEST_IMAGE_GLYPHS
    // 'S','P','F'
    ImImpl_InitParams::CustomFontGlyph::ImageData imageData(512,512,"Tile8x8.png",8,8); // The image we want to use for our glyphs
    gImGuiInitParams.customFontGlyphs.push_back(ImImpl_InitParams::CustomFontGlyph(0,'S',imageData, 9));
    gImGuiInitParams.customFontGlyphs.push_back(ImImpl_InitParams::CustomFontGlyph(0,'P',imageData,10));
    gImGuiInitParams.customFontGlyphs.push_back(ImImpl_InitParams::CustomFontGlyph(0,'F',imageData,11));

    // Numbers from 1 to 9
    ImImpl_InitParams::CustomFontGlyph::ImageData imageData2(128,128,"myNumbersTexture.png",3,3); // The image we want to use for our glyphs
    for (int i=0;i<10;i++)   {
        gImGuiInitParams.customFontGlyphs.push_back(ImImpl_InitParams::CustomFontGlyph(0,(ImWchar)('1'+i),imageData2,i,0.f));   // Here we use a zero advance_x_delta (default is 1.0f)
    }

    // Not sure how to specify an ImWchar using a custom definition (like FontAwesome in main2.cpp)...
#   endif //TEST_IMAGE_GLYPHS


#   ifndef IMGUI_USE_AUTO_BINDING_WINDOWS  // IMGUI_USE_AUTO_ definitions get defined automatically (e.g. do NOT touch them!)
    ImImpl_Main(&gImGuiInitParams,argc,argv);
#   else //IMGUI_USE_AUTO_BINDING_WINDOWS
    ImImpl_WinMain(&gImGuiInitParams,hInstance,hPrevInstance,lpCmdLine,iCmdShow);
#   endif //IMGUI_USE_AUTO_BINDING_WINDOWS

#   endif //USE_ADVANCED_SETUP

    // todo: 这里没起作用，前面阻塞循环了，for QT Signal/Slot
    QCoreApplication app(argc, argv);
	return app.exec();
}
