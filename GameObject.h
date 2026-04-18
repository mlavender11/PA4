#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Point2D.h"
class GameObject
{
protected:
    Point2D location;
    int id_num;
    char display_code;
    char state;

public:
    GameObject(char in_code);
    GameObject(Point2D in_loc, int in_id, char in_code);
    virtual ~GameObject();

    Point2D GetLocation() const;
    int GetId() const;
    char GetState() const;

    virtual void ShowStatus() const;
    virtual bool Update() = 0;
    virtual bool ShouldBeVisible() const = 0;

    void DrawSelf(char* ptr);
};
#endif