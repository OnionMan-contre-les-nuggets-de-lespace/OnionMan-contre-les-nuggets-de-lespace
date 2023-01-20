templateFunction = """
    template<> 
    void EncodingUtility::PutEncodedValueInBuffer<typeuh>(typeuh value, TArray<uint8>& buffer, int& offset)
    {
        PutToBuffer(buffer, (uint8*)&value, offset, sizeof(typeuh));
    }"""

typeName = "typeuh"

types = [
    "FString", 
    "bool", 
    "char", 
    "double",
    "float", 
    "int", 
    "long", 
    "short", 
    "uint32", 
    "uint64",
    "uint16",
    "FVector3f",
    "FIntVector", 
    "FVector2f", 
    "FIntVector2", 
    "FQuat4f"
    ]

for t in types:
    print(templateFunction.replace(typeName, t))