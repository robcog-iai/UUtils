#pragma once

#include "UTreeViewItem.h"

UTreeViewItem::UTreeViewItem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UTreeViewItem::UTreeViewItem(const FString& InObjectName): ObjectName(InObjectName)
{
}

void FTreeViewItemData::AddChild(FTreeViewItemDataPtrType InChildNodePtr)
{
	// Ensure the node is not already parented elsewhere
	
	//Add to the list of children the In Node
	Children.Add(InChildNodePtr);
	// Add the given node as a child and link its parent
	InChildNodePtr->ParentItemPtr = MakeShareable(this);
}
