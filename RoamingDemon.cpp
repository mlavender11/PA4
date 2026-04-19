
#include "RoamingDemon.h"
using namespace std;

RoamingDemon::RoamingDemon(string name, double attack, double health, bool variant, int id, Point2D in_loc)
    : GameObject(in_loc, id, 'W')
{
    this->name = name;
    this->attack = attack;
    this->health = health;
    this->variant = variant;
}

void RoamingDemon::follow(Mage *m)
{
    current_mage = m;
    // update mage to being followed
}

bool RoamingDemon::get_variant()
{
    return variant;
}

double RoamingDemon::get_attack()
{
    return attack;
}

double RoamingDemon::get_health()
{
    return health;
}

bool RoamingDemon::get_in_combat()
{
    return in_combat;
}

bool RoamingDemon::IsAlive()
{
    return health > 0;
}

bool RoamingDemon::Update()
{
    switch (state)
    {
    case IN_ENVIRONMENT:
        return false;
        break;
    case DEAD:
        return false;
        break;
    case IN_HUNT:
        return false; // chkec this
        break;
    }
}

void RoamingDemon::ShowStatus() const
{
    cout << name << " status: " << endl;
    GameObject::ShowStatus();

    switch (state)
    {
    case IN_ENVIRONMENT:
        cout << "Health: " << health << endl;
        cout << "Attack: " << attack << endl;
        break;
    case DEAD:
        cout << "Dead" << endl;
        break;
    case IN_HUNT:
        cout << "Health: " << health << endl;
        cout << "Attack: " << attack << endl;
        cout << "In Combat: " << in_combat << endl;
        break;
    }
}

bool RoamingDemon::ShouldBeVisible() const
{
    return state != DEAD;
}

bool RoamingDemon::isDead() const
{
    return DEAD;
}