// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ScriptPB.proto

#ifndef PROTOBUF_ScriptPB_2eproto__INCLUDED
#define PROTOBUF_ScriptPB_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

namespace LuaScriptPB {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ScriptPB_2eproto();
void protobuf_AssignDesc_ScriptPB_2eproto();
void protobuf_ShutdownFile_ScriptPB_2eproto();

class LScriptRequest;
class LScriptRequest_call;
class LScriptResponse;
class LScriptResponse_result;

// ===================================================================

class LScriptRequest_call : public ::google::protobuf::Message {
 public:
  LScriptRequest_call();
  virtual ~LScriptRequest_call();
  
  LScriptRequest_call(const LScriptRequest_call& from);
  
  inline LScriptRequest_call& operator=(const LScriptRequest_call& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const LScriptRequest_call& default_instance();
  
  void Swap(LScriptRequest_call* other);
  
  // implements Message ----------------------------------------------
  
  LScriptRequest_call* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const LScriptRequest_call& from);
  void MergeFrom(const LScriptRequest_call& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required int32 scriptNo = 1;
  inline bool has_scriptno() const;
  inline void clear_scriptno();
  static const int kScriptNoFieldNumber = 1;
  inline ::google::protobuf::int32 scriptno() const;
  inline void set_scriptno(::google::protobuf::int32 value);
  
  // required int32 RepeateTime = 2 [default = 1];
  inline bool has_repeatetime() const;
  inline void clear_repeatetime();
  static const int kRepeateTimeFieldNumber = 2;
  inline ::google::protobuf::int32 repeatetime() const;
  inline void set_repeatetime(::google::protobuf::int32 value);
  
  // required string content = 3;
  inline bool has_content() const;
  inline void clear_content();
  static const int kContentFieldNumber = 3;
  inline const ::std::string& content() const;
  inline void set_content(const ::std::string& value);
  inline void set_content(const char* value);
  inline void set_content(const char* value, size_t size);
  inline ::std::string* mutable_content();
  inline ::std::string* release_content();
  
  // @@protoc_insertion_point(class_scope:LuaScriptPB.LScriptRequest.call)
 private:
  inline void set_has_scriptno();
  inline void clear_has_scriptno();
  inline void set_has_repeatetime();
  inline void clear_has_repeatetime();
  inline void set_has_content();
  inline void clear_has_content();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::int32 scriptno_;
  ::google::protobuf::int32 repeatetime_;
  ::std::string* content_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_ScriptPB_2eproto();
  friend void protobuf_AssignDesc_ScriptPB_2eproto();
  friend void protobuf_ShutdownFile_ScriptPB_2eproto();
  
  void InitAsDefaultInstance();
  static LScriptRequest_call* default_instance_;
};
// -------------------------------------------------------------------

class LScriptRequest : public ::google::protobuf::Message {
 public:
  LScriptRequest();
  virtual ~LScriptRequest();
  
  LScriptRequest(const LScriptRequest& from);
  
  inline LScriptRequest& operator=(const LScriptRequest& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const LScriptRequest& default_instance();
  
  void Swap(LScriptRequest* other);
  
  // implements Message ----------------------------------------------
  
  LScriptRequest* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const LScriptRequest& from);
  void MergeFrom(const LScriptRequest& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  typedef LScriptRequest_call call;
  
  // accessors -------------------------------------------------------
  
  // repeated .LuaScriptPB.LScriptRequest.call requests = 1;
  inline int requests_size() const;
  inline void clear_requests();
  static const int kRequestsFieldNumber = 1;
  inline const ::LuaScriptPB::LScriptRequest_call& requests(int index) const;
  inline ::LuaScriptPB::LScriptRequest_call* mutable_requests(int index);
  inline ::LuaScriptPB::LScriptRequest_call* add_requests();
  inline const ::google::protobuf::RepeatedPtrField< ::LuaScriptPB::LScriptRequest_call >&
      requests() const;
  inline ::google::protobuf::RepeatedPtrField< ::LuaScriptPB::LScriptRequest_call >*
      mutable_requests();
  
  // @@protoc_insertion_point(class_scope:LuaScriptPB.LScriptRequest)
 private:
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::LuaScriptPB::LScriptRequest_call > requests_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_ScriptPB_2eproto();
  friend void protobuf_AssignDesc_ScriptPB_2eproto();
  friend void protobuf_ShutdownFile_ScriptPB_2eproto();
  
  void InitAsDefaultInstance();
  static LScriptRequest* default_instance_;
};
// -------------------------------------------------------------------

class LScriptResponse_result : public ::google::protobuf::Message {
 public:
  LScriptResponse_result();
  virtual ~LScriptResponse_result();
  
  LScriptResponse_result(const LScriptResponse_result& from);
  
