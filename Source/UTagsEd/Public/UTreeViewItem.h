#pragma once
#include "UnrealEd.h"
#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "UTreeViewItem.generated.h"

UCLASS()
class UTreeViewItem : public UObject
{
	GENERATED_BODY ()

public:
	//properties
	UPROPERTY(Transient)
		FString ObjectName;

public:
	//methods
	UTreeViewItem(const FObjectInitializer& ObjectInitializer);

	UTreeViewItem(const FString & InObjectName);

	/** PostInitProperties override. */
//	virtual void PostInitProperties() override;


};

// TreeView Data pointer type
typedef TSharedPtr<struct FTreeViewItemData> FTreeViewItemDataPtrType;

USTRUCT()
struct FTreeViewItemData
{
	GENERATED_USTRUCT_BODY()

	//	~FTreeViewItemData() { delete *ObjectName; } //TODO What should If I should
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