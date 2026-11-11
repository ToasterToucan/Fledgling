#pragma once

#include "CoreMinimal.h"
#include "InventoryTypes.generated.h"

class FLEDGLING_API InventoryTypes
{
public:
	InventoryTypes();
	~InventoryTypes();
};

UENUM(BlueprintType)
enum class E_itemType : uint8 {
	AMBER			UMETA(DisplayName = "AMBER"),
	COMPANION		UMETA(DisplayName = "Companion"),
	WEAPON			UMETA(DisplayName = "WEAPON")
};

USTRUCT(BlueprintType)
struct FInvItem {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_itemType type;
};


USTRUCT(BlueprintType)
struct FAmberCardSelection {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName row_name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 value;
};