#include "GameCommand.h"
#include "Model.h"

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

void DoAdvanceCommand(Model& model, View& view)
{
    cout << "Advancing one tick" << endl;
    model.Update();
    model.ShowStatus();
    model.Display(view);
}

void DoRunCommand(Model& model, View& view)
{
    cout << "Advanding to next event" << endl;
    for (int steps = 0; steps < 5; steps++)
    {
        if(model.Update()) {
            break;
        }

    }
    model.ShowStatus();
    model.Display(view);
}


void getInput(Model& model, View& view) {
    cout << endl << "*********" << endl;
    char code;
    int in1, in2, in3;

    cout << "Enter a command: "; //check if this is correct
    cin >> code;

    switch (code) {
        case 'm':
            cin >> in1 >> in2 >> in3;
            DoMoveCommand(model, in1, Point2D(in2, in3));
            break;
        case 's':
            cin >> in1 >> in2;
            DoMoveToSpireCommand(model, in1, in2);
            break;
        case 'd':
            cin >> in1 >> in2;
            DoMoveToHideoutCommand(model, in1, in2);
            break;
        case 'h':
            cin >> in1;
            DoStopCommand(model, in1);
            break;
        case 'c':
            cin >> in1 >> in2;
            DoRecoverInSpireCommand(model, in1, in2);
            break;
        case 'b':
            cin >> in1 >> in2;
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
    }
}


