// Copyright 2018, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#pragma once

#include "EngineMinimal.h"
#include "Misc/Guid.h"
#include "Misc/Base64.h"
#include "Ids.generated.h"

/**
* Helper functions to generate UUIDs in base64 using FGuid
* and convert them back from base64
*/
USTRUCT(BlueprintType, Category = "UIds")
struct UIDS_API FIds
{
	GENERATED_BODY()

	// Encodes GUID to base64
	static FString GuidToBase64(FGuid InGuid)
	{		
		FBufferArchive GuidBufferArchive;							// FBufferArchive inherits from TArray<uint8>
		GuidBufferArchive << InGuid;
		FString GuidInBase64 = FBase64::Encode(GuidBufferArchive);	// Needs binary as TArray<uint8>
		GuidInBase64.RemoveFromEnd(TEXT("=="));						// Remove last unnecessary two equal characters from end
		return GuidInBase64;
	}

	// Creates a new GUID and encodes it to base64
	static FString NewGuidInBase64()
	{
		FGuid NewGuid = FGuid::NewGuid();
		return GuidToBase64(NewGuid);
	}

	// Creates a GUID from base64
	static FGuid Base64ToGuid(const FString& InGuidInBase64, bool bNewIfInvalid = false)
	{
		TArray<uint8> GuidBinaryArray;
		FBase64::Decode(InGuidInBase64, GuidBinaryArray);
		FMemoryReader Ar = FMemoryReader(GuidBinaryArray, true);
		Ar.Seek(0);
		FGuid LocalGuid;
		Ar << LocalGuid;
		if (bNewIfInvalid)
		{
			if (LocalGuid.IsValid())
			{
				return LocalGuid;
			}
			else
			{
				return FGuid::NewGuid();
			}
		}
		else
		{
			return LocalGuid;
		}
	}
};
