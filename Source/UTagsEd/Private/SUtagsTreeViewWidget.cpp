#include "SUTagsTreeViewWidget.h"



#define LOCTEXT_NAMESPACE "SUTagsTreeWidget"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SUTagsTreeViewWidget::Construct(const FArguments & Args)
{
	// Data Aqusition
	ActorsAndTagsMap = FTags::GetWorldTagsData(GEditor->GetEditorWorldContext().World());
	//Configuration
	const FString ButtonFString("Add New Item To Tree");
	const FText ButtonFText = FText::FromString(ButtonFString);

	const FString GenerateButtonFString("Generate Values");
	const FText GenerateButtonFText = FText::FromString(GenerateButtonFString);

	TreeItemHeight = 16.0f;
	ItemCounterIndex = 0;

	// UI Implementation
	ChildSlot[
		SNew(SBox)
			//	.MaxDesiredHeight(ChildSlot) FOR SCROLLBAR WE MUST GET THE SIZE OF THE CHILDREN AND SET IT TO THE MAXIMUM OF THE WINDOW
			[
				SNew(SBorder)[
					SNew(SScrollBox)//TODO Incercam de data asta cu Overlay vedem dupa daca ii mai bun scrollbox

						+ SScrollBox::Slot()[//TODO Aici putem pune border color
							SNew(SSearchBox)
								.HintText(LOCTEXT("SearchBoxHint", "Search after object name"))
								//.OnTextChanged(this, &SUtagsListWidget::HandleFilterStringTextChanged) //ToDo fImplement this
						]
						+ SScrollBox::Slot()
								[
									SNew(SButton)
									.Text(ButtonFText)
								.OnClicked(this, &SUTagsTreeViewWidget::ButtonPressed)
								]
						+ SScrollBox::Slot()
									[
										SNew(SButton)
										.Text(ButtonFText)
									.OnClicked(this, &SUTagsTreeViewWidget::ChildButtonPressed)
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
								//.ClearSelectionOnClick(false)
							]


				]
			]
		];


}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FReply SUTagsTreeViewWidget::ButtonPressed()
{
	
	FString TheFString =  FString(TEXT("Parent.This is my test FString."));
	FTreeViewItemData* NewItem = new FTreeViewItemData;
	NewItem->Index = ItemCounterIndex;
	NewItem->Parent = 0; 
	if (ItemCounterIndex) {
		NewItem->Parent = ItemCounterIndex - 1;
	}
	NewItem->ObjectName = TheFString;
	SharedTreeItems.Add(MakeShareable(NewItem));
	UTagsTree->RequestTreeRefresh();
	ItemCounterIndex++;
	return FReply::Handled();
}

FReply SUTagsTreeViewWidget::ChildButtonPressed()
{
	FString TheFString = FString(TEXT("Child Element"));
	FTreeViewItemData* NewItem = new FTreeViewItemData;
	NewItem->Index = ItemCounterIndex;
	NewItem->Parent = 1;
	NewItem->ObjectName = TheFString;
	FTreeViewItemDataPtrType NewItemPtrType = MakeShareable(NewItem);
	//Find in Shared items the 0 parent
	FTreeViewItemDataPtrType* DataPtr = SharedTreeItems.GetData();
	if(DataPtr->IsValid()){
	DataPtr->Get()->AddChild(NewItemPtrType);
	}
	//DataPtr.Get()->AddChild(NewItemPtrType);
	SharedTreeItems.Add(MakeShareable(NewItem));
	UTagsTree->RequestTreeRefresh();
	ItemCounterIndex++;
	return FReply::Handled();
}

FReply SUTagsTreeViewWidget::GenerateButtonPressed()
{
	// Data Aqusition
	//TMap<TWeakObjectPtr<UObject>, TArray<FTagData>> 
 	ActorsAndTagsMap = FTags::GetWorldTagsData(GEditor->GetEditorWorldContext().World());
 		for (auto& Elem : ActorsAndTagsMap) {
			//Object Title Part
			FTreeViewItemData* NewItem = new FTreeViewItemData;
			FString ObjectName = Elem.Key.Get()->GetName();
			//Convert to our Data Type
			NewItem = new FTreeViewItemData;
			NewItem->Index = ItemCounterIndex;
			NewItem->Parent = 1;
			NewItem->ObjectName = ObjectName;
			ItemCounterIndex++;

			FTreeViewItemDataPtrType NewItemPtrType = MakeShareable(NewItem);
			SharedTreeItems.Add(NewItemPtrType);

			//Object Tag Data
			FString TagTypeFString = Elem.Value.GetData()->TagType;
			FTreeViewItemData* NewItemTag = new FTreeViewItemData;
			NewItemTag->Index = ItemCounterIndex;
			NewItemTag->Parent = ItemCounterIndex;
			NewItemTag->ObjectName = TagTypeFString;
			FTreeViewItemDataPtrType NewItemPtrTagType = MakeShareable(NewItemTag);

			FTreeViewItemDataPtrType* DataPtr = SharedTreeItems.FindByKey(NewItemPtrType);
			if (DataPtr->IsValid()) {
				DataPtr->Get()->AddChild(NewItemPtrTagType);
			}
			ItemCounterIndex++;

			//	TODO Iterate over map 
			// add all key values 
			// GenerateRowForTree cumva mai special sa faca diferit pentru element (think ahead of crud la datatype)
	}
		UTagsTree->RequestTreeRefresh();
		
		return FReply::Handled();

}
TSharedRef<ITableRow> SUTagsTreeViewWidget::OnGenerateRowForTree(FTreeViewItemDataPtrType Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	//The function behaves differently for Tags than for Object Names
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

#undef LOCTEXT_NAMESPACE