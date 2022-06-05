#pragma once

#include <string>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "Equipment.h"
const double dodge = 33.0;
const double block = 20.;
using namespace std;
enum Profession
{
	warrior = 1,
	scout = 2,
	mage = 3
};

class CharacterClass
{
public:
	CharacterClass();
	virtual ~CharacterClass() = 0;
	Profession getProf();
	int getmainStat();
	int getattackModifier();
	int getvitalityModifier();
	int getdefenseModifier();
	string getmainStatName();
	string getspecialAbility();

protected:
	Profession Prof;
	int mainStat;
	int attackModifier;
	int vitalityModifier;
	int defenseModifier;
	void setspecialAbility(string);
	void setmainStatName(string);
	void setdefenseModifier(int);
	void setmainStat(int);
	void setvitalityModifier(int);
	void setattackModifier(int);
	void setProf(Profession);
	string mainStatName;
	string SpecialAbility;
};

class Scout : public CharacterClass
{
public:
	Scout();
	~Scout();
};

class Mage : public CharacterClass
{
public:
	Mage();
	~Mage();
};
class Warrior : public CharacterClass
{
public:
	Warrior();
	~Warrior();
};



class Character
{
public:
	Character();
	virtual ~Character()=0;
	int getminimalAttack();
	virtual void setminimalAttack() {}
	int getmaximalAttack();
	virtual void setmaximalAttack() {}
	int getlevel();
	virtual void setlevel(int) {}
	int getcurrentHealth();
	void setcurrentHealth(int);
	double getcriticalChance();
	void setcriticalChance(double);
	int getmaxHealth();
	virtual void setmaxHealth() {}
	virtual void setdefense() {}
	int getdefense();
	int getDamage(int);
	virtual void chooseClass() {}
	virtual string getName() { return ""; }
	virtual void setName() {}
	bool useSpecialEffect(Character *opponent);
	int useSpecialAttack();
	void attackOpponent(Character * opponent);
protected:
	
	int minimalAttack;
	int maximalAttack;
	int level;
	int currentHealth;
	int maxHealth;
	int defense;
	double criticalChance;
	CharacterClass *Class;
};

class Hero : public Character
{
public:
	~Hero();
	static Hero *getInstance();
	Hero(Hero &other) = delete;
	void operator=(const Hero &) = delete;
	void showStatistics();
	void chooseClass();
	void death();
	void setmaxHealth(int);
	void setdefense(int);
	void setlevel(int);
	void setminimalAttack(int);
	void setmaximalAttack(int);
	void setName(string);
	string getName();
private:
	Hero();
	static Hero *hero;
	int money;
	string nick;
	Equipment *EQ;
};



class monster : public Character
{
public:
	monster(int);
	~monster();
	void chooseClass();
	void setmaxHealth();
	void setdefense();
	void setlevel(int);
	void setminimalAttack();
	void setmaximalAttack();
	void setName();
private:
	string name;
};
