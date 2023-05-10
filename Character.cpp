#include "Character.h"
#include <thread>
#include <utility>


const int defaultHealth = 50;
const double defaultCriticalChance = 3.;
const int defaultAttackMin = 2;
const int defaultAttackMax = 5;
const int counterAttackMin = 2;
const int counterAttackMax = 3;
const int defaultMonsterDefense = 3;
const double defaultMonsterCriticalChance = 15.;
const int defaultHealthMonster = 80;
const int defaultAttackMonsterMin = 20;
const int defaultAttackMonsterMax = 50;


Character::Character() = default;
Character::~Character() = default;

int Character::getMinimalAttack() const
{
	return this->minimalAttack;
}
int Character::getMaximalAttack() const
{
	return this->maximalAttack;
}
int Character::getLevel() const
{
	return this->level;
}
int Character::getCurrentHealth() const
{
	return this->currentHealth;
}
void Character::setCurrentHealth(int h)
{
	if (h > this->getMaxHealth())
	{
		h = this->getMaxHealth();
	}
	this->currentHealth = h;
}
int Character::getMaxHealth() const
{
	return this->maxHealth;
}
int Character::getDefense() const
{
	return this->defense;
}
string Character::getName()
{
	return this->name;
}
int Character::getDamage(int d)
{
	if (d >= this->getCurrentHealth())
	{
        this->setCurrentHealth(0);
	}
	else
	{
        this->setCurrentHealth(this->getCurrentHealth() - d);
	}
	return this->getCurrentHealth();
}
double Character::getCriticalChance() const
{
	return this->criticalChance;
}
double Character::getBlockChance() const
{
	return this->blockChance;
}
void Character::setCriticalChance(double c)
{
	this->criticalChance = c;
}
int Character::useSpecialAttack() const
{
	if (chance() <= this->getCriticalChance())
	{
		return 2;
	}
	return 1;
}
Profession Character::getProf()
{
	return this->Class->getProf();
}
void Character::attackOpponent(shared_ptr<Character>& opponent, const shared_ptr<View>& view)
{
	if (!this->useSpecialEffect(opponent, view))
	{
		return;
	}
	int damage = static_cast<int>(round(makeRand(this->getMinimalAttack(), this->getMaximalAttack())));
	damage = damage * this->useSpecialAttack() - opponent->getDefense();
	if (damage < 1) damage = 1;
	opponent->getDamage(damage);

    view->ShowCourseOfRound(this->getName(), opponent->getName(), damage);
    view->ShowCurrentHealthAfterRound(opponent->getName(), opponent->getCurrentHealth());
}
bool Character::useSpecialEffect(shared_ptr<Character>& opponent, const shared_ptr<View>& view)
{
	if (this->Class->getProf() == mage || opponent->Class->getProf() == mage)
	{
		return true;
	}
	if (opponent->Class->getProf() == scout)
	{
		if (chance() <= dodge)
		{
            view->DodgedHit(opponent->getName(), this->getName());
			return false;
		}
		return true;
	}
	if (opponent->Class->getProf() == warrior)
	{
		if (chance() <= opponent->getBlockChance())
		{
            view->BlockedHit(opponent->getName(), this->getName());
			return false;
		}
		return true;
	}
	return true;
}


CharacterClass::CharacterClass() = default;
CharacterClass::~CharacterClass() = default;

Profession CharacterClass::getProf()
{
	return this->Prof;
}
void CharacterClass::setProf(Profession p)
{
	this->Prof = p;
}
int CharacterClass::getAttackModifier() const
{
	return this->attackModifier;
}
void CharacterClass::setAttackModifier(int am)
{
	this->attackModifier = am;
}
int CharacterClass::getDefenseModifier() const
{
	return this->defenseModifier;
}
void CharacterClass::setDefenseModifier(int dm)
{
	this->defenseModifier = dm;
}
int CharacterClass::getMainStat() const
{
	return this->mainStat;
}
void CharacterClass::setMainStat(int ms)
{
	this->mainStat = ms;
}
int CharacterClass::getVitalityModifier() const
{
	return this->vitalityModifier;
}
void CharacterClass::setVitalityModifier(int vm)
{
	this->vitalityModifier = vm;
}
string CharacterClass::getSpecialAbility()
{
	return this->SpecialAbility;
}
void CharacterClass::setSpecialAbility(string sa)
{
	this->SpecialAbility = std::move(sa);
}
string CharacterClass::getMainStatName()
{
	return this->mainStatName;
}
void CharacterClass::setMainStatName(string sm)
{
	this->mainStatName = std::move(sm);
}
string CharacterClass::getProfName()
{
	if (this->getProf() == warrior)
	{
		return "Warrior";
	}
	else if (this->getProf() == scout)
	{
		return "Scout";
	}
	else if(this->getProf()==mage)
	{
		return "Mage";
	}
	else
	{
		return "undefined";
	}
}


