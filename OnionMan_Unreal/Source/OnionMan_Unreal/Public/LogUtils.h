// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// custom log category
DECLARE_LOG_CATEGORY_EXTERN(OnionMan_Unreal, Log, All);

// custom log macro
#define LOG(x, ...) UE_LOG(OnionMan_Unreal, Log, TEXT(x), __VA_ARGS__)
#define LOG_WARNING(x, ...) UE_LOG(OnionMan_Unreal, Warning, TEXT(x), __VA_ARGS__)
#define LOG_ERROR(x, ...) UE_LOG(OnionMan_Unreal, Warning, TEXT(x), __VA_ARGS__)


namespace internal
{
    static const unsigned int FRONT_SIZE = sizeof("internal::GetTypeNameHelper<") - 1u;
    static const unsigned int BACK_SIZE = sizeof(">::GetTypeName") - 1u;

    template <typename T>
    struct GetTypeNameHelper
    {
        static const char* GetTypeName(void)
        {
            static const size_t size = sizeof(__FUNCTION__) - FRONT_SIZE - BACK_SIZE;
            static char typeName[size] = {};
            memcpy(typeName, __FUNCTION__ + FRONT_SIZE, size - 1u);

            return typeName;
        }
    };
}


//template <typename T>
//static const char* GetTypeName(void)
//{
//    return internal::GetTypeNameHelper<T>::GetTypeName();
//}
