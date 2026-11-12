#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "InventoryTypes.generated.h"

class FLEDGLING_API InventoryTypes
{
public:
	/*InventoryTypes();
	~InventoryTypes();*/
};

// ITEM TYPES
UENUM(BlueprintType)
enum class E_itemType : uint8 {
	AMBER			UMETA(DisplayName = "AMBER"),
	COMPANION		UMETA(DisplayName = "Companion"),
	WEAPON			UMETA(DisplayName = "WEAPON")
};

// INVENTORY ITEM
USTRUCT(BlueprintType)
struct FInvItem {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_itemType type;
};

USTRUCT(BlueprintType)
struct FGenericItem : public FTableRowBase {
	GENERATED_BODY()

	// Display info
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> icon;

	// Tags
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag unlock_tag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag equip_tag;
};

// AMBER
struct FAmber : public FGenericItem {
	// GENERATED_BODY()

	// Card selection
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> card_data_table;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FAmberCardSelection> card_options;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int mana_available;
};

// COMPANION
struct FCompanion : public FGenericItem {
	// GENERATED_BODY()

	// Empty for now, but used so changes are easy to make in the future :)
};

// WEAPON
struct FWeapon : public FGenericItem {
	// GENERATED_BODY()

	// Card data table
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> card_data_table;
};

// AMBER CARD SELECTION
USTRUCT(BlueprintType)
struct FAmberCardSelection {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName row_name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 value;
};