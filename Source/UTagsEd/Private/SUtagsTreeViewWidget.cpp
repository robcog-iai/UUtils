#include "SUtagsTreeViewWidget.h"



#define LOCTEXT_NAMESPACE "SUtagsListWidget"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SUtagsTreeViewWidget::Construct(const FArguments & Args)
{
	// Data Aquisition


	// UI Implementation
	//ChildSlot[
	//	SNew(SBox)
	//		//	.MaxDesiredHeight(ChildSlot) FOR SCROLLBAR WE MUST GET THE SIZE OF THE CHILDREN AND SET IT TO THE MAXIMUM OF THE WINDOW
	//		[
	//			SNew(SBorder)[
	//				SNew(SOverlay)//TODO Incercam de data asta cu Overlay vedem dupa daca ii mai bun scrollbox

	//					+ SOverlay::Slot()[//TODO Aici putem pune border color
	//						SNew(SSearchBox)
	//							.HintText(LOCTEXT("SearchBoxHint", "Search after object name"))
	//							//.OnTextChanged(this, &SUtagsListWidget::HandleFilterStringTextChanged)

	//					]


	//			]
	//		];


}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

//--Object Name and Tag Lists and their generation
//SListView<TSharedPtr<FString>> SUtagsTreeViewWidget::GenerateObjectNameList()
//{
//	return  TABEL NOU;
//}
/**
 * 
 */
TSharedRef<ITableRow> SUtagsTreeViewWidget::OnGenerateRowForNameList(TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	//Create the row
	return
		SNew(STableRow< TSharedPtr<FString> >, OwnerTable)
		.Padding(2.0f)

		[
			SNew(STextBlock).Text(FText::FromString(*Item.Get()))
		];
}

#undef LOCTEXT_NAMESPACE

