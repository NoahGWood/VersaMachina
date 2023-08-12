#pragma once

#include "Versa.h"
#include "panels/SceneHierarchyPanel.h"
#define VERSA_MACHINA
#include <ImGuizmo/GraphEditor.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui/imgui_internal.h>
#define IMAPP_IMPL


template <typename T, std::size_t N>
struct Array
{
   T data[N];
   const size_t size() const { return N; }

   const T operator [] (size_t index) const { return data[index]; }
   operator T* () {
      T* p = new T[N];
      memcpy(p, data, sizeof(data));
      return p;
   }
};

template <typename T, typename ... U> Array(T, U...)->Array<T, 1 + sizeof...(U)>;
struct GraphEditorDelegate : public GraphEditor::Delegate
{
   bool AllowedLink(GraphEditor::NodeIndex from, GraphEditor::NodeIndex to) override
   {
      return true;
   }

   void SelectNode(GraphEditor::NodeIndex nodeIndex, bool selected) override
   {
      mNodes[nodeIndex].mSelected = selected;
   }

   void MoveSelectedNodes(const ImVec2 delta) override
   {
      for (auto& node : mNodes)
      {
         if (!node.mSelected)
         {
            continue;
         }
         node.x += delta.x;
         node.y += delta.y;
      }
   }

   virtual void RightClick(GraphEditor::NodeIndex nodeIndex, GraphEditor::SlotIndex slotIndexInput, GraphEditor::SlotIndex slotIndexOutput) override
   {
   }

   void AddLink(GraphEditor::NodeIndex inputNodeIndex, GraphEditor::SlotIndex inputSlotIndex, GraphEditor::NodeIndex outputNodeIndex, GraphEditor::SlotIndex outputSlotIndex) override
   {
      mLinks.push_back({ inputNodeIndex, inputSlotIndex, outputNodeIndex, outputSlotIndex });
   }

   void DelLink(GraphEditor::LinkIndex linkIndex) override
   {
      mLinks.erase(mLinks.begin() + linkIndex);
   }

   void CustomDraw(ImDrawList* drawList, ImRect rectangle, GraphEditor::NodeIndex nodeIndex) override
   {
      drawList->AddLine(rectangle.Min, rectangle.Max, IM_COL32(0, 0, 0, 255));
      drawList->AddText(rectangle.Min, IM_COL32(255, 128, 64, 255), "Draw");
   }

   const size_t GetTemplateCount() override
   {
      return sizeof(mTemplates) / sizeof(GraphEditor::Template);
   }

   const GraphEditor::Template GetTemplate(GraphEditor::TemplateIndex index) override
   {
      return mTemplates[index];
   }

   const size_t GetNodeCount() override
   {
      return mNodes.size();
   }

   const GraphEditor::Node GetNode(GraphEditor::NodeIndex index) override
   {
      const auto& myNode = mNodes[index];
      return GraphEditor::Node
      {
          myNode.name,
          myNode.templateIndex,
          ImRect(ImVec2(myNode.x, myNode.y), ImVec2(myNode.x + 200, myNode.y + 200)),
          myNode.mSelected
      };
   }

   const size_t GetLinkCount() override
   {
      return mLinks.size();
   }

   const GraphEditor::Link GetLink(GraphEditor::LinkIndex index) override
   {
      return mLinks[index];
   }

   // Graph datas
   static const inline GraphEditor::Template mTemplates[] = {
       {
           IM_COL32(160, 160, 180, 255),
           IM_COL32(100, 100, 140, 255),
           IM_COL32(110, 110, 150, 255),
           1,
           Array{"MyInput"},
           nullptr,
           2,
           Array{"MyOutput0", "MyOuput1"},
           nullptr
       },

       {
           IM_COL32(180, 160, 160, 255),
           IM_COL32(140, 100, 100, 255),
           IM_COL32(150, 110, 110, 255),
           3,
           nullptr,
           Array{ IM_COL32(200,100,100,255), IM_COL32(100,200,100,255), IM_COL32(100,100,200,255) },
           1,
           Array{"MyOutput0"},
           Array{ IM_COL32(200,200,200,255)}
       }
   };

   struct Node
   {
      const char* name;
      GraphEditor::TemplateIndex templateIndex;
      float x, y;
      bool mSelected;
   };

   std::vector<Node> mNodes = {
       {
           "My Node 0",
           0,
           0, 0,
           false
       },

       {
           "My Node 1",
           0,
           400, 0,
           false
       },

       {
           "My Node 2",
           1,
           400, 400,
           false
       }
   };

   std::vector<GraphEditor::Link> mLinks = { {0, 0, 1, 0} };
};

namespace VersaMachina
{
class EditorLayer : public Layer
{
    public:
        EditorLayer();
        ~EditorLayer() = default;
        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnEvent(Event &e) override;
        virtual void OnUpdate(Timestep ts) override;
    	virtual void OnImGuiRender() override;

    private:
         // Editor
         Camera::EditorCamera m_EditorCamera;
         // Scene Management
         Ref<ECS::Scene> m_Scene;
         std::string m_SceneFile;
         ECS::Entity m_HoveredEntity;
         // Rendering
         Ref<Render::Framebuffer> m_Framebuffer;
         glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
         glm::vec2 m_ViewportBounds[2];
         bool m_ViewportFocused=false, m_ViewportHovered=false;
         // Panels
         SceneHierarchyPanel m_SceneHierarchyPanel;
         // Gizmos
         int m_ImGuizmoType = -1;
         // Node editor
         GraphEditorDelegate m_NodeDelegate;
         GraphEditor::Options m_NodeOptions;
         GraphEditor::ViewState m_NodeViewState;
         GraphEditor::FitOnScreen m_NodeFit = GraphEditor::Fit_None;

    private:
        bool OnMouseButtonPressed(VersaMachina::MouseButtonPressedEvent& e);
        bool OnKeyPressed(VersaMachina::KeyPressedEvent& e);
        void NewScene();
        void Open();
        void Save();
        void SaveAs();
    };    
} // namespace VersaMachina

