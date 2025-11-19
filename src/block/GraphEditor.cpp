// #include <block/BlockSpec.h>

// namespace VM
// {
//     struct GraphEditorDelegate : public GraphEditor::Delegate
//     {
//         std::shared_ptr<AppContext> ctx; // Injected
//         std::vector<entt::entity> m_NodeIndexToEntity;
//         std::vector<entt::entity> m_LinkIndexToEntity;

//         size_t GetNodeCount() override {
//             auto view = ctx->blockRegistry().view<BlockInstance, CNodeVisual>();
//             m_NodeIndexToEntity.assign(view.begin(), view.end());
//             return m_NodeIndexToEntity.size();
//         }

//         bool AllowedLink(GraphEditor::NodeIndex from, GraphEditor::NodeIndex to) override
//         {
//             return true;
//         }
//         void SelectNode(GraphEditor::NodeIndex index, bool selected) override
//         {
//             m_Nodes[index].selected = selected;
//         }
//         void MoveSelectedNodes(const ImVec2 delta) override
//         {
//             for (auto &node : m_Nodes)
//             {
//                 if (!node.selected)
//                 {
//                     continue;
//                 }
//                 node.x += delta.x;
//                 node.y += delta.y;
//             }
//         }
//         void RightClick(GraphEditor::NodeIndex nodeIndex, GraphEditor::SlotIndex slotIndexInput, GraphEditor::SlotIndex slotIndexOutput) override
//         {
//         }
//         void AddLink(GraphEditor::NodeIndex inputNodeIndex, GraphEditor::SlotIndex inputSlotIndex, GraphEditor::NodeIndex outputNodeIndex, GraphEditor::SlotIndex outputSlotIndex) override
//         {
//             m_Links.push_back({inputNodeIndex, inputSlotIndex, outputNodeIndex, outputSlotIndex});
//         }
//         void DelLink(GraphEditor::LinkIndex index) override
//         {
//             m_Links.erase(m_Links.begin() + index);
//         }

//         void CustomDraw(ImDrawList *drawList, ImRect rectangle, GraphEditor::NodeIndex nodeIndex) override
//         {
//             drawList->AddLine(rectangle.Min, rectangle.Max, IM_COL32(0, 0, 0, 255));
//             drawList->AddText(rectangle.Min, IM_COL32(255, 128, 64, 255), "Draw");
//         }

//         const size_t GetTemplateCount() override
//         {
//             return sizeof(m_Templates) / sizeof(GraphEditor::Template);
//         }
//         const GraphEditor::Template GetTemplate(GraphEditor::TemplateIndex index) override
//         {
//             return m_Templates[index];
//         }
//         const size_t GetNodeCount() override
//         {
//             return m_Nodes.size();
//         }
//         const GraphEditor::Node GetNode(GraphEditor::NodeIndex index) override
//         {
//             const auto &node = m_Nodes[index];
//             return GraphEditor::Node{
//                 node.name,
//                 node.templateIndex,
//                 ImRect(ImVec2(node.x, node.y), ImVec2(node.x + 200, node.y + 200)),
//                 node.selected};
//         }
//         const size_t GetLinkCount() override
//         {
//             return m_Links.size();
//         }
//         const GraphEditor::Link GetLink(GraphEditor::LinkIndex index) override
//         {
//             return m_Links[index];
//         }
//         static const inline GraphEditor::Template m_Templates[] = {
//             {IM_COL32(160, 160, 180, 255),
//              IM_COL32(100, 100, 140, 255),
//              IM_COL32(110, 110, 150, 255),
//              1,
//              Array{"MyInput"},
//              nullptr,
//              2,
//              Array{"MyOutput0", "MyOuput1"},
//              nullptr},
//             {IM_COL32(180, 160, 160, 255),
//              IM_COL32(140, 100, 100, 255),
//              IM_COL32(150, 110, 110, 255),
//              3,
//              nullptr,
//              Array{IM_COL32(200, 100, 100, 255), IM_COL32(100, 200, 100, 255), IM_COL32(100, 100, 200, 255)},
//              1,
//              Array{"MyOutput0"},
//              Array{IM_COL32(200, 200, 200, 255)}}};

//         struct Node
//         {
//             int e;
//             const char *name;
//             GraphEditor::TemplateIndex templateIndex;
//             float x, y;
//             bool selected;
//         };

//         std::vector<Node> m_Nodes = {
//             {0,
//             "My Node 0",
//              0,
//              0, 0,
//              false},

//             {1, "My Node 1",
//              0,
//              400, 0,
//              false},

//             {2, "My Node 2",
//              1,
//              400, 400,
//              false}};

//         std::vector<GraphEditor::Link> m_Links = {{0, 0, 1, 0}};
//     };
// } // namespace VM
