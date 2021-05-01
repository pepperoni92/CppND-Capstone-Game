#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include <memory>

class Entity;

class EntityManager {
public:
    EntityManager() = default;
    virtual ~EntityManager() = default;

    void Draw();
    void Update();
    void Refresh();

    void AddEntity(Entity* player);
    void EraseEntity(Entity* player);
    Entity* CloneEntity(Entity* player);

private:
    std::vector<std::unique_ptr<Entity>> _entities;
};

#endif