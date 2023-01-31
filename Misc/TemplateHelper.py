templateFunction = """template<>
static int GetSizeOf<TYPE>(TYPE* value);"""

typeName = "TYPE"

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