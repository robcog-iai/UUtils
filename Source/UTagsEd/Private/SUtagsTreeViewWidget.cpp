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
	NewItem->ObjectName = TheFString;
	SharedTreeItems.Add(MakeShareable(NewItem));
	UTagsTree->RequestTreeRefresh();
	return FReply::Handled();
}

FReply SUTagsTreeViewWidget::ChildButtonPressed()
{
	FString TheFString = FString(TEXT("Child Element"));
	FTreeViewItemData* NewItem = new FTreeViewItemData;
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
	return FReply::Handled();
}

FReply SUTagsTreeViewWidget::GenerateButtonPressed()
{
	// Data Aqusition
 	ActorsAndTagsMap = FTags::GetWorldTagsData(GEditor->GetEditorWorldContext().World());
 		for (auto& Elem : ActorsAndTagsMap) {
			//Object Title Part TODO Check if Unique
			FTreeViewItemData* NewItem = new FTreeViewItemData;
			FString ObjectName = Elem.Key.Get()->GetName();
			//Convert to our Data Type
			NewItem = new FTreeViewItemData;
			NewItem->ObjectName = ObjectName;
			ItemCounterIndex++;
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
			.Text(FText::FromString(GetAllKeyValueTags(Item->KeyValueTags)))
		]
		];
		
	} // return SNew(SSpacer); Pentru Empty
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

 FString SUTagsTreeViewWidget::GetAllKeyValueTags(TMap<FString, FString> KeyValueTags)
{
	 FString TagsFstring = "";
	 for (TPair< FString, FString>& Tag: KeyValueTags)
	 {
		 TagsFstring = TagsFstring + Tag.Key + "," + Tag.Value +  ";";
	 }

	 return TagsFstring;
}
#undef LOCTEXT_NAMESPACE

 /*
 Find Function :
 // Get all objects with TF tags
 auto ObjToTagData = FTagStatics::GetObjectsToKeyValuePairs(GetWorld(), TEXT("TF"));
 */