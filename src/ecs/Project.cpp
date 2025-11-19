#include <ecs/Project.h>
#include <ecs/ProjectSerializer.h>
#include <ecs/Components.h>

namespace VM
{
    entt::entity Project::CreateEntity(const std::string &name)
    {
        auto e = m_Registry.create();
        AddComponent<TagComponent>(e, name);
        AddComponent<TransformComponent>(e);
        AddComponent<HierarchyComponent>(e);
        return e;
    }
    entt::entity Project::CreateEntity(entt::entity id, const std::string &name, entt::entity parent)
    {
        auto e = m_Registry.create(id);
        AddComponent<TagComponent>(e, name);
        AddComponent<TransformComponent>(e);
        auto hc = AddComponent<HierarchyComponent>(e);
        if (parent != entt::null && IsValid(parent))
        {
            hc.parent = parent;
            auto ph = m_Registry.get<HierarchyComponent>(parent);
            ph.children.push_back(e);
        }
        return e;
    }


    entt::entity Project::CloneEntity(const entt::entity& entity){
        if(!IsValid(entity)) return entt::null;
        auto e = m_Registry.create();
        for(auto& [type, ops] : ComponentRegistry::Instance().All()){
            ops.clone(m_Registry, entity, e);
        }
        return e;
    }

    void Project::DestroyEntity(entt::entity id) {
        if (!m_Registry.valid(id))
            return;
        auto* h = m_Registry.try_get<HierarchyComponent>(id);
        if (h && h->parent != entt::null) {
            if (auto* ph = m_Registry.try_get<HierarchyComponent>(h->parent)) {
                std::erase(ph->children, id);
            }
        }
        DestroyEntityRecursively(id);
    }

    void Project::DestroyEntityRecursively(entt::entity id){
        if (!m_Registry.valid(id))
            return;
        auto* h = m_Registry.try_get<HierarchyComponent>(id);
        if (h) {
            auto children = h->children;          // copy so we can safely mutate registry
            for (auto child : children) {
                DestroyEntityRecursively(child);
            }
        }
        m_Registry.destroy(id);
    }     

    void Project::Save()
    {
        ProjectSerializer ser(*this);
        ser.Serialize(m_ProjectDir / m_Name);
    }

    void Project::SaveAs(const std::filesystem::path &file)
    {
        if (std::string(file.stem()).empty())
        {
            m_ProjectDir = file;
        }
        else
        {
            m_Name = file.stem();
            m_ProjectDir = file.parent_path();
        }
        Save();
    }

    void Project::SetParent(entt::entity child, entt::entity newParent)
    {
        if(child == newParent || IsAncestor(child, newParent)){
            CORE_WARN("New Parent is Ancestor or Child");
            return;
        }

        auto& hChild = GetComponent<HierarchyComponent>(child);
        auto& oParent = hChild.parent;
        if (oParent != entt::null)
        {
            auto& oldH = GetComponent<HierarchyComponent>(oParent);
            std::erase(oldH.children, child);
        }
        hChild.parent = newParent;
        if (newParent != entt::null)
        {
            auto& newH = GetComponent<HierarchyComponent>(newParent);
            newH.children.push_back(child);
        }
    }
    void Project::ReparentAndReorder(entt::entity child, entt::entity newParentOrSibling)
    {
        auto &reg = m_Registry;
        auto &childH = reg.get<HierarchyComponent>(child);
        if(IsAncestor(child, newParentOrSibling)){
            CORE_WARN("Dragged to child");
            return;
        }
        entt::entity oldParent = childH.parent;

        auto &newParentH = reg.get<HierarchyComponent>(newParentOrSibling);
        entt::entity newParent = newParentH.parent == entt::null && newParentOrSibling != child
                                     ? newParentOrSibling // drop ON node -> becomes its child
                                     : newParentH.parent; // tweak if you want sibling semantics

        // remove from old parent
        if (oldParent != entt::null)
        {
            auto &oldH = reg.get<HierarchyComponent>(oldParent);
            std::erase(oldH.children, child);
        }

        // attach to new parent (as last child for now)
        childH.parent = newParent;
        if (newParent != entt::null)
        {
            auto &parentH = reg.get<HierarchyComponent>(newParent);
            parentH.children.push_back(child);
        }
    }

    bool Project::IsAncestor(entt::entity ancestor, entt::entity node) {
        if (ancestor == entt::null || node == entt::null)
            return false;

        while(node != entt::null){
            if(node == ancestor) return true;
            auto h = GetComponent<HierarchyComponent>(node);
            node = h.parent;
        }    
        return false;
    }

    EntitySnapshot Project::GetEntitySnapshot(entt::entity e){
        EntitySnapshot snapshot;
        snapshot.entity = e;
        for(auto& [type, ops] : ComponentRegistry::Instance().All()){
            ops.snapshot(m_Registry, e, snapshot.components);
        }
        // Handle hierarchy component special case
        auto h = GetComponent<HierarchyComponent>(e);
        snapshot.parent = h.parent;
        for(const auto child : h.children){
            snapshot.children.push_back(GetEntitySnapshot(child));
        }
        return snapshot;
    }

    void Project::RestoreEntitySnapshot(const EntitySnapshot& snapshot){
        for(auto& [type, ops] : ComponentRegistry::Instance().All()){
            ops.restore(m_Registry, snapshot.entity, snapshot.components);
        }
        if(snapshot.parent != entt::null){
            SetParent(snapshot.entity, snapshot.parent);
        }
        for(const auto child : snapshot.children){
            RestoreEntitySnapshot(child);
        }
    }
    // EntitySnapshot Project::GetEntitySnapshot(entt::entity entity){
    //     EntitySnapshot snapshot;
    //     snapshot.entity = entity;
    //     for(auto& [type, ops] : m_ComponentOps){
    //         ops.snapshot(m_Registry, entity, snapshot.components);
    //     }
    //     return snapshot;
    // }
    // void Project::RestoreEntitySnapshot(entt::entity entity, const EntitySnapshot& snapshot){
    //     for(auto& [type, ops] : m_ComponentOps){
    //         ops.restore(m_Registry, entity, snapshot.components);
    //     }
    // }

} // namespace VM
