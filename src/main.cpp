#include "VM.h"
#include <app/Application.h>
volatile std::sig_atomic_t g_SignalCaught = 0;

void SignalHandler(int signal){
    if(signal == SIGINT){
        g_SignalCaught = 1;
    }
}

int main(int argc, char* argv[]){
    std::signal(SIGINT, SignalHandler); // Ctrl+C
    VM::Logger::Init();
    VM::Application app;
    bool init_code = app.Init();
    if(!init_code) CORE_TRACE("Error initializing!");
    while(app.IsRunning()){
        if(g_SignalCaught){
            app.Shutdown();
        }
        if(!app.Tick()){
            app.Shutdown();
        }
    }
    // while (!g_SignalCaught && app.IsRunning() && app.Tick()) {
    //     if (!app.IsRunning()) break; // redundant but explicit
    // }
    return init_code;
}