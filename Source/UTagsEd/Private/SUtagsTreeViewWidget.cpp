#include "SUTagsTreeViewWidget.h"



#define LOCTEXT_NAMESPACE "SUTagsTreeWidget"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SUTagsTreeViewWidget::Construct(const FArguments & Args)
{
	// Data Aquisition

	//TMap<TWeakObjectPtr<UObject>, TArray<FTagData>> ActorsAndTagsMap;
	//ActorsAndTagsMap = FTags::GetAllTagsFromWorldActors(GEditor->GetEditorWorldContext().World());

	//Configuration
	const FString ButtonFString("Add New Item To Tree");
	const FText ButtonFText = FText::FromString(ButtonFString);

	TreeItemHeight = 16.0f;

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
							+ SScrollBox::Slot()[

								SAssignNew(UTagsTree, SUTagsTreeView)
								.ItemHeight(TreeItemHeight)
								.TreeItemsSource(&ItemsFirstColumn)
								.OnGenerateRow(this, &SUTagsTreeViewWidget::OnGenerateRowForTree)
								.OnGetChildren(this, &SUTagsTreeViewWidget::OnGetChildrenForTree)
								.ClearSelectionOnClick(false)
							]


				]
			]
		];


}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FReply SUTagsTreeViewWidget::ButtonPressed()
{
	//ItemsFirstColumn.Add(MakeShareable(new UTreeViewItem()));
	FString TheFString =  FString(TEXT("This is my test FString."));
	FTreeViewItemData NewItem;
	NewItem.ObjectName = TheFString;
	//UTreeViewItem* NewItem;
	//NewItem = NewObject<UTreeViewItem>;
	//NewItem.ObjectNameXY = TheFString;
	ItemsFirstColumn.Add(MakeShareable(&NewItem));
	UTagsTree->RequestTreeRefresh();
	return FReply::Handled();
}

TSharedRef<ITableRow> SUTagsTreeViewWidget::OnGenerateRowForTree(TSharedPtr<FTreeViewItemData> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
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
		//	.Font(Font)
		]
		];
}

void SUTagsTreeViewWidget::OnGetChildrenForTree(TSharedPtr<FTreeViewItemData>  Item, TArray< TSharedPtr<FTreeViewItemData> >& OutChildren)
{
	//OutChildren = nullptr;
}

#undef LOCTEXT_NAMESPACE

