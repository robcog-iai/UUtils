#pragma once

#include "Runtime/Slate/Public/Widgets/Views/STreeView.h"

class SUTagsTreeView : public STreeView< TSharedPtr< FString>>
{
public:
	~SUTagsTreeView()
	{
		delete(ItemsSource);
	}
};