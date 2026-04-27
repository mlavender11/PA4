#ifndef ROAMINGDEMON_H
#define ROAMINGDEMON_H
#include "GameObject.h"
#include <list>
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
    int in_mage_id; // Used during file reading
    double detectionRadius = 5.0;
    list<Mage*> mage_ptrs;
    
    
public:
    RoamingDemon(string name, double attack, double health, bool variant, int id, Point2D in_loc, list<Mage*> mage_ptrs);
    RoamingDemon(string name, double attack, double health, bool variant, int id, Point2D in_loc, int in_mage_id);
    ~RoamingDemon();

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

    void save(ofstream& file) const override;
    static RoamingDemon* restore(stringstream& file);
    void setState(RoamingDemonStates state);

    bool findMages();

    void addMageList(list<Mage*> mage_ptrs);
    int getInMageId();

};

// Intersection formula for detecting mages
bool pathIntersectsCircle(Point2D start, Vector2D delta, Point2D circleCenter, double radius);
bool pointInCircle(Point2D point, Point2D circleCenter, double radius);



#endif