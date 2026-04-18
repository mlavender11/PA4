#include "Model.h"
using namespace std;

Model::Model()
{
    time = 0;

    Mage *Mage1 = new Mage("Serena", 1, 'M', 1, Point2D(5, 1));
    object_ptrs[0] = Mage1;
    mage_ptrs[0] = Mage1;

    Mage *Mage2 = new Mage("Rumi", 2, 'M', 2, Point2D(10, 1));
    object_ptrs[1] = Mage2;
    mage_ptrs[1] = Mage2;

    ManaSpire *ManaSpire1 = new ManaSpire(1, 1, 100, Point2D(1, 20));
    object_ptrs[2] = ManaSpire1;
    spire_ptrs[0] = ManaSpire1;

    ManaSpire *ManaSpire2 = new ManaSpire(2, 2, 200, Point2D(10, 20));
    object_ptrs[3] = ManaSpire2;
    spire_ptrs[1] = ManaSpire2;

    DemonHideout *DemonHideout1 = new DemonHideout(10, 1, 2, 3, 1, Point2D(0, 0));
    object_ptrs[4] = DemonHideout1;
    hideout_ptrs[0] = DemonHideout1;

    DemonHideout *DemonHideout2 = new DemonHideout(20, 5, 7.5, 4, 2, Point2D(5, 5));
    object_ptrs[5] = DemonHideout2;
    hideout_ptrs[1] = DemonHideout2;

    RoamingDemon* roamer1 = new RoamingDemon("Roamer 1", 5, 2, false, 1, Point2D(10, 12));
    object_ptrs[6] = roamer1;
    roaming_prts[0] = roamer1;

    RoamingDemon* roamer2 = new RoamingDemon("Roamer 2", 5, 2, false, 2, Point2D(15, 5));
    object_ptrs[7] = roamer2;
    roaming_prts[1] = roamer2;

    num_objects = 8;
    num_mages = 2;
    num_spires = 2;
    num_hideouts = 2;
    num_roamers = 2;

    cout << "Model default constructed " << endl;
}

Model::~Model()
{
    for (int i = 0; i < num_objects; i++)
    {
        delete object_ptrs[i];
    }

    cout << "Model destructed" << endl;
}

Mage *Model::GetMagePtr(int id)
{
    for (int i = 0; i < num_mages; i++)
    {
        if (mage_ptrs[i]->GetId() == id)
        {
            return mage_ptrs[i];
        }
    }
    return 0;
}

ManaSpire *Model::GetManaSpirePtr(int id)
{
    for (int i = 0; i < num_spires; i++)
    {
        if (spire_ptrs[i]->GetId() == id)
        {
            return spire_ptrs[i];
        }
    }
    return 0;
}

DemonHideout *Model::GetDemonHideoutPtr(int id)
{
    for (int i = 0; i < num_hideouts; i++)
    {
        if (hideout_ptrs[i]->GetId() == id)
        {
            return hideout_ptrs[i];
        }
    }
    return 0;
}

bool Model::Update()
{
    time++;
    bool output = false;
    for (int i = 0; i < num_objects; i++)
    {
        if (object_ptrs[i]->Update())
            output = true;
    }

    bool defeated = true;
    for (int i = 0; i < num_hideouts; i++)
    {
        if (hideout_ptrs[i]->GetState() == NOT_DEFEATED)
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
    for (int i = 0; i < num_mages; i++)
    {
        if (mage_ptrs[i]->GetState() != KNOCKED_OUT)
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

// make virtual functions???

void Model::Display(View &view)
{
    view.Clear();
    for (int i = 0; i < num_objects; i++)
    {
        if (object_ptrs[i]->ShouldBeVisible())
            view.Plot(object_ptrs[i]);
    }
    view.Draw();
}

void Model::ShowStatus()
{
    cout << "Time: " << time << endl;
    for (int i = 0; i < num_objects; i++)
    {
        object_ptrs[i]->ShowStatus();
    }
}
