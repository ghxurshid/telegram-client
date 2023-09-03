#include "AuthKey.h"

AuthKey* CreateAuthKey(char* data)
{
    /*key = data;
    using SHA1 sHA = new SHA1Managed();
    using MemoryStream input = new MemoryStream(sHA.ComputeHash(key), writable: false);
    using BinaryReader binaryReader = new BinaryReader(input);
    auxHash = binaryReader.ReadUInt64();
    binaryReader.ReadBytes(4);
    keyId = binaryReader.ReadUInt64();*/
    return new AuthKey();
}
