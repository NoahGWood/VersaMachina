#pragma once
#include "Core/Base.h"
#include "Core/Application.h"

extern VersaMachina::Application* VersaMachina::CreateApplication();

int main(int argc, char** argv) {

    VersaMachina::Log::Init();

    VM_PROFILE_BEGIN_SESSION("Startup", "VersaMachinaProfile-Startup.json");
    auto app = VersaMachina::CreateApplication();
    VM_PROFILE_END_SESSION();

    VM_PROFILE_BEGIN_SESSION("Runtime", "VersaMachinaProfile-Runtime.json");
    app->Run();
    VM_PROFILE_END_SESSION();

    VM_PROFILE_BEGIN_SESSION("Shutdown", "VersaMachinaProfile-Shutdown.json");
    delete app;
    VM_PROFILE_END_SESSION();

    return 0;
}