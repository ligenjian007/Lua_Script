// Generated by the protocol buffer compiler.  DO NOT EDIT!
#include "stdafx.h"
#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION


#include "ScriptPB.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace LuaScriptPB {

namespace {

const ::google::protobuf::Descriptor* LScriptRequest_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  LScriptRequest_reflection_ = NULL;
const ::google::protobuf::Descriptor* LScriptRequest_call_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  LScriptRequest_call_reflection_ = NULL;
const ::google::protobuf::Descriptor* LScriptResponse_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  LScriptResponse_reflection_ = NULL;
const ::google::protobuf::Descriptor* LScriptResponse_result_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  LScriptResponse_result_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_ScriptPB_2eproto() {
  protobuf_AddDesc_ScriptPB_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "ScriptPB.proto");
  GOOGLE_CHECK(file != NULL);
  LScriptRequest_descriptor_ = file->message_type(0);
  static const int LScriptRequest_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LScriptRequest, requests_),
  };
  LScriptRequest_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      LScriptRequest_descriptor_,
      LScriptRequest::default_instance_,
      LScriptRequest_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LScriptRequest, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LScriptRequest, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(LScriptRequest));
  LScriptRequest_call_descriptor_ = LScriptRequest_descriptor_->nested_type(0);
  static const int LScriptRequest_call_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LScriptRequest_call, scriptno_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LScriptRequest_call, repeatetime_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LScriptRequest_call, content_),
  };
  LScriptRequest_call_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      LScriptRequest_call_descriptor_,
      LScriptRequest_call::default_instance_,
      LScriptRequest_call_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LScriptRequest_call, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LScriptRequest_call, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(LScriptRequest_call));
  LScriptResponse_descriptor_ = file->message_type(1);
  static const int LScriptResponse_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LScriptResponse, responses_),
  };
  LScriptResponse_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      LScriptResponse_descriptor_,
      LScriptResponse::default_instance_,
      LScriptResponse_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LScriptResponse, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LScriptResponse, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(LScriptResponse));
  LScriptResponse_result_descriptor_ = LScriptResponse_descriptor_->nested_type(0);
  static const int LScriptResponse_result_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LScriptResponse_result, scriptno_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LScriptResponse_result, content_),
  };
  LScriptResponse_result_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      LScriptResponse_result_descriptor_,
      LScriptResponse_result::default_instance_,
      LScriptResponse_result_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LScriptResponse_result, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LScriptResponse_result, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(LScriptResponse_result));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_ScriptPB_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    LScriptRequest_descriptor_, &LScriptRequest::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    LScriptRequest_call_descriptor_, &LScriptRequest_call::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    LScriptResponse_descriptor_, &LScriptResponse::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    LScriptResponse_result_descriptor_, &LScriptResponse_result::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_ScriptPB_2eproto() {
  delete LScriptRequest::default_instance_;
  delete LScriptRequest_reflection_;
  delete LScriptRequest_call::default_instance_;
  delete LScriptRequest_call_reflection_;
  delete LScriptResponse::default_instance_;
  delete LScriptResponse_reflection_;
  delete LScriptResponse_result::default_instance_;
  delete LScriptResponse_result_reflection_;
}

