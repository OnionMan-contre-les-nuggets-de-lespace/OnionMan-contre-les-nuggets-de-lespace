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
                #region Base Types
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
                #endregion
                #region Derived Types
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
                #endregion
                default:
                    throw new NotImplementedException($"The type {typeof(T)} cannot be encoded yet, u looser");
            }
        }

        public static void PutEncodedValueInBuffer<T>(T value, byte[] buffer, ref int offset)
        {
            switch (value)
            {
                #region Base Types
                //Misc
                case string stringValue:
                    PutToBuffer(buffer, Encoding.UTF8.GetBytes(stringValue), ref offset);
                    break;
                case bool boolValue:
                    PutToBuffer(buffer, BitConverter.GetBytes(boolValue), ref offset);
                    break;
                case char charValue:
                    PutToBuffer(buffer, BitConverter.GetBytes(charValue), ref offset);
                    break;

                //Numbers
                case double doubleValue:
                    PutToBuffer(buffer, BitConverter.GetBytes(doubleValue), ref offset);
                    break;
                case float floatValue:
                    PutToBuffer(buffer, BitConverter.GetBytes(floatValue), ref offset);
                    break;
                case int intValue:
                    PutToBuffer(buffer, BitConverter.GetBytes(intValue), ref offset);
                    break;
                case long longValue:
                    PutToBuffer(buffer, BitConverter.GetBytes(longValue), ref offset);
                    break;
                case short shortValue:
                    PutToBuffer(buffer, BitConverter.GetBytes(shortValue), ref offset);
                    break;
                case uint uintValue:
                    PutToBuffer(buffer, BitConverter.GetBytes(uintValue), ref offset);
                    break;
                case ulong ulongValue:
                    PutToBuffer(buffer, BitConverter.GetBytes(ulongValue), ref offset);
                    break;
                case ushort ushortValue:
                    PutToBuffer(buffer, BitConverter.GetBytes(ushortValue), ref offset);
                    break;
                #endregion
                #region Derived Types
                //Vectors
                case Vector3 vector3Value:
                    PutEncodedValueInBuffer(vector3Value.x, buffer, ref offset);
                    PutEncodedValueInBuffer(vector3Value.y, buffer, ref offset);
                    PutEncodedValueInBuffer(vector3Value.z, buffer, ref offset);
                    break;

                case Vector3Int vector3IntValue:
                    PutEncodedValueInBuffer(vector3IntValue.x, buffer, ref offset);
                    PutEncodedValueInBuffer(vector3IntValue.y, buffer, ref offset);
                    PutEncodedValueInBuffer(vector3IntValue.z, buffer, ref offset);
                    break;

                case Vector2 vector2Value:
                    PutEncodedValueInBuffer(vector2Value.x, buffer, ref offset);
                    PutEncodedValueInBuffer(vector2Value.y, buffer, ref offset);
                    break;

                case Vector2Int vector2IntValue:
                    PutEncodedValueInBuffer(vector2IntValue.x, buffer, ref offset);
                    PutEncodedValueInBuffer(vector2IntValue.y, buffer, ref offset);
                    break;

                case Quaternion quaternionValue:
                    PutEncodedValueInBuffer(quaternionValue.x, buffer, ref offset);
                    PutEncodedValueInBuffer(quaternionValue.y, buffer, ref offset);
                    PutEncodedValueInBuffer(quaternionValue.z, buffer, ref offset);
                    PutEncodedValueInBuffer(quaternionValue.w, buffer, ref offset);
                    break;
                #endregion
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

        public static int GetEncodedSize<T>(T value = default)
        {
            // string are too specific
            if (typeof(T) == typeof(string))
            {
                if (value == null)
                {
                    throw new ArgumentException($"In order to get a string size, it shouldn't be null or default");
                }
                return Encode(value).Count();
            }

            T defaultObj = GetDefaultObjOfType<T>();

            switch (defaultObj)
            {
                #region Base Types
                //Misc
                case bool:
                    return sizeof(bool);
                case char:
                    return sizeof(char);

                //Numbers
                case double:
                    return sizeof(double);
                case float:
                    return sizeof(float);
                case int:
                    return sizeof(int);
                case long:
                    return sizeof(long);
                case short:
                    return sizeof(short);
                case uint:
                    return sizeof(uint);
                case ulong:
                    return sizeof(ulong);
                case ushort:
                    return sizeof(ushort);
                #endregion
                #region Derived Types
                //Vectors
                case Vector3:
                    return sizeof(float) * 3;

                case Vector3Int:
                    return sizeof(int) * 3;

                case Vector2:
                    return sizeof(float) * 2;

                case Vector2Int:
                    return sizeof(int) * 2;

                case Quaternion:
                    return sizeof(float) * 4;
                #endregion
                default:
                    throw new NotImplementedException($"The size of {typeof(T)} cannot be found yet");
            }
        }
        public static bool HasFixedEncodedSize<T>()
        {
            // string are too specific
            if (typeof(T) == typeof(string))
            {
                return false;
            }

            T defaultObj = GetDefaultObjOfType<T>();

            switch (defaultObj)
            {
                #region Base Types
                //Misc
                case bool:
                case char:

                //Numbers
                case double:
                case float:
                case int:
                case long:
                case short:
                case uint:
                case ulong:
                case ushort:
                #endregion
                #region Derived Types
                //Vectors
                case Vector3:
                case Vector3Int:
                case Vector2:
                case Vector2Int:
                case Quaternion:
                    return true;
                #endregion
                default:
                    throw new NotImplementedException($"The size of {typeof(T)} cannot be found yet");
            }
        }

        public static void PutToBuffer(byte[] toBuffer, byte[] fromBuffer, ref int offset)
		{
            for (int i = 0; offset < fromBuffer.Length; offset++, i++)
			{
                toBuffer[offset] = fromBuffer[i];
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
