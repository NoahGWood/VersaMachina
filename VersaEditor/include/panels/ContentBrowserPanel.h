#pragma once

#include "Core/Application.h"
#include "Render/Texture.h"

#include <filesystem>

namespace VersaMachina
{
    class ContentBrowserPanel
    {
        public:
            ContentBrowserPanel();
            void OnImGuiRender();

            void NextButton();
            void BackButton();

        private:
            friend class EditorLayer;
            bool m_Focused = false, m_Hovered = false;
            std::filesystem::path m_CurrentDirectory;
            std::filesystem::path m_LastDirectory;
            Ref<Render::Texture2D> m_DirectoryIcon;
            Ref<Render::Texture2D> m_FileIcon;
    };

} // namespace VersaMachina