void protobuf_AddDesc_ScriptPB_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\016ScriptPB.proto\022\013LuaScriptPB\"\207\001\n\016LScrip"
    "tRequest\0222\n\010requests\030\001 \003(\0132 .LuaScriptPB"
    ".LScriptRequest.call\032A\n\004call\022\020\n\010scriptNo"
    "\030\001 \002(\005\022\026\n\013RepeateTime\030\002 \002(\005:\0011\022\017\n\007conten"
    "t\030\003 \002(\t\"v\n\017LScriptResponse\0226\n\tresponses\030"
    "\001 \003(\0132#.LuaScriptPB.LScriptResponse.resu"
    "lt\032+\n\006result\022\020\n\010scriptNo\030\001 \002(\005\022\017\n\007conten"
    "t\030\002 \002(\t", 287);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "ScriptPB.proto", &protobuf_RegisterTypes);
  LScriptRequest::default_instance_ = new LScriptRequest();
  LScriptRequest_call::default_instance_ = new LScriptRequest_call();
  LScriptResponse::default_instance_ = new LScriptResponse();
  LScriptResponse_result::default_instance_ = new LScriptResponse_result();
  LScriptRequest::default_instance_->InitAsDefaultInstance();
  LScriptRequest_call::default_instance_->InitAsDefaultInstance();
  LScriptResponse::default_instance_->InitAsDefaultInstance();
  LScriptResponse_result::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_ScriptPB_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_ScriptPB_2eproto {
  StaticDescriptorInitializer_ScriptPB_2eproto() {
    protobuf_AddDesc_ScriptPB_2eproto();
  }
} static_descriptor_initializer_ScriptPB_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int LScriptRequest_call::kScriptNoFieldNumber;
const int LScriptRequest_call::kRepeateTimeFieldNumber;
const int LScriptRequest_call::kContentFieldNumber;
#endif  // !_MSC_VER

LScriptRequest_call::LScriptRequest_call()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void LScriptRequest_call::InitAsDefaultInstance() {
}

LScriptRequest_call::LScriptRequest_call(const LScriptRequest_call& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void LScriptRequest_call::SharedCtor() {
  _cached_size_ = 0;
  scriptno_ = 0;
  repeatetime_ = 1;
  content_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

LScriptRequest_call::~LScriptRequest_call() {
  SharedDtor();
}

void LScriptRequest_call::SharedDtor() {
  if (content_ != &::google::protobuf::internal::kEmptyString) {
    delete content_;
  }
  if (this != default_instance_) {
  }
}

void LScriptRequest_call::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* LScriptRequest_call::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return LScriptRequest_call_descriptor_;
}

const LScriptRequest_call& LScriptRequest_call::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ScriptPB_2eproto();  return *default_instance_;
}

LScriptRequest_call* LScriptRequest_call::default_instance_ = NULL;

LScriptRequest_call* LScriptRequest_call::New() const {
  return new LScriptRequest_call;
}

