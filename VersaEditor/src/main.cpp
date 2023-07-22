#include "Versa.h"
#include <iostream>

class ExampleLayer : public VersaMachina::Layer
{
    ExampleLayer()
    : Layer("Example") {}

    public:
        void OnUpdate() override
        {
            VM_INFO("ExampleLayer::Update");
        }

        void OnEvent(VersaMachina::Event& event) override
        {
//            VM_TRACE("{0}", event);
        }
};


class VersaEditor : public VersaMachina::Application
{
    public:
        VersaEditor()
        {
//            PushLayer(new ExampleLayer());
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
