#pragma once

#include "UTreeViewItem.h"

void FTreeViewItemData::AddChild(FTreeViewItemDataPtrType InChildNodePtr)
{
	//Ensure the node is not already parented elsewhere
	//Todo: This should not be a problem though but you nerver know.
	//Add to the list of children the In Node
	Children.Add(InChildNodePtr);
	// Add the given node as a child and link its parent
	InChildNodePtr->ParentItemPtr = MakeShareable(this);
}
