#pragma once
#ifndef CHAMBER_H
#define CHAMBER_H
#include "Events.h"

class ActionVisitor;

// Part of Controller
class Chamber {
public:
    virtual void action(ActionVisitor visitor, shared_ptr<View> view) = 0;
};

class BossChamber : public Chamber {
public:
    void action(ActionVisitor visitor, shared_ptr<View> view) override;
    static shared_ptr<EventNode> prepareEventsGraph();
};

class PassageChamber : public Chamber {};
class NormalChamber : public PassageChamber {};
class SafeChamber : public PassageChamber {};

class MonsterRoom : public NormalChamber {
public:
    void action(ActionVisitor visitor, shared_ptr<View> view) override;
    static shared_ptr<EventNode> prepareEventsGraph();
};

class TrapRoom : public NormalChamber {
public:
    void action(ActionVisitor visitor, shared_ptr<View> view) override;
    static shared_ptr<EventNode> prepareEventsGraph();
};

class PotionRoom : public NormalChamber {
public:
    void action(ActionVisitor visitor, shared_ptr<View> view) override;
    static shared_ptr<EventNode> prepareEventsGraph();
};

class TreasureRoom : public SafeChamber {
public:
    void action(ActionVisitor visitor, shared_ptr<View> view) override;
    static shared_ptr<EventNode> prepareEventsGraph();
};

class HealthRoom : public SafeChamber {
public:
    void action(ActionVisitor visitor, shared_ptr<View> view) override;
    static shared_ptr<EventNode> prepareEventsGraph();
};

class TraderRoom : public SafeChamber {
public:
    void action(ActionVisitor visitor, shared_ptr<View> view) override;
    static shared_ptr<EventNode> prepareEventsGraph();
};

class EmptyRoom : public SafeChamber {
public:
    void action(ActionVisitor visitor, shared_ptr<View> view) override;
    static shared_ptr<EventNode> prepareEventsGraph();
};

class StartingRoom : public SafeChamber {
public:
    void action(ActionVisitor visitor, shared_ptr<View> view) override;
    static shared_ptr<EventNode> prepareEventsGraph();
};

class ChamberNode {
public:
	explicit ChamberNode(shared_ptr<Chamber> curr);
	shared_ptr<Chamber> current;
	shared_ptr<ChamberNode> option1;
	shared_ptr<ChamberNode> option2;
};


// Part of Controller
class IVisitor {
public:
    virtual ~IVisitor() = default;
    virtual void visitMonsterRoom(shared_ptr<View> view) = 0;
    virtual void visitTrapRoom(shared_ptr<View> view) = 0;
    virtual void visitPotionRoom(shared_ptr<View> view) = 0;
    virtual void visitTreasureRoom(shared_ptr<View> view) = 0;
    virtual void visitHealthRoom(shared_ptr<View> view) = 0;
    virtual void visitTraderRoom(shared_ptr<View> view) = 0;
    virtual void visitEmptyRoom(shared_ptr<View> view) = 0;
    virtual void visitStartingRoom(shared_ptr<View> view) = 0;
    virtual void visitBossRoom(shared_ptr<View> view) = 0;
};

// Part of Controller
class ActionVisitor : public IVisitor {
public:
    explicit ActionVisitor(const shared_ptr<Hero>& h);
    void visitMonsterRoom(shared_ptr<View> view) override;
    void visitTrapRoom(shared_ptr<View> view) override;
    void visitPotionRoom(shared_ptr<View> view) override;
    void visitTreasureRoom(shared_ptr<View> view) override;
    void visitHealthRoom(shared_ptr<View> view) override;
    void visitTraderRoom(shared_ptr<View> view) override;
    void visitEmptyRoom(shared_ptr<View> view) override;
    void visitStartingRoom(shared_ptr<View> view) override;
    void visitBossRoom(shared_ptr<View> view) override;

private:
    void eventTransitionFunction(shared_ptr<EventNode>& start, shared_ptr<Hero>& h, const shared_ptr<View>& view);
    shared_ptr<Observer> obs;
};

#endif