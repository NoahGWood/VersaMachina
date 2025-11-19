#pragma once
#include <common/Base.h>
#include <cmd/ICommand.h>
#include <ecs/EntitySnapshot.h>

namespace VM
{
    // Generic Create command for any entity type
    using LifecycleCallback = std::function<void(Project&, entt::entity)>;
    class CreateEntityCommand : public ICommand {
        public:
            CreateEntityCommand(const std::string& name="Entity",
            const std::optional<LifecycleCallback> create = std::nullopt,
            const std::optional<LifecycleCallback> undo = std::nullopt)
            : m_Entity(entt::null), m_Name(std::move(name)) {
                if(create) m_Create = *create;
                if(undo) m_Undo = *undo;
            }
            const std::string Name() const override { return "Create Entity"; }

            void Execute(Project& project) override {
                if(m_Entity == entt::null || !project.IsValid(m_Entity)){
                    // Recreate using old ID if possible
                    m_Entity = project.CreateEntity(m_Entity, m_Name);
                    // Restore snapshot if available
                    if(m_Snapshot){
                        project.RestoreEntitySnapshot(*m_Snapshot);
                    }
                    // callbacks
                    if(m_Create) m_Create(project, m_Entity);
                }
            }
            void Undo(Project& project) override {
                if(m_Entity != entt::null && project.IsValid(m_Entity)){
                    // TODO: Save snapshot/state before destruction
                    m_Snapshot = project.GetEntitySnapshot(m_Entity);
                    if(m_Undo) m_Undo(project, m_Entity);
                    project.DestroyEntity(m_Entity);
                }
            }
        private:
            entt::entity m_Entity;
            std::string m_Name;
            LifecycleCallback m_Create;
            LifecycleCallback m_Undo;
            std::optional<EntitySnapshot> m_Snapshot;       
    };

    class DeleteEntityCommand : public ICommand{
        public:
            DeleteEntityCommand(const entt::entity& e)
                : m_Entity(e) {}
            const std::string Name() const override { return "Delete Entity"; }
            void Execute(Project& project) override {
                if(m_Entity != entt::null && project.IsValid(m_Entity)){
                    m_Snapshot = project.GetEntitySnapshot(m_Entity);
                    project.DestroyEntity(m_Entity);
                }
            }
            void Undo(Project& project) override {
                if(!project.IsValid(m_Entity)){
                    if(m_Snapshot){
                        project.RestoreEntitySnapshot(*m_Snapshot);                           
                    }
                }
            }
        private:
            entt::entity m_Entity;
            std::optional<EntitySnapshot> m_Snapshot;
    };

    class CopyPasteEntityCommand : public ICommand {
        public:
            CopyPasteEntityCommand(entt::entity copied)
                : m_Copied(copied) { }
            const std::string Name() const override { return "Copy Past Entity"; }
            void Execute(Project& project) override {
                if(m_Entity == entt::null || ! project.IsValid(m_Entity)){
                    m_Entity = project.CloneEntity(m_Copied);
                } else {
                    if(project.IsValid(m_Entity)){
                        CORE_ERROR("Pasting Entity with ID already exists. Skipping command.");
                        return;
                    }
                    // Entity past was undone and redone, restore snapshot
                    // m_Deleted->Undo(project);
                }
            }
            void Undo(Project& project) override {
                if(m_Entity != entt::null && project.IsValid(m_Entity)){
                    project.DestroyEntity(m_Entity);
                }
            }
        private:
            entt::entity m_Copied = entt::null;
            entt::entity m_Entity = entt::null;
    };

    class ReparentEntityCommand : public ICommand {
        public:
            ReparentEntityCommand(entt::entity child, entt::entity parent)
                : m_Child(child), m_Parent(parent) {}
            const std::string Name() const override { return "Reparent Entity"; }
            void Execute(Project& project) override {
                if(m_Child != entt::null){
                    auto h = project.GetComponent<HierarchyComponent>(m_Child);
                    m_OldParent = h.parent;
                    project.SetParent(m_Child, m_Parent);
                }
            }
            void Undo(Project& project) override {
                if(m_Child != entt::null){
                    project.SetParent(m_Child, m_OldParent);
                }
            }

        private:
            entt::entity m_Child;
            entt::entity m_Parent;
            entt::entity m_OldParent;
    };

} // namespace VM