Scout::Scout()
{
    this->setAttackModifier(2);
    this->setDefenseModifier(2);
    this->setVitalityModifier(2);
	this->setProf(scout);
    this->setMainStat(10);
    this->setSpecialAbility("You have 33 percent chance to dodge your opponent's attack");
    this->setMainStatName("Agility");
}
Scout::~Scout() = default;

Warrior::Warrior()
{

    this->setAttackModifier(1);
    this->setDefenseModifier(4);
    this->setVitalityModifier(4);
	this->setProf(warrior);
    this->setMainStat(5);
    this->setSpecialAbility("You have shield, which is able to block your opponent's attacks");
    this->setMainStatName("Strength");
}
Warrior::~Warrior() = default;

Mage::Mage()
{
    this->setAttackModifier(4);
    this->setDefenseModifier(1);
    this->setVitalityModifier(1);
	this->setProf(mage);
    this->setMainStat(20);
    this->setSpecialAbility("Opponent is not able to block your attack");
    this->setMainStatName("Intelligence");
}
Mage::~Mage() = default;


void monster::chooseClass()
{
	int p = static_cast<int>(round(makeRand(1, 3)));
	if (p == 1)
	{
		this->Class = make_unique<Warrior>();
	}
	else if (p == 2)
	{
		this->Class = make_unique<Scout>();
	}
	else
	{
		this->Class = make_unique<Mage>();
	}
}
void monster::setMaxHealth()
{
	this->maxHealth = defaultHealthMonster * this->getLevel() * this->Class->getVitalityModifier();
    this->setCurrentHealth(this->maxHealth);
}
void monster::setDefense()
{
	this->defense = defaultMonsterDefense * this->getLevel() * this->Class->getDefenseModifier();
}
void monster::setLevel(int l)
{
	this->level = l;
}
void monster::setBlockChance()
{
	if (this->Class->getProf() == warrior)
	{
		this->blockChance = 15.;
	}
	else
	{
		this->blockChance = 0.;
	}
}
void monster::setMinimalAttack()
{
	this->minimalAttack = defaultAttackMonsterMin * this->getLevel() * this->Class->getAttackModifier();
}
void monster::setMaximalAttack()
{
	this->maximalAttack = defaultAttackMonsterMax * this->getLevel() * this->Class->getAttackModifier();
}
void monster::setName(bool p)
{
	if (!p)
	{
		int rd = static_cast<int>(round(makeRand(0, sizeNamesForMonsters - 1)));
		this->name = namesForMonsters[rd];
	}
	else
	{
		int rd = static_cast<int>(round(makeRand(0, sizeNamesForBosses - 1)));
		this->name = namesForBosses[rd];
	}
}
monster::monster(int lvl,bool p)
{
	setALL(lvl);
	this->setName(p);
}

void monster::setALL(int lvl)
{
	this->chooseClass();
    this->setLevel(lvl);
    this->setMaxHealth();
    this->setDefense();
    this->setMinimalAttack();
    this->setMaximalAttack();
    this->setCriticalChance(defaultMonsterCriticalChance);
}
monster::~monster() = default;


shared_ptr<Hero> Hero::hero = nullptr;
shared_ptr<Hero>& Hero::getInstance()
{
	if (hero == nullptr)
	{
		hero.reset(new Hero());
	}
	return hero;
}
Hero::Hero() = default;

void Hero::setClassGenerateStartEQ(int classNum) {
    this->chooseClass(classNum);
    this->setLevel(1);
    this->setMoney(100);
    EQ = make_unique<Equipment>(this->getLevel(), this->getProf());
    this->setAllStats();
    this->setCurrentHealth(this->getMaxHealth());
}
Hero::~Hero() = default;
void Hero::setCurrentHealth(int h)
{
    Character::setCurrentHealth(h);
	if(!this->getCurrentHealth())
	{
		this->Notify();
	}
}
void Hero::AddObserver(const shared_ptr<Observer>& o)
{
	this->obs.push_back(o);
}
void Hero::DeleteObserver(const shared_ptr<Observer>& o)
{
	this->obs.remove(o);
}
void Hero::Notify()
{
	for(auto& ob : this->obs)
	{
		ob->setTrue();
	}
}

void Hero::chooseClass(int ch)
{
    switch (ch) {
        case 1:
            this->Class = make_unique<Warrior>();
            break;
        case 2:
            this->Class = make_unique<Scout>();
            break;
        case 3:
            this->Class = make_unique<Mage>();
            break;
        default:
            throw invalid_argument("Invalid class number");
    }
}
void Hero::setLevel(int s)
{
	this->level = s;
}