  inline LScriptResponse_result& operator=(const LScriptResponse_result& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const LScriptResponse_result& default_instance();
  
  void Swap(LScriptResponse_result* other);
  
  // implements Message ----------------------------------------------
  
  LScriptResponse_result* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const LScriptResponse_result& from);
  void MergeFrom(const LScriptResponse_result& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required int32 scriptNo = 1;
  inline bool has_scriptno() const;
  inline void clear_scriptno();
  static const int kScriptNoFieldNumber = 1;
  inline ::google::protobuf::int32 scriptno() const;
  inline void set_scriptno(::google::protobuf::int32 value);
  
  // required string content = 2;
  inline bool has_content() const;
  inline void clear_content();
  static const int kContentFieldNumber = 2;
  inline const ::std::string& content() const;
  inline void set_content(const ::std::string& value);
  inline void set_content(const char* value);
  inline void set_content(const char* value, size_t size);
  inline ::std::string* mutable_content();
  inline ::std::string* release_content();
  
  // @@protoc_insertion_point(class_scope:LuaScriptPB.LScriptResponse.result)
 private:
  inline void set_has_scriptno();
  inline void clear_has_scriptno();
  inline void set_has_content();
  inline void clear_has_content();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* content_;
  ::google::protobuf::int32 scriptno_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_ScriptPB_2eproto();
  friend void protobuf_AssignDesc_ScriptPB_2eproto();
  friend void protobuf_ShutdownFile_ScriptPB_2eproto();
  
  void InitAsDefaultInstance();
  static LScriptResponse_result* default_instance_;
};
// -------------------------------------------------------------------

class LScriptResponse : public ::google::protobuf::Message {
 public:
  LScriptResponse();
  virtual ~LScriptResponse();
  
  LScriptResponse(const LScriptResponse& from);
  
