#include <Versa.h>
#include <Core/Entry.h>
#include "Sandbox2D.h"


class VersaEditor : public VersaMachina::Application
{
public:
    VersaEditor()
    {
        PushLayer(new Sandbox2D());
        VM_INFO("Hello, VersaMachina World");
        VM_TRACE("Trace");
        VM_INFO("Info");
        VM_WARN("Warn");
        VM_ERROR("Error");
        VM_CRITICAL("Critical");
    }
    ~VersaEditor()
    {
    }
};

VersaMachina::Application *VersaMachina::CreateApplication()
{
    return new VersaEditor();
}