#include "Strategy.h"
#include <utility>


Strategy::Strategy(shared_ptr<Hero>& hero) : h(hero) {}

void Strategy::takeMoney()
{
    h->setMoney(h->getMoney() - this->getCurrentPrice());
}

bool Strategy::buyingProcess(int price, shared_ptr<View> view)
{
    if(this->makeNewPrice(price, std::move(view)))
    {
        this->takeMoney();
        return true;
    }
    return false;
}


StandardStrategy::StandardStrategy(shared_ptr<Hero> h) : Strategy(h){}

bool StandardStrategy::makeNewPrice(int p_heroPrice, shared_ptr<View> view)
{
	bool l_flag{ false };
	if(p_heroPrice>h->getMoney())
	{
        view->NotEnoughGoldToBuyItem();
	}
	else if(p_heroPrice<this->getStartPrice()/2)
	{
		view->MuchTooLowOfferForItem();
	}
	else if(p_heroPrice>=this->getCurrentPrice())
	{
		l_flag = true;
		view->FairPriceOfferForItem();
		this->setCurrentPrice(p_heroPrice);
	}
	else
	{
		int l_newPrice{ (this->getCurrentPrice() + p_heroPrice) / 2 };
        view->AlmostFairPriceOfferForItem(l_newPrice);
		this->setCurrentPrice(l_newPrice);
	}
	if (!l_flag)
	{
		view->ShowFinalPrice(this->getCurrentPrice());
	}
	return l_flag;
}