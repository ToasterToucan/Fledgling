#include "InventorySubsystem.h"
#include "PlayerParent.h"
#include "Kismet/GameplayStatics.h"

// +++++++++++++++++++++++ VARIABLES +++++++++++++++++++++++
// The card choices the player has made for each amber.
TArray<FAmberCardSelection> amber_card_choices;

// The player's currently equipped items.
TArray<FInvItem> equipped_ambers;
TArray<FInvItem> equipped_companions;
TArray<FInvItem> equipped_weapon;		// Stored in an array for consistency's sake. Also allows for future double weapon allowances!

// The player's unlocked items. EXCLUDES equipped items.
TArray<FInvItem> unlocked_ambers;
TArray<FInvItem> unlocked_companions;
TArray<FInvItem> unlocked_weapons;


// Data tables! For looking up item info.
UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(RowType="FAmber"))
TObjectPtr<UDataTable> DT_ambers;

UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (RowType = "FCompanion"))
TObjectPtr<UDataTable> DT_companions;

UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (RowType = "FWeapon"))
TObjectPtr<UDataTable> DT_weapons;


// +++++++++++++++++++++++ SAVE/LOAD +++++++++++++++++++++++
/** Save all inventory data to file and instance. */
void UInventorySubsystem::SaveInventory() {
	// body
}

/** Load all inventory data from file. **The inventory will never load from the instance. */
void UInventorySubsystem::LoadInventory() {
	// body
}


// +++++++++++++++++++++++ AMBER CARD CHOICE +++++++++++++++++++++++

int UInventorySubsystem::NumChosenOfCardFromAmber(FName amber_name, int card_index) {
	// Fail out if this is an invalid index.
	if (card_index < 0 || card_index > 2) { return -1; }

	// Get this amber's index in the choice array. Fail out if it was not found in the array.
	int choice_array_index = FindAmberInChoiceArray(amber_name);
	if (choice_array_index < 0) { return -1; }

	// Shift the card selection byte over so the wanted bits are rightmost, then extract just the 3 rightmost bits using a mask.
	return ((amber_card_choices[choice_array_index].value) >> card_index * 3) & 7;
}

uint8 UInventorySubsystem::EncodeAmberCardChoices(int val0, int val1, int val2) {
	return val0 + (val1 << 3) + (val2 << 6);
}

int UInventorySubsystem::FindAmberInChoiceArray(FName amber_name) {
	for (int i = 0; i < amber_card_choices.Num(); i++) {
		if (amber_card_choices[i].row_name == amber_name) { return i; }
	}

	// Fail out - amber wasn't found in the choice array.
	return -1;
}


// +++++++++++++++++++++++ GET INV INFO AS INV ITEM +++++++++++++++++++++++

void UInventorySubsystem::GetAllEquipped(TArray<FInvItem>& Ambers, TArray<FInvItem>& Companions, TArray<FInvItem>& Weapon) {
	Ambers = equipped_ambers;
	Companions = equipped_companions;
	Weapon = equipped_weapon;
}

void UInventorySubsystem::GetAllUnlocked(TArray<FInvItem>& Ambers, TArray<FInvItem>& Companions, TArray<FInvItem>& Weapons) {
	Ambers = unlocked_ambers;
	Companions = unlocked_companions;
	Weapons = unlocked_weapons;
}

// +++++++++++++++++++++++ GET INV INFO AS CARDS +++++++++++++++++++++++

TArray<FCard> UInventorySubsystem::GetCardArrayOfAmber(FInvItem amber) {
	// Fail out if this is the empty amber or not an amber.
	if (amber.name == "Empty" || amber.type != E_itemType::AMBER) { return {}; }

	// Try to find the amber in the ambers data table
	FAmber* amber_row = DT_ambers->FindRow<FAmber>(amber.name, FString("GetCardArrayOfAmber in InventorySubsystem.cpp - Get amber"));

	// Fail out if the row was not found.
	if (!amber_row) { return {}; }

	TArray<FCard> result;

	// For each card option....
	for (FAmberCardSelection card_choice : amber_row->card_options) {
		// Grab the current card from the card data table specified by the amber.
		FCard* card = amber_row->card_data_table->FindRow<FCard>(card_choice.row_name, FString("GetCardArrayOfAmber in InventorySubsystem.cpp - Get card"));
		
		// For as many times as the player has chosen of this card, add the card to the result array.
		for (int i = 0; i < card_choice.value; i++) {
			result.Add(*card);
		}
	}

	return result;
}

TArray<FCard> UInventorySubsystem::GetCardArrayOfWeapon(FInvItem weapon) {
	// Fail out if this is the empty weapon or not an weapon.
	if (weapon.name == "Empty" || weapon.type != E_itemType::WEAPON) { return {}; }

	// Try to find the weapon in the weapons data table
	FWeapon* weapon_row = DT_weapons->FindRow<FWeapon>(weapon.name, FString("GetCardArrayOfWeapon in InventorySubsystem.cpp - Get weapon"));

	// Fail out if the row was not found.
	if (!weapon_row) { return {}; }

	// Get all cards this weapon gives, as an array of FCard pointers.
	TArray<FCard*> cards_ptr;
	weapon_row->card_data_table->GetAllRows<FCard>(FString("GetCardArrayOfWeapon in InventorySubsystem.cpp - Get card array"), cards_ptr);

	// Copy data from the pointer array into an object array for return.
	TArray<FCard> cards_obj;
	cards_obj.SetNum(cards_ptr.Num());
	for (int i = 0; i < cards_ptr.Num(); i++) {
		cards_obj[i] = *cards_ptr[i];
	}

	return cards_obj;
}

