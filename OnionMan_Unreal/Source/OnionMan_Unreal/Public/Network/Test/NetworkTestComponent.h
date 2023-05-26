// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/SynchronizedActorComponent.h"
#include "../SpecializedSynchronizedProperty.h"
#include "../SpecializedProperties/FString/SynchronizedFStringList.h"
#include "../SpecializedProperties/FString/SynchronizedFString.h"
#include "../SpecializedProperties/Bool/SynchronizedBool.h"

#include "Network/NetworkManager.h"
#include "Network/EncodingUtility.h"
#include "LogUtils.h"
#include "OnionManGameInstance.h"
#include "Kismet/GameplayStatics.h"

#include "NetworkTestComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class ONIONMAN_UNREAL_API UNetworkTestComponent : public USynchronizedActorComponent
{
    GENERATED_BODY()

private:
    bool m_firstFrame = true;

    TObjectPtr<UNetworkManager> m_networkManager;
    

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Network", meta = (ShowInnerProperties))
        USynchronizedFStringList* SP0 {/* TEXT("WAAAAAAAW"), 25*/
    };
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Network", meta = (ShowInnerProperties))
        USynchronizedFString* SP1 {/* TEXT("WAAAAAAAW"), 25*/
    };
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Network", meta = (ShowInnerProperties))
        USynchronizedBool* SP3 {/* TEXT("WAAAAAAAW"), 25*/
    };
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Network", meta = (ShowInnerProperties))
        USpecializedSynchronizedProperty* SP2 {/* TEXT("WAAAAAAAW"), 25*/
    };

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString EncodedString;
    //USynchronizedProperty<int> SP0{9, 12};
    //USynchronizedProperty<FString> SP1{ "Waw", 32 };
    //USynchronizedFStringProperty SP2{ "Waw", 2 };

    virtual void LoadProperties() override;

    //UFUNCTION(BlueprintCallable)
    /*USynchronizedFStringProperty* GetSP2()
    {
        return &SP2;
    }*/

    virtual void BeginPlay() override;

    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable)
    void EncodeAll();
    
    UFUNCTION(BlueprintCallable)
    void DecodeAll();


};
