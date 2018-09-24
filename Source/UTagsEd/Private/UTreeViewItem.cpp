#pragma once

#include "UTreeViewItem.h"

UTreeViewItem::UTreeViewItem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UTreeViewItem::UTreeViewItem(const FString& InObjectName): ObjectName(InObjectName)
{
}
