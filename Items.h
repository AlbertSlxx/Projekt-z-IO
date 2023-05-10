#pragma once
#ifndef ITEMS_H
#define ITEMS_H
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include "Names.h"
#include "Views.h"
using namespace std;


enum Profession
{
    warrior = 1,
    scout = 2,
    mage = 3,
    undefined = 4
};

enum ItemType
{
    weapon = 0,
    armor = 1,
    headgear = 2,
    talisman = 3,
    shield = 4
};


class Item {
protected:
    int item_ID;
    int value{};
    string name;
    ItemType type;

public:
    explicit Item(int level) {
        item_ID = static_cast<int>(round(makeRand(0, 999)));
    }
    int getValue() const { return value; }
    int getItemID() const { return item_ID; }
    string getName() const { return name; }
    ItemType getType() const { return type; }
    virtual int getMainStat() const { return 0; }
    virtual string getMainStatName() const { return ""; }
    virtual int getDefense() const { return 0; }
    virtual int getHealth() const { return 0; }
    virtual double getCriticalChance() const { return 0; }
    virtual double getBlockChance() const { return 0; }
    virtual int getMinDamage() const { return 0; }
    virtual int getMaxDamage() const { return 0; }
};


class Weapon : public Item {
protected:
    int min_damage;
    int max_damage;
    double critical_chance;

public:
    explicit Weapon(int level);
    int getMinDamage() const override { return min_damage; }
    int getMaxDamage() const override { return max_damage; }
    double getCriticalChance() const override { return critical_chance; }
};

class Sword : public Weapon {
protected:
    int main_stat;

public:
    explicit Sword(int level);
    int getMainStat() const override { return main_stat; }
    string getMainStatName() const override { return "strength"; }
};

class MagicStick : public Weapon {
protected:
    int main_stat;

public:
    explicit MagicStick(int level);
    int getMainStat() const override { return main_stat; }
    string getMainStatName() const override { return "intelligence"; }
};

class Bow : public Weapon {
protected:
    int main_stat;

public:
    explicit Bow(int level);
    int getMainStat() const override { return main_stat; }
    string getMainStatName() const override { return "agility"; }
};


class Armor : public Item {
protected:
    int defense;
    int health;

public:
    explicit Armor(int level);
    int getDefense() const override { return defense; }
    int getHealth() const override { return health; }
};


class Headgear : public Item {
protected:
    int defense;

public:
    explicit Headgear(int level);
    int getDefense() const override { return defense; }
};

class Helmet : public Headgear {
protected:
    int health;

public:
    explicit Helmet(int level);
    int getHealth() const override { return health; }
    string getMainStatName() const override { return "strength"; }
};

class MagicHat : public Headgear {
protected:
    int intelligence;

public:
    explicit MagicHat(int level);
    int getMainStat() const override { return intelligence; }
    string getMainStatName() const override { return "intelligence"; }
};


class Talisman : public Item {
protected:
    double critical_chance;

public:
    explicit Talisman(int level);
    double getCriticalChance() const override { return critical_chance; }
};

class ScoutTalisman : public Talisman {
protected:
    int agility;

public:
    explicit ScoutTalisman(int level);
    int getMainStat() const override { return agility; }
    string getMainStatName() const override { return "agility"; }
};

class WarriorTalisman : public Talisman {
protected:
    int strength;

public:
    explicit WarriorTalisman(int level);
    int getMainStat() const override { return strength; }
    string getMainStatName() const override { return "strength"; }
};

class MageTalisman : public Talisman {
protected:
    int intelligence;

public:
    explicit MageTalisman(int level);
    int getMainStat() const override { return intelligence; }
    string getMainStatName() const override { return "intelligence"; }
};


class Shield : public Item {
protected:
    int defense;
    double block_chance;

public:
    explicit Shield(int level);
    int getDefense() const override { return defense; }
    double getBlockChance() const override { return block_chance; }
};


class ItemFactory {
public:
    static unique_ptr<Item> createItem(int level, ItemType type, Profession profession);
};

static void showItemDetails(shared_ptr<Item>& item, Profession prof, const shared_ptr<View>& view)
{
    string type, proff;

    if (item->getType() == weapon)
        type = "weapon";
    else if (item->getType() == armor)
        type = "armor";
    else if (item->getType() == headgear)
        type = "headgear";
    else if (item->getType() == talisman)
        type = "talisman";
    else if (item->getType() == shield)
        type = "shield";

    if (prof == warrior)
        proff = "Warrior";
    else if (prof == scout)
        proff = "Scout";
    else if (prof == mage)
        proff = "Mage";

    view->ShowOneItem(type, proff, item->getValue(), item->getName(), item->getMinDamage(), item->getMaxDamage(), item->getMainStat(), item->getMainStatName());
}

#endif