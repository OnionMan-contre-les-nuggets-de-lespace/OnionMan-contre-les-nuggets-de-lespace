using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

namespace OnionMan.Network
{
    public class EncodingUtility : MonoBehaviour
    {
        public static IEnumerable<byte> Encode<T>(T value)
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
                        .Concat(Encode(vector3Value.z));

                case Vector3Int vector3IntValue:
                    return Encode(vector3IntValue.x)
                        .Concat(Encode(vector3IntValue.y))
                        .Concat(Encode(vector3IntValue.z));

                case Vector2 vector2Value:
                    return Encode(vector2Value.x)
                        .Concat(Encode(vector2Value.y));

                case Vector2Int vector2IntValue:
                    return Encode(vector2IntValue.x)
                        .Concat(Encode(vector2IntValue.y));

                case Quaternion quaternionValue:
                    return Encode(quaternionValue.x)
                        .Concat(Encode(quaternionValue.y))
                        .Concat(Encode(quaternionValue.z))
                        .Concat(Encode(quaternionValue.w));

                default:
                    throw new NotImplementedException($"The type {typeof(T)} cannot be encoded yet, u looser");
            }
        }

        public static T Decode<T>(byte[] bytes, ref int offset, int size = -1)
        {
            int initialOffset = offset;
            // string are too specific
            if (typeof(T) == typeof(string))
            {
                if (size == -1)
                {
                    throw new ArgumentException($"In order to decode a string, the argument 'size' must be set");
                }
                object st = Encoding.UTF8.GetString(bytes, offset, size);
                offset += size;
                return (T)st;
            }

            object decodedValue;
            T defaultObj = GetDefaultObjOfType<T>();

            switch (defaultObj)
            {
                #region Base Types
                //Misc
                case bool:
                    decodedValue = BitConverter.ToBoolean(bytes, offset);
                    offset += sizeof(bool);
                    break;
                case char:
                    decodedValue = BitConverter.ToChar(bytes, offset);
                    offset += sizeof(char);
                    break;

                //Numbers
                case double:
                    decodedValue = BitConverter.ToDouble(bytes, offset);
                    offset += sizeof(double);
                    break;
                case float:
                    decodedValue = BitConverter.ToSingle(bytes, offset);
                    offset += sizeof(float);
                    break;
                case int:
                    decodedValue = BitConverter.ToInt32(bytes, offset);
                    offset += sizeof(int);
                    break;
                case long:
                    decodedValue = BitConverter.ToInt64(bytes, offset);
                    offset += sizeof(long);
                    break;
                case short:
                    decodedValue = BitConverter.ToInt16(bytes, offset);
                    offset += sizeof(short);
                    break;
                case uint:
                    decodedValue = BitConverter.ToUInt32(bytes, offset);
                    offset += sizeof(uint);
                    break;
                case ulong:
                    decodedValue = BitConverter.ToUInt64(bytes, offset);
                    offset += sizeof(ulong);
                    break;
                case ushort:
                    decodedValue = BitConverter.ToUInt16(bytes, offset); 
                    offset += sizeof(ushort);
                    break;
                #endregion
                #region Derived Types
                //Vectors
                case Vector3:
                    decodedValue = new Vector3(
                        Decode<float>(bytes, ref offset),
                        Decode<float>(bytes, ref offset),
                        Decode<float>(bytes, ref offset));
                    break;

                case Vector3Int:
                    decodedValue = new Vector3Int(
                        Decode<int>(bytes, ref offset),
                        Decode<int>(bytes, ref offset),
                        Decode<int>(bytes, ref offset));
                    break;

                case Vector2:
                    decodedValue = new Vector2(
                        Decode<float>(bytes, ref offset),
                        Decode<float>(bytes, ref offset));
                    break;

                case Vector2Int:
                    decodedValue = new Vector2Int(
                        Decode<int>(bytes, ref offset),
                        Decode<int>(bytes, ref offset));
                    break;

                case Quaternion:
                    decodedValue = new Quaternion(
                        Decode<float>(bytes, ref offset),
                        Decode<float>(bytes, ref offset),
                        Decode<float>(bytes, ref offset),
                        Decode<float>(bytes, ref offset));
                    break;
                #endregion
                default:
                    throw new NotImplementedException($"The type {typeof(T)} cannot be decoded yet");
            }

            if (size != -1 && offset - initialOffset != size)
            {
                Debug.LogError("Offset Overflow !");
            }
            return (T)decodedValue;
        }

        public static int GetSize<T>(T value = default)
        {
            // string are too specific
            if (typeof(T) == typeof(string))
            {
                if ()
                return ;
            }

            object decodedValue;
            T defaultObj = GetDefaultObjOfType<T>();

            switch (defaultObj)
            {
                #region Base Types
                //Misc
                case bool:
                    decodedValue = BitConverter.ToBoolean(bytes, offset);
                    offset += sizeof(bool);
                    break;
                case char:
                    decodedValue = BitConverter.ToChar(bytes, offset);
                    offset += sizeof(char);
                    break;

                //Numbers
                case double:
                    decodedValue = BitConverter.ToDouble(bytes, offset);
                    offset += sizeof(double);
                    break;
                case float:
                    decodedValue = BitConverter.ToSingle(bytes, offset);
                    offset += sizeof(float);
                    break;
                case int:
                    decodedValue = BitConverter.ToInt32(bytes, offset);
                    offset += sizeof(int);
                    break;
                case long:
                    decodedValue = BitConverter.ToInt64(bytes, offset);
                    offset += sizeof(long);
                    break;
                case short:
                    decodedValue = BitConverter.ToInt16(bytes, offset);
                    offset += sizeof(short);
                    break;
                case uint:
                    decodedValue = BitConverter.ToUInt32(bytes, offset);
                    offset += sizeof(uint);
                    break;
                case ulong:
                    decodedValue = BitConverter.ToUInt64(bytes, offset);
                    offset += sizeof(ulong);
                    break;
                case ushort:
                    decodedValue = BitConverter.ToUInt16(bytes, offset);
                    offset += sizeof(ushort);
                    break;
                #endregion
                #region Derived Types
                //Vectors
                case Vector3:
                    decodedValue = new Vector3(
                        Decode<float>(bytes, ref offset),
                        Decode<float>(bytes, ref offset),
                        Decode<float>(bytes, ref offset));
                    break;

                case Vector3Int:
                    decodedValue = new Vector3Int(
                        Decode<int>(bytes, ref offset),
                        Decode<int>(bytes, ref offset),
                        Decode<int>(bytes, ref offset));
                    break;

                case Vector2:
                    decodedValue = new Vector2(
                        Decode<float>(bytes, ref offset),
                        Decode<float>(bytes, ref offset));
                    break;

                case Vector2Int:
                    decodedValue = new Vector2Int(
                        Decode<int>(bytes, ref offset),
                        Decode<int>(bytes, ref offset));
                    break;

                case Quaternion:
                    decodedValue = new Quaternion(
                        Decode<float>(bytes, ref offset),
                        Decode<float>(bytes, ref offset),
                        Decode<float>(bytes, ref offset),
                        Decode<float>(bytes, ref offset));
                    break;
                #endregion
                default:
                    throw new NotImplementedException($"The type {typeof(T)} cannot be decoded yet");
            }
        }

        private static T GetDefaultObjOfType<T>()
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

        #region Debug
        public static string GetBytesAsString(IEnumerable<byte> bytesEnum)
        {
            string returnValue = string.Empty;
            byte[] bytes = bytesEnum.ToArray();
            int byteCount = bytes.Count();
            for (int i = 0; i < byteCount; i++)
            {
                returnValue += $"{bytes[i]}" + (i < byteCount - 1 ? "|" : "");
            }
            return returnValue;
        }

        public static byte[] GetStringAsBytes(string stringifiedBytes)
        {
            string[] splittedString = stringifiedBytes.Split('|');

            byte[] bytes = new byte[splittedString.Length];
            for ( int i = 0; i < splittedString.Length; i++)
            {
                bytes[i] = byte.Parse(splittedString[i]);
            }

            return bytes;
        }
        #endregion
    }
}
