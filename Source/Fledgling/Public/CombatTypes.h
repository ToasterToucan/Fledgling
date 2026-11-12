#pragma once

#include "CoreMinimal.h"
#include "CombatTypes.generated.h"

class FLEDGLING_API CombatTypes
{
public:
	CombatTypes();
	~CombatTypes();
};

USTRUCT(BlueprintType)
struct FCard {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName name;
};