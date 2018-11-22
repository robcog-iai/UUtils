// Copyright 2018, Institute for Artificial Intelligence - University of Bremen
// Author: Chifor Tudor

#include "SUTagsTreeViewWidget.h"

#define LOCTEXT_NAMESPACE "SUTagsTreeWidget"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SUTagsTreeViewWidget::Construct(const FArguments & Args)
{
	//Configuration
	const FString ButtonFString("Add New Item To Tree");
	const FText ButtonFText = FText::FromString(ButtonFString);

	const FString GenerateButtonFString("Generate Values");
	const FText GenerateButtonFText = FText::FromString(GenerateButtonFString);

	TreeItemHeight = 16.0f;

	// UI Implementation
	ChildSlot[
		SNew(SBox)
			//	.MaxDesiredHeight(ChildSlot) FOR SCROLLBAR WE MUST GET THE SIZE OF THE CHILDREN AND SET IT TO THE MAXIMUM OF THE WINDOW
			[
				SNew(SBorder)[
					SNew(SScrollBox)
						+ SScrollBox::Slot()[//TODO Could add border color
							SNew(SSearchBox)
								.HintText(LOCTEXT("SearchBoxHint", "Search after object name"))
								//.OnTextChanged(this, &SUtagsListWidget::HandleFilterStringTextChanged) //ToDo fImplement this
						]
						+ SScrollBox::Slot()
							[
								SNew(SButton)
								.Text(GenerateButtonFText)
							.OnClicked(this, &SUTagsTreeViewWidget::GenerateButtonPressed)
							]
							+ SScrollBox::Slot()[

								SAssignNew(UTagsTree, SUTagsTreeView)
								.ItemHeight(TreeItemHeight)
								.TreeItemsSource(&SharedTreeItems)
								.OnGenerateRow(this, &SUTagsTreeViewWidget::OnGenerateRowForTree)
								.OnGetChildren(this, &SUTagsTreeViewWidget::OnGetChildrenForTree)
								.ClearSelectionOnClick(false)
							]
				]
			]
		];
}

FReply SUTagsTreeViewWidget::GenerateButtonPressed()
{
	// Data Aqusition
 	ActorsAndComponentsTagsMap = FTags::GetWorldTagsData(GEditor->GetEditorWorldContext().World());
 		for (auto& Elem : ActorsAndComponentsTagsMap) {
			//Object Title Part TODO Check if Unique
			FTreeViewItemData* NewItem = new FTreeViewItemData;
			FString ObjectName = Elem.Key.Get()->GetName();
			//Convert to our Data Type
			NewItem = new FTreeViewItemData;
			NewItem->ObjectName = ObjectName;
			//Object TagData
			FTreeViewItemDataPtrType NewItemPtrType = MakeShareable(NewItem);
			SharedTreeItems.Add(NewItemPtrType);

			TArray<FTagData> FTagDataArray = Elem.Value;
			for (auto& FTagDataElem : FTagDataArray){ 
				//TagType Add
				FString TagTypeFString = FTagDataElem.TagType;
				FTreeViewItemData* NewItemTag = new FTreeViewItemData;
				NewItemTag->ObjectName = TagTypeFString;
				FTreeViewItemDataPtrType NewItemPtrTagType = MakeShareable(NewItemTag);
				//KeyValue Add
				NewItemTag->KeyValueTags = FTagDataElem.KeyValueMap;
				//Add to current Title Item As Child
				FTreeViewItemDataPtrType* DataPtr = SharedTreeItems.FindByKey(NewItemPtrType);
				if (DataPtr->IsValid()) {
					DataPtr->Get()->AddChild(NewItemPtrTagType);
				}
			}
	}
		UTagsTree->RequestTreeRefresh();
		
		return FReply::Handled();
}
TSharedRef<ITableRow> SUTagsTreeViewWidget::OnGenerateRowForTree(FTreeViewItemDataPtrType Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	//The function behaves differently for Tags than for Object Names
	if (Item->KeyValueTags.Num() == 0)
	{//Title Row
		return
			SNew(STableRow< TSharedPtr<FTreeViewItemData> >, OwnerTable)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
			.FillWidth(1000)
			.Padding(2.0f)
			[
				SNew(STextBlock)
				.Text(FText::FromString(Item->ObjectName))
			]
			];
	}
	else
	{//Data Row
 	return
		SNew(STableRow< TSharedPtr<FTreeViewItemData> >, OwnerTable)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
		.MaxWidth(300)
		.FillWidth(300)
		.Padding(2.0f)
		[
			SNew(STextBlock)
			.Text(FText::FromString(Item->ObjectName))
		]
			+ SHorizontalBox::Slot()
		.FillWidth(1000)
		.Padding(2.0f)
		[
			SNew(SEditableTextBox)
			.Text(FText::FromString(StringifyAllKeyValueTags(Item->KeyValueTags)))
		]
		];		
	}
}

void SUTagsTreeViewWidget::OnGetChildrenForTree(FTreeViewItemDataPtrType  Info, TArray< FTreeViewItemDataPtrType >& OutChildren)
{	
	if (Info.IsValid())
	{
		const TArray<FTreeViewItemDataPtrType>& Children = Info->GetChildren();
		OutChildren.Reserve(Children.Num());
		OutChildren = Children;
	}
	else
	{
		OutChildren.Empty();
	}
}

 FString SUTagsTreeViewWidget::StringifyAllKeyValueTags(TMap<FString, FString> KeyValueTags)
{
	 FString TagsFstring = "";
	 for (TPair< FString, FString>& Tag: KeyValueTags)
	 {
		 TagsFstring = TagsFstring + Tag.Key + "," + Tag.Value +  ";";
	 }

	 return TagsFstring;
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef LOCTEXT_NAMESPACE
