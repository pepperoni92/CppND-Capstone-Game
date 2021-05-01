#include "EntityManager.h"
#include "Entity.h"

void EntityManager::Draw() {
    for (auto& entity : _entities) entity->Draw();
}

void EntityManager::Update() {
    for (auto& entity : _entities) entity->Update();
}

void EntityManager::Refresh() {

}

void EntityManager::AddEntity(Entity* entity) {
    std::unique_ptr<Entity> uniquePtr{entity};
    _entities.emplace_back(std::move(uniquePtr));
}

void EntityManager::EraseEntity(Entity* entity) {

}

Entity* EntityManager::CloneEntity(Entity* entity) {
    return nullptr;
}
