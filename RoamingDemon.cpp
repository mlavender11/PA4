
#include "RoamingDemon.h"
#include "Mage.h"
#include "Model.h"
using namespace std;

RoamingDemon::RoamingDemon(string name, double attack, double health, bool variant, int id, Point2D in_loc, list<Mage*> mage_ptrs)
    : GameObject(in_loc, id, 'W')
{
    this->name = name;
    this->attack = attack;
    this->health = health;
    this->variant = variant;
    state = IN_ENVIRONMENT;

    current_mage = nullptr;
    this->mage_ptrs = mage_ptrs;

    cout << "RoamingDemon constructed." << endl;
}

RoamingDemon::RoamingDemon(string name, double attack, double health, bool variant, int id, Point2D in_loc, int in_mage_id)
    : GameObject(in_loc, id, 'W')
{
    this->name = name;
    this->attack = attack;
    this->health = health;
    this->variant = variant;
    state = IN_ENVIRONMENT;

    current_mage = nullptr;
    this->in_mage_id = in_mage_id;

    cout << "RoamingDemon constructed." << endl;
}

RoamingDemon::~RoamingDemon()
{
    cout << "RoamingDemon destructed." << endl;
}

void RoamingDemon::follow(Mage *m)
{
    current_mage = m;     // Follow mage
    m->AddFollower(this); // Set mage to being followed
}

bool RoamingDemon::get_variant()
{
    return variant;
}

double RoamingDemon::get_attack()
{
    return attack;
}

double RoamingDemon::get_health()
{
    return health;
}

bool RoamingDemon::get_in_combat()
{
    return in_combat;
}

bool RoamingDemon::IsAlive()
{
    return health > 0;
}

bool RoamingDemon::Update()
{
    if (health <= 0)
    {
        if (state != DEAD)
        {
            current_mage->killRoamer();
            cout << "RoamingDemon " << name << " has been killed by Mage " << current_mage->GetId() << endl;
            current_mage = nullptr;
            state = DEAD;
            return true;
        }
    }

    switch (state)
    {
    case IN_ENVIRONMENT:
    {
        if (findMages())
        {
            state = IN_HUNT;
            return true;
        }
        else return false;
    }
    case DEAD:
        return false;
        break;
    case IN_HUNT:
        return false; // chkec this
        break;
    }
    return false;
}

void RoamingDemon::ShowStatus() const
{
    cout << name << " status: " << endl;
    GameObject::ShowStatus();

    switch (state)
    {
    case IN_ENVIRONMENT:
        cout << "Health: " << health << endl;
        cout << "Attack: " << attack << endl;
        break;
    case DEAD:
        cout << "Dead" << endl;
        break;
    case IN_HUNT:
        cout << "Health: " << health << endl;
        cout << "Attack: " << attack << endl;
        cout << "In combat with Mage " << current_mage->GetId() << endl;
        break;
    }
}

bool RoamingDemon::ShouldBeVisible() const
{
    return state != DEAD;
}

bool RoamingDemon::isDead() const
{
    return state == DEAD;
}

void RoamingDemon::UpdateLocation(Point2D loc)
{
    if (state != DEAD)
    { // only move if not dead
        this->location = loc;
        this->health -= 0.25; // Loses .25 health with every step
    }
 
}

void RoamingDemon::save(ofstream &file) const
{
    GameObject::save(file); // Call parent functions
    file << attack << " ";
    file << health << " ";
    file << variant << " ";
    file << in_combat << " ";
    file << name << " ";
    if (current_mage != nullptr)
        file << current_mage->GetId() << " ";
    else
        file << -1 << " ";

    file << endl;
}

RoamingDemon* RoamingDemon::restore(stringstream& file)
{
    //GameObject data
    int id_num;
    double locX, locY;
    int state;
    file >> id_num >> locX >> locY >> state;

    //RoamingDemon data
    double attack, health;
    bool variant, in_combat;
    string name;
    int current_mage_id;

    file >> attack >> health >> variant >> in_combat >> name >> current_mage_id;

    RoamingDemon* demon = new RoamingDemon(name, attack, health, variant, id_num, Point2D(locX, locY), current_mage_id);

    RoamingDemonStates roamerState = (RoamingDemonStates)state;
    demon->setState(roamerState);

    return demon;
}

void RoamingDemon::addMageList(list<Mage*> mage_ptrs)
{
    this->mage_ptrs = mage_ptrs;
}

void RoamingDemon::setState(RoamingDemonStates state)
{
    this->state = state;
}

void RoamingDemon::restorePointers(Model& model){
    if (in_mage_id != -1)
    {
        current_mage = model.GetMagePtr(in_mage_id);
    }
}

// Find mages within detection radius
bool RoamingDemon::findMages()
{
    for (Mage *mage : mage_ptrs)
    {
        Point2D mageLoc = mage->GetLocation();
        Vector2D mageDelta = mage->getDelta();

        if (pathIntersectsCircle(mageLoc, mageDelta, this->location, this->detectionRadius) || pointInCircle(mageLoc, this->location, this->detectionRadius))
        {
            this->follow(mage);
            return true;
        }
    }
    return false;
}

bool pathIntersectsCircle(Point2D start, Vector2D delta, Point2D circleCenter, double radius)
{
    // Movement vector components
    double dx = delta.x;  // or delta.getX() depending on your Vector2D class
    double dy = delta.y;  // or delta.getY()
    
    // Vector from start to circle center
    double fx = start.x - circleCenter.x;
    double fy = start.y - circleCenter.y;
    
    // Quadratic coefficients: at² + bt + c = 0
    double a = dx * dx + dy * dy;
    double b = 2 * (fx * dx + fy * dy);
    double c = (fx * fx + fy * fy) - radius * radius;
    
    double discriminant = b * b - 4 * a * c;
    
    if (discriminant < 0)
        return false;
    
    discriminant = sqrt(discriminant);
    double t1 = (-b - discriminant) / (2 * a);
    double t2 = (-b + discriminant) / (2 * a);
    
    return (t1 >= 0 && t1 <= 1) || (t2 >= 0 && t2 <= 1);
}

bool pointInCircle(Point2D point, Point2D circleCenter, double radius)
{
    double dx = point.x - circleCenter.x;
    double dy = point.y - circleCenter.y;
    double distance = sqrt(dx*dx + dy*dy);
    if (distance <= radius) return true;
    else return false;
}