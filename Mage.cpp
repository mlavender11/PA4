#include "Mage.h"
using namespace std;

Mage::Mage() : GameObject('M')
{
    state = STOPPED;
    speed = 5;

    is_at_spire = false;
    is_in_hideout = false;
    mana = 20;
    experience = 0;
    gold_pieces = 0;
    battles_to_buy = 0;
    crystals_to_buy = 0;
    current_spire = 0;
    current_hideout = 0;

    follower = 0;
    HuntedByDemon = false;

    cout << "Mage default constructed" << endl;
}

Mage::Mage(char in_code) : GameObject(in_code)
{
    // add other default values
    state = STOPPED;
    speed = 5;

    is_at_spire = false;
    is_in_hideout = false;
    mana = 20;
    experience = 0;
    gold_pieces = 0;
    battles_to_buy = 0;
    crystals_to_buy = 0;
    current_spire = 0;
    current_hideout = 0;

    follower = 0;
    HuntedByDemon = false;

    cout << "Mage constructed." << endl;

    // initialize to null pointers
}

Mage::Mage(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc)
    : GameObject(in_loc, in_id, in_code)
{
    state = STOPPED;
    speed = in_speed;
    name = in_name;

    is_at_spire = false;
    is_in_hideout = false;
    mana = 20;
    experience = 0;
    gold_pieces = 0;
    battles_to_buy = 0;
    crystals_to_buy = 0;
    current_spire = 0;
    current_hideout = 0;

    follower = 0;
    HuntedByDemon = false;

    cout << "Mage constructed." << endl;
}

void Mage::StartMoving(Point2D dest)
{
    destination = dest;

    if ((location - destination).x == 0 && (location - destination).y == 0)
    {
        cout << display_code << id_num << ": I'm already there. See?" << endl;
    }
    else if (state == KNOCKED_OUT)
    {
        cout << display_code << id_num << ": I am knocked out. I may move but you cannot see me." << endl;
    }
    else
    {
        // Remove mage when it leaves a building
        if (state == IN_HIDEOUT)
            current_hideout->RemoveOneMage();
        if (state == AT_SPIRE)
            current_spire->RemoveOneMage();

        cout << display_code << id_num << ": On my way" << endl;
        state = MOVING;
        SetupDestination(destination);
    }
}

void Mage::StartMovingToHideout(DemonHideout *hideout)
{
    destination = hideout->GetLocation();
    current_hideout = hideout;

    if (state == KNOCKED_OUT)
    {
        cout << display_code << id_num << ": I am knocked out so I can't move to hideout..." << endl;
    }
    else if ((location - destination).x == 0 && (location - destination).y == 0)
    {
        cout << display_code << id_num << ": I am already at the Demon Hideout!" << endl;
    }
    else
    {
        cout << display_code << id_num << ": on my way to hideout " << hideout->GetId() << "." << endl;
        SetupDestination(destination);
        state = MOVING_TO_HIDEOUT;
    }
}

void Mage::StartMovingToSpire(ManaSpire *spire)
{
    Point2D dest = spire->GetLocation();
    current_spire = spire;

    if (state == KNOCKED_OUT)
    {
        cout << display_code << id_num << ": I am knocked out so I should have gone to the spire..." << endl;
    }
    else if ((location - dest).x == 0 && (location - dest).y == 0)
    {
        cout << display_code << id_num << ": I am already at the Spire!" << endl;
    }
    else
    {
        cout << display_code << id_num << ": on my way to Spire " << spire->GetId() << "." << endl;
        SetupDestination(dest);
        state = MOVING_TO_SPIRE;
    }
}

