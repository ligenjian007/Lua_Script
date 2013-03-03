echo on
protoc --descriptor_set_out=ScriptPB.protobin --include_imports ScriptPB.proto
protogen ScriptPB.protobin   

