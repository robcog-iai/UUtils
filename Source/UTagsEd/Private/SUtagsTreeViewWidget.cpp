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
	UTreeViewItem NewItem(TheFString);
	//NewItem.ObjectName = new FString("Test Name Object");

	ItemsFirstColumn.Add(&NewItem);
	return FReply::Handled();
}

TSharedRef<class ITableRow> SUTagsTreeViewWidget::OnGenerateRowForTree(UTreeViewItem* Item, const TSharedRef<STableViewBase>& OwnerTable)
{
//	FString DisplayString = 
	//Create the row
	return
		SNew(STableRow< UTreeViewItem* >, OwnerTable)
		.Padding(2.0f)

		[
			SNew(STextBlock)
			//.TreeItem(Item)
			.Text(FText::FromString(Item->ObjectName))
		
		
		];
}

void SUTagsTreeViewWidget::OnGetChildrenForTree(class UTreeViewItem* Item, TArray< UTreeViewItem*>& OutChildren)
{
	//OutChildren = nullptr;
}

#undef LOCTEXT_NAMESPACE

