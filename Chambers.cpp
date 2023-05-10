#include <iostream>
#include <utility>
#include "Chambers.h"
using namespace std;


template<typename Derived, typename T>
inline bool instanceof(const shared_ptr<T> ptr) {
    shared_ptr<Derived> d = dynamic_pointer_cast<Derived>(ptr);
    return d != nullptr;
}
ActionVisitor::ActionVisitor(const shared_ptr<Hero>& h)
{
    this->obs = make_shared<Observer>(h);
    this->obs->addToObserver();
}
void ActionVisitor::eventTransitionFunction(shared_ptr<EventNode> &start, shared_ptr<Hero> &h, const shared_ptr<View>& view) {
    shared_ptr<EventNode> curr = start;
    while (true)
    {
        curr->current->Action(h, view);

        if (this->obs->check(view))
            break;

        int numOfNexts = (int)curr->allNexts.size();

        if (numOfNexts == 1)
            curr = curr->allNexts[0];
        else {
            int i = 1;
            vector <shared_ptr<EventNode>> options = curr->allNexts;
            shared_ptr<DescriptionVisitor> visitor(new DescriptionVisitor());

            for (auto & option : options) {
                view->OptionsForGoNext(i);
                option->current->DisplayDescription(*visitor, view);
                i++;
            }

            int choice;
            while (true) {
                cin >> choice;
                if (cin.fail() || choice < 1 || choice > numOfNexts) {
                    view->NotRecognizedCharacter();

                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else
                    break;
            }

            curr = curr->allNexts[choice - 1];
        }

        if (instanceof<EndPoint>(curr->current))
        {
            curr->current->Action(h, view);
            break;
        }

    }
}

void ActionVisitor::visitMonsterRoom(shared_ptr<View> view) {
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<EventNode> start = MonsterRoom::prepareEventsGraph();

    eventTransitionFunction(start, h, view);
}

void ActionVisitor::visitTrapRoom(shared_ptr<View> view)
{
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<EventNode> start = TrapRoom::prepareEventsGraph();

    eventTransitionFunction(start, h, view);
}

void ActionVisitor::visitPotionRoom(shared_ptr<View> view)
{
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<EventNode> start = PotionRoom::prepareEventsGraph();

    eventTransitionFunction(start, h, view);
}

void ActionVisitor::visitTreasureRoom(shared_ptr<View> view)
{
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<EventNode> start = TreasureRoom::prepareEventsGraph();

    eventTransitionFunction(start, h, view);
}

void ActionVisitor::visitHealthRoom(shared_ptr<View> view)
{
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<EventNode> start = HealthRoom::prepareEventsGraph();

    eventTransitionFunction(start, h, view);
}

void ActionVisitor::visitTraderRoom(shared_ptr<View> view)
{
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<EventNode> start = TraderRoom::prepareEventsGraph();

    eventTransitionFunction(start, h, view);
}

void ActionVisitor::visitEmptyRoom(shared_ptr<View> view)
{
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<EventNode> start = EmptyRoom::prepareEventsGraph();

    eventTransitionFunction(start, h, view);
}

void ActionVisitor::visitStartingRoom(shared_ptr<View> view)
{
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<EventNode> start = StartingRoom::prepareEventsGraph();

    eventTransitionFunction(start, h, view);
}

void ActionVisitor::visitBossRoom(shared_ptr<View> view)
{
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<EventNode> start = BossChamber::prepareEventsGraph();

    eventTransitionFunction(start, h, view);

    if (h->getCurrentHealth() > 0)
        view->GameSuccessfulFinished();
    else
        view->GameAlmostFinished();
}



void BossChamber::action(ActionVisitor visitor, shared_ptr<View> view) {
    visitor.visitBossRoom(view);
}
shared_ptr<EventNode> BossChamber::prepareEventsGraph() {
    shared_ptr<Hero> h = Hero::getInstance();

    shared_ptr<EventNode> start = make_shared<EventNode>(make_shared<EnterToBossRoom>());
    shared_ptr<EventNode> bossFight = make_shared<EventNode>(make_shared<BossFight>());
    bossFight->allNexts.reserve(1);
    start->allNexts.reserve(1);
    start->allNexts.emplace_back(bossFight);
    bossFight->allNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>()));

    return start;
}


void MonsterRoom::action(ActionVisitor visitor, shared_ptr<View> view) {
    visitor.visitMonsterRoom(view);
}
shared_ptr<EventNode> MonsterRoom::prepareEventsGraph() {
    shared_ptr<Hero> h = Hero::getInstance();

    shared_ptr<EventNode> start = make_shared<EventNode>(make_shared<EnterToMonsterRoom>());
    shared_ptr<EventNode> fight = make_shared<EventNode>(make_shared<Fight>());
    shared_ptr<EventNode> runAway = make_shared<EventNode>(make_shared<RunAway>());
    shared_ptr<EventNode> openBox = make_shared<EventNode>(make_unique<CheckChest>());
    start->allNexts.reserve(2);
    fight->allNexts.reserve(2);
    openBox->allNexts.reserve(1);
    runAway->allNexts.reserve(1);
    start->allNexts.emplace_back(fight);
    start->allNexts.emplace_back(runAway);
    fight->allNexts.emplace_back(openBox);
    fight->allNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>()));
    openBox->allNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>()));
    runAway->allNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>()));

    return start;
}


