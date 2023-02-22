// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedList.h"

#include "TYPENAMESynchronizedList.generated.h"


class UTYPENAMESynchronizedList : public USpecializedSynchronizedProperty
{
private:
	TYPENAME m_value;

public:
	UTYPENAMESynchronizedList(TArray<TYPENAME>& initialValue, uint16 propertyID);

	const TArray<TYPENAME>& GetValue() const
	{
		return m_value;
	}

	void SetValue(TArray<TYPENAME>& value)
	{
		if (!ListEquals<TYPENAME>)
		m_value = value;
	}

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;

protected:
	virtual void CheckNeedSync() override;
};

UTYPENAMESynchronizedList::UTYPENAMESynchronizedList(TArray<TYPENAME>& initialValue, uint16 propertyID)
{
	m_value = Copy(initialValue);
	m_propertyID = propertyID;
}
