#include "Equipment.h"


Equipment::Equipment(int lvl,Profession prof)
{
	fac = make_unique<ItemFactory>();
	weapon_slot = fac->createItem(lvl, weapon, prof);
	armor_slot = fac->createItem(lvl, armor, prof);
	talisman_slot = fac->createItem(lvl, talisman, prof);
	headgear_slot = fac->createItem(lvl, headgear, prof);
	if (prof == warrior)
		shield_slot = fac->createItem(lvl, shield, prof);
	else
		shield_slot = nullptr;
}

bool Equipment::ChangeItem(shared_ptr<Item>& i)
{
    ItemType type = i->getType();

    switch (type) {
        case weapon:
            this->weapon_slot = i;
            break;
        case armor:
            this->armor_slot = i;
            break;
        case headgear:
            this->headgear_slot = i;
            break;
        case talisman:
            this->talisman_slot = i;
            break;
        case shield:
            this->shield_slot = i;
            break;
    }

	return true;
}

Equipment::~Equipment() = default;