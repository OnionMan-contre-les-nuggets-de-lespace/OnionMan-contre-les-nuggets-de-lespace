using System.Collections.Generic;

namespace OnionMan.Network
{
    public enum NetworkRole
    {
        SenderAndReciever = 0,
        Sender = 1,
        Reciever = 2,
    }

    public interface ISynchronizedProperty
    {
        public bool NeedSync { get; set; }

        public ushort PropertyID { get; }

        public NetworkRole Role { get; }

        public void Init();

        public int GetEncodedPropertySize();

        public void PutEncodedPropertyToBuffer(byte[] buffer, ref int offset, bool forSync = true);
        public IEnumerable<byte> EncodeProperty(bool forSync = true);

        public void DecodeProperty(byte[] encodedProperty, ref int offset, int propertySize);
    }
}
