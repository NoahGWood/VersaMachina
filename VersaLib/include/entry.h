#pragma once
//#include <application.h>

extern VersaMachina::Application* VersaMachina::CreateApplication();

int main(int argc, char** argv) {
    auto app = VersaMachina::CreateApplication();
    app->Run();
    delete app;
}