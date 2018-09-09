#pragma once

#include "SlateBasics.h"
#include "SSearchBox.h"
#include "Engine.h"
#include "Tags.h"
//use SNullWidget when you need a placeholder
class SUTagsTreeViewWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SUTagsTreeViewWidget) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& Args);

	/*--Object Name and Tag Lists and their generation */ 
	SListView<TSharedPtr<FString>> GenerateObjectNameList();
	/** Generate each row for the name list */
	TSharedRef<ITableRow> OnGenerateRowForNameList(TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& OwnerTable);
private:


};

