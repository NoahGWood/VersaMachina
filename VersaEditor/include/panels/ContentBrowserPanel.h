#pragma once

#include "Render/Texture.h"

#include <filesystem>

namespace VersaMachina
{
    class ContentBrowserPanel
    {
        public:
            ContentBrowserPanel();

            void OnImGuiRender();
        private:
            std::filesystem::path m_CurrentDirectory;
            Ref<Render::Texture2D> m_DirectoryIcon;
            Ref<Render::Texture2D> m_FileIcon;
    };

} // namespace VersaMachina
