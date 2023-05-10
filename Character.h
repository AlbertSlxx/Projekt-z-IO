#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <cmath>
#include <cstdlib>
#include <memory>
#include "Equipment.h"
#include <list>
#include <utility>
class Observer;


class CharacterClass
{
public:
	CharacterClass();
	virtual ~CharacterClass() = 0;
	Profession getProf();
	int getMainStat() const;
	int getAttackModifier() const;
	int getVitalityModifier() const;
	int getDefenseModifier() const;
	string getMainStatName();
	string getProfName();
	string getSpecialAbility();

protected:
	Profession Prof;
	int mainStat{};
	int attackModifier{};
	int vitalityModifier{};
	int defenseModifier{};
	void setSpecialAbility(string sa);
	void setMainStatName(string sm);
	void setDefenseModifier(int);
	void setMainStat(int);
	void setVitalityModifier(int);
	void setAttackModifier(int);
	void setProf(Profession);
	string mainStatName;
	string SpecialAbility;
};

class Scout : public CharacterClass
{
public:
	Scout();
	~Scout() override;
};

class Mage : public CharacterClass
{
public:
	Mage();
	~Mage() override;
};

class Warrior : public CharacterClass
{
public:
	Warrior();
	~Warrior() override;
};


class Character
{
public:
	Character();
	virtual ~Character()=0;
	int getMinimalAttack() const;
	virtual void setMinimalAttack() {}
	int getMaximalAttack() const;
	virtual void setMaximalAttack() {}
	int getLevel() const;
	virtual void setLevel(int) {}
	int getCurrentHealth() const;
	virtual void setCurrentHealth(int);
	double getCriticalChance() const;
	void setCriticalChance(double);
	int getMaxHealth() const;
	virtual void setBlockChance() {}
	double getBlockChance() const;
	virtual void setMaxHealth() {}
	virtual void setDefense() {}
	int getDefense() const;
	int getDamage(int);
	virtual void chooseClass() {}
	string getName();
	bool useSpecialEffect(shared_ptr<Character>& opponent, const shared_ptr<View>& view);
	int useSpecialAttack() const;
	Profession getProf();
	void attackOpponent(shared_ptr<Character>& opponent, const shared_ptr<View>& view);

protected:
	int minimalAttack{};
	int maximalAttack{};
	int level{};
	int currentHealth{};
	int maxHealth{};
	int defense{};
	double blockChance{};
	string name;
	double criticalChance{};
	unique_ptr<CharacterClass> Class;
};

class Hero : public Character
{
public:
	~Hero() override;
	static shared_ptr<Hero>& getInstance();
	Hero(Hero &other) = delete;
	void operator=(const Hero &) = delete;
	void showStatistics(const shared_ptr<View>& view);
	void showEQ(const shared_ptr<View>& view);
	void showOneItem(ItemType, Profession, const shared_ptr<View>& view);
	void setAllStats();
	void chooseClass(int c);
	void setMaxHealth(int);
	void setDefense(int);
	void setCurrentHealth(int) override;
	void setLevel(int) override;
	void setMinimalAttack(int);
	void setMaximalAttack(int);
	void setAttack(int, int,int);
	void setName(string n);
	void levelUp();
	void setBlockChance() override;
	void setMoney(int);
	int getMoney() const;
	void ChangeEQ(shared_ptr<Item>&, const shared_ptr<View>& view);
	bool fight(shared_ptr<Character>&,bool, const shared_ptr<View>& view);
	void AddObserver(const shared_ptr<Observer>&);
	void DeleteObserver(const shared_ptr<Observer>&);
	
private:
	Hero();
    int money{};
	void Notify();
	list<shared_ptr<Observer>> obs;
	static shared_ptr<Hero> hero;
	unique_ptr<Equipment> EQ;
};

class monster : public Character
{
public:
	monster(int,bool);
	~monster() override;
	void chooseClass() override;
	void setMaxHealth() override;
	void setDefense() override;
	void setLevel(int) override;
	void setMinimalAttack() override;
	void setMaximalAttack() override;
	void setBlockChance() override;
    void setName(bool);
	void setALL(int);
};


class Observer : public enable_shared_from_this<Observer>
{
public:
    explicit Observer(shared_ptr<Hero> hero): h(std::move(hero)){}
    void setTrue();
    bool check(const shared_ptr<View>& view);
    void removeFromObserver();
    void addToObserver();

private:
    bool endik{ false };
    bool getEndik() const;
    shared_ptr<Hero> h;
};

#endif