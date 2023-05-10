#pragma once
#ifndef STRATEGY_H
#define STRATEGY_H
#include "Character.h"


class Strategy {
public:
    explicit Strategy(shared_ptr<Hero>& h);
	void setStartingPrice(int p_value) { this->m_startingPrice = p_value, this->m_currentPrice = p_value; }
	bool buyingProcess(int price, shared_ptr<View> view);

protected:
	int getStartPrice() const { return m_startingPrice; }
	int getCurrentPrice() const { return m_currentPrice; }
	void setCurrentPrice(int p_value) { this->m_currentPrice = p_value; }
	virtual bool makeNewPrice( int p_heroPrice, shared_ptr<View> view) = 0;
	shared_ptr<Hero> h;

private:
	int m_startingPrice{};
	int m_currentPrice{};
	void takeMoney();
};

class StandardStrategy : public Strategy {
public:
	explicit StandardStrategy(shared_ptr<Hero> h);

private:
	bool makeNewPrice(int p_heroPrice, shared_ptr<View> view) override;
};

#endif