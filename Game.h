#ifndef GAME_H
#define GAME_H
#pragma once
#include "Chambers.h"


// Controller
class Game
{
public:
	Game();
	~Game();
	void play();
    shared_ptr<View> view;
	static shared_ptr<ChamberNode> prepareMap();
	void chamberTransitionFunction(shared_ptr<ChamberNode>& start);

private:
	shared_ptr<Hero> hero;
	shared_ptr<Observer> o;
    void heroSetClass();
    void heroSetName();
};

#endif