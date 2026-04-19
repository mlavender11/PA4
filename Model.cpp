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

    for (GameObject *obj : object_ptrs)
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
    for (GameObject *obj : active_ptrs)
    {
        if (obj->Update())
            output = true;
    }

    auto it = active_ptrs.begin();
    while (it != active_ptrs.end())
    {
        GameObject *obj = *it;

        if (obj->isDead())
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
    for (GameObject *obj : object_ptrs)
    {
        view.Plot(obj);
    }
    view.Draw();
}

void Model::ShowStatus()
{
    cout << "Time: " << time << endl;
    for (GameObject *obj : object_ptrs)
    {
        obj->ShowStatus();
    }
}

void Model::NewCommand(char type, int id, Point2D loc)
{
    switch (type)
    {
    case 's':
    {
        if (GetManaSpirePtr(id))
            throw Invalid_Input("ManaSpire " + to_string(id) + " already exists.");

        ManaSpire *new_spire = new ManaSpire(id, 2, 200, loc);
        object_ptrs.push_back(new_spire);
        active_ptrs.push_back(new_spire);
        spire_ptrs.push_back(new_spire);
    }

    case 'd':
    {
        if (GetDemonHideoutPtr(id))
            throw Invalid_Input("DemonHideout " + to_string(id) + " already exists.");

        DemonHideout *new_hideout = new DemonHideout(10, 1, 2, 3, id, loc);
        object_ptrs.push_back(new_hideout);
        active_ptrs.push_back(new_hideout);
        hideout_ptrs.push_back(new_hideout);
        break;
    }

    case 'g':
    {
        if (GetMagePtr(id))
            throw Invalid_Input("Mage " + to_string(id) + " already exists.");

        string name = "New Mage" + to_string(id);
        Mage *new_mage = new Mage(name, id, 'M', 1, loc);

        object_ptrs.push_back(new_mage);
        active_ptrs.push_back(new_mage);
        mage_ptrs.push_back(new_mage);
        break;
    }

    case 'o':
    {
        if (GetRoamingDemonPtr(id))
            throw Invalid_Input("RoamingDemon " + to_string(id) + " already exists.");

        string name = "Placeholder"; //??
        RoamingDemon *new_roamer = new RoamingDemon(name, 5, 2, false, id, loc);

        object_ptrs.push_back(new_roamer);
        active_ptrs.push_back(new_roamer);
        roaming_ptrs.push_back(new_roamer);
        break;
    }

    default:
        break;
    }
}
