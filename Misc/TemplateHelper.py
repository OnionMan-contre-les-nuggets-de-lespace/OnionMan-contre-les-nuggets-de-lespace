import os

class Type:
    def __init__(self, typeName : str, additionalIncludes : list[str]) -> None:
        self.Typename = typeName
        self.AdditionalIncludes = additionalIncludes



headerIncludes = """// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedProperty.h"

"""



header = """
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

    UFUNCTION(BlueprintCallable)
    inline const TYPENAME& GetValue() const
    {
        return GetValueGeneric<TYPENAME>(m_value);
    }

    UFUNCTION(BlueprintCallable)
    inline void GetValue(TYPENAME& newValue)
    {
        GetValueGeneric<TYPENAME>(newValue, m_value);
    }

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
    Type("FString"    ,[]),
    Type("bool"       ,[]),
    Type("TCHAR"      ,[]),
    Type("double"     ,[]),
    Type("float"      ,[]),
    Type("int"        ,[]),
    Type("long"       ,[]),
    Type("short"      ,[]),
    Type("uint32"     ,[]),
    Type("uint64"     ,[]),
    Type("uint16"     ,[]),
    Type("FVector3f"  ,["""#include "Runtime/Core/Public/Math/Vector.h" """]),
    Type("FIntVector" ,["""#include "Runtime/Core/Public/Math/IntVector.h" """]),
    Type("FVector2f"  ,["""#include "Runtime/Core/Public/Math/Vector.h" """]),
    Type("FIntVector2",["""#include "Runtime/Core/Public/Math/IntVector.h" """]),
    Type("FQuat4f"    ,["""#include "Runtime/Core/Public/Math/Quat.h" """])
    ]


for t in types:
    realFileName = fileName.replace(typeName, t.Typename)

    if not os.path.exists(f"{headerPath}\{t.Typename}"):
        os.makedirs(f"{headerPath}\{t.Typename}")

    includes = headerIncludes
    for include in t.AdditionalIncludes:
        includes += f"{include}\n" 
    print(includes + header.replace(typeName, t.Typename), file = open(f"{headerPath}\{t.Typename}\{realFileName}.h",'w',encoding='utf-8'))

    if not os.path.exists(f"{sourcePath}\{t.Typename}"):
        os.makedirs(f"{sourcePath}\{t.Typename}")
    print(source.replace(typeName, t.Typename), file = open(f"{sourcePath}\{t.Typename}\{realFileName}.cpp",'w',encoding='utf-8'))