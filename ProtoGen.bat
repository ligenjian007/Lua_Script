echo on
protoc --descriptor_set_out=LuaScript.protobin --include_imports LuaScript.proto
protogen LuaScript.protobin   

