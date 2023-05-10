#pragma once
#ifndef VIEWS_H
#define VIEWS_H
#include <string>
#include "Items.h"


class View {
public:
    //game
    virtual void OneOptionToMoveOn() = 0;
    virtual void TwoOptionsToMoveOn() = 0;


    //chambers
    virtual void OptionsForGoNext(int i) = 0;
    virtual void NotRecognizedCharacter() = 0;
    virtual void GameSuccessfulFinished() = 0;
    virtual void GameAlmostFinished() = 0;


    //events
    virtual void DescriptionEndPoint() = 0;
    virtual void DescriptionEnterToMonsterRoom() = 0;
    virtual void DescriptionFight() = 0;
    virtual void DescriptionRunAway() = 0;
    virtual void DescriptionCheckChest() = 0;
    virtual void DescriptionEnterToTrapRoom() = 0;
    virtual void DescriptionActiveTheTrap() = 0;
    virtual void DescriptionEnterToPotionRoom() = 0;
    virtual void DescriptionDrinkPotion() = 0;
    virtual void DescriptionEnterToTreasureRoom() = 0;
    virtual void DescriptionEnterToHealthRoom() = 0;
    virtual void DescriptionHealthYourself() = 0;
    virtual void DescriptionEnterToTraderRoom() = 0;
    virtual void DescriptionSeeItems() = 0;
    virtual void DescriptionEnterToEmptyRoom() = 0;
    virtual void DescriptionEnterToStartingRoom() = 0;
    virtual void DescriptionEnterToBossRoom() = 0;
    virtual void DescriptionBossFight() = 0;



    virtual void GoldFoundInChest(int i) = 0;
    virtual void ItemFoundInChest() = 0;
    virtual void ShowItemToChange() = 0;
    virtual void DecisionToReplaceItem() = 0;

    virtual void CheckStatisticsOrEquipment() = 0;

    virtual void EnteredToMonsterRoom() = 0;
    virtual void ShowCurrentHealth(int curr, int max) = 0;
    virtual void MonsterDefeated() = 0;
    virtual void RemainingHealth(int curr) = 0;
    virtual void LevelUp(int lvl) = 0;
    virtual void EscapeWithBeingHit() = 0;
    virtual void EscapeWithoutBeingHit() = 0;
    virtual void ChestFound() = 0;

    virtual void EnteredToTrapRoom() = 0;
    virtual void HurtedByTrap() = 0;

    virtual void EnteredToPotionRoom() = 0;
    virtual void HealthRestoredByPotion() = 0;
    virtual void HealthLostByPoisonedPotion(int lost) = 0;

    virtual void EnteredToTreasureRoom() = 0;

    virtual void EnteredToHealthRoom() = 0;
    virtual void HealthRestoredByMagicFountain() = 0;

    virtual void EnteredToTraderRoom() = 0;
    virtual void ShowMerchantItemWithPrice(int num, int price) = 0;
    virtual void ShowGoldBalance(int bal) = 0;
    virtual void DecisionToBuySomething() = 0;
    virtual void SelectNumberOfItemToBuy() = 0;
    virtual void SelectedItemHasAlreadyBeenBought() = 0;
    virtual void InvalidItemNumber() = 0;
    virtual void DecisionToBuyingAnotherItem() = 0;
    virtual void AllItemsHaveAlreadyBeenBought() = 0;
    virtual void DecisionToNegotiateItemPrice() = 0;
    virtual void PriceOfferForItem() = 0;

    virtual void EnteredToEmptyRoom() = 0;

    virtual void EnteredToStartingRoom() = 0;

    virtual void EnteredToBossRoom() = 0;
    virtual void BossDefeated() = 0;
    virtual void HeroDefeatedByBoss() = 0;


    //items
    virtual void InvalidClassValue() = 0;


    //strategy
    virtual void NotEnoughGoldToBuyItem() = 0;
    virtual void MuchTooLowOfferForItem() = 0;
    virtual void FairPriceOfferForItem() = 0;
    virtual void AlmostFairPriceOfferForItem(int offer) = 0;
    virtual void ShowFinalPrice(int price) = 0;


    //character (character1, character2);
    virtual void ShowCourseOfRound(string ch1, string ch2, int damage) = 0;
    virtual void ShowCurrentHealthAfterRound(string ch, int currH) = 0;
    virtual void DodgedHit(string ch1, string ch2) = 0;
    virtual void BlockedHit(string ch1, string ch2) = 0;

    virtual void ShowPossibleClassesToChoose() = 0;
    virtual void IncorrectNumber(int min, int max) = 0;
    virtual void ShowChosenClass(int ch) = 0;

    virtual void WriteHeroName() = 0;

