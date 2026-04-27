#ifndef DEMONHIDEOUT_H
#define DEMONHIDEOUT_H
#include "Building.h"

enum DemonHideoutStates
{
    DEFEATED = 0,
    NOT_DEFEATED = 1
};

class DemonHideout : public Building
{
private:
    unsigned int num_battles_remaining;
    unsigned int max_number_of_battles;
    unsigned int mana_cost_per_battle;
    double gold_cost_per_battle;
    unsigned int experience_per_battle;

public:
    DemonHideout();
    DemonHideout(unsigned int max_battle, unsigned int mana_loss, double cost, unsigned int exp_per_battle, int in_id, Point2D in_loc);
    ~DemonHideout();

    double GetGoldCost(unsigned int battle_qty) const;
    unsigned int GetManaCost(unsigned int battle_qty) const;
    unsigned int GetNumBattlesRemaining() const;
    bool IsAbleToBattle(unsigned int battle_qty, double budget, unsigned int mana) const;
    unsigned int DemonBattle(unsigned int battle_units);
    unsigned int GetExperiencePerBattle() const;
    bool Update() override;
    bool passed() const;
    void ShowStatus() const override;
    bool isDead() const override;

    void save(ofstream& file) const override;
    void restore(ifstream& file, Model& model) const override;
};
#endif