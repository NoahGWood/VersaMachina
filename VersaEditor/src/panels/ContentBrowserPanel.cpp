#include "pch.h"
#include "panels/ContentBrowserPanel.h"

#include <imgui/imgui.h>
#include <filesystem>

namespace VersaMachina
{
    // Once we have projects, change this.
    extern const std::filesystem::path g_AssetPath = "VersaEditor/assets";

    ContentBrowserPanel::ContentBrowserPanel()
        : m_CurrentDirectory(g_AssetPath), m_LastDirectory(g_AssetPath)
        {
            m_DirectoryIcon = Render::Texture2D::Create("VersaEditor/resources/DirectoryIcon.png");
            m_FileIcon = Render::Texture2D::Create("VersaEditor/resources/FileIcon.png");
        }

    void ContentBrowserPanel::OnImGuiRender()
    {
        ImGui::Begin("Content Browser");


        m_Focused = ImGui::IsWindowFocused();
        m_Hovered = ImGui::IsWindowHovered();
        Application::Get().GetImGuiLayer()->BlockEvents(!m_Focused || !m_Hovered);

        // Iterate through directory

        if (m_CurrentDirectory != std::filesystem::path(g_AssetPath))
        {
            if (ImGui::Button("<-"))
            {
                BackButton();
            }
        }

		static float padding = 16.0f;
		static float thumbnailSize = 128.0f;
		float cellSize = thumbnailSize + padding;

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / cellSize);
		if (columnCount < 1)
			columnCount = 1;

		ImGui::Columns(columnCount, 0, false);

        for (auto &p : std::filesystem::directory_iterator(m_CurrentDirectory))
        {
            const auto path = p.path();
			auto relativePath = std::filesystem::relative(path, g_AssetPath);
            std::string relPathString = relativePath.filename().string();

            ImGui::PushID(relPathString.c_str());
            Ref<Render::Texture2D> icon = p.is_directory() ? m_DirectoryIcon : m_FileIcon;           
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0,0,0,0));
            ImGui::ImageButton((ImTextureID)icon->GetRendererID(), { thumbnailSize, thumbnailSize}, {0,1}, {1,0});

            if(ImGui::BeginDragDropSource())
            {
                // std::filesystem::path::c_str uses wchar_t, so if shit's all fucked up, that's probably why
                ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", path.c_str(), std::strlen(path.c_str()) * sizeof(wchar_t));
                ImGui::EndDragDropSource();
            }

            ImGui::PopStyleColor();

            if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
            {
                if(p.is_directory())
                    m_CurrentDirectory /= path.filename();
            }
            ImGui::TextWrapped(relPathString.c_str());
            ImGui::NextColumn();
            ImGui::PopID();
        }
        ImGui::Columns(1);

		ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
		ImGui::SliderFloat("Padding", &padding, 0, 32);
        ImGui::End();
    }

    void ContentBrowserPanel::NextButton()
    {
        if(m_LastDirectory != g_AssetPath)
            m_CurrentDirectory = m_LastDirectory;
            
        if(m_CurrentDirectory != g_AssetPath)
            m_LastDirectory = m_CurrentDirectory.parent_path();
    }
    void ContentBrowserPanel::BackButton()
    {
        if(m_CurrentDirectory != g_AssetPath)
        {
            m_LastDirectory = m_CurrentDirectory;
            m_CurrentDirectory = m_CurrentDirectory.parent_path();
        }
    }

} // namespace VersaMachina
