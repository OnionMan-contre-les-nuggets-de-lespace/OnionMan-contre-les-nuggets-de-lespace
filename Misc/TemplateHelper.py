import os

class Type:
    def __init__(self, typeName : str, additionalIncludes : list[str], ignoreReflection : bool) -> None:
        self.Typename = typeName
        self.AdditionalIncludes = additionalIncludes
        self.IgnoreReflection = ignoreReflection

reflectionMacroToIgnore = ["UFUNCTION(BlueprintCallable)\n    "]

headerIncludes = """// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedList.h"

"""



headerTemplate = """
#include "SynchronizedCLASSNAMEList.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, EditInlineNew)
class ONIONMAN_UNREAL_API USynchronizedCLASSNAMEList : public USpecializedSynchronizedList
{
	GENERATED_BODY()
private:
	TArray<TYPENAME> m_value{};
	TArray<TYPENAME> m_previousValue{};

public:
	USynchronizedCLASSNAMEList();
	USynchronizedCLASSNAMEList(TArray<TYPENAME>& initialValue, uint16 propertyID);

    UFUNCTION(BlueprintCallable)
    inline void GetValue(TArray<TYPENAME>& outValue) const
    {
		outValue = m_value;
    }

    UFUNCTION(BlueprintCallable)
    inline void SetValue(TArray<TYPENAME>& newValue)
    {
        SetValueGeneric<TYPENAME>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;

protected:
	virtual void CheckNeedSync() override;
};
"""
sourceTemplate = """#include "Network/SpecializedProperties/TYPENAME/SynchronizedCLASSNAMEList.h"

USynchronizedCLASSNAMEList::USynchronizedCLASSNAMEList()
{
}

USynchronizedCLASSNAMEList::USynchronizedCLASSNAMEList(TArray<TYPENAME> &initialValue, uint16 propertyID) : 
    USpecializedSynchronizedList::USpecializedSynchronizedList(propertyID)
{
    CopyTo<TYPENAME>(initialValue, m_value);
}

void USynchronizedCLASSNAMEList::Init()
{
    USpecializedSynchronizedList::Init();
    InitGeneric<TYPENAME>();
}

int USynchronizedCLASSNAMEList::GetEncodedPropertySize()
{
    USpecializedSynchronizedList::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<TYPENAME>(m_value);
}

void USynchronizedCLASSNAMEList::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedList::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<TYPENAME>(m_value, buffer, offset, forSync);
}

void USynchronizedCLASSNAMEList::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedList::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<TYPENAME>(m_value, m_previousValue, encodedProperty, offset, propertySize);
}

void USynchronizedCLASSNAMEList::CheckNeedSync()
{
    USpecializedSynchronizedList::CheckNeedSync();
    CheckNeedSyncGeneric<TYPENAME>(m_value, m_previousValue);
}
"""


headerPath = r"OnionMan_Unreal\Source\OnionMan_Unreal\Public\Network\SpecializedProperties"
sourcePath = r"OnionMan_Unreal\Source\OnionMan_Unreal\Private\Network\SpecializedProperties"
fileName = "SynchronizedTYPENAMEList"

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