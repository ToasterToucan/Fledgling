// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "FL_DialogueHelpers.generated.h"

/**
 * 
 */
UCLASS()
class FLEDGLING_API UFL_DialogueHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	public:
		UFUNCTION(BlueprintPure, Category = "GameplayTags")
		static bool TryRequestGameplayTag(FName tag_name, FGameplayTag& tag);
	
};
