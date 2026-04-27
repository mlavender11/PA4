#include "GameCommand.h"
#include "Model.h"
#include "Invalid_Input.h"

void DoMoveCommand(Model &model, int mage_id, Point2D p1)
{
    Mage *mage = model.GetMagePtr(mage_id);
    cout << "Moving " << mage->GetName() << " to " << p1 << endl;

    mage->StartMoving(p1);
}

void DoMoveToSpireCommand(Model &model, int mage_id, int spire_id)
{
    Mage *mage = model.GetMagePtr(mage_id);
    ManaSpire *spire = model.GetManaSpirePtr(spire_id);
    cout << "Moving " << mage->GetName() << " to Mana Spire " << spire_id << endl;

    mage->StartMovingToSpire(spire);
}

void DoMoveToHideoutCommand(Model &model, int mage_id, int hideout_id)
{
    Mage *mage = model.GetMagePtr(mage_id);
    DemonHideout *hideout = model.GetDemonHideoutPtr(hideout_id);
    cout << "Moving " << mage->GetName() << " to hideout " << hideout_id << endl;

    mage->StartMovingToHideout(hideout);
}

void DoStopCommand(Model &model, int mage_id)
{
    Mage *mage = model.GetMagePtr(mage_id);
    cout << "Stopping " << mage->GetName() << endl;

    mage->Stop();
}

void DoBattleCommand(Model &model, int mage_id, unsigned int battles)
{
    Mage *mage = model.GetMagePtr(mage_id);
    cout << mage->GetName() << " is battling" << endl;

    mage->StartBattling(battles);
}

void DoRecoverInSpireCommand(Model &model, int mage_id, unsigned int crystals_needed)
{
    Mage *mage = model.GetMagePtr(mage_id);
    cout << "Recovering " << mage->GetName() << "'s mana" << endl;

    mage->StartRecoveringMana(crystals_needed);
}

void DoAdvanceCommand(Model &model, View &view)
{
    cout << "Advancing one tick" << endl;
    model.Update();
    model.ShowStatus();
    model.Display(view);
}

void DoRunCommand(Model &model, View &view)
{
    cout << "Advanding to next event" << endl;
    for (int steps = 0; steps < 5; steps++)
    {
        if (model.Update())
        {
            break;
        }
    }
    model.ShowStatus();
    model.Display(view);
}

void getInput(Model &model, View &view)
{
    cout << endl
         << "*********" << endl;
    char code;

    cout << "Enter a command: ";
    cin >> code;

    try
    {
        switch (code)
        {
        case 'm':
        {
            int id;
            double x, y;
            cin >> id >> x >> y;
            if (cin.fail())
                throw Invalid_Input("Wrong input types");
            if (!model.GetMagePtr(id))
                throw Invalid_Input("No mage with id: " + to_string(id));
            if (x < 0 || x > view.GetMaxSize() || y < 0 || y > view.GetMaxSize())
                throw Invalid_Input("Coordinates (" + to_string(x) + ", " + to_string(y) + ") are out of bounds");
            DoMoveCommand(model, id, Point2D(x, y));
            break;
        }

        case 's':
        {
            int in1, in2;
            cin >> in1 >> in2;
            if (cin.fail())
                throw Invalid_Input("Wrong input types");
            if (!model.GetMagePtr(in1))
                throw Invalid_Input("No mage with id: " + to_string(in1));
            if (!model.GetManaSpirePtr(in2))
                throw Invalid_Input("No spire with id: " + to_string(in2));
            DoMoveToSpireCommand(model, in1, in2);
            break;
        }
        case 'd':
        {
            int in1, in2;
            cin >> in1 >> in2;
            if (cin.fail())
                throw Invalid_Input("Wrong input types");
            if (!model.GetMagePtr(in1))
                throw Invalid_Input("No mage with id: " + to_string(in1));
            if (!model.GetDemonHideoutPtr(in2))
                throw Invalid_Input("No hideout with id: " + to_string(in2));
            DoMoveToHideoutCommand(model, in1, in2);
            break;
        }
        case 'h':
        {
            int in1;
            cin >> in1;
            if (cin.fail())
                throw Invalid_Input("Wrong input types");
            if (!model.GetMagePtr(in1))
                throw Invalid_Input("No mage with id: " + to_string(in1));
            DoStopCommand(model, in1);
            break;
        }
        case 'c':
        {
            int in1, in2;
            cin >> in1 >> in2;
            if (cin.fail())
                throw Invalid_Input("Wrong input types");
            if (!model.GetMagePtr(in1))
                throw Invalid_Input("No mage with id: " + to_string(in1));
            if (model.GetMagePtr(in1)->GetState() == RECOVERING_MANA)
                throw Invalid_Input("Mage " + to_string(in1) + " is already recovering mana");
            if (model.GetMagePtr(in1)->GetState() != AT_SPIRE)
                throw Invalid_Input("Mage " + to_string(in1) + " is not at a ManaSpire");
            DoRecoverInSpireCommand(model, in1, in2);
            break;
        }
        case 'b':
        {
            int in1, in2;
            cin >> in1 >> in2;
            if (cin.fail())
                throw Invalid_Input("Wrong input types");
            if (!model.GetMagePtr(in1))
                throw Invalid_Input("No mage with id: " + to_string(in1));
            if (model.GetMagePtr(in1)->GetState() == BATTLING_IN_HIDEOUT)
                throw Invalid_Input("Mage " + to_string(in1) + " is already battling");
            if (model.GetMagePtr(in1)->GetState() != IN_HIDEOUT)
                throw Invalid_Input("Mage " + to_string(in1) + " is not at a DemonHideout");
            DoBattleCommand(model, in1, in2);
            break;
        }
        case 'a':
        {
            DoAdvanceCommand(model, view);
            break;
        }
        case 'r':
        {
            DoRunCommand(model, view);
            break;
        }
        case 'q':
        {
            cout << "Quitting" << endl;
            exit(0);
            break;
        }
        case 'n':
        {
            char type;
            int id;
            double x, y;
            cin >> type >> id >> x >> y;

            if (cin.fail())
                throw Invalid_Input("Wrong input types");
            if (type != 's' && type != 'd' && type != 'g' && type != 'o')
                throw Invalid_Input(string(1, type) + " is not a valid type");
            if (x < 0 || x > view.GetMaxSize() || y < 0 || y > view.GetMaxSize())
                throw Invalid_Input("Coordinates (" + to_string(x) + ", " + to_string(y) + ") are out of bounds");
            if (id < 0 || id > 9)
                throw Invalid_Input("ID " + to_string(id) + " is out of bounds");

            model.NewCommand(type, id, Point2D(x, y));
            break;
        }
        case 'S': {
            string filename;
            cout << "Enter filename: ";
            cin >> filename;
            
            ofstream file(filename);
            model.save(file);
            break;
        }
        case 'R': {
            string filename;
            cout << "Enter filename: ";
            cin >> filename;

            ifstream file(filename);
            if (!file.is_open()) 
            {
                throw Invalid_Input("Could not open file " + filename);
            }
            else
                model.restore(file); 
            break;
        }

        default:
            throw Invalid_Input("Unknown command entered");
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear cin input on bad input
    }

    catch (Invalid_Input &e)
    {
        if (cin.fail())
            cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error: " << e.msg_ptr << endl;
    }
}