void Mage::StartBattling(unsigned int num_battles)
{
    if (state != IN_HIDEOUT)
    {
        cout << display_code << id_num << ": I can only battle in a DemonHideout" << endl;
        return;
    }

    battles_to_buy = min(num_battles, current_hideout->GetNumBattlesRemaining());
    double goldNeeded = current_hideout->GetGoldCost(battles_to_buy);
    if (mana == 0)
    {
        cout << display_code << id_num << ": I'm knocked out and out of mana so no more battles for me..." << endl;
    }
    else if (gold_pieces < goldNeeded)
    {
        cout << display_code << id_num << ": Not enough money for battles." << endl;
    }
    else if (current_hideout->GetNumBattlesRemaining() == 0)
    {
        cout << display_code << id_num << ": Cannot battle! This DemonHideout has no more mages to battle!" << endl;
    }
    else
    {

        state = BATTLING_IN_HIDEOUT;
        cout << display_code << id_num << ": Started to battle at the DemonHideout " << current_hideout->GetId() << " with " << num_battles << " battles." << endl;
    }
}

void Mage::StartRecoveringMana(unsigned int num_crystals)
{
    if (state != AT_SPIRE)
    {
        cout << display_code << id_num << ": I can only recover mana at a ManaSpire!" << endl;
    }
    else if (!current_spire->CanAffordCrystal(num_crystals, gold_pieces))
    {
        cout << display_code << id_num << ": Not enough money to recover mana." << endl;
    }
    else if (current_spire->GetNumCrystalsRemaining() == 0)
    {
        cout << display_code << id_num << ": Cannot recover! No crystal remaining in this ManaSpire." << endl;
    }
    else
    {
        state = RECOVERING_MANA;
        cout << display_code << id_num << ": Started recovering " << num_crystals << " at ManaSpire " << current_spire->GetId() << endl;
        crystals_to_buy = current_spire->DistributeCrystals(num_crystals);
    }
}

void Mage::Stop()
{
    cout << display_code << id_num << ": Stopping." << endl;
    state = STOPPED;
}

bool Mage::IsKnockedOut() const
{
    return mana == 0;
}

bool Mage::ShouldBeVisible() const
{
    return state != KNOCKED_OUT;
}

void Mage::ShowStatus() const
{

    cout << name << " status: " << endl;
    GameObject::ShowStatus();
    cout << "Mana: " << mana << endl;
    cout << "Gold Pieces: " << gold_pieces << endl;
    cout << "Experience: " << experience << endl;

    switch (state)
    {
    case STOPPED:
        cout << "stopped" << endl;
        break;

    case MOVING:
        cout << "moving at a speed of " << speed << " to destination " << destination << " at each step of " << delta << endl;
        break;

    case MOVING_TO_HIDEOUT:
        cout << "heading to DemonHideout " << current_hideout->GetId() << " at a speed of " << speed << " at each step of " << delta << endl;
        break;

    case MOVING_TO_SPIRE:
        cout << "heading to ManaSpire " << current_spire->GetId() << " at a speed of " << speed << " at each step of " << delta << endl;
        break;

    case IN_HIDEOUT:
        cout << "inside DemonHideout " << current_hideout->GetId() << endl;
        break;

    case AT_SPIRE:
        cout << "inside ManaSpire " << current_spire->GetId() << endl;
        break;

    case BATTLING_IN_HIDEOUT:
        cout << "battling in DemonHideout " << current_hideout->GetId() << endl;
        break;

    case RECOVERING_MANA:
        cout << "recovering mana in ManaSpire " << current_spire->GetId() << endl;
        break;
    }
}

