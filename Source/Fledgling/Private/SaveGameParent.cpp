// Fill out your copyright notice in the Description page of Project Settings.

#include "SaveGameParent.h"
#include "ISaveable.h"

void USaveGameParent::SaveAllData(TArray<UObject*> saveable_objects, bool at_checkpoint) {
	for (TObjectPtr<UObject> current : saveable_objects) {
		ISaveable::Execute_SaveData(current, this, at_checkpoint);
	}
}

void USaveGameParent::LoadDataForRequester(UObject* requester) {
	ISaveable::Execute_LoadData(requester, this);
}