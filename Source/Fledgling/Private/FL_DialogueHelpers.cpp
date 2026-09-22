// Fill out your copyright notice in the Description page of Project Settings.


#include "FL_DialogueHelpers.h"
#include "GameplayTagsManager.h"

bool UFL_DialogueHelpers::TryRequestGameplayTag(FName tag_name, FGameplayTag& tag) {
	tag = UGameplayTagsManager::Get().RequestGameplayTag(tag_name, false);
	return tag.IsValid();
}