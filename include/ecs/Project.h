#pragma once
#include "common/Base.h"
#include "ecs/ComponentRegistry.h"
#include "ecs/Components.h"
#include "ecs/EntitySnapshot.h"

namespace VM
{
    class Project{
        public:
            Project(){
                m_ProjectDir = std::filesystem::current_path();
                m_Name = "New Project";
            }
            // Create
            entt::entity CreateEntity(const std::string& name = "Entity");
            entt::entity CreateEntity(entt::entity id, const std::string& name="New Entity", entt::entity parent = entt::null);
            // Clone
            entt::entity CloneEntity(const entt::entity& entity);
            // Delete
            void DestroyEntity(entt::entity id);
            void DestroyEntityRecursively(entt::entity id);
            // Snapshot
            EntitySnapshot GetEntitySnapshot(entt::entity entity);
            // Restore
            void RestoreEntitySnapshot(const EntitySnapshot& snapshot);            

            bool IsValid(const entt::entity& entity) const {
                return m_Registry.valid(entity);
            }

            template<typename T, typename... Args>
            T& AddComponent(entt::entity e, Args&&... args){
                ComponentRegistry::Instance().Register<T>();
                return m_Registry.emplace<T>(e, std::forward<Args>(args)...);
            }

            template<typename T>
            bool HasComponent(entt::entity e){
                return m_Registry.any_of<T>(e);
            }

            template<typename T>
            T& GetComponent(entt::entity e){
                auto c = m_Registry.try_get<T>(e);
                return *c;
            }
            
            template<typename T>
            void RemoveComponent(entt::entity e){
                if(!HasComponent<T>(e)) return;
                m_Registry.remove<T>(e);
            }
            entt::registry& GetRegistry() { return m_Registry; }

            void Clear() {
                m_Registry.clear();
            }
            void New() {
                m_ProjectDir = std::filesystem::current_path();
                m_Name = "New Project";
                Clear();
            }

            void SetName(std::string& name){
                m_Name = name;
            }
            const std::string GetName() { return m_Name; }
       
            void SelectEntity(entt::entity id){
                m_Selected = id;
            }

            void DeselectEntity(){
                m_Selected = entt::null;
            }

            entt::entity GetSelected(){
                if(!IsValid(m_Selected)) DeselectEntity();
                return m_Selected;
            }
            bool IsAncestor(entt::entity ancestor, entt::entity node);
            void SetParent(entt::entity child, entt::entity newParent);
            void ReparentAndReorder(entt::entity child, entt::entity newParentOrSibling);

            void Save();
            void SaveAs(const std::filesystem::path& file);
        private:
            entt::registry m_Registry;
            entt::entity current = entt::null;
            entt::entity m_Selected = entt::null;
            std::filesystem::path m_ProjectDir;
            std::string m_Name;
   
    };
} // namespace VM
