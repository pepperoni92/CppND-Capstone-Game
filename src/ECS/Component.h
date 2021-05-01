#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

class Component {
public:
    Component() {}
    virtual ~Component() {}

    Entity *Entity;

    virtual bool Init() { return true; }
    virtual void Draw() { }
    virtual void Update() { }

private:

};

#endif