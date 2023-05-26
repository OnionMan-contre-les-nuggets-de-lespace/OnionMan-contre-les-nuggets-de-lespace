// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/ISynchronizedObjectBase.h"
#include "Components/ActorComponent.h"
#include "Network/ISynchronizedPropertyBase.h"
#include "SynchronizedActorComponent.generated.h"


UCLASS(Abstract/*, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) */)
class ONIONMAN_UNREAL_API USynchronizedActorComponent : public UActorComponent, public ISynchronizedObjectBase
{
    GENERATED_BODY()
protected:
    UPROPERTY(EditAnywhere, DisplayName = "Object ID", Category = "Network")
    uint32 m_objectID;

private:
    TMap<uint16, TObjectPtr<ISynchronizedPropertyBase>> m_synchronizedProperties{};
    int m_encodedPropertiesSize;
    TArray<TObjectPtr<ISynchronizedPropertyBase>> m_propertiesArray{};

public:	
    // Sets default values for this component's properties
    USynchronizedActorComponent();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;
    virtual void BeginDestroy() override;

public:	
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    virtual const uint32 ObjectID() const override;

    virtual const TMap<uint16, TObjectPtr<ISynchronizedPropertyBase>>& Properties() const override;

    virtual ObjectNeedSyncResult NeedSync() override;

    virtual void PutEncodedObjectToBuffer(TArray<uint8>& buffer, int& offset, bool forSync = true) override;

    virtual void DecodeObject(TArray<uint8>& encodedProperties, int& offset, int size) override;

    virtual void LoadProperties() override;

    void AddSynchronizedProperty(TObjectPtr<ISynchronizedPropertyBase> synchronizedProperty); 
    void RemoveSynchronizedProperty(TObjectPtr<ISynchronizedPropertyBase> synchronizedProperty);
    void GetPropertiesToSync(TArray<TObjectPtr<ISynchronizedPropertyBase>>& result);
};