    virtual void ShowEquipment(shared_ptr<Item> weapon, shared_ptr<Item> armor, shared_ptr<Item> headgear, shared_ptr<Item> talisman, shared_ptr<Item> shield) = 0;
    virtual void ShowStatistics(string name, string prof, string mainStatName, string skill, int level, int mainStat, int maxHealth, int currHealth, int minAttack,
                                int maxAttack, double crit, int def, int money, double block) = 0;

    virtual void ShowOneItem(shared_ptr<Item> item) = 0;

    virtual void CompletedEqChanging() = 0;
    virtual void BreakLine() = 0;
    virtual void EndGameMessage() = 0;
};

class TXTView : public View {
public:
    TXTView();

    //game
    void OneOptionToMoveOn() override;
    void TwoOptionsToMoveOn() override;


    //chambers
    void OptionsForGoNext(int i) override;
    void NotRecognizedCharacter() override;
    void GameSuccessfulFinished() override;
    void GameAlmostFinished() override;


    //events
    void DescriptionEndPoint() override;
    void DescriptionEnterToMonsterRoom() override;
    void DescriptionFight() override;
    void DescriptionRunAway() override;
    void DescriptionCheckChest() override;
    void DescriptionEnterToTrapRoom() override;
    void DescriptionActiveTheTrap() override;
    void DescriptionEnterToPotionRoom() override;
    void DescriptionDrinkPotion() override;
    void DescriptionEnterToTreasureRoom() override;
    void DescriptionEnterToHealthRoom() override;
    void DescriptionHealthYourself() override;
    void DescriptionEnterToTraderRoom() override;
    void DescriptionSeeItems() override;
    void DescriptionEnterToEmptyRoom() override;
    void DescriptionEnterToStartingRoom() override;
    void DescriptionEnterToBossRoom() override;
    void DescriptionBossFight() override;

    void GoldFoundInChest(int i) override;
    void ItemFoundInChest() override;
    void ShowItemToChange() override;
    void DecisionToReplaceItem() override;

    void CheckStatisticsOrEquipment() override;

    void EnteredToMonsterRoom() override;
    void ShowCurrentHealth(int curr, int max) override;
    void MonsterDefeated() override;
    void RemainingHealth(int curr) override;
    void LevelUp(int lvl) override;
    void EscapeWithBeingHit() override;
    void EscapeWithoutBeingHit() override;
    void ChestFound() override;

    void EnteredToTrapRoom() override;
    void HurtedByTrap() override;

    void EnteredToPotionRoom() override;
    void HealthRestoredByPotion() override;
    void HealthLostByPoisonedPotion(int lost) override;

    void EnteredToTreasureRoom() override;

    void EnteredToHealthRoom() override;
    void HealthRestoredByMagicFountain() override;

    void EnteredToTraderRoom() override;
    void ShowMerchantItemWithPrice(int num, int price) override;
    void ShowGoldBalance(int bal) override;
    void DecisionToBuySomething() override;
    void SelectNumberOfItemToBuy() override;
    void SelectedItemHasAlreadyBeenBought() override;
    void InvalidItemNumber() override;
    void DecisionToBuyingAnotherItem() override;
    void AllItemsHaveAlreadyBeenBought() override;
    void DecisionToNegotiateItemPrice() override;
    void PriceOfferForItem() override;

    void EnteredToEmptyRoom() override;

    void EnteredToStartingRoom() override;

    void EnteredToBossRoom() override;
    void BossDefeated() override;
    void HeroDefeatedByBoss() override;


    //items
    void InvalidClassValue() override;


    //strategy
    void NotEnoughGoldToBuyItem() override;
    void MuchTooLowOfferForItem() override;
    void FairPriceOfferForItem() override;
    void AlmostFairPriceOfferForItem(int offer) override;
    void ShowFinalPrice(int price) override;


    //character (character1, character2);
    void ShowCourseOfRound(string ch1, string ch2, int damage) override;
    void ShowCurrentHealthAfterRound(string ch, int currH) override;
    void DodgedHit(string ch1, string ch2) override;
    void BlockedHit(string ch1, string ch2) override;

    void ShowPossibleClassesToChoose() override;
    void IncorrectNumber(int min, int max) override;
    void ShowChosenClass(int ch) override;

    void WriteHeroName() override;

    void ShowEquipment(shared_ptr<Item> weapon, shared_ptr<Item> armor, shared_ptr<Item> headgear, shared_ptr<Item> talisman, shared_ptr<Item> shield) override;
    void ShowStatistics(string name, string prof, string mainStatName, string skill, int level, int mainStat, int maxHealth, int currHealth, int minAttack,
                        int maxAttack, double crit, int def, int money, double block) override;

    void ShowOneItem(shared_ptr<Item> item) override;

    void CompletedEqChanging() override;
    void BreakLine() override;
    void EndGameMessage() override;
};
#endif
