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
	TArray<FAmber> unlocked_ambers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FCompanion> unlocked_companions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FWeapon> unlocked_weapons;

	// Equipped Inventory Items
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FWeapon> equipped_ambers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FCompanion> equipped_companions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FWeapon> equipped_weapon;

	// Amber Card Choices
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FAmberCardSelection> amber_card_choices;


	UFUNCTION(BlueprintCallable)
	void SaveAllData(TArray<UObject*> saveable_objects, bool at_checkpoint);

	UFUNCTION(BlueprintCallable)
	void LoadDataForRequester(UObject* requester);
};
