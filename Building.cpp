#include "Building.h"
using namespace std;

Building::Building()
    : GameObject('B')
{
    mage_count = 0;
    cout << "Building default constructed" << endl;
}

Building::Building(char in_code, int in_Id, Point2D in_loc)
    : GameObject(in_loc, in_Id, in_code)
{
    mage_count = 0;
    cout << "Building constructed" << endl;
}

void Building::AddOneMage()
{
    mage_count++;
}

void Building::RemoveOneMage()
{
    mage_count--;
}

void Building::ShowStatus() const
{
    cout << display_code << id_num << " located at " << location << endl;
    if (mage_count == 1)
        cout << "1 mage is in this building" << endl;
    else 
        cout << mage_count << " mages are in this building" << endl;
}

bool Building::ShouldBeVisible() const
{
    return true;
}
