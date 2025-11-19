#pragma once
#include "common/Base.h"
#include <app/AppContext.h>
#include "ecs/Project.h"
#include "ecs/Components.h"
#include <ImGuizmo.h>
#include <GraphEditor.h>

namespace VM
{

    template <typename T, std::size_t N>
    struct Array
    {
        T data[N];
        const size_t size() const { return N; }

        const T operator[](size_t index) const { return data[index]; }
        operator T *()
        {
            T *p = new T[N];
            memcpy(p, data, sizeof(data));
            return p;
        }
    };

    template <typename T, typename... U>
    Array(T, U...) -> Array<T, 1 + sizeof...(U)>;

    struct TemplateBinding {
        std::string blockId;

        GraphEditor::Template tmpl;

        // slot index → port index (into BlockInstance::ports)
        std::vector<size_t> inputPortIndices;
        std::vector<size_t> outputPortIndices;

        // inverse: port index → slot index, -1 = not in that side
        std::vector<int> portToInputSlot;
        std::vector<int> portToOutputSlot;
    };

    // void BuildTemplateForPrefab(const BlockPrefab& bp, TemplateBinding& tb){
    //     tb.blockId = bp.id;
    //     tb.portToInputSlot.assign(bp.ports.size(), -1);
    //     tb.portToOutputSlot.assign(bp.ports.size(), -1);
    //     for(size_t i=0; i<bp.ports.size(); ++i){
    //         const auto& p = bp.ports[i];
    //         if(IsInputDir(p.dir)){
    //             tb.portToInputSlot[i]
    //         }
    //     }
    // }

    struct GraphEditorDelegate : public GraphEditor::Delegate
    {
            bool AllowedLink(GraphEditor::NodeIndex from, GraphEditor::NodeIndex to) override {
                return true; // TODO
            }
            const size_t GetNodeCount() override {
                m_NodeIndexToEntity.clear();
                m_EntityToNodeIndex.clear();
                auto view = m_AppContext->project().GetRegistry().view<BlockInstance>();
                for(auto e : view ){
                    m_EntityToNodeIndex[e] = (GraphEditor::NodeIndex)m_NodeIndexToEntity.size();
                    m_NodeIndexToEntity.push_back(e);
                }
                return m_NodeIndexToEntity.size();
            }
            const GraphEditor::Node GetNode(GraphEditor::NodeIndex idx) override {
                IM_ASSERT(idx < m_NodeIndexToEntity.size());
                auto e = m_NodeIndexToEntity[idx];
                auto& bi = m_AppContext->project().GetComponent<BlockInstance>(e);
                GraphEditor::Node n;
                n.mName = bi.label.c_str();
                n.mTemplateIndex = 0;
                n.mRect = ImRect(bi.position,ImVec2(bi.position.x+220,bi.position.y+120));
                n.mSelected = bi.selected;
                return n;
            }
            void SelectNode(GraphEditor::NodeIndex idx, bool selected) override {
                m_AppContext->project().GetComponent<BlockInstance>(m_NodeIndexToEntity[idx]).selected = selected;
                // m_Nodes[idx].mSelected = selected;
            }
            void MoveSelectedNodes(const ImVec2 delta) override {
                auto view = m_AppContext->project().GetRegistry().view<BlockInstance>();
                for(auto [e, bi] : view.each()){
                    if(!bi.selected) continue;
                    bi.position.x += delta.x;
                    bi.position.y += delta.y;
                }
            }
            const size_t GetLinkCount() override {
                m_LinkCache.clear();
                auto view = m_AppContext->project().GetRegistry().view<BlockInstance>();
                for(auto [e, bi] : view.each()) {
                    for(auto& [portIndex, targets] : bi.connections){
                        for(auto &[other, port] : targets){
                            if((uint32_t)e >= (uint32_t)other) continue;
                            m_LinkCache.emplace_back(e, portIndex, other, port);
                        }
                    }
                }
                return m_LinkCache.size();
            }
            const GraphEditor::Link GetLink(GraphEditor::LinkIndex idx) override {
                auto [a, aPort, b, bPort] = m_LinkCache[idx];
                auto aNode = m_EntityToNodeIndex[a];
                auto bNode = m_EntityToNodeIndex[b];
                return GraphEditor::Link{
                    bNode,
                    bPort,
                    aNode,
                    aPort,
                };
            }
            void AddLink(GraphEditor::NodeIndex inNode, GraphEditor::SlotIndex inSlot,
                GraphEditor::NodeIndex outNode, GraphEditor::SlotIndex outSlot) override {
                auto inE = m_NodeIndexToEntity[inNode];
                auto outE = m_NodeIndexToEntity[outNode];
                auto& inBi = m_AppContext->project().GetComponent<BlockInstance>(inE);
                auto& outBi = m_AppContext->project().GetComponent<BlockInstance>(outE);
                // Validate
                inBi.connections[inSlot].push_back(std::make_pair(outE, outSlot));
                outBi.connections[outSlot].push_back(std::make_pair(inE, inSlot));
            }
            void DelLink(GraphEditor::LinkIndex idx) override {
                auto [a, aPort, b, bPort] = m_LinkCache[idx];

                auto& aBi = m_AppContext->project().GetComponent<BlockInstance>(a);
                auto& bBi = m_AppContext->project().GetComponent<BlockInstance>(b);

                auto delA = aBi.connections[aPort];
                auto delB = bBi.connections[bPort];

                auto removed_a = std::remove_if(delA.begin(), delA.end(),
                    [a](const std::pair<entt::entity, size_t>& p){
                        return p.first == a;
                    });
                auto removed_b = std::remove_if(delB.begin(), delB.end(),
                    [b](const std::pair<entt::entity, size_t>& p){
                        return p.first == b;
                    });
                
                // aBi.connections[aPort].reset();
                // bBi.connections[bPort].reset();

            }
            void CustomDraw(ImDrawList* drawList, ImRect rectangle, GraphEditor::NodeIndex nodeIndex) override {

            }

            void RightClick(GraphEditor::NodeIndex nodeIndex, GraphEditor::SlotIndex slotIndexIn, GraphEditor::SlotIndex slotIndexOut) override {

            }

            const size_t GetTemplateCount() override{
                return 2;
            }
            const GraphEditor::Template GetTemplate(GraphEditor::TemplateIndex idx) override {
                return m_Templates[idx];
            }

            static const inline GraphEditor::Template m_Templates[] = {
            {IM_COL32(160, 160, 180, 255),
             IM_COL32(100, 100, 140, 255),
             IM_COL32(110, 110, 150, 255),
             1,
             Array{"MyInput"},
             nullptr,
             2,
             Array{"MyOutput0", "MyOuput1"},
             nullptr},
            {IM_COL32(180, 160, 160, 255),
             IM_COL32(140, 100, 100, 255),
             IM_COL32(150, 110, 110, 255),
             3,
             nullptr,
             Array{IM_COL32(200, 100, 100, 255), IM_COL32(100, 200, 100, 255), IM_COL32(100, 100, 200, 255)},
             1,
             Array{"MyOutput0"},
             Array{IM_COL32(200, 200, 200, 255)}}};

            std::vector<GraphEditor::Node> m_Nodes;
            std::shared_ptr<AppContext> m_AppContext;
            std::vector<entt::entity> m_NodeIndexToEntity;
            std::unordered_map<entt::entity, GraphEditor::NodeIndex> m_EntityToNodeIndex;
            std::vector<std::tuple<entt::entity,size_t,entt::entity,size_t>> m_LinkCache;
    };
} // namespace VM
