#ifndef MAGE_H
#define MAGE_H
#include <random>
#include "GameObject.h"
#include "DemonHideout.h"
#include "ManaSpire.h"

enum MageStates {
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

class Mage : public GameObject {
public: 
    Mage();
    Mage(char in_code);
    Mage(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc);
    ~Mage();

    void StartMoving(Point2D dest);
    void StartMovingToHideout(DemonHideout* hideout);
    void StartMovingToSpire(ManaSpire* spire);

    void StartBattling(unsigned int num_battles);
    void StartRecoveringMana(unsigned int num_crystals);

    void Stop();

    bool IsKnockedOut() const;
    bool ShouldBeVisible() const override;
    void ShowStatus() const override;
    bool Update() override;

    string GetName();

    bool isDead() const override;


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
    ManaSpire* current_spire;
    DemonHideout* current_hideout;
    Point2D destination;
    Vector2D delta;
};

double GetRandomAmountOfGP();

#endif