void TrapRoom::action(ActionVisitor visitor, shared_ptr<View> view) {
    visitor.visitTrapRoom(view);
}
shared_ptr<EventNode> TrapRoom::prepareEventsGraph() {
    shared_ptr<Hero> h = Hero::getInstance();

    shared_ptr<EventNode> start = make_shared<EventNode>(make_shared<EnterToTrapRoom>());
    start->allNexts.reserve(1);
    shared_ptr<EventNode> trap = make_shared<EventNode>(make_shared<ActiveTheTrap>());
    trap->allNexts.reserve(1);
    start->allNexts.emplace_back(trap);
    trap->allNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>()));

    return start;
}


void PotionRoom::action(ActionVisitor visitor, shared_ptr<View> view) {
    visitor.visitPotionRoom(view);
}
shared_ptr<EventNode> PotionRoom::prepareEventsGraph() {
    shared_ptr<Hero> h = Hero::getInstance();

    shared_ptr<EventNode> start = make_shared<EventNode>(make_shared<EnterToPotionRoom>());
    start->allNexts.reserve(2);
    shared_ptr<EventNode> potion = make_shared<EventNode>(make_shared<DrinkPotion>());
    potion->allNexts.reserve(1);
    start->allNexts.emplace_back(potion);
    start->allNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>()));
    potion->allNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>()));

    return start;
}


void TreasureRoom::action(ActionVisitor visitor, shared_ptr<View> view) {
    visitor.visitTreasureRoom(view);
}
shared_ptr<EventNode> TreasureRoom::prepareEventsGraph() {
    shared_ptr<Hero> h = Hero::getInstance();

    shared_ptr<EventNode> start = make_shared<EventNode>(make_shared<EnterToTreasureRoom>());
    start->allNexts.reserve(2);
    shared_ptr<EventNode> chestEvent = make_shared<EventNode>(make_shared<CheckChest>());
    chestEvent->allNexts.reserve(1);
    start->allNexts.emplace_back(chestEvent);
    start->allNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>()));
    chestEvent->allNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>()));

    return start;
}


void HealthRoom::action(ActionVisitor visitor, shared_ptr<View> view) {
    visitor.visitHealthRoom(view);
}
shared_ptr<EventNode> HealthRoom::prepareEventsGraph() {
    shared_ptr<Hero> h = Hero::getInstance();

    shared_ptr<EventNode> start = make_shared<EventNode>(make_shared<EnterToHealthRoom>());
    start->allNexts.reserve(2);
    shared_ptr<EventNode> health = make_shared<EventNode>(make_shared<HealthYourself>());
    health->allNexts.reserve(1);
    start->allNexts.emplace_back(health);
    start->allNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>()));
    health->allNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>()));

    return start;
}


void TraderRoom::action(ActionVisitor visitor, shared_ptr<View> view) {
    visitor.visitTraderRoom(view);
}
shared_ptr<EventNode> TraderRoom::prepareEventsGraph() {
    shared_ptr<Hero> h = Hero::getInstance();

    shared_ptr<EventNode> start = make_shared<EventNode>(make_shared<EnterToTraderRoom>());
    start->allNexts.reserve(2);
    shared_ptr<EventNode> see = make_shared<EventNode>(make_shared<SeeItems>());
    see->allNexts.reserve(1);

    start->allNexts.emplace_back(see);
    start->allNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>()));
    see->allNexts.push_back(make_shared<EventNode>(make_shared<EndPoint>()));

    return start;
}


void EmptyRoom::action(ActionVisitor visitor, shared_ptr<View> view) {
    visitor.visitEmptyRoom(view);
}
shared_ptr<EventNode> EmptyRoom::prepareEventsGraph() {
    shared_ptr<Hero> h = Hero::getInstance();

    shared_ptr<EventNode> start = make_shared<EventNode>(make_shared<EnterToEmptyRoom>());
    start->allNexts.reserve(1);
    start->allNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>()));

    return start;
}


void StartingRoom::action(ActionVisitor visitor, shared_ptr<View> view) {
    visitor.visitStartingRoom(view);
}
shared_ptr<EventNode> StartingRoom::prepareEventsGraph() {
    shared_ptr<Hero> h = Hero::getInstance();

    shared_ptr<EventNode> start= make_shared<EventNode>(make_shared<EnterToStartingRoom>());
    start->allNexts.reserve(1);
    start->allNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>()));

    return start;
}



ChamberNode::ChamberNode(shared_ptr<Chamber> curr) {
	current = std::move(curr);
	option1 = nullptr;
	option2 = nullptr;
}