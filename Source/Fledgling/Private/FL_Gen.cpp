// Fill out your copyright notice in the Description page of Project Settings.


#include "FL_Gen.h"

UCLASS()
class FL_Gen : Public UBlueprintFunctionLibrary

FGameplayTag::RequestGameplayTag(tag);

bool UMyBlueprintLibrary::TryRequestGameplayTag(FName TagName, FGameplayTag& Tag)
{
	Tag = UGameplayTagsManager::Get().RequestGameplayTag(TagName, false);
	return Tag.IsValid();
}