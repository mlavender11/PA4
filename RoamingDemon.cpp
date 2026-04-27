
#include "RoamingDemon.h"
#include "Mage.h"
using namespace std;

RoamingDemon::RoamingDemon(string name, double attack, double health, bool variant, int id, Point2D in_loc)
    : GameObject(in_loc, id, 'W')
{
    this->name = name;
    this->attack = attack;
    this->health = health;
    this->variant = variant;
    state = IN_ENVIRONMENT;
}

void RoamingDemon::follow(Mage *m)
{
    current_mage = m; // Follow mage
    m->AddFollower(this); // Set mage to being followed
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
    if (health <= 0) state = DEAD;
    switch (state)
    {
    case IN_ENVIRONMENT:
        return false;
        break;
    case DEAD:
        return false;
        break;
    case IN_HUNT:
        cout << "RoamingDemon " << this->id_num << " is following Mage " << current_mage->GetId() << endl;
        return false; // chkec this
        break;
    }
    return false;
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
        cout << "In combat with Mage " << current_mage->GetId() << endl;
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

bool RoamingDemon::UpdateLocation(Point2D loc)
{
    this->location = loc;
    this->health -= 0.25; // Loses .25 health with every step
    return true; //?? What to do with this
}

void RoamingDemon::save(ofstream& file) const
{
    GameObject::save(file); // Call parent functions 
    file << attack;
    file << health;
    file << variant;
    file << in_combat;
    file << name;
    if (current_mage != nullptr) file << current_mage->GetId();
    else file << -1;

    file << endl;
}