import os

class Type:
    def __init__(self, typeName : str, additionalIncludes : list[str], ignoreReflection : bool) -> None:
        self.Typename = typeName
        self.AdditionalIncludes = additionalIncludes
        self.IgnoreReflection = ignoreReflection

reflectionMacroToIgnore = ["UFUNCTION(BlueprintCallable)"]

headerIncludes = """// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedProperty.h"

"""



headerTemplate = """
#include "SynchronizedCLASSNAME.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API USynchronizedCLASSNAME : public USpecializedSynchronizedProperty
{
	GENERATED_BODY()
private:
	TYPENAME m_value;

public:
	USynchronizedCLASSNAME();
	USynchronizedCLASSNAME(TYPENAME value, uint16 propertyID);

    UFUNCTION(BlueprintCallable)
    inline TYPENAME GetValue() const
    {
        return GetValueGeneric<TYPENAME>(m_value);
    }

    UFUNCTION(BlueprintCallable)
    inline void SetValue(TYPENAME& newValue)
    {
        SetValueGeneric<TYPENAME>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;
};
"""
sourceTemplate = """#include "Network/SpecializedProperties/TYPENAME/SynchronizedCLASSNAME.h"

USynchronizedCLASSNAME::USynchronizedCLASSNAME()
{
}

USynchronizedCLASSNAME::USynchronizedCLASSNAME(TYPENAME value, uint16 propertyID) : 
    USpecializedSynchronizedProperty::USpecializedSynchronizedProperty(propertyID)
{
    m_value = value;
}

void USynchronizedCLASSNAME::Init()
{
    USpecializedSynchronizedProperty::Init();
    InitGeneric<TYPENAME>();
}

int USynchronizedCLASSNAME::GetEncodedPropertySize()
{
    USpecializedSynchronizedProperty::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<TYPENAME>(m_value);
}

void USynchronizedCLASSNAME::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedProperty::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<TYPENAME>(m_value, buffer, offset, forSync);
}

void USynchronizedCLASSNAME::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedProperty::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<TYPENAME>(m_value, encodedProperty, offset, propertySize);
}
"""


headerPath = r"OnionMan_Unreal\Source\OnionMan_Unreal\Public\Network\SpecializedProperties"
sourcePath = r"OnionMan_Unreal\Source\OnionMan_Unreal\Private\Network\SpecializedProperties"
fileName = "SynchronizedTYPENAME"

typeName = "TYPENAME"
className = "CLASSNAME"

types = [
    Type(
        "FString",
        [],
        False),

    Type(
        "bool",
        [],
        False),

    # Type(
    #     "TCHAR",
    #     ["""#include "HAL/Platform.h" """],
    #     False),

    Type(
        "double",
        [],
        False),

    Type(
        "float",
        [],
        False),

    Type(
        "int",
        [],
        False),

    Type(
        "int64",
        [],
        False),

    Type(
        "int16",
        [],
        True),

    Type(
        "uint32",
        [],
        True),

    Type(
        "uint64",
        [],
        True),

    Type(
        "uint16",
        [],
        True),

    Type(
        "FVector3f",
        ["""#include "Runtime/Core/Public/Math/Vector.h" """],
        False),

    Type(
        "FIntVector",
        ["""#include "Runtime/Core/Public/Math/IntVector.h" """],
        False),

    Type(
        "FVector2f",
        ["""#include "Runtime/Core/Public/Math/Vector.h" """],
        False),

    Type(
        "FIntVector2",
        ["""#include "Runtime/Core/Public/Math/IntVector.h" """],
        True),

    Type(
        "FQuat4f",
        ["""#include "Runtime/Core/Public/Math/Quat.h" """],
        False)
    ]


for t in types:
    capitalizedType = t.Typename[0].upper() + t.Typename[1:]
    realFileName = fileName.replace(typeName, capitalizedType)
    print(realFileName)


    if not os.path.exists(f"{headerPath}\{capitalizedType}"):
        os.makedirs(f"{headerPath}\{capitalizedType}")

    includes = headerIncludes
    for include in t.AdditionalIncludes:
        includes += f"{include}\n" 
    

    header = includes + headerTemplate.replace(typeName, t.Typename).replace(className, capitalizedType)

    if (t.IgnoreReflection):
        for macro in reflectionMacroToIgnore:
            header = header.replace(macro, '')

    print(header, file = open(f"{headerPath}\{capitalizedType}\{realFileName}.h",'w',encoding='utf-8'))

    if not os.path.exists(f"{sourcePath}\{capitalizedType}"):
        os.makedirs(f"{sourcePath}\{capitalizedType}")
    print(sourceTemplate.replace(typeName, t.Typename).replace(className, capitalizedType), file = open(f"{sourcePath}\{capitalizedType}\{realFileName}.cpp",'w',encoding='utf-8'))