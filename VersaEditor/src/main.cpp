#include <Versa.h>
#include <Core/Entry.h>
#include "EditorLayer.h"


class VersaEditor : public VersaMachina::Application
{
public:
    VersaEditor(VersaMachina::ApplicationCommandLineArgs args)
        : Application("VersaEditor", args)
    {
        PushLayer(new VersaMachina::EditorLayer());
    }
    ~VersaEditor()
    {
    }
};

VersaMachina::Application *VersaMachina::CreateApplication(VersaMachina::ApplicationCommandLineArgs args)
{
    return new VersaEditor(args);
}