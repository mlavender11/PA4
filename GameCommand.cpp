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
    int in1, in2, in3;

    cout << "Enter a command: ";
    cin >> code;

    try
    {
        switch (code)
        {
        case 'm':
            cin >> in1 >> in2 >> in3;
            if (!model.GetMagePtr(in1))
                throw Invalid_Input("No mage with id: " + to_string(in1));
            if (in2 < 0 || in2 > view.GetMaxSize() || in3 < 0 || in3 > view.GetMaxSize())
                throw Invalid_Input("Coordinates (" + to_string(in2) + ", " + to_string(in3) + ") are out of bounds");
            DoMoveCommand(model, in1, Point2D(in2, in3));
            break;

        case 's':
            cin >> in1 >> in2;
            if (!model.GetMagePtr(in1))
                throw Invalid_Input("No mage with id: " + to_string(in1));
            if (!model.GetManaSpirePtr(in2))
                throw Invalid_Input("No spire with id: " + to_string(in2));
            DoMoveToSpireCommand(model, in1, in2);
            break;
        case 'd':
            cin >> in1 >> in2;
            if (!model.GetMagePtr(in1))
                throw Invalid_Input("No mage with id: " + to_string(in1));
            if (!model.GetDemonHideoutPtr(in2))
                throw Invalid_Input("No hideout with id: " + to_string(in2));
            DoMoveToHideoutCommand(model, in1, in2);
            break;
        case 'h':
            cin >> in1;
            if (!model.GetMagePtr(in1))
                throw Invalid_Input("No mage with id: " + to_string(in1));
            DoStopCommand(model, in1);
            break;
        case 'c':
            cin >> in1 >> in2;
            if (!model.GetMagePtr(in1))
                throw Invalid_Input("No mage with id: " + to_string(in1));
            if (model.GetMagePtr(in1)->GetState() == RECOVERING_MANA)
                throw Invalid_Input("Mage " + to_string(in1) + " is already recovering mana");
            if (model.GetMagePtr(in1)->GetState() != AT_SPIRE)
                throw Invalid_Input("Mage " + to_string(in1) + " is not at a ManaSpire");
            DoRecoverInSpireCommand(model, in1, in2);
            break;
        case 'b':
            cin >> in1 >> in2;
            if (!model.GetMagePtr(in1))
                throw Invalid_Input("No mage with id: " + to_string(in1));
            if (model.GetMagePtr(in1)->GetState() == BATTLING_IN_HIDEOUT)
                throw Invalid_Input("Mage " + to_string(in1) + " is already battling");
            if (model.GetMagePtr(in1)->GetState() != IN_HIDEOUT)
                throw Invalid_Input("Mage " + to_string(in1) + " is not at a DemonHideout");
            DoBattleCommand(model, in1, in2);
            break;
        case 'a':
            DoAdvanceCommand(model, view);
            break;
        case 'r':
            DoRunCommand(model, view);
            break;
        case 'q':
            cout << "Quitting" << endl;
            exit(0);
            break;

        default:
            throw Invalid_Input("Unkown command entered");
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    catch (Invalid_Input &e)
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error: " << e.msg_ptr << endl;
    }
}
