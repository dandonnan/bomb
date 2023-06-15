#ifndef Scene_H
#define Scene_H

// A base class for a scene.
class Scene
{
    public:
        virtual ~Scene() {}
        virtual void Update() = 0;
        virtual void Draw() = 0;
};

#endif // Scene_H