#include "ManaSpire.h"
using namespace std;

ManaSpire::ManaSpire()
    : Building()
{
    display_code = 'S';
    crystal_capacity = 100;
    num_crystals_remaining = crystal_capacity;
    cost_per_crystal = 5;
    state = CRYSTALS_AVAILABLE;
    cout << "ManaSpire default constructed" << endl;
}

ManaSpire::ManaSpire(int in_id, double crystal_cost, unsigned int crystal_cap, Point2D in_loc)
    : Building('S', in_id, in_loc)
{
    cost_per_crystal = crystal_cost;
    crystal_capacity = crystal_cap;
    num_crystals_remaining = crystal_capacity;
    state = CRYSTALS_AVAILABLE;
    cout << "ManaSpire constructed" << endl;
}

bool ManaSpire::HasCrystals() const
{
    return (num_crystals_remaining >= 1);
}

unsigned int ManaSpire::GetNumCrystalsRemaining() const
{
    return num_crystals_remaining;
}

bool ManaSpire::CanAffordCrystal(unsigned int crystal, double budget) const
{
    return (crystal * cost_per_crystal) <= budget;
}

double ManaSpire::GetCrystalCost(unsigned int crystal) const
{
    return crystal * cost_per_crystal;
}

unsigned int ManaSpire::DistributeCrystals(unsigned int crystals_needed)
{
    if (num_crystals_remaining >= crystals_needed)
    {
        num_crystals_remaining -= crystals_needed;
        return crystals_needed;
    }
    else
    {
        unsigned int temp = num_crystals_remaining;
        num_crystals_remaining = 0;
        return temp;
    }
}

bool ManaSpire::Update()
{
    if (state == NO_CRYSTALS_AVAILABLE)
        return false;
    else
    {
        if (num_crystals_remaining == 0)
        {
            state = NO_CRYSTALS_AVAILABLE;
            display_code = 's';
            cout << "ManaSpire " << id_num << " has ran out of crystals." << endl;
            return true;
        }
        else
            return false;
    }
}

void ManaSpire::ShowStatus() const
{
    cout << "ManaSpire Status: " << endl;
    Building::ShowStatus();
    cout << "Gold pieces per crystal: " << cost_per_crystal << endl;

    if (num_crystals_remaining == 1)
        cout << "has 1 crystal remaining." << endl;
    else
        cout << "has " << num_crystals_remaining << " crystals remaining." << endl;
    ;
}

ManaSpire::~ManaSpire(){
    cout << "ManaSpire destructed" << endl;
}

bool ManaSpire::isDead() const
{
    return state == NO_CRYSTALS_AVAILABLE;
}

void ManaSpire::save(ofstream& file) const
{
    Building::save(file); // Call parent functions 
    file << crystal_capacity << " ";
    file << num_crystals_remaining << " ";
    file << cost_per_crystal << " ";

    file << endl;
}

void ManaSpire::restore(ifstream &file, Model &model) const
{
    // todo
}