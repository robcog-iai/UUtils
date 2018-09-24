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
	//methods
	UTreeViewItem(const FObjectInitializer& ObjectInitializer);

	UTreeViewItem(const FString & InObjectName);


public:
	//properties
	UPROPERTY(Transient)
		FString ObjectName;


};