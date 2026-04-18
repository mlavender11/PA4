#ifndef MANASPIRE_H
#define MANASPIRE_H
#include "Building.h"

enum ManaSpireStates
{
    CRYSTALS_AVAILABLE = 0,
    NO_CRYSTALS_AVAILABLE = 1
};

class ManaSpire : public Building
{
private:
    unsigned int crystal_capacity;
    unsigned int num_crystals_remaining;
    double cost_per_crystal;

public:
    ManaSpire();
    ManaSpire(int in_id, double crystal_cost, unsigned int crystal_cap, Point2D in_loc);
    ~ManaSpire();

    bool HasCrystals() const;
    unsigned int GetNumCrystalsRemaining() const;
    bool CanAffordCrystal(unsigned int crystal, double budget) const;
    double GetCrystalCost(unsigned int crystal) const;
    unsigned int DistributeCrystals(unsigned int crystals_needed);
    bool Update() override;
    void ShowStatus() const override;
};

#endif