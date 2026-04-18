#include "Model.h"
using namespace std;

Model::Model()
{
    time = 0;

    Mage *Mage1 = new Mage("Serena", 1, 'M', 1, Point2D(5, 1));
    object_ptrs.push_back(Mage1);
    mage_ptrs.push_back(Mage1);

    Mage *Mage2 = new Mage("Rumi", 2, 'M', 2, Point2D(10, 1));
    object_ptrs.push_back(Mage2);
    mage_ptrs.push_back(Mage2);

    ManaSpire *ManaSpire1 = new ManaSpire(1, 1, 100, Point2D(1, 20));
    object_ptrs.push_back(ManaSpire1);
    spire_ptrs.push_back(ManaSpire1);

    ManaSpire *ManaSpire2 = new ManaSpire(2, 2, 200, Point2D(10, 20));
    object_ptrs.push_back(ManaSpire2);
    spire_ptrs.push_back(ManaSpire2);

    DemonHideout *DemonHideout1 = new DemonHideout(10, 1, 2, 3, 1, Point2D(0, 0));
    object_ptrs.push_back(DemonHideout1);
    hideout_ptrs.push_back(DemonHideout1);

    DemonHideout *DemonHideout2 = new DemonHideout(20, 5, 7.5, 4, 2, Point2D(5, 5));
    object_ptrs.push_back(DemonHideout2);
    hideout_ptrs.push_back(DemonHideout2);

    RoamingDemon *roamer1 = new RoamingDemon("Roamer 1", 5, 2, false, 1, Point2D(10, 12));
    object_ptrs.push_back(roamer1);
    roaming_ptrs.push_back(roamer1);

    RoamingDemon *roamer2 = new RoamingDemon("Roamer 2", 5, 2, false, 2, Point2D(15, 5));
    object_ptrs.push_back(roamer2);
    roaming_ptrs.push_back(roamer2);

    for (GameObject* obj : object_ptrs) 
    {
        active_ptrs.push_back(obj);
    }

    cout << "Model default constructed " << endl;
}

Model::~Model()
{
    for (GameObject *obj : object_ptrs)
    {
        delete obj;
    }
    object_ptrs.clear();

    cout << "Model destructed" << endl;
}

Mage *Model::GetMagePtr(int id)
{
    for (Mage *mage : mage_ptrs)
    {
        if (mage->GetId() == id)
        {
            return mage;
        }
    }
    return nullptr;
}

ManaSpire *Model::GetManaSpirePtr(int id)
{
    for (ManaSpire *spire : spire_ptrs)
    {
        if (spire->GetId() == id)
        {
            return spire;
        }
    }
    return nullptr;
}

DemonHideout *Model::GetDemonHideoutPtr(int id)
{
    for (DemonHideout *hideout : hideout_ptrs)
    {
        if (hideout->GetId() == id)
        {
            return hideout;
        }
    }
    return nullptr;
}

RoamingDemon *Model::GetRoamingDemonPtr(int id)
{
    for (RoamingDemon *roamer : roaming_ptrs)
    {
        if (roamer->GetId() == id)
        {
            return roamer;
        }
    }
    return nullptr;
}

bool Model::Update()
{
    time++;
    bool output = false;
    for (GameObject* obj : active_ptrs)
    {
        if (obj->Update())
            output = true;
    }

    auto it = active_ptrs.begin();
    while (it != active_ptrs.end())
    {
        GameObject* obj = *it;
        bool dead = (obj->GetState() == KNOCKED_OUT || obj->GetState() == DEFEATED || obj->GetState() == NO_CRYSTALS_AVAILABLE || obj->GetState() == DEAD);
        
        if (dead)
        {
            cout << "Dead object removed: " << obj->GetId() << obj->GetDisplayCode() << endl;
            it = active_ptrs.erase(it);
        }
        else
        {
            ++it;
        }
    }

    bool defeated = true;
    for (DemonHideout *hideout : hideout_ptrs)
    {
        if (hideout->GetState() == NOT_DEFEATED)
        {
            defeated = false;
            break;
        }
    }
    if (defeated)
    {
        cout << "GAME OVER: You win! All battles done!" << endl;
        exit(0);
    }

    bool knocked = true;
    for (Mage *mage : mage_ptrs)
    {
        if (mage->GetState() != KNOCKED_OUT)
        {
            knocked = false;
            break;
        }
    }
    if (knocked)
    {
        cout << "GAME OVER: You lose! All of your Mages' mana is lost!" << endl;
        exit(0);
    }

  

    return output;
}

void Model::Display(View &view)
{
    view.Clear();
    for (GameObject* obj : object_ptrs)
    {
        view.Plot(obj);
    }
    view.Draw();
}

void Model::ShowStatus()
{
    cout << "Time: " << time << endl;
    for (GameObject* obj : object_ptrs)
    {
        obj->ShowStatus();
    }
}
