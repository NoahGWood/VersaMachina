#include "Versa.h"
#include <UI/ImGUILayer.h>
#include <iostream>

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
            VM_INFO("ExampleLayer::Update");
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
//            PushLayer(new ExampleLayer());
            PushLayer(new ImGUILayer());
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
