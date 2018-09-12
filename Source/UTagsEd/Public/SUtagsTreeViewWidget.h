#pragma once

#include "SlateBasics.h"
#include "SSearchBox.h"
#include "Engine.h"
#include "Tags.h"
#include "SUTagsTreeView.h"
//use SNullWidget when you need a placeholder
class SUTagsTreeViewWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SUTagsTreeViewWidget) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& Args);
	/**Todo delete Temporary button to manually add items to the tree*/
	FReply ButtonPressed();
	/** Generate each row for the name list */
	TSharedRef<ITableRow> OnGenerateRowForTree(TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& OwnerTable);
	/** Generate Children*/
	void OnGetChildrenForTree(class TSharedPtr<FString> Item, TArray< TSharedRef<FString>>& OutChildren);

private:
	TSharedPtr<SUTagsTreeView> UTagsTree;
	/**Tree View List Item Height Todo? : UProperty*/
	float TreeItemHeight;

	TArray<TSharedPtr<FString>> ItemsFirstColumn;

};
//STreeView< TSharedPtr<struct FUTagsItem>> Todo make with your own struct
