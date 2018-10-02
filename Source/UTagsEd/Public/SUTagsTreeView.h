#pragma once

#include "Runtime/Slate/Public/Widgets/Views/STreeView.h"
#include "UTreeViewItem.h" 


class SUTagsTreeView : public STreeView<TSharedRef<FTreeViewItemData>>
{
public:
	~SUTagsTreeView()
	{
	//	delete(ItemsSource); //TODO Struct delete
	}

};