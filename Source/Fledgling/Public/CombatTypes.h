#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CombatTypes.generated.h"

class FLEDGLING_API CombatTypes
{
public:
	CombatTypes();
	~CombatTypes();
};

USTRUCT(BlueprintType)
struct FCard : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName name;
};