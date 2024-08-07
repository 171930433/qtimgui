#include <QtImGui.h>
#include <QApplication>
#include <QTimer>
#include <QSurfaceFormat>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include "implot.h"
#include "imgui.h"

class DemoWindow : public QOpenGLWidget, private QOpenGLExtraFunctions
{
protected:
    void initializeGL() override
    {
        initializeOpenGLFunctions();
        QtImGui::initialize(this);
    }
    void paintGL() override
    {
        QtImGui::newFrame();

        // 1. Show a simple window
        // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
        {
            static float f = 0.0f;
            ImGui::Text("Hello, world!");
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
            ImGui::ColorEdit3("clear color", (float*)&clear_color);
            if (ImGui::Button("ImGui Demo")) show_imgui_demo_window ^= 1;
            if (ImGui::Button("ImPlot Demo")) show_implot_demo_window ^= 1;
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }

        // 2. Show another simple window, this time using an explicit Begin/End pair
        if (show_imgui_demo_window)
        {
            ImGui::SetNextWindowSize(ImVec2(200,100), ImGuiCond_FirstUseEver);
            ImGui::ShowDemoWindow(&show_imgui_demo_window);
        }

        // 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
        if (show_implot_demo_window)
        {
            ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
            ImPlot::CreateContext();
            ImPlot::ShowDemoWindow(&show_implot_demo_window);
            ImPlot::DestroyContext();
        }

        // Do render before ImGui UI is rendered
        glViewport(0, 0, width(), height());
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui::Render();
        QtImGui::render();
    }

private:
    bool show_imgui_demo_window = true;
    bool show_implot_demo_window = false;
    ImVec4 clear_color = ImColor(114, 144, 154);
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Use OpenGL 3 Core Profile, when available
    QSurfaceFormat glFormat;
    if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL)
    {
        glFormat.setVersion(3, 3);
        glFormat.setProfile(QSurfaceFormat::CoreProfile);
    }
    QSurfaceFormat::setDefaultFormat(glFormat);

    // Show window
    DemoWindow w;
    w.setWindowTitle("QtImGui widget example");
    w.resize(1280, 720);
    w.show();

    // Update at 60 fps
    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), &w, SLOT(update()));
    timer.start(16);

    return a.exec();
}
