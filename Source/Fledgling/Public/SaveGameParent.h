#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "InventoryTypes.h"
#include "SaveGameParent.generated.h"

UCLASS(BlueprintType)
class FLEDGLING_API USaveGameParent : public USaveGame
{
	GENERATED_BODY()

public:
	// Unlocked Inventory Items
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FInvItem> unlocked_ambers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FInvItem> unlocked_companions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FInvItem> unlocked_weapons;

	// Equipped Inventory Items
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FInvItem> equipped_ambers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FInvItem> equipped_companions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FInvItem> equipped_weapon;

	// Amber Card Choices
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FAmberCardSelection> amber_card_choices;

	/*
	UFUNCTION(BlueprintCallable)
	void SaveAllData(TArray<UObject*> saveable_objects, bool at_checkpoint);

	UFUNCTION(BlueprintCallable)
	void LoadDataForRequester(UObject* requester);
	*/
};
