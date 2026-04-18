#include <iostream>
#include "GameObject.h"
using namespace std;

GameObject::GameObject(char in_code)
{
    display_code = in_code;
    id_num = 1;
    state = 0;
    cout << "GameObject constructed" << endl;
}

GameObject::GameObject(Point2D in_loc, int in_id, char in_code)
{
    location = in_loc;
    id_num = in_id;
    display_code = in_code;
    state = 0;
    cout << "GameObject constructed" << endl;
}

Point2D GameObject::GetLocation() const
{
    return location;
}

int GameObject::GetId() const
{
    return id_num;
}

char GameObject::GetState() const
{
    return state;
}

void GameObject::ShowStatus() const
{
    cout << display_code << id_num << " at " << location << endl;
}

GameObject::~GameObject()
{
    cout << "GameObject destructed" << endl;
}

void GameObject::DrawSelf(char* ptr)
{
    *ptr = display_code;
    *(ptr+1) = '0' + id_num;
}

char GameObject::GetDisplayCode() const
{
    return display_code;
}