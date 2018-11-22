// Copyright 2018, Institute for Artificial Intelligence - University of Bremen
// Author: Chifor Tudor

#pragma once

#include "SlateBasics.h"
#include "SSearchBox.h"
#include "Engine.h"
#include "Tags.h"
#include "SUTagsTreeView.h"
#include "UTreeViewItem.h"
#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "UObject/ObjectMacros.h"

class SUTagsTreeViewWidget : public SCompoundWidget
{
public: 
	SLATE_BEGIN_ARGS(SUTagsTreeViewWidget) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& Args);
	/**Generate Tags from Actor Components when the generate button is pressed*/
	FReply GenerateButtonPressed();
	/** Generate each row for the name list */
	TSharedRef<ITableRow> OnGenerateRowForTree(FTreeViewItemDataPtrType  Item, const TSharedRef<STableViewBase>& OwnerTable);
	/** Generate Children*/
	void OnGetChildrenForTree(FTreeViewItemDataPtrType  Item, TArray<FTreeViewItemDataPtrType>& OutChildren);
	/**Method for stringifying all the Tags such that they are appropriate for the Text Box*/
	static FString StringifyAllKeyValueTags(TMap<FString, FString> KeyValueTags);

private:
	TSharedPtr<SUTagsTreeView> UTagsTree;
	/**Tree View List Item Height Todo? : UProperty*/
	float TreeItemHeight;
	/**List with actual Items inside the displayed Tree*/
	TArray<FTreeViewItemDataPtrType> SharedTreeItems;
	/** The list of items to generate widgets for */
	TArray<FTreeViewItemData> Items;
	//The Map containing a reference to each Actor/Components and its tags
	TMap<TWeakObjectPtr<UObject>, TArray<FTagData>> ActorsAndComponentsTagsMap;
};

