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

    RoamingDemon *roamer1 = new RoamingDemon("Roamer1", 5, 2, false, 1, Point2D(10, 12), mage_ptrs);
    object_ptrs.push_back(roamer1);
    roaming_ptrs.push_back(roamer1);

    RoamingDemon *roamer2 = new RoamingDemon("Roamer2", 5, 2, false, 2, Point2D(15, 5), mage_ptrs);
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
    bool output = false; // Output is true if an event happens - tells run to pause
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

    // // Loop to find if mage is within proximity of roaming demon
    // const double DETECTIONRADIUS = 5.0;
    // for (RoamingDemon *roamer : roaming_ptrs) // Loop over all roaming demons
    // {
    //     if (roamer->get_in_combat())
    //         continue; // If the roamer is already following a mage, ignore

    //     Point2D roamerLoc = roamer->GetLocation();
    //     Point2D mageLoc;

    //     for (Mage *mage : mage_ptrs)
    //     {
    //         if (mage->IsFollowed())
    //             continue; // If the mage is already being followed, ignore
    //         mageLoc = mage->GetLocation();

    //         double dx = mageLoc.x - roamerLoc.x;
    //         double dy = mageLoc.y - roamerLoc.y;
    //         double distance = sqrt(dx*dx + dy*dy);
    //         if (distance <= DETECTIONRADIUS) // If the mage is within roamer's detection radius, then the roamer will start following it
    //         {
    //             roamer->follow(mage);
    //             output = true;
    //         }
    //     }
    // }

    return output;
}

void Model::Display(View &view)
{
    view.Clear();
    for (GameObject *obj : active_ptrs)
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

// Create new object
void Model::NewCommand(char type, int id, Point2D loc)
{
    switch (type)
    {
    case 's':
    {
        if (GetManaSpirePtr(id))
            throw Invalid_Input("ManaSpire " + to_string(id) + " already exists.");

        double crystal_cost;
        int crystal_cap;
        cout << "Enter Crystal Cost and Crystal Capacity: ";
        cin >> crystal_cost >> crystal_cap;
        while (cin.fail() || crystal_cost <= 0 || crystal_cap <= 0)
        {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Error. Enter a valid input for Crystal Cost and Crystal Capacity: ";
            cin >> crystal_cost >> crystal_cap;
        }

        ManaSpire *new_spire = new ManaSpire(id, crystal_cost, crystal_cap, loc);

        object_ptrs.push_back(new_spire);
        active_ptrs.push_back(new_spire);
        spire_ptrs.push_back(new_spire);
        break;
    }

    case 'd':
    {
        if (GetDemonHideoutPtr(id))
            throw Invalid_Input("DemonHideout " + to_string(id) + " already exists.");

        int max_battle;
        int mana_loss;
        double cost;
        double experience_per_battle;
        cout << "Enter Max Battles, Mana Loss per Battle, Cost, and Experience per Battle: ";
        cin >> max_battle >> mana_loss >> cost >> experience_per_battle;
        while (cin.fail() || max_battle <= 0 || mana_loss <= 0 || cost <= 0 || experience_per_battle <= 0)
        {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Error. Enter a valid input for Max Battles, Mana Loss per Battle, Cost, and Experience per Battle: ";
            cin >> max_battle >> mana_loss >> cost >> experience_per_battle;
        }

        DemonHideout *new_hideout = new DemonHideout(max_battle, mana_loss, cost, experience_per_battle, id, loc);

        object_ptrs.push_back(new_hideout);
        active_ptrs.push_back(new_hideout);
        hideout_ptrs.push_back(new_hideout);
        break;
    }

    case 'g':
    {
        if (GetMagePtr(id))
            throw Invalid_Input("Mage " + to_string(id) + " already exists.");

        string name;
        cout << "Enter Mage name: ";
        cin >> name;

        int speed;
        cout << "Enter Mage speed: ";
        cin >> speed;
        while (cin.fail() || speed <= 0)
        {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Error. Enter a valid speed: ";
            cin >> speed;
        }

        Mage *new_mage = new Mage(name, id, 'M', speed, loc);

        object_ptrs.push_back(new_mage);
        active_ptrs.push_back(new_mage);
        mage_ptrs.push_back(new_mage);
        break;
    }

    case 'o':
    {
        if (GetRoamingDemonPtr(id))
            throw Invalid_Input("RoamingDemon " + to_string(id) + " already exists.");

        string name;
        cout << "Enter RoamingDemon name: ";
        cin >> name;

        double attack;
        double health;
        cout << "Enter Attack and Health values: ";
        cin >> attack >> health;
        while (cin.fail() || attack <= 0 || health <= 0)
        {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Error. Enter a valid input for Attack and Health: ";
            cin >> attack >> health;
        }

        RoamingDemon *new_roamer = new RoamingDemon(name, attack, health, false, id, loc, mage_ptrs);

        object_ptrs.push_back(new_roamer);
        active_ptrs.push_back(new_roamer);
        roaming_ptrs.push_back(new_roamer);
        break;
    }

    default:
        break;
    }
}

void Model::save(ofstream &file) const
{
    file << time << endl;               // save game time
    file << active_ptrs.size() << endl; // save number of active objects
    for (GameObject *obj : active_ptrs) // save each object
    {
        obj->save(file); // each writes its display code and id num
    }

    file.close();
}

void Model::restore(ifstream &file)
{

    for (GameObject *obj : object_ptrs)
    {
        delete obj;
    }
    object_ptrs.clear();
    active_ptrs.clear();
    mage_ptrs.clear();
    spire_ptrs.clear();
    hideout_ptrs.clear();
    roaming_ptrs.clear();

    // go thorugh file, make new obj based on type

    string line;   // each line is a saved object
    char obj_code; // First entry in every string
    int time;      // Saved game time
    int num_objects;

    file >> time >> num_objects;

    while (getline(file, line))
    {
        stringstream obj_data_line(line);

        obj_data_line >> obj_code;

        switch (obj_code)
        {
        case 'M':
            mage_ptrs.push_back(Mage::restore(obj_data_line));
            break;
        case 'S':
            spire_ptrs.push_back(ManaSpire::restore(obj_data_line));
            break;
        case 'D':
            hideout_ptrs.push_back(DemonHideout::restore(obj_data_line));
            break;
        case 'W':
            roaming_ptrs.push_back(RoamingDemon::restore(obj_data_line));
            break;
        default:
            break;
        }
    }

    // Add all objects to object and active ptrs lists
    for (GameObject *obj : mage_ptrs)
    {
        object_ptrs.push_back(obj);
        active_ptrs.push_back(obj);
    }
    for (GameObject *obj : spire_ptrs)
    {
        object_ptrs.push_back(obj);
        active_ptrs.push_back(obj);
    }
    for (GameObject *obj : hideout_ptrs)
    {
        object_ptrs.push_back(obj);
        active_ptrs.push_back(obj);
    }
    for (GameObject *obj : roaming_ptrs)
    {
        object_ptrs.push_back(obj);
        active_ptrs.push_back(obj);
    }

    // After all are made, assign pointers
    for (Mage *mage : mage_ptrs)
    {
        mage->restorePointers(*this);
    }
    for (RoamingDemon *roamer : roaming_ptrs)
    {
        roamer->restorePointers(*this);
        roamer->addMageList(this->mage_ptrs);
    }

    this->setTime(time);
    file.close();
}

void Model::setTime(int time)
{
    this->time = time;
}