bool Mage::Update()
{

    if (IsKnockedOut() && state != AT_SPIRE && state != RECOVERING_MANA && state != IN_HIDEOUT)
    {
        state = KNOCKED_OUT;
        cout << "**************************" << endl;
    }

    switch (state)
    {
    case STOPPED:
        return false;
        break;

    case MOVING:
        if (UpdateLocation())
        {
            state = STOPPED;
            return true;
        }
        else
            return false;
        break;

    case MOVING_TO_HIDEOUT:
        if (UpdateLocation())
        {
            state = IN_HIDEOUT;
            current_hideout->AddOneMage();
            return true;
        }
        else
            return false;
        break;

    case MOVING_TO_SPIRE:
        if (UpdateLocation())
        {
            state = AT_SPIRE;
            current_spire->AddOneMage();
            return true;
        }
        else
            return false;
        break;

    case IN_HIDEOUT:
        return false;

    case AT_SPIRE:
        return false;

        // fix these two
    case BATTLING_IN_HIDEOUT:
    {
        mana -= current_hideout->GetManaCost(battles_to_buy);
        gold_pieces -= current_hideout->GetGoldCost(battles_to_buy);
        double expGained = battles_to_buy * current_hideout->GetExperiencePerBattle();
        experience += expGained;
        cout << "** " << name << " completed " << battles_to_buy << " battle(s)! **" << endl;
        cout << "** " << name << " gained " << expGained << " experience! **" << endl;
        state = IN_HIDEOUT;
        return true;
    }
    break;

    case RECOVERING_MANA:
    {
        int manaGained = crystals_to_buy * 5;
        mana += manaGained;
        gold_pieces -= current_spire->GetCrystalCost(crystals_to_buy);
        cout << "** " << name << " recovered " << manaGained << " mana! ** " << endl;
        cout << "** " << name << " bought " << crystals_to_buy << " crystal(s)! ** " << endl;
        state = AT_SPIRE;
        return true;
        break;
    }

    case KNOCKED_OUT:
        cout << name << " is out of mana and can't move" << endl;
        return false;
        break;
    }

    return false;
}

bool Mage::UpdateLocation()
{
    if (fabs(destination.x - location.x) <= fabs(delta.x) && fabs(destination.y - location.y) <= fabs(delta.y))
    {
        gold_pieces += GetRandomAmountOfGP();
        prevLocation = location;
        location = destination;
        cout << display_code << id_num << ": I'm there!" << endl;
        mana -= 1;

        if (HuntedByDemon) {
            mana -= 1; // Loses double mana when hunted by demon
            follower->UpdateLocation(prevLocation);
        }

        return true;
    }
    else
    {
        gold_pieces += GetRandomAmountOfGP();
        prevLocation = location;
        location = location + delta;
        cout << display_code << id_num << ": step...!" << endl;
        mana -= 1;

        if (HuntedByDemon) {
            mana -= 1;
            follower->UpdateLocation(prevLocation);
        }

        return false;
    }
}

void Mage::SetupDestination(Point2D dest)
{
    delta = (dest - location) * (speed / Point2D::GetDistanceBetweenPoints(dest, location));
    destination = dest;
}

double GetRandomAmountOfGP()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0.0, 2.0);
    return dis(gen);
}

Mage::~Mage()
{
    cout << "Mage destructed" << endl;
}

string Mage::GetName()
{
    return name;
}

bool Mage::isDead() const
{
    return state == KNOCKED_OUT;
}

void Mage::AddFollower(RoamingDemon *roamer)
{
    HuntedByDemon = true;
    follower = roamer;
    cout << "Mage " << id_num << " is being followed by RoamingDemon " << roamer->GetId() << endl;
}

bool Mage::IsFollowed()
{
    return HuntedByDemon;
}

void Mage::save(ofstream& file) const
{
    GameObject::save(file); // Call parent functions 
    file << speed;
    file << is_at_spire;
    file << is_in_hideout;
    file << mana;
    file << experience;
    file << gold_pieces;
    file << battles_to_buy;
    file << crystals_to_buy;
    file << name;

    if (current_spire != nullptr) file << current_spire->GetId();
    else file << -1;

    if (current_hideout != nullptr) file << current_hideout->GetId();
    else file << -1;

    file << destination.x << " " << destination.y;
    file << delta.x << " " << delta.y;

    if (follower != nullptr) file << follower->GetId();
    else file << -1;

    file << HuntedByDemon;
    file << prevLocation.x << " " << prevLocation.y;
    file << endl;
}
// void restore(ifstream& file, Model& model) const;