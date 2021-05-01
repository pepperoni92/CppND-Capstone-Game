#ifndef ENTITY_H
#define ENTITY_H

#include "ECS.h"
#include <vector>
#include <memory>
#include "Component.h"
#include "Components/Transform.h"

class Entity {
public:
    Entity() {
        this->AddComponent<Transform>(0,0);
    }

    virtual ~Entity() {}

    template<typename T, typename... TArgs>
    inline T& AddComponent(TArgs&&... args) {
        T* c(new T(std::forward<TArgs>(args)...));

        std::unique_ptr<Component> uptr(c);
        _components.emplace_back(std::move(uptr));

        if (c->Init()) {
            _componentList[GetComponentTypeID<T>()] = c;
            _componentBitset[GetComponentTypeID<T>()] = true;
            c->Entity = this;
            return *c;
        }

        return *static_cast<T*>(nullptr);
    }

    template<typename T>
    inline T& GetComponent() const {
        auto ptr(_componentList[GetComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }

    template<typename T>
    inline bool HasComponent() const {
        return _componentBitset[GetComponentTypeID<T>()];
    }

    inline bool IsActive() const { return _active; }

    inline void Destroy() {
        _active = false;
    }

    inline void Draw() {
        for(auto& comp : _components) 
        {
            comp->Draw();
        }
    }

    inline void Update() {
        for(auto& comp : _components) 
        {
            comp->Update();
        }
    }

private:
    bool _active;
    ComponentList _componentList;
    ComponentBitset _componentBitset;
    std::vector<std::unique_ptr<Component>> _components;
};

#endif