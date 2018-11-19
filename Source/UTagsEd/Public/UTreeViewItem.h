#pragma once
#include "UnrealEd.h"
#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "UTreeViewItem.generated.h"

// TreeView Data pointer type
typedef TSharedPtr<struct FTreeViewItemData> FTreeViewItemDataPtrType;

USTRUCT()
struct FTreeViewItemData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Transient)
	FString ObjectName;

	FTreeViewItemDataPtrType ParentItemPtr;

	TArray<FTreeViewItemDataPtrType> Children;

	TMap<FString, FString> KeyValueTags;
	/**
	* Adds the given data as a child data.
	*/
	void AddChild(FTreeViewItemDataPtrType InChildNodePtr);

	const TArray<FTreeViewItemDataPtrType>& GetChildren() const { return Children; }
};