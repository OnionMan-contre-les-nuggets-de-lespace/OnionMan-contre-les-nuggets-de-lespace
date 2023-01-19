using System.Collections.Generic;

namespace OnionMan.Network
{
    public interface ISynchronizedProperty
    {
        public bool NeedSync { get; set; }

        public ushort PropertyID { get; }

        public int GetEncodedPropertySize();

        public IEnumerable<byte> EncodeProperty(bool forSync = true);

        public void DecodeProperty(byte[] encodedProperty, ref int offset, int propertySize);
    }
}
