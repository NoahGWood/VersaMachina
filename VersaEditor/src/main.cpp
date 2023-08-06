#include <Versa.h>
#include <Core/Entry.h>
#include "EditorLayer.h"


class VersaEditor : public VersaMachina::Application
{
public:
    VersaEditor()
    {
        PushLayer(new VersaMachina::EditorLayer());
    }
    ~VersaEditor()
    {
    }
};

VersaMachina::Application *VersaMachina::CreateApplication()
{
    return new VersaEditor();
}