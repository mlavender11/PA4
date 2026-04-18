#ifndef ROAMINGDEMON_H
#define ROAMINGDEMON_H
#include "GameObject.h"
#include "Mage.h"
using namespace std;

enum RoamingDemonStates
{
    IN_ENVIRONMENT = 1,
    DEAD = 2,
    IN_HUNT = 3,
};

class RoamingDemon : public GameObject
{
protected:
    double attack; // says default is 5, where to implement this?
    double health;
    bool variant;
    bool in_combat;
    string name;
    Mage *current_mage;

public:
    RoamingDemon(string name, double attack, double health, bool variant, int id, Point2D in_loc);
    void follow(Mage *m);
    bool get_variant();
    double get_attack();
    double get_health();
    bool get_in_combat();
    bool ShouldBeVisible() const override;
    void ShowStatus() const override;
    bool Update() override;
    bool IsAlive();
};
#endif