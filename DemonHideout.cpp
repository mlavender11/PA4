#include "DemonHideout.h"
using namespace std;

DemonHideout::DemonHideout()
    : Building()
{
    display_code = 'D';
    state = NOT_DEFEATED;
    max_number_of_battles = 10;
    num_battles_remaining = max_number_of_battles;
    mana_cost_per_battle = 1;
    gold_cost_per_battle = 1.0;
    experience_per_battle = 2;
    cout << "DemonHideout default constructed" << endl;
}

DemonHideout::DemonHideout(unsigned int max_battle, unsigned int mana_loss, double cost, unsigned int exp_per_battle, int in_id, Point2D in_loc)
    : Building('D', in_id, in_loc)
{
    max_number_of_battles = max_battle;
    num_battles_remaining = max_number_of_battles;
    mana_cost_per_battle = mana_loss;
    experience_per_battle = exp_per_battle;
    gold_cost_per_battle = cost;
    state = NOT_DEFEATED;

    cout << "DemonHideout constructed" << endl;
}

double DemonHideout::GetGoldCost(unsigned int battle_qty) const
{
    return battle_qty * gold_cost_per_battle;
}
unsigned int DemonHideout::GetManaCost(unsigned int battle_qty) const
{
    return battle_qty * mana_cost_per_battle;
}
unsigned int DemonHideout::GetNumBattlesRemaining() const
{
    return num_battles_remaining;
}

bool DemonHideout::IsAbleToBattle(unsigned int battle_qty, double budget, unsigned int mana) const
{
    if (battle_qty * mana_cost_per_battle <= mana && battle_qty * gold_cost_per_battle <= budget)
        return true;
    else
        return false;
}

unsigned int DemonHideout::DemonBattle(unsigned int battle_units)
{
    if (battle_units <= num_battles_remaining)
    {
        num_battles_remaining -= battle_units;
        return battle_units * experience_per_battle;
    }
    else
    {
        unsigned int exp = num_battles_remaining * experience_per_battle;
        num_battles_remaining = 0;
        return exp;
    }
}

unsigned int DemonHideout::GetExperiencePerBattle() const
{
    return experience_per_battle;
}

bool DemonHideout::Update()
{
    if (state == DEFEATED)
        return false;
    else
    {
        if (num_battles_remaining == 0)
        {
            state = DEFEATED;
            display_code = 'd';
            cout << display_code << id_num << " has been beaten" << endl;
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool DemonHideout::passed() const
{
    return num_battles_remaining == 0;
}

void DemonHideout::ShowStatus() const
{
    cout << "DemonHideoutStatus:" << endl;
    Building::ShowStatus();
    cout << "Max number of battles: " << max_number_of_battles << endl;
    cout << "Mana cost per battle: " << mana_cost_per_battle << endl;
    cout << "Gold per battle: " << gold_cost_per_battle << endl;
    cout << "Experience per battle: " << experience_per_battle << endl;

    if (num_battles_remaining == 1)
        cout << "1 battle is remaining for this DemonHideout" << endl;
    else
        cout << num_battles_remaining << " battles are remaining for this DemonHideout" << endl;
}

DemonHideout::~DemonHideout() {
    cout << "DemonHideout destructed" << endl;
}

bool DemonHideout::isDead() const
{
    return state == DEFEATED;
}


//??

void DemonHideout::save(ofstream& file) const
{
    Building::save(file); // Call parent functions 
    file << num_battles_remaining;
    file << max_number_of_battles;
    file << mana_cost_per_battle;
    file << gold_cost_per_battle;
    file << experience_per_battle;
    file << endl;
}
// void restore(ifstream& file, Model& model) const;