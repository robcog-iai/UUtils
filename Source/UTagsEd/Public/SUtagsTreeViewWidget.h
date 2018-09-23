#pragma once

#include "SlateBasics.h"
#include "SSearchBox.h"
#include "Engine.h"
#include "Tags.h"
#include "SUTagsTreeView.h"
#include "UTreeViewItem.h"
//use SNullWidget when you need a placeholder

#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "UObject/ObjectMacros.h"




class SUTagsTreeViewWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SUTagsTreeViewWidget) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& Args);
	/**Todo delete Temporary button to manually add items to the tree*/
	FReply ButtonPressed();
	/** Generate each row for the name list */
	TSharedRef<class ITableRow> OnGenerateRowForTree(class UTreeViewItem* Item, const TSharedRef<STableViewBase>& OwnerTable);
	/** Generate Children*/
	void OnGetChildrenForTree(class UTreeViewItem* Item, TArray< UTreeViewItem*>& OutChildren);

private:
	TSharedPtr<SUTagsTreeView> UTagsTree;
	/**Tree View List Item Height Todo? : UProperty*/
	float TreeItemHeight;

	TArray<UTreeViewItem*> ItemsFirstColumn;

};
//STreeView< TSharedPtr<struct FUTagsItem>> Todo make with your own struct
