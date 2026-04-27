#ifndef MAGE_H
#define MAGE_H
#include <random>
#include "GameObject.h"
#include "DemonHideout.h"
#include "ManaSpire.h"
#include "RoamingDemon.h"
#include <string>
#include <sstream>

class Model;

enum MageStates
{
    KNOCKED_OUT = 0,
    MOVING = 1,
    STOPPED = 2,
    AT_SPIRE = 3,
    IN_HIDEOUT = 4,
    MOVING_TO_SPIRE = 5,
    MOVING_TO_HIDEOUT = 6,
    BATTLING_IN_HIDEOUT = 7,
    RECOVERING_MANA = 8
};

class Mage : public GameObject
{
public:
    Mage();
    Mage(char in_code);
    Mage(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc);
    ~Mage();

    //Constructor for read function
    Mage(string in_name, int in_id, unsigned int in_speed, Point2D in_loc,
        int in_spire_id, int in_hideout_id, int in_follower_id, MageStates state, double gold_pieces,
        Point2D destination, Vector2D delta, Point2D prevLoc, bool is_at_spire, bool is_in_hideout, bool HuntedByDemon,
        unsigned int mana, unsigned int experience, unsigned int battles_to_buy, unsigned int crystals_to_buy);
    

    void StartMoving(Point2D dest);
    void StartMovingToHideout(DemonHideout *hideout);
    void StartMovingToSpire(ManaSpire *spire);

    void StartBattling(unsigned int num_battles);
    void StartRecoveringMana(unsigned int num_crystals);

    void Stop();

    bool IsKnockedOut() const;
    bool ShouldBeVisible() const override;
    void ShowStatus() const override;
    bool Update() override;

    string GetName();

    bool isDead() const override;

    // Roaming Demon functions
    void AddFollower(RoamingDemon *roamer);
    bool IsFollowed();
    void killRoamer();
    Vector2D getDelta();


    //Restore helpers
    void save(ofstream& file) const override;
    static Mage* restore(stringstream& file);
    void setState(MageStates state);
    int getInSpireId();
    int getInHideoutId();
    int getInFollowerId();
    void restorePointers(Model& model);

protected:
    bool UpdateLocation();
    void SetupDestination(Point2D dest);

private:
    double speed;
    bool is_at_spire;
    bool is_in_hideout;
    unsigned int mana;
    unsigned int experience;
    double gold_pieces;
    unsigned int battles_to_buy;
    unsigned int crystals_to_buy;
    string name;
    ManaSpire *current_spire;
    DemonHideout *current_hideout;
    Point2D destination;
    Vector2D delta;

    RoamingDemon *follower; // Roaming demon following this mage
    bool HuntedByDemon;     // True if there is a mage following it
    Point2D prevLocation; // For the roamer to lag behind

    //Restore helpers - only valid during restore
    int in_spire_id;
    int in_hideout_id;
    int in_follower_id;
};

double GetRandomAmountOfGP();

#endif