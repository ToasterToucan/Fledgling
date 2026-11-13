#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "GameplayTags.h"
#include "PlayerParent.generated.h"

UCLASS()
class FLEDGLING_API APlayerParent : public APaperZDCharacter
{
	GENERATED_BODY()
	
	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer player_tags_cpp;
};
