// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LogUtils.h"

#include "NetworkBatch.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API UNetworkBatch : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	TArray<uint8> EncodedBatch;

public:
	UNetworkBatch();
	~UNetworkBatch();
};
