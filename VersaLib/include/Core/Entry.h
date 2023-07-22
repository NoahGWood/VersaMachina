#pragma once

extern VersaMachina::Application* VersaMachina::CreateApplication();

int main(int argc, char** argv) {

    VersaMachina::Log::Init();
    VM_CORE_WARN("Initialized Log!");
    VM_INFO("Initialized Log!");
    auto app = VersaMachina::CreateApplication();
    app->Run();
    delete app;

    return 0;
}