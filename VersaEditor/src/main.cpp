#include "Versa.h"
#include <UI/ImGUILayer.h>
#include <iostream>
#include "imgui/imgui.h"

using namespace VersaMachina;
using namespace UI;

class ExampleLayer : public VersaMachina::Layer
{
    public:
        ExampleLayer()
        : Layer("Example") {}


        void OnAttach() override {}
        void OnDetach() override {}
        void OnUpdate() override
        {
//            VM_INFO("ExampleLayer::Update");
            
            if(Input::Input::IsKeyPressed(Key::Tab))
                VM_INFO("Tab key pressed");
        }


        virtual void OnImGuiRender() override
        {
            ImGui::Begin("Test");
            ImGui::Text("Hello World!");
            ImGui::End();
        }

        void OnEvent(VersaMachina::Event& event) override
        {
            VM_INFO("ExampleLayer::Event: {0}", event);
        }

};


class VersaEditor : public VersaMachina::Application
{
    public:
        VersaEditor()
        {
            PushLayer(new ExampleLayer());
//            PushOverlay(new ImGUILayer());
            VM_INFO("Hello, VersaMachina World");
        }
        ~VersaEditor()
        {

        }
};

VersaMachina::Application* VersaMachina::CreateApplication()
{
    return new VersaEditor();
}