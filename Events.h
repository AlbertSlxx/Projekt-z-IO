#pragma once
#ifndef EVENTS_H
#define EVENTS_H
#include "Views.h"
#include <vector>
#include "Strategy.h"


ItemType getRandomItemType( shared_ptr<Hero>&h);
class DescriptionVisitor;

// Part of Controller
class Chest {
public:
    static void openBox(shared_ptr<Hero>& hero, const shared_ptr<View>& view);
};

class Event {
public:
    Event();
    virtual void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) = 0;
    virtual void Action(shared_ptr<Hero> &h, const shared_ptr<View>& view);
};

class EndPoint : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) override;
    void Action(shared_ptr<Hero> &h, const shared_ptr<View>& view) override;
};

class EnterToMonsterRoom : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) override;
    void Action(shared_ptr<Hero> &h, const shared_ptr<View>& view) override;
};

class Fight : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) override;
    void Action(shared_ptr<Hero> &h, const shared_ptr<View>& view) override;
};

class RunAway : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) override;
    void Action(shared_ptr<Hero> &h, const shared_ptr<View>& view) override;
};

class CheckChest : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) override;
    void Action(shared_ptr<Hero> &h, const shared_ptr<View>& view) override;
};

class EnterToTrapRoom : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) override;
    void Action(shared_ptr<Hero> &h, const shared_ptr<View>& view) override;
};

class ActiveTheTrap : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) override;
    void Action(shared_ptr<Hero> &h, const shared_ptr<View>& view) override;
};

class EnterToPotionRoom : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) override;
    void Action(shared_ptr<Hero> &h, const shared_ptr<View>& view) override;
};

class DrinkPotion : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) override;
    void Action(shared_ptr<Hero> &h, const shared_ptr<View>& view) override;
};

class EnterToTreasureRoom : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) override;
    void Action(shared_ptr<Hero> &h, const shared_ptr<View>& view) override;
};

class EnterToHealthRoom : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) override;
    void Action(shared_ptr<Hero> &h, const shared_ptr<View>& view) override;
};

class HealthYourself : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) override;
    void Action(shared_ptr<Hero> &h, const shared_ptr<View>& view) override;
};

class EnterToTraderRoom : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) override;
    void Action(shared_ptr<Hero> &h, const shared_ptr<View>& view) override;
};

class SeeItems : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) override;
    void Action(shared_ptr<Hero> &h, const shared_ptr<View>& view) override;

protected:
    static void BuyItems(shared_ptr<Hero> &h, shared_ptr<Item>& i1, shared_ptr<Item>& i2, shared_ptr<Item>& i3, const shared_ptr<View>& view);
    static bool buyOneItem(shared_ptr<Hero> &h, shared_ptr<Item>& item, const shared_ptr<View>& view);
};

class EnterToEmptyRoom : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) override;
    void Action(shared_ptr<Hero> &h, const shared_ptr<View>& view) override;
};

class EnterToStartingRoom : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) override;
    void Action(shared_ptr<Hero> &h, const shared_ptr<View>& view) override;
};

class EnterToBossRoom : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) override;
    void Action(shared_ptr<Hero> &h, const shared_ptr<View>& view) override;
};

class BossFight : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) override;
    void Action(shared_ptr<Hero> &h, const shared_ptr<View>& view) override;
};


class EventNode {
public:
    explicit EventNode(shared_ptr<Event>&& curr);
    shared_ptr<Event> current;
    vector <shared_ptr<EventNode>> allNexts;
};


// Part of Controller
class DescriptionVisitor {
public:
    static void visitEndPoint(const shared_ptr<View> &view);
    static void visitEnterToMonsterRoom(const shared_ptr<View> &view);
    static void visitFight(const shared_ptr<View> &view);
    static void visitRunAway(const shared_ptr<View> &view);
    static void visitCheckChest(const shared_ptr<View> &view);
    static void visitEnterToTrapRoom(const shared_ptr<View> &view);
    static void visitActiveTheTrap(const shared_ptr<View> &view);
    static void visitEnterToPotionRoom(const shared_ptr<View> &view);
    static void visitDrinkPotion(const shared_ptr<View> &view);
    static void visitEnterToTreasureRoom(const shared_ptr<View> &view);
    static void visitEnterToHealthRoom(const shared_ptr<View> &view);
    static void visitHealthYourself(const shared_ptr<View> &view);
    static void visitEnterToTraderRoom(const shared_ptr<View> &view);
    static void visitSeeItems(const shared_ptr<View> &view);
    static void visitEnterToEmptyRoom(const shared_ptr<View> &view);
    static void visitEnterToStartingRoom(const shared_ptr<View> &view);
    static void visitEnterToBossRoom(const shared_ptr<View>& view);
    static void visitBossFight(const shared_ptr<View>& view);
};

#endif