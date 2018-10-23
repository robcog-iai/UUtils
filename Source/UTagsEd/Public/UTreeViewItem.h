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

	//	TODO Delte after final implementation. Debugging purposes to understand easily
	int Index;;
	UPROPERTY(Transient)
	int Parent;

	UPROPERTY(Transient)
	FString ObjectName;

	FTreeViewItemDataPtrType ParentItemPtr;

	TArray<FTreeViewItemDataPtrType> Children;
	/**
	* Adds the given data as a child data.
	*/
	void AddChild(FTreeViewItemDataPtrType InChildNodePtr);

	const TArray<FTreeViewItemDataPtrType>& GetChildren() const { return Children; }
};