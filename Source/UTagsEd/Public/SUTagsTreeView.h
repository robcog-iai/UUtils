#pragma once

#include "Runtime/Slate/Public/Widgets/Views/STreeView.h"
#include "UTreeViewItem.h" 


class SUTagsTreeView : public STreeView<  UTreeViewItem*>
{
public:
	~SUTagsTreeView()
	{
		delete(ItemsSource);
	}
};