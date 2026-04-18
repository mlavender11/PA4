#ifndef MODEL_H
#define MODEL_H
#include "View.h"
#include "GameObject.h"
#include "Mage.h"
#include "ManaSpire.h"
#include "DemonHideout.h"
#include "RoamingDemon.h"

class Model
{

private:
    int time;

    GameObject *object_ptrs[10];
    int num_objects;

    Mage *mage_ptrs[10];
    int num_mages;

    ManaSpire *spire_ptrs[10];
    int num_spires;

    DemonHideout *hideout_ptrs[10];
    int num_hideouts;

    RoamingDemon* roaming_prts[10];
    int num_roamers;

public:
    Model();
    ~Model();

    Mage *GetMagePtr(int id);
    ManaSpire *GetManaSpirePtr(int id);
    DemonHideout *GetDemonHideoutPtr(int id);

    bool Update();
    void Display(View &view);
    void ShowStatus();
};

#endif