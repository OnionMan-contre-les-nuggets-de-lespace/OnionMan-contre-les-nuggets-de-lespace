// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ISynchronizedObjectBase.h"
#include "Components/ActorComponent.h"
#include "ISynchronizedPropertyBase.h"
#include "USynchronizedActorComponent.generated.h"


UCLASS(Abstract/*, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) */)
class ONIONMAN_UNREAL_API USynchronizedActorComponent : public UActorComponent, public ISynchronizedObjectBase
{
	GENERATED_BODY()

private:
	TMap<uint16, ISynchronizedPropertyBase*> m_synchronizedProperties;
	uint32 m_objectID;
	int m_encodedPropertiesSize;
	TArray<ISynchronizedPropertyBase*> m_propertiesArray;

public:	
	// Sets default values for this component's properties
	USynchronizedActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    const uint32 ObjectID() const override;

    const TMap<uint16, ISynchronizedPropertyBase*>& Properties() const override;

    ObjectNeedSyncResult NeedSync() override;

    void PutEncodedObjectToBuffer(TArray<uint8>& buffer, int& offset, bool forSync = true) override;

    void DecodeObject(TArray<uint8>& encodedProperties, int& offset, int size) override;

    virtual void LoadProperties() override;

	void AddSynchronizedProperty(ISynchronizedPropertyBase* synchronizedProperty);
	void GetPropertiesToSync(TArray<ISynchronizedPropertyBase*>& result);
};
