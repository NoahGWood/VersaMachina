#include <window/Window.h>
#include <app/Application.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#include <SDL_opengl.h>
#include <ImGuizmo.h>

namespace VM
{
    static std::string AppDir;

    bool Window::Init(std::shared_ptr<AppContext> context){
        m_AppContext = context;
        std::string name = "VM";
        AppDir = PlatformDirs::get_app_dir("VersaMachina");
        std::filesystem::create_directory(AppDir);

        int width=800, height=480;
        // Create SDL window
        CORE_INFO("Initializing SDL...");
        if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0){
            CORE_ERROR("SDL_Init failed: {}", SDL_GetError());
            return false;
        }
        CORE_TRACE("SDL Initialized.");
        CORE_TRACE("Setting OpenGL Attributes...");
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        CORE_INFO("Creating Window...");
        m_Window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL |
                SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
            );
        if(!m_Window){
            CORE_ERROR("Error while creating window: {}",SDL_GetError());
            return false;
        }
        CORE_INFO("Creating GL Context");
        m_Context = SDL_GL_CreateContext(m_Window);
        if(!m_Context){
            CORE_ERROR("Error while creating GL Context.");
            return false;
        }
        CORE_INFO("SDL Window Created: {} ({}x{})", name, width, height);
        // Subscribe to tick event
        m_AppContext->eventRouter().Subscribe(EventCategory::App, EventType::Tick, [this](Event& e){
            if(auto* tick = std::get_if<AppTickData>(&e.data)){
                Tick(tick->deltaTime);
                return true;
            }
            return false;
        });
        CORE_INFO("Initializing ImGui...");
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;
        io.IniFilename = NULL;
        ImGui::StyleColorsDark();
        ImGui_ImplSDL2_InitForOpenGL(m_Window, m_Context);
        ImGui_ImplOpenGL3_Init("#version 130");
        ImGui::LoadIniSettingsFromDisk((AppDir + "/settings.ini").c_str());
        CORE_INFO("Window setup complete.");
        return true;
    }

    bool Window::Tick(double dt){
        if (!m_Window || !m_Context || !Application::Get().IsRunning()){
            return false;
        }
        if(!PollEvents()) return false;
        if(BeginFrame()){
            if(!Render()) {
                CORE_ERROR("Error rendering frame.");
                return false;
            }
            if(!EndFrame()){
                CORE_ERROR("Error ending frame.");
                return false;
            }
            return true;
        } 
        CORE_ERROR("Error creating new frame.");
        return false;
    }

    bool Window::PollEvents(){
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                Application::Get().Shutdown();
                return false;
            }
            // Handle closing on multi-viewports
            else if (e.type == SDL_WINDOWEVENT){
                if(e.window.event == SDL_WINDOWEVENT_CLOSE){
                    if(e.window.windowID == SDL_GetWindowID(m_Window)) {
                        Application::Get().Shutdown();
                        return false;
                    }
                }
            }       // Handle resize
            if(e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED){
                int newW = e.window.data1;
                int newH = e.window.data2;
                glViewport(0, 0, newW, newH);
            }
            ImGui_ImplSDL2_ProcessEvent(&e);
        }
        return true;
    }

    bool Window::BeginFrame(){
        if(!m_Window) CORE_FATAL("Lost window pointer during Window::BeginFrame!");
        if(!m_Context) CORE_FATAL("Lost GL Context during Window::BeginFrame!");
        // Resize framebuffer
        SDL_GL_GetDrawableSize(m_Window, &m_Width, &m_Height);
        if(m_Width <=0 || m_Height<= 0) return false; // Nothing to render
        auto io = ImGui::GetIO();
        io.DisplaySize = ImVec2((float)m_Width, (float)m_Height);
        // Start a new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        ImGuizmo::BeginFrame();
        // Create dockspace if needed
        if(io.ConfigFlags & ImGuiConfigFlags_DockingEnable){
            ImGui::DockSpaceOverViewport();
        }
        return true;
    }

    bool Window::Render(){
        if(!m_Window) CORE_FATAL("Lost window pointer during Window::BeginFrame!");
        if(!m_Context) CORE_FATAL("Lost GL Context during Window::BeginFrame!");
        if(ImGui::BeginMainMenuBar()){
            for(auto& p : m_Menus){
                p->Render();
            }
            if(ImGui::BeginMenu("Window")){
                for(auto& p : m_Panels){
                    if(ImGui::MenuItem(p->Name().c_str(),nullptr,nullptr,!p->IsOpen())){
                        p->Open();
                    }
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
        for(auto& p : m_Panels){
            if(p->IsOpen()) p->Render();
        }
        ImGui::ShowDemoWindow();
        ImGui::Render();
        // Handle undo/redo
        if (ImGui::IsKeyDown(ImGuiKey_ModCtrl) && ImGui::IsKeyPressed(ImGuiKey_Z)){
            m_AppContext->cmdManager().Undo(m_AppContext->project());
        }
        if (ImGui::IsKeyDown(ImGuiKey_ModCtrl) && ImGui::IsKeyPressed(ImGuiKey_Y))
            m_AppContext->cmdManager().Redo(m_AppContext->project());
        return true;
    }

    bool Window::EndFrame(){
        if(!m_Window) CORE_FATAL("Lost window pointer during Window::BeginFrame!");
        if(!m_Context) CORE_FATAL("Lost GL Context during Window::BeginFrame!");
        auto io = ImGui::GetIO();
        // Update platform windows if multi-viewport
        if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable){
            SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
            SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
        }
        // Clear GL buffers (color/depth) before drawing
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(m_Window);
        SDL_Delay(16);
        return true;

    }

    bool Window::Shutdown(){
        ImGui::SaveIniSettingsToDisk((AppDir + "/settings.ini").c_str());
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
        if(m_Context) {
            SDL_GL_DeleteContext(m_Context);
            m_Context = nullptr;
        }
        if(m_Window){
            SDL_DestroyWindow(m_Window);
            m_Window = nullptr;
        }
        SDL_Quit();
        return true;
    }
} // namespace VM