  inline LScriptResponse& operator=(const LScriptResponse& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const LScriptResponse& default_instance();
  
  void Swap(LScriptResponse* other);
  
  // implements Message ----------------------------------------------
  
  LScriptResponse* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const LScriptResponse& from);
  void MergeFrom(const LScriptResponse& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  typedef LScriptResponse_result result;
  
  // accessors -------------------------------------------------------
  
  // repeated .LuaScriptPB.LScriptResponse.result responses = 1;
  inline int responses_size() const;
  inline void clear_responses();
  static const int kResponsesFieldNumber = 1;
  inline const ::LuaScriptPB::LScriptResponse_result& responses(int index) const;
  inline ::LuaScriptPB::LScriptResponse_result* mutable_responses(int index);
  inline ::LuaScriptPB::LScriptResponse_result* add_responses();
  inline const ::google::protobuf::RepeatedPtrField< ::LuaScriptPB::LScriptResponse_result >&
      responses() const;
  inline ::google::protobuf::RepeatedPtrField< ::LuaScriptPB::LScriptResponse_result >*
      mutable_responses();
  
  // @@protoc_insertion_point(class_scope:LuaScriptPB.LScriptResponse)
 private:
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::LuaScriptPB::LScriptResponse_result > responses_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_ScriptPB_2eproto();
  friend void protobuf_AssignDesc_ScriptPB_2eproto();
  friend void protobuf_ShutdownFile_ScriptPB_2eproto();
  
  void InitAsDefaultInstance();
  static LScriptResponse* default_instance_;
};
// ===================================================================


// ===================================================================

// LScriptRequest_call

// required int32 scriptNo = 1;
inline bool LScriptRequest_call::has_scriptno() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void LScriptRequest_call::set_has_scriptno() {
  _has_bits_[0] |= 0x00000001u;
}
inline void LScriptRequest_call::clear_has_scriptno() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void LScriptRequest_call::clear_scriptno() {
  scriptno_ = 0;
  clear_has_scriptno();
}
inline ::google::protobuf::int32 LScriptRequest_call::scriptno() const {
  return scriptno_;
}
inline void LScriptRequest_call::set_scriptno(::google::protobuf::int32 value) {
  set_has_scriptno();
  scriptno_ = value;
}

// required int32 RepeateTime = 2 [default = 1];
inline bool LScriptRequest_call::has_repeatetime() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void LScriptRequest_call::set_has_repeatetime() {
  _has_bits_[0] |= 0x00000002u;
}
inline void LScriptRequest_call::clear_has_repeatetime() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void LScriptRequest_call::clear_repeatetime() {
  repeatetime_ = 1;
  clear_has_repeatetime();
}
inline ::google::protobuf::int32 LScriptRequest_call::repeatetime() const {
  return repeatetime_;
}
inline void LScriptRequest_call::set_repeatetime(::google::protobuf::int32 value) {
  set_has_repeatetime();
  repeatetime_ = value;
}

// required string content = 3;
inline bool LScriptRequest_call::has_content() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void LScriptRequest_call::set_has_content() {
  _has_bits_[0] |= 0x00000004u;
}
inline void LScriptRequest_call::clear_has_content() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void LScriptRequest_call::clear_content() {
  if (content_ != &::google::protobuf::internal::kEmptyString) {
    content_->clear();
  }
  clear_has_content();
}
inline const ::std::string& LScriptRequest_call::content() const {
  return *content_;
}
inline void LScriptRequest_call::set_content(const ::std::string& value) {
  set_has_content();
  if (content_ == &::google::protobuf::internal::kEmptyString) {
    content_ = new ::std::string;
  }
  content_->assign(value);
}
inline void LScriptRequest_call::set_content(const char* value) {
  set_has_content();
  if (content_ == &::google::protobuf::internal::kEmptyString) {
    content_ = new ::std::string;
  }
  content_->assign(value);
}
inline void LScriptRequest_call::set_content(const char* value, size_t size) {
  set_has_content();
  if (content_ == &::google::protobuf::internal::kEmptyString) {
    content_ = new ::std::string;
  }
  content_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* LScriptRequest_call::mutable_content() {
  set_has_content();
  if (content_ == &::google::protobuf::internal::kEmptyString) {
    content_ = new ::std::string;
  }
  return content_;
}
inline ::std::string* LScriptRequest_call::release_content() {
  clear_has_content();
  if (content_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = content_;
    content_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// -------------------------------------------------------------------

// LScriptRequest

// repeated .LuaScriptPB.LScriptRequest.call requests = 1;
inline int LScriptRequest::requests_size() const {
  return requests_.size();
}
inline void LScriptRequest::clear_requests() {
  requests_.Clear();
}
inline const ::LuaScriptPB::LScriptRequest_call& LScriptRequest::requests(int index) const {
  return requests_.Get(index);
}
inline ::LuaScriptPB::LScriptRequest_call* LScriptRequest::mutable_requests(int index) {
  return requests_.Mutable(index);
}
inline ::LuaScriptPB::LScriptRequest_call* LScriptRequest::add_requests() {
  return requests_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::LuaScriptPB::LScriptRequest_call >&
LScriptRequest::requests() const {
  return requests_;
}
inline ::google::protobuf::RepeatedPtrField< ::LuaScriptPB::LScriptRequest_call >*
LScriptRequest::mutable_requests() {
  return &requests_;
}

// -------------------------------------------------------------------

// LScriptResponse_result

// required int32 scriptNo = 1;
inline bool LScriptResponse_result::has_scriptno() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void LScriptResponse_result::set_has_scriptno() {
  _has_bits_[0] |= 0x00000001u;
}
inline void LScriptResponse_result::clear_has_scriptno() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void LScriptResponse_result::clear_scriptno() {
  scriptno_ = 0;
  clear_has_scriptno();
}
inline ::google::protobuf::int32 LScriptResponse_result::scriptno() const {
  return scriptno_;
}
inline void LScriptResponse_result::set_scriptno(::google::protobuf::int32 value) {
  set_has_scriptno();
  scriptno_ = value;
}

// required string content = 2;
inline bool LScriptResponse_result::has_content() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void LScriptResponse_result::set_has_content() {
  _has_bits_[0] |= 0x00000002u;
}
inline void LScriptResponse_result::clear_has_content() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void LScriptResponse_result::clear_content() {
  if (content_ != &::google::protobuf::internal::kEmptyString) {
    content_->clear();
  }
  clear_has_content();
}
inline const ::std::string& LScriptResponse_result::content() const {
  return *content_;
}
inline void LScriptResponse_result::set_content(const ::std::string& value) {
  set_has_content();
  if (content_ == &::google::protobuf::internal::kEmptyString) {
    content_ = new ::std::string;
  }
  content_->assign(value);
}
inline void LScriptResponse_result::set_content(const char* value) {
  set_has_content();
  if (content_ == &::google::protobuf::internal::kEmptyString) {
    content_ = new ::std::string;
  }
  content_->assign(value);
}
inline void LScriptResponse_result::set_content(const char* value, size_t size) {
  set_has_content();
  if (content_ == &::google::protobuf::internal::kEmptyString) {
    content_ = new ::std::string;
  }
  content_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* LScriptResponse_result::mutable_content() {
  set_has_content();
  if (content_ == &::google::protobuf::internal::kEmptyString) {
    content_ = new ::std::string;
  }
  return content_;
}
inline ::std::string* LScriptResponse_result::release_content() {
  clear_has_content();
  if (content_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = content_;
    content_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// -------------------------------------------------------------------

// LScriptResponse

// repeated .LuaScriptPB.LScriptResponse.result responses = 1;
inline int LScriptResponse::responses_size() const {
  return responses_.size();
}
inline void LScriptResponse::clear_responses() {
  responses_.Clear();
}
inline const ::LuaScriptPB::LScriptResponse_result& LScriptResponse::responses(int index) const {
  return responses_.Get(index);
}
inline ::LuaScriptPB::LScriptResponse_result* LScriptResponse::mutable_responses(int index) {
  return responses_.Mutable(index);
}
inline ::LuaScriptPB::LScriptResponse_result* LScriptResponse::add_responses() {
  return responses_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::LuaScriptPB::LScriptResponse_result >&
LScriptResponse::responses() const {
  return responses_;
}
inline ::google::protobuf::RepeatedPtrField< ::LuaScriptPB::LScriptResponse_result >*
LScriptResponse::mutable_responses() {
  return &responses_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace LuaScriptPB

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ScriptPB_2eproto__INCLUDED