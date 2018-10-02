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

USTRUCT()
struct FTreeViewItemData
{
	GENERATED_USTRUCT_BODY()

		//	~FTreeViewItemData() { delete *ObjectName; } //TODO What should I do here
	int Index;;
	UPROPERTY(Transient)
	int Parent;

	UPROPERTY(Transient)
	FString ObjectName;
};