#ifndef ROAMINGDEMON_H
#define ROAMINGDEMON_H
#include "GameObject.h"
using namespace std;

class Mage;

enum RoamingDemonStates
{
    DEAD = 0,
    IN_ENVIRONMENT = 1,
    IN_HUNT = 2,
};

class RoamingDemon : public GameObject
{
    
protected:
    double attack; // says default is 5, where to implement this?
    double health; // default is 2
    bool variant; // initially false
    bool in_combat; //Returns true if the RoamingDemon is attacking a Mage - Default is false
    string name;
    Mage *current_mage; // Holds the current Mage it is following
    
public:
    RoamingDemon(string name, double attack, double health, bool variant, int id, Point2D in_loc);
    void follow(Mage *m); // This follows Mage m - This should both change the Roaming Demon´s current_mage value and update the mage´s information as needed as well
    bool get_variant();
    double get_attack();
    double get_health();
    bool get_in_combat();
    bool ShouldBeVisible() const override;
    void ShowStatus() const override;
    bool Update() override;
    bool IsAlive();

    bool isDead() const override;
    bool UpdateLocation(Point2D loc); // Follow Mage, called from Mage

};
#endif