TArray<FCard> UInventorySubsystem::GetFullLoadout() {
	TArray<FCard> result;

	// For each equipped weapon, get its card array and append that to result.
	for (FInvItem weapon : equipped_weapon) {
		result.Append(GetCardArrayOfWeapon(weapon));
	}

	// For each equipped amber, get its card array and append that to result.
	for (FInvItem amber : equipped_ambers) {
		result.Append(GetCardArrayOfAmber(amber));
	}

	return result;
}

// +++++++++++++++++++++++ ITEM MANIP +++++++++++++++++++++++

void UInventorySubsystem::UnlockItem(const FInvItem item) {
	// Get the player and this item's data, and add the item's unlock tag to the player.
	APlayerParent* player = Cast<APlayerParent>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	FGenericItem* data = GetItemData(item);
	player->player_tags_cpp.AddTag(data->unlock_tag);

	// Add this item to the correct unlocks array.
	GetArray(item.type, false)->Add(item);

	// If this is an amber, add a new entry with its name to amber_card_choices.
	if (item.type == E_itemType::AMBER) {
		amber_card_choices.Add(FAmberCardSelection(item.name));
	}
}

bool UInventorySubsystem::EquipItem_Item(FInvItem item, bool force_equip, int equip_slot) {
	// Find the item to equip within the unlocks array. Fail out if it's not there.
	int item_loc = GetArray(item.type, false)->Find(item);
	if (item_loc == INDEX_NONE) { return false; }

	// Call to equip the item, return what that returns.
	return EquipItem_Index(item.type, item_loc, force_equip, equip_slot);
}

bool UInventorySubsystem::EquipItem_Index(E_itemType type, int index, bool force_equip, int equip_slot) {
	// Slot in the equips array we're going to equip into
	int equip_to = equip_slot;

	// Equip array of this item type, for easy use
	TArray<FInvItem> equip_array = *GetArray(type, true);

	// If not force equipping, try to find an empty slot to equip into.
	if (!force_equip) {
		int empty_slot = FindFirstEmptySpace(equip_array);
		if (empty_slot <= -1) { return false; }
		equip_to = empty_slot;
	}

	// Unlocks array of this item type, for easy use
	TArray<FInvItem> unlocks_array = *GetArray(type, false);

	// Swapsie!
	FInvItem temp = equip_array[equip_to];
	equip_array[equip_to] = unlocks_array[index];
	unlocks_array[index] = temp;

	// Update player tags
	APlayerParent* player = Cast<APlayerParent>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	FItemG
	player->player_tags_cpp.AddTag

	return true;
}

void UInventorySubsystem::UnequipItem_Item(FInvItem item) {
	// pass
}

void UInventorySubsystem::UnequipItem_Index(E_itemType type, int index) {
	// pass
}

// +++++++++++++++++++++++ OPEN/CLOSE +++++++++++++++++++++++

void UInventorySubsystem::OpenInventory() {
	// pass
}

void UInventorySubsystem::CloseInventory() {
	// pass
}

// +++++++++++++++++++++++ HELPERS +++++++++++++++++++++++

int UInventorySubsystem::FindFirstEmptySpace(TArray<FInvItem> array) {
	for (FInvItem item : array) {
		return -1;
	}
	return -1;
}

FGenericItem* UInventorySubsystem::GetItemData(FInvItem item) {
	return GetDTOfItemType(item.type)->FindRow<FGenericItem>(item.name, "guh");
}

TObjectPtr<UDataTable> UInventorySubsystem::GetDTOfItemType(E_itemType type) {
	switch (type) {
		case E_itemType::AMBER:
			return DT_ambers;
			break;

		case E_itemType::COMPANION:
			return DT_companions;
			break;

		case E_itemType::WEAPON:
			return DT_weapons;
			break;
	}

	// SHOULD NEVER HAPPEN!
	return nullptr;
}

TArray<FInvItem>* UInventorySubsystem::GetArray(E_itemType type, bool equips) {
	if (equips) {
		switch (type) {
			case E_itemType::AMBER:
				return &equipped_ambers;
				break;

			case E_itemType::COMPANION:
				return &equipped_companions;
				break;

			case E_itemType::WEAPON:
				return &equipped_weapon;
		}
	} else {
		switch (type) {
			case E_itemType::AMBER:
				return &unlocked_ambers;
				break;

			case E_itemType::COMPANION:
				return &unlocked_companions;
				break;

			case E_itemType::WEAPON:
				return &unlocked_weapons;
		}
	}

	// SHOULD NEVER HAPPEN!.
	return nullptr;
}