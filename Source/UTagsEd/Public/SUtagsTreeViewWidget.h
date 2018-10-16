#pragma once

#include "SlateBasics.h"
#include "SSearchBox.h"
//#include "SProjectViewItem.h"
#include "Engine.h"
#include "Tags.h"
#include "SUTagsTreeView.h"
#include "UTreeViewItem.h"
//use SNullWidget when you need a placeholder
#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "UObject/ObjectMacros.h"
//#include "SUTagsTreeViewWidget.generated.h"




class SUTagsTreeViewWidget : public SCompoundWidget
{
public: 
	SLATE_BEGIN_ARGS(SUTagsTreeViewWidget) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& Args);
	/**Todo delete Temporary button to manually add items to the tree*/
	FReply ButtonPressed();
	FReply ChildButtonPressed();
	/** Generate each row for the name list */
	TSharedRef<ITableRow> OnGenerateRowForTree(FTreeViewItemDataPtrType  Item, const TSharedRef<STableViewBase>& OwnerTable);
	/** Generate Children*/
	void OnGetChildrenForTree(FTreeViewItemDataPtrType  Item, TArray<FTreeViewItemDataPtrType>& OutChildren);

private:
	TSharedPtr<SUTagsTreeView> UTagsTree;
	/**Tree View List Item Height Todo? : UProperty*/
	float TreeItemHeight;
	/**List with actual Items inside the displayed Tree*/
	TArray<FTreeViewItemDataPtrType> SharedTreeItems;
	/** The list of items to generate widgets for */
	TArray<FTreeViewItemData> Items;

	int ItemCounterIndex;

};
//STreeView< TSharedPtr<struct FUTagsItem>> Todo make with your own struct

