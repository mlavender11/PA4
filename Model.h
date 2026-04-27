// TODO:

// • Model::update() should update each object in the active_ptrs list, and then scan the list
// looking for dead objects; if found, the dead object is removed from the active_ptrs list so
// that it is no longer updated. For debugging and demonstration purposes, output a message like
// Dead object removed.

#ifndef MODEL_H
#define MODEL_H
#include "View.h"
#include "GameObject.h"
#include "Mage.h"
#include "ManaSpire.h"
#include "DemonHideout.h"
#include "RoamingDemon.h"
#include "Invalid_Input.h"
#include <list>
#include <sstream>

class Model
{

private:
    int time;

    list<GameObject *> object_ptrs;
    list<GameObject *> active_ptrs;
    list<Mage *> mage_ptrs;
    list<ManaSpire *> spire_ptrs;
    list<DemonHideout *> hideout_ptrs;
    list<RoamingDemon *> roaming_ptrs;

public:
    Model();
    ~Model();

    Mage *GetMagePtr(int id);
    ManaSpire *GetManaSpirePtr(int id);
    DemonHideout *GetDemonHideoutPtr(int id);
    RoamingDemon *GetRoamingDemonPtr(int id);

    bool Update();
    void Display(View &view);
    void ShowStatus();

    void NewCommand(char type, int id, Point2D loc);

    void save(ofstream &file) const;
    void restore(ifstream &file);
    void setTime(int time);
};

#endif