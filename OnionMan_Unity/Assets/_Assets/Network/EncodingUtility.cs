using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEditor.ShaderGraph.Internal;
using UnityEngine;
using static UnityEngine.Rendering.DebugUI;

namespace OnionMan.Network
{
    public class EncodingUtility : MonoBehaviour
    {
        public static int FloatSize = sizeof(float);
        public static int IntSize = sizeof(int);




        public static byte[] Encode<T>(T value)
        {
            switch (value)
            {
                //Misc
                case string stringValue:
                    return Encoding.UTF8.GetBytes(stringValue);
                case bool boolValue:
                    return BitConverter.GetBytes(boolValue);
                case char charValue:
                    return BitConverter.GetBytes(charValue);

                //Numbers
                case double doubleValue:
                    return BitConverter.GetBytes(doubleValue);
                case float floatValue:
                    return BitConverter.GetBytes(floatValue);
                case int intValue:
                    return BitConverter.GetBytes(intValue);
                case long longValue:
                    return BitConverter.GetBytes(longValue);
                case short shortValue:
                    return BitConverter.GetBytes(shortValue);
                case uint uintValue:
                    return BitConverter.GetBytes(uintValue);
                case ulong ulongValue:
                    return BitConverter.GetBytes(ulongValue);
                case ushort ushortValue:
                    return BitConverter.GetBytes(ushortValue);

                //Vectors
                case Vector3 vector3Value:
                    return Encode(vector3Value.x)
                        .Concat(Encode(vector3Value.y))
                        .Concat(Encode(vector3Value.z)).ToArray();

                case Vector3Int vector3IntValue:
                    return Encode(vector3IntValue.x)
                        .Concat(Encode(vector3IntValue.y))
                        .Concat(Encode(vector3IntValue.z))
                        .ToArray();

                case Vector2 vector2Value:
                    return Encode(vector2Value.x)
                        .Concat(Encode(vector2Value.y))
                        .ToArray();

                case Vector2Int vector2IntValue:
                    return Encode(vector2IntValue.x)
                        .Concat(Encode(vector2IntValue.y))
                        .ToArray();

                case Quaternion quaternionValue:
                    return Encode(quaternionValue.x)
                        .Concat(Encode(quaternionValue.y))
                        .Concat(Encode(quaternionValue.z))
                        .Concat(Encode(quaternionValue.w))
                        .ToArray();

                default:
                    throw new NotSupportedException($"The type {typeof(T)} cannot be encoded");
            }
        }

        public static T Decode<T>(byte[] bytes, int startIndex)
        {
            // string are too specifics
            if (typeof(T) == typeof(string))
            {
                object st = Encoding.UTF8.GetString(bytes);
                return (T)st;
            }

            object decodedValue;
            T defaultObj = GetDefaultObj<T>();

            switch (defaultObj)
            {
                //Misc
                case bool:
                    decodedValue = BitConverter.ToBoolean(bytes, startIndex);
                    break;
                case char:
                    decodedValue = BitConverter.ToChar(bytes, startIndex);
                    break;

                //Numbers
                case double:
                    decodedValue = BitConverter.ToDouble(bytes, startIndex);
                    break;
                case float:
                    decodedValue = BitConverter.ToSingle(bytes, startIndex);
                    break;
                case int:
                    decodedValue = BitConverter.ToInt32(bytes, startIndex);
                    break;
                case long:
                    decodedValue = BitConverter.ToInt64(bytes, startIndex);
                    break;
                case short:
                    decodedValue = BitConverter.ToInt16(bytes, startIndex);
                    break;
                case uint:
                    decodedValue = BitConverter.ToUInt32(bytes, startIndex);
                    break;
                case ulong:
                    decodedValue = BitConverter.ToUInt64(bytes, startIndex);
                    break;
                case ushort:
                    decodedValue = BitConverter.ToUInt16(bytes, startIndex);
                    break;

                //Vectors
                case Vector3:
                    decodedValue = new Vector3(
                        Decode<float>(bytes, startIndex),
                        Decode<float>(bytes, startIndex + FloatSize),
                        Decode<float>(bytes, startIndex + FloatSize * 2));
                    break;

                case Vector3Int:
                    decodedValue = new Vector3Int(
                        Decode<int>(bytes, startIndex),
                        Decode<int>(bytes, startIndex + IntSize),
                        Decode<int>(bytes, startIndex + IntSize * 2));
                    break;

                case Vector2:
                    decodedValue = new Vector2(
                        Decode<float>(bytes, startIndex),
                        Decode<float>(bytes, startIndex + FloatSize));
                    break;

                case Vector2Int:
                    decodedValue = new Vector2Int(
                        Decode<int>(bytes, startIndex),
                        Decode<int>(bytes, startIndex + IntSize));
                    break;

                case Quaternion:
                    decodedValue = new Quaternion(
                        Decode<float>(bytes, startIndex),
                        Decode<float>(bytes, startIndex + FloatSize),
                        Decode<float>(bytes, startIndex + FloatSize * 2),
                        Decode<float>(bytes, startIndex + FloatSize * 3));
                    break;

                default:
                    throw new NotSupportedException($"The type {typeof(T)} cannot be decoded");
            }
            return (T)decodedValue;
        }
        public static string PrintBytes(byte[] bytes)
        {
            string returnValue = string.Empty;
            foreach (byte b in bytes)
            {
                returnValue += b.ToString();
            }
            return returnValue;
        }


        private static T GetDefaultObj<T>()
        {
            if (typeof(T).IsValueType || typeof(T) == typeof(string))
            {
                return default(T);
            }
            else
            {
                return (T)Activator.CreateInstance(typeof(T));
            }
        }
    }
}