void Hero::setMinimalAttack(int s)
{
	this->minimalAttack = (s + defaultAttackMin * this->getLevel()) * this->Class->getAttackModifier();
}
void Hero::setMaximalAttack(int s)
{
	this->maximalAttack = (s + defaultAttackMax * this->getLevel()) * this->Class->getAttackModifier();
}
void Hero::setName(string n)
{
	this->name = std::move(n);
}
void Hero::levelUp()
{
	++this->level;
	this->setAllStats();
    this->setCurrentHealth(this->getCurrentHealth() + int(this->getMaxHealth() * 0.3));
}
void Hero::showStatistics(const shared_ptr<View>& view)
{
    int mainStat = this->EQ->weapon_slot->getMainStat() + this->EQ->headgear_slot->getMainStat() +
            this->Class->getMainStat() + this->EQ->talisman_slot->getMainStat();

	if (this->getProf())
	{
		view->ShowStatistics(this->getName(), this->Class->getProfName(), this->Class->getMainStatName(),
                             this->Class->getSpecialAbility(), this->getLevel(), mainStat, this->getMaxHealth(),
                             this->getCurrentHealth(), this->getMinimalAttack(), this->getMaximalAttack(),
                             this->getCriticalChance(), this->getDefense(), this->getMoney(), this->getBlockChance());
	}
	else
	{
	}
}
void Hero::showOneItemFromEQ(ItemType it, Profession p, const shared_ptr<View>& view)
{
    shared_ptr<Item> item;

	if (it == weapon) {
        item = this->EQ->weapon_slot;
	}
	else if (it == talisman) {
        item = this->EQ->talisman_slot;
	}
	else if (it == shield) {
        item = this->EQ->shield_slot;
	}
	else if (it == armor) {
        item = this->EQ->armor_slot;
	}
	else if (it == headgear) {
        item = this->EQ->headgear_slot;
	}

    view->ShowOneItem(item);
}
void Hero::showEQ(const shared_ptr<View>& view)
{
    shared_ptr<Item> weapon = this->EQ->weapon_slot;

    view->ShowEquipment(weapon, this->EQ->armor_slot, this->EQ->headgear_slot, this->EQ->talisman_slot, this->EQ->shield_slot);
}
void Hero::setAllStats()
{
    this->setMaxHealth(this->EQ->headgear_slot->getHealth() + this->EQ->armor_slot->getHealth());
	if (this->getCurrentHealth() > this->getMaxHealth())
	{
        this->setCurrentHealth(this->getMaxHealth());
	}
    this->setCriticalChance(this->EQ->talisman_slot->getCriticalChance() + this->EQ->weapon_slot->getCriticalChance() +
                            defaultCriticalChance *
                            this->getLevel());
    this->setDefense(this->EQ->armor_slot->getDefense() + this->EQ->headgear_slot->getDefense());
	this->setAttack(this->EQ->weapon_slot->getMainStat() + this->EQ->headgear_slot->getMainStat() +
                            this->Class->getMainStat() + this->EQ->talisman_slot->getMainStat(), this->EQ->weapon_slot->getMinDamage(), this->EQ->weapon_slot->getMaxDamage());
	this->setBlockChance();
}
void Hero::setAttack(int ms, int weaponMin, int weaponMax)
{
    this->setMinimalAttack(ms + weaponMin * counterAttackMin);
    this->setMaximalAttack(ms + weaponMax * counterAttackMax);
}
void Hero::setMaxHealth(int h)
{
	this->maxHealth = (this->getLevel() * defaultHealth + h) * this->Class->getVitalityModifier();
}
void Hero::setDefense(int d)
{
	if (this->Class->getProf() == warrior)
	{
		d += this->EQ->shield_slot->getDefense();
	}
	this->defense = d * this->Class->getDefenseModifier();
}
void Hero::setBlockChance()
{
	if (this->Class->getProf() == warrior) {
		this->blockChance = this->EQ->shield_slot->getBlockChance();
	}
	else {
		this->blockChance = 0;
	}
}
void Hero::setMoney(int m)
{
	this->money = m;
}
int Hero::getMoney() const
{
	return this->money;
}
void Hero::ChangeEQ(shared_ptr<Item>&i, const shared_ptr<View>& view)
{
	this->EQ->ChangeItem(i);
	this->setAllStats();

	view->CompletedEqChanging();
}
bool Hero::fight(shared_ptr<Character>& opponent,bool boss, const shared_ptr<View>& view)
{
	bool whoIsAttacking = true;
	chrono::milliseconds timespan(1000);
	while (this->getCurrentHealth() != 0 && opponent->getCurrentHealth() != 0)
	{
        view->BreakLine();
		if (whoIsAttacking) {
			this->attackOpponent(opponent, view);
		}
		else {
			shared_ptr<Character> h = this->getInstance();
			opponent->attackOpponent(h, view);
		}
		whoIsAttacking = !whoIsAttacking;

		if (boss)
			this_thread::sleep_for(timespan);
	}
    view->BreakLine();
	return this->getCurrentHealth() != 0;
}
void Observer::setTrue()
{
	this->endik = true;
}
bool Observer::getEndik() const
{
	return this->endik;
}
bool Observer::check(const shared_ptr<View>& view)
{
	if (this->getEndik())
	{
        view->EndGameMessage();
		return true;
	}
	else
		return false;
}
void Observer::removeFromObserver()
{
	this->h->DeleteObserver(shared_from_this());
}
void Observer::addToObserver()
{
	this->h->AddObserver(shared_from_this());
}