void LScriptRequest_call::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    scriptno_ = 0;
    repeatetime_ = 1;
    if (has_content()) {
      if (content_ != &::google::protobuf::internal::kEmptyString) {
        content_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool LScriptRequest_call::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 scriptNo = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &scriptno_)));
          set_has_scriptno();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_RepeateTime;
        break;
      }
      
      // required int32 RepeateTime = 2 [default = 1];
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_RepeateTime:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &repeatetime_)));
          set_has_repeatetime();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_content;
        break;
      }
      
      // required string content = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_content:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_content()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->content().data(), this->content().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void LScriptRequest_call::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required int32 scriptNo = 1;
  if (has_scriptno()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->scriptno(), output);
  }
  
  // required int32 RepeateTime = 2 [default = 1];
  if (has_repeatetime()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->repeatetime(), output);
  }
  
  // required string content = 3;
  if (has_content()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->content().data(), this->content().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      3, this->content(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* LScriptRequest_call::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required int32 scriptNo = 1;
  if (has_scriptno()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->scriptno(), target);
  }
  
  // required int32 RepeateTime = 2 [default = 1];
  if (has_repeatetime()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->repeatetime(), target);
  }
  
  // required string content = 3;
  if (has_content()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->content().data(), this->content().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->content(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int LScriptRequest_call::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 scriptNo = 1;
    if (has_scriptno()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->scriptno());
    }
    
    // required int32 RepeateTime = 2 [default = 1];
    if (has_repeatetime()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->repeatetime());
    }
    
    // required string content = 3;
    if (has_content()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->content());
    }
    
  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void LScriptRequest_call::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const LScriptRequest_call* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const LScriptRequest_call*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void LScriptRequest_call::MergeFrom(const LScriptRequest_call& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_scriptno()) {
      set_scriptno(from.scriptno());
    }
    if (from.has_repeatetime()) {
      set_repeatetime(from.repeatetime());
    }
    if (from.has_content()) {
      set_content(from.content());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void LScriptRequest_call::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void LScriptRequest_call::CopyFrom(const LScriptRequest_call& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool LScriptRequest_call::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;
  
  return true;
}

void LScriptRequest_call::Swap(LScriptRequest_call* other) {
  if (other != this) {
    std::swap(scriptno_, other->scriptno_);
    std::swap(repeatetime_, other->repeatetime_);
    std::swap(content_, other->content_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata LScriptRequest_call::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = LScriptRequest_call_descriptor_;
  metadata.reflection = LScriptRequest_call_reflection_;
  return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int LScriptRequest::kRequestsFieldNumber;
#endif  // !_MSC_VER

LScriptRequest::LScriptRequest()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void LScriptRequest::InitAsDefaultInstance() {
}

LScriptRequest::LScriptRequest(const LScriptRequest& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void LScriptRequest::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

LScriptRequest::~LScriptRequest() {
  SharedDtor();
}

void LScriptRequest::SharedDtor() {
  if (this != default_instance_) {
  }
}

void LScriptRequest::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* LScriptRequest::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return LScriptRequest_descriptor_;
}

const LScriptRequest& LScriptRequest::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ScriptPB_2eproto();  return *default_instance_;
}

LScriptRequest* LScriptRequest::default_instance_ = NULL;

LScriptRequest* LScriptRequest::New() const {
  return new LScriptRequest;
}

void LScriptRequest::Clear() {
  requests_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool LScriptRequest::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .LuaScriptPB.LScriptRequest.call requests = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_requests:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_requests()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_requests;
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void LScriptRequest::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .LuaScriptPB.LScriptRequest.call requests = 1;
  for (int i = 0; i < this->requests_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->requests(i), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* LScriptRequest::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .LuaScriptPB.LScriptRequest.call requests = 1;
  for (int i = 0; i < this->requests_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->requests(i), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int LScriptRequest::ByteSize() const {
  int total_size = 0;
  
  // repeated .LuaScriptPB.LScriptRequest.call requests = 1;
  total_size += 1 * this->requests_size();
  for (int i = 0; i < this->requests_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->requests(i));
  }
  
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void LScriptRequest::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const LScriptRequest* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const LScriptRequest*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void LScriptRequest::MergeFrom(const LScriptRequest& from) {
  GOOGLE_CHECK_NE(&from, this);
  requests_.MergeFrom(from.requests_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void LScriptRequest::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void LScriptRequest::CopyFrom(const LScriptRequest& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool LScriptRequest::IsInitialized() const {
  
  for (int i = 0; i < requests_size(); i++) {
    if (!this->requests(i).IsInitialized()) return false;
  }
  return true;
}

void LScriptRequest::Swap(LScriptRequest* other) {
  if (other != this) {
    requests_.Swap(&other->requests_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata LScriptRequest::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = LScriptRequest_descriptor_;
  metadata.reflection = LScriptRequest_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int LScriptResponse_result::kScriptNoFieldNumber;
const int LScriptResponse_result::kContentFieldNumber;
#endif  // !_MSC_VER

LScriptResponse_result::LScriptResponse_result()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void LScriptResponse_result::InitAsDefaultInstance() {
}

LScriptResponse_result::LScriptResponse_result(const LScriptResponse_result& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void LScriptResponse_result::SharedCtor() {
  _cached_size_ = 0;
  scriptno_ = 0;
  content_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

LScriptResponse_result::~LScriptResponse_result() {
  SharedDtor();
}

void LScriptResponse_result::SharedDtor() {
  if (content_ != &::google::protobuf::internal::kEmptyString) {
    delete content_;
  }
  if (this != default_instance_) {
  }
}

void LScriptResponse_result::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* LScriptResponse_result::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return LScriptResponse_result_descriptor_;
}

const LScriptResponse_result& LScriptResponse_result::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ScriptPB_2eproto();  return *default_instance_;
}

LScriptResponse_result* LScriptResponse_result::default_instance_ = NULL;

LScriptResponse_result* LScriptResponse_result::New() const {
  return new LScriptResponse_result;
}

void LScriptResponse_result::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    scriptno_ = 0;
    if (has_content()) {
      if (content_ != &::google::protobuf::internal::kEmptyString) {
        content_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool LScriptResponse_result::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 scriptNo = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &scriptno_)));
          set_has_scriptno();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_content;
        break;
      }
      
      // required string content = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_content:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_content()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->content().data(), this->content().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void LScriptResponse_result::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required int32 scriptNo = 1;
  if (has_scriptno()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->scriptno(), output);
  }
  
  // required string content = 2;
  if (has_content()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->content().data(), this->content().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->content(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* LScriptResponse_result::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required int32 scriptNo = 1;
  if (has_scriptno()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->scriptno(), target);
  }
  
  // required string content = 2;
  if (has_content()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->content().data(), this->content().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->content(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int LScriptResponse_result::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 scriptNo = 1;
    if (has_scriptno()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->scriptno());
    }
    
    // required string content = 2;
    if (has_content()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->content());
    }
    
  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void LScriptResponse_result::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const LScriptResponse_result* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const LScriptResponse_result*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void LScriptResponse_result::MergeFrom(const LScriptResponse_result& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_scriptno()) {
      set_scriptno(from.scriptno());
    }
    if (from.has_content()) {
      set_content(from.content());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void LScriptResponse_result::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void LScriptResponse_result::CopyFrom(const LScriptResponse_result& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool LScriptResponse_result::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;
  
  return true;
}

void LScriptResponse_result::Swap(LScriptResponse_result* other) {
  if (other != this) {
    std::swap(scriptno_, other->scriptno_);
    std::swap(content_, other->content_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata LScriptResponse_result::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = LScriptResponse_result_descriptor_;
  metadata.reflection = LScriptResponse_result_reflection_;
  return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int LScriptResponse::kResponsesFieldNumber;
#endif  // !_MSC_VER

LScriptResponse::LScriptResponse()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void LScriptResponse::InitAsDefaultInstance() {
}

LScriptResponse::LScriptResponse(const LScriptResponse& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void LScriptResponse::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

LScriptResponse::~LScriptResponse() {
  SharedDtor();
}

void LScriptResponse::SharedDtor() {
  if (this != default_instance_) {
  }
}

void LScriptResponse::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* LScriptResponse::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return LScriptResponse_descriptor_;
}

const LScriptResponse& LScriptResponse::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ScriptPB_2eproto();  return *default_instance_;
}

LScriptResponse* LScriptResponse::default_instance_ = NULL;

LScriptResponse* LScriptResponse::New() const {
  return new LScriptResponse;
}

void LScriptResponse::Clear() {
  responses_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool LScriptResponse::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .LuaScriptPB.LScriptResponse.result responses = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_responses:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_responses()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_responses;
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void LScriptResponse::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .LuaScriptPB.LScriptResponse.result responses = 1;
  for (int i = 0; i < this->responses_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->responses(i), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* LScriptResponse::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .LuaScriptPB.LScriptResponse.result responses = 1;
  for (int i = 0; i < this->responses_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->responses(i), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int LScriptResponse::ByteSize() const {
  int total_size = 0;
  
  // repeated .LuaScriptPB.LScriptResponse.result responses = 1;
  total_size += 1 * this->responses_size();
  for (int i = 0; i < this->responses_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->responses(i));
  }
  
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void LScriptResponse::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const LScriptResponse* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const LScriptResponse*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void LScriptResponse::MergeFrom(const LScriptResponse& from) {
  GOOGLE_CHECK_NE(&from, this);
  responses_.MergeFrom(from.responses_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void LScriptResponse::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void LScriptResponse::CopyFrom(const LScriptResponse& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool LScriptResponse::IsInitialized() const {
  
  for (int i = 0; i < responses_size(); i++) {
    if (!this->responses(i).IsInitialized()) return false;
  }
  return true;
}

void LScriptResponse::Swap(LScriptResponse* other) {
  if (other != this) {
    responses_.Swap(&other->responses_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata LScriptResponse::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = LScriptResponse_descriptor_;
  metadata.reflection = LScriptResponse_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace LuaScriptPB

// @@protoc_insertion_point(global_scope)