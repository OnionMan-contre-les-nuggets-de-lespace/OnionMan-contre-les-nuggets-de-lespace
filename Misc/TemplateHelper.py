import os

header = """// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedProperty.h"

#include "SynchronizedTYPENAME.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API USynchronizedTYPENAME : public USpecializedSynchronizedProperty
{
	GENERATED_BODY()
private:
	TYPENAME m_value;

public:
	USynchronizedTYPENAME();
	USynchronizedTYPENAME(TYPENAME value, uint16 propertyID);

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;
};
"""
source = """#include "Network/SpecializedProperties/TYPENAME/SynchronizedTYPENAME.h"

USynchronizedTYPENAME::USynchronizedTYPENAME()
{
}

USynchronizedTYPENAME::USynchronizedTYPENAME(TYPENAME value, uint16 propertyID) : 
    USpecializedSynchronizedProperty::USpecializedSynchronizedProperty(propertyID)
{
    m_value = value;
}

void USynchronizedTYPENAME::Init()
{
    USpecializedSynchronizedProperty::Init();
    InitGeneric<TYPENAME>();
}

int USynchronizedTYPENAME::GetEncodedPropertySize()
{
    USpecializedSynchronizedProperty::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<TYPENAME>(m_value);
}

void USynchronizedTYPENAME::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedProperty::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<TYPENAME>(m_value, buffer, offset, forSync);
}

void USynchronizedTYPENAME::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedProperty::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<TYPENAME>(m_value, encodedProperty, offset, propertySize);
}
"""


headerPath = r"OnionMan_Unreal\Source\OnionMan_Unreal\Public\Network\SpecializedProperties"
sourcePath = r"OnionMan_Unreal\Source\OnionMan_Unreal\Private\Network\SpecializedProperties"
fileName = "SynchronizedTYPENAME"

typeName = "TYPENAME"

types = [
    "FString", 
    "bool", 
    "TCHAR", 
    "double",
    "float", 
    "int", 
    "long", 
    "short", 
    "uint32", 
    "uint64",
    "uint16",
    # "FVector3f",
    # "FIntVector", 
    # "FVector2f", 
    # "FIntVector2", 
    # "FQuat4f"
    ]


for t in types:
    realFileName = fileName.replace(typeName, t)

    if not os.path.exists(f"{headerPath}\{t}"):
        os.makedirs(f"{headerPath}\{t}")
    print(header.replace(typeName, t), file = open(f"{headerPath}\{t}\{realFileName}.h",'w',encoding='utf-8'))

    if not os.path.exists(f"{sourcePath}\{t}"):
        os.makedirs(f"{sourcePath}\{t}")
    print(source.replace(typeName, t), file = open(f"{sourcePath}\{t}\{realFileName}.cpp",'w',encoding='utf-8'))