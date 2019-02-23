// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: push.proto

#ifndef PROTOBUF_INCLUDED_push_2eproto
#define PROTOBUF_INCLUDED_push_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_push_2eproto 

namespace protobuf_push_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[4];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_push_2eproto
namespace push {
class Cmd;
class CmdDefaultTypeInternal;
extern CmdDefaultTypeInternal _Cmd_default_instance_;
class Notify;
class NotifyDefaultTypeInternal;
extern NotifyDefaultTypeInternal _Notify_default_instance_;
class NotifyWrapper;
class NotifyWrapperDefaultTypeInternal;
extern NotifyWrapperDefaultTypeInternal _NotifyWrapper_default_instance_;
class Ret;
class RetDefaultTypeInternal;
extern RetDefaultTypeInternal _Ret_default_instance_;
}  // namespace push
namespace google {
namespace protobuf {
template<> ::push::Cmd* Arena::CreateMaybeMessage<::push::Cmd>(Arena*);
template<> ::push::Notify* Arena::CreateMaybeMessage<::push::Notify>(Arena*);
template<> ::push::NotifyWrapper* Arena::CreateMaybeMessage<::push::NotifyWrapper>(Arena*);
template<> ::push::Ret* Arena::CreateMaybeMessage<::push::Ret>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace push {

// ===================================================================

class Cmd : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:push.Cmd) */ {
 public:
  Cmd();
  virtual ~Cmd();

  Cmd(const Cmd& from);

  inline Cmd& operator=(const Cmd& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Cmd(Cmd&& from) noexcept
    : Cmd() {
    *this = ::std::move(from);
  }

  inline Cmd& operator=(Cmd&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Cmd& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Cmd* internal_default_instance() {
    return reinterpret_cast<const Cmd*>(
               &_Cmd_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(Cmd* other);
  friend void swap(Cmd& a, Cmd& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Cmd* New() const final {
    return CreateMaybeMessage<Cmd>(NULL);
  }

  Cmd* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Cmd>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Cmd& from);
  void MergeFrom(const Cmd& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Cmd* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string msg = 2;
  void clear_msg();
  static const int kMsgFieldNumber = 2;
  const ::std::string& msg() const;
  void set_msg(const ::std::string& value);
  #if LANG_CXX11
  void set_msg(::std::string&& value);
  #endif
  void set_msg(const char* value);
  void set_msg(const char* value, size_t size);
  ::std::string* mutable_msg();
  ::std::string* release_msg();
  void set_allocated_msg(::std::string* msg);

  // string device = 3;
  void clear_device();
  static const int kDeviceFieldNumber = 3;
  const ::std::string& device() const;
  void set_device(const ::std::string& value);
  #if LANG_CXX11
  void set_device(::std::string&& value);
  #endif
  void set_device(const char* value);
  void set_device(const char* value, size_t size);
  ::std::string* mutable_device();
  ::std::string* release_device();
  void set_allocated_device(::std::string* device);

  // int32 type = 1;
  void clear_type();
  static const int kTypeFieldNumber = 1;
  ::google::protobuf::int32 type() const;
  void set_type(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:push.Cmd)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr msg_;
  ::google::protobuf::internal::ArenaStringPtr device_;
  ::google::protobuf::int32 type_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_push_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class Notify : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:push.Notify) */ {
 public:
  Notify();
  virtual ~Notify();

  Notify(const Notify& from);

  inline Notify& operator=(const Notify& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Notify(Notify&& from) noexcept
    : Notify() {
    *this = ::std::move(from);
  }

  inline Notify& operator=(Notify&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Notify& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Notify* internal_default_instance() {
    return reinterpret_cast<const Notify*>(
               &_Notify_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(Notify* other);
  friend void swap(Notify& a, Notify& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Notify* New() const final {
    return CreateMaybeMessage<Notify>(NULL);
  }

  Notify* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Notify>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Notify& from);
  void MergeFrom(const Notify& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Notify* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string msg = 2;
  void clear_msg();
  static const int kMsgFieldNumber = 2;
  const ::std::string& msg() const;
  void set_msg(const ::std::string& value);
  #if LANG_CXX11
  void set_msg(::std::string&& value);
  #endif
  void set_msg(const char* value);
  void set_msg(const char* value, size_t size);
  ::std::string* mutable_msg();
  ::std::string* release_msg();
  void set_allocated_msg(::std::string* msg);

  // int32 err = 1;
  void clear_err();
  static const int kErrFieldNumber = 1;
  ::google::protobuf::int32 err() const;
  void set_err(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:push.Notify)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr msg_;
  ::google::protobuf::int32 err_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_push_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class NotifyWrapper : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:push.NotifyWrapper) */ {
 public:
  NotifyWrapper();
  virtual ~NotifyWrapper();

  NotifyWrapper(const NotifyWrapper& from);

  inline NotifyWrapper& operator=(const NotifyWrapper& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  NotifyWrapper(NotifyWrapper&& from) noexcept
    : NotifyWrapper() {
    *this = ::std::move(from);
  }

  inline NotifyWrapper& operator=(NotifyWrapper&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const NotifyWrapper& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const NotifyWrapper* internal_default_instance() {
    return reinterpret_cast<const NotifyWrapper*>(
               &_NotifyWrapper_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  void Swap(NotifyWrapper* other);
  friend void swap(NotifyWrapper& a, NotifyWrapper& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline NotifyWrapper* New() const final {
    return CreateMaybeMessage<NotifyWrapper>(NULL);
  }

  NotifyWrapper* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<NotifyWrapper>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const NotifyWrapper& from);
  void MergeFrom(const NotifyWrapper& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(NotifyWrapper* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string device = 1;
  void clear_device();
  static const int kDeviceFieldNumber = 1;
  const ::std::string& device() const;
  void set_device(const ::std::string& value);
  #if LANG_CXX11
  void set_device(::std::string&& value);
  #endif
  void set_device(const char* value);
  void set_device(const char* value, size_t size);
  ::std::string* mutable_device();
  ::std::string* release_device();
  void set_allocated_device(::std::string* device);

  // .push.Notify notify = 2;
  bool has_notify() const;
  void clear_notify();
  static const int kNotifyFieldNumber = 2;
  private:
  const ::push::Notify& _internal_notify() const;
  public:
  const ::push::Notify& notify() const;
  ::push::Notify* release_notify();
  ::push::Notify* mutable_notify();
  void set_allocated_notify(::push::Notify* notify);

  // @@protoc_insertion_point(class_scope:push.NotifyWrapper)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr device_;
  ::push::Notify* notify_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_push_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class Ret : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:push.Ret) */ {
 public:
  Ret();
  virtual ~Ret();

  Ret(const Ret& from);

  inline Ret& operator=(const Ret& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Ret(Ret&& from) noexcept
    : Ret() {
    *this = ::std::move(from);
  }

  inline Ret& operator=(Ret&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Ret& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Ret* internal_default_instance() {
    return reinterpret_cast<const Ret*>(
               &_Ret_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    3;

  void Swap(Ret* other);
  friend void swap(Ret& a, Ret& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Ret* New() const final {
    return CreateMaybeMessage<Ret>(NULL);
  }

  Ret* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Ret>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Ret& from);
  void MergeFrom(const Ret& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Ret* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string msg = 2;
  void clear_msg();
  static const int kMsgFieldNumber = 2;
  const ::std::string& msg() const;
  void set_msg(const ::std::string& value);
  #if LANG_CXX11
  void set_msg(::std::string&& value);
  #endif
  void set_msg(const char* value);
  void set_msg(const char* value, size_t size);
  ::std::string* mutable_msg();
  ::std::string* release_msg();
  void set_allocated_msg(::std::string* msg);

  // int32 err = 1;
  void clear_err();
  static const int kErrFieldNumber = 1;
  ::google::protobuf::int32 err() const;
  void set_err(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:push.Ret)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr msg_;
  ::google::protobuf::int32 err_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_push_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Cmd

// int32 type = 1;
inline void Cmd::clear_type() {
  type_ = 0;
}
inline ::google::protobuf::int32 Cmd::type() const {
  // @@protoc_insertion_point(field_get:push.Cmd.type)
  return type_;
}
inline void Cmd::set_type(::google::protobuf::int32 value) {
  
  type_ = value;
  // @@protoc_insertion_point(field_set:push.Cmd.type)
}

// string msg = 2;
inline void Cmd::clear_msg() {
  msg_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Cmd::msg() const {
  // @@protoc_insertion_point(field_get:push.Cmd.msg)
  return msg_.GetNoArena();
}
inline void Cmd::set_msg(const ::std::string& value) {
  
  msg_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:push.Cmd.msg)
}
#if LANG_CXX11
inline void Cmd::set_msg(::std::string&& value) {
  
  msg_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:push.Cmd.msg)
}
#endif
inline void Cmd::set_msg(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  msg_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:push.Cmd.msg)
}
inline void Cmd::set_msg(const char* value, size_t size) {
  
  msg_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:push.Cmd.msg)
}
inline ::std::string* Cmd::mutable_msg() {
  
  // @@protoc_insertion_point(field_mutable:push.Cmd.msg)
  return msg_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Cmd::release_msg() {
  // @@protoc_insertion_point(field_release:push.Cmd.msg)
  
  return msg_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Cmd::set_allocated_msg(::std::string* msg) {
  if (msg != NULL) {
    
  } else {
    
  }
  msg_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), msg);
  // @@protoc_insertion_point(field_set_allocated:push.Cmd.msg)
}

// string device = 3;
inline void Cmd::clear_device() {
  device_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Cmd::device() const {
  // @@protoc_insertion_point(field_get:push.Cmd.device)
  return device_.GetNoArena();
}
inline void Cmd::set_device(const ::std::string& value) {
  
  device_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:push.Cmd.device)
}
#if LANG_CXX11
inline void Cmd::set_device(::std::string&& value) {
  
  device_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:push.Cmd.device)
}
#endif
inline void Cmd::set_device(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  device_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:push.Cmd.device)
}
inline void Cmd::set_device(const char* value, size_t size) {
  
  device_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:push.Cmd.device)
}
inline ::std::string* Cmd::mutable_device() {
  
  // @@protoc_insertion_point(field_mutable:push.Cmd.device)
  return device_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Cmd::release_device() {
  // @@protoc_insertion_point(field_release:push.Cmd.device)
  
  return device_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Cmd::set_allocated_device(::std::string* device) {
  if (device != NULL) {
    
  } else {
    
  }
  device_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), device);
  // @@protoc_insertion_point(field_set_allocated:push.Cmd.device)
}

// -------------------------------------------------------------------

// Notify

// int32 err = 1;
inline void Notify::clear_err() {
  err_ = 0;
}
inline ::google::protobuf::int32 Notify::err() const {
  // @@protoc_insertion_point(field_get:push.Notify.err)
  return err_;
}
inline void Notify::set_err(::google::protobuf::int32 value) {
  
  err_ = value;
  // @@protoc_insertion_point(field_set:push.Notify.err)
}

// string msg = 2;
inline void Notify::clear_msg() {
  msg_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Notify::msg() const {
  // @@protoc_insertion_point(field_get:push.Notify.msg)
  return msg_.GetNoArena();
}
inline void Notify::set_msg(const ::std::string& value) {
  
  msg_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:push.Notify.msg)
}
#if LANG_CXX11
inline void Notify::set_msg(::std::string&& value) {
  
  msg_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:push.Notify.msg)
}
#endif
inline void Notify::set_msg(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  msg_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:push.Notify.msg)
}
inline void Notify::set_msg(const char* value, size_t size) {
  
  msg_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:push.Notify.msg)
}
inline ::std::string* Notify::mutable_msg() {
  
  // @@protoc_insertion_point(field_mutable:push.Notify.msg)
  return msg_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Notify::release_msg() {
  // @@protoc_insertion_point(field_release:push.Notify.msg)
  
  return msg_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Notify::set_allocated_msg(::std::string* msg) {
  if (msg != NULL) {
    
  } else {
    
  }
  msg_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), msg);
  // @@protoc_insertion_point(field_set_allocated:push.Notify.msg)
}

// -------------------------------------------------------------------

// NotifyWrapper

// string device = 1;
inline void NotifyWrapper::clear_device() {
  device_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& NotifyWrapper::device() const {
  // @@protoc_insertion_point(field_get:push.NotifyWrapper.device)
  return device_.GetNoArena();
}
inline void NotifyWrapper::set_device(const ::std::string& value) {
  
  device_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:push.NotifyWrapper.device)
}
#if LANG_CXX11
inline void NotifyWrapper::set_device(::std::string&& value) {
  
  device_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:push.NotifyWrapper.device)
}
#endif
inline void NotifyWrapper::set_device(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  device_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:push.NotifyWrapper.device)
}
inline void NotifyWrapper::set_device(const char* value, size_t size) {
  
  device_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:push.NotifyWrapper.device)
}
inline ::std::string* NotifyWrapper::mutable_device() {
  
  // @@protoc_insertion_point(field_mutable:push.NotifyWrapper.device)
  return device_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* NotifyWrapper::release_device() {
  // @@protoc_insertion_point(field_release:push.NotifyWrapper.device)
  
  return device_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void NotifyWrapper::set_allocated_device(::std::string* device) {
  if (device != NULL) {
    
  } else {
    
  }
  device_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), device);
  // @@protoc_insertion_point(field_set_allocated:push.NotifyWrapper.device)
}

// .push.Notify notify = 2;
inline bool NotifyWrapper::has_notify() const {
  return this != internal_default_instance() && notify_ != NULL;
}
inline void NotifyWrapper::clear_notify() {
  if (GetArenaNoVirtual() == NULL && notify_ != NULL) {
    delete notify_;
  }
  notify_ = NULL;
}
inline const ::push::Notify& NotifyWrapper::_internal_notify() const {
  return *notify_;
}
inline const ::push::Notify& NotifyWrapper::notify() const {
  const ::push::Notify* p = notify_;
  // @@protoc_insertion_point(field_get:push.NotifyWrapper.notify)
  return p != NULL ? *p : *reinterpret_cast<const ::push::Notify*>(
      &::push::_Notify_default_instance_);
}
inline ::push::Notify* NotifyWrapper::release_notify() {
  // @@protoc_insertion_point(field_release:push.NotifyWrapper.notify)
  
  ::push::Notify* temp = notify_;
  notify_ = NULL;
  return temp;
}
inline ::push::Notify* NotifyWrapper::mutable_notify() {
  
  if (notify_ == NULL) {
    auto* p = CreateMaybeMessage<::push::Notify>(GetArenaNoVirtual());
    notify_ = p;
  }
  // @@protoc_insertion_point(field_mutable:push.NotifyWrapper.notify)
  return notify_;
}
inline void NotifyWrapper::set_allocated_notify(::push::Notify* notify) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete notify_;
  }
  if (notify) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      notify = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, notify, submessage_arena);
    }
    
  } else {
    
  }
  notify_ = notify;
  // @@protoc_insertion_point(field_set_allocated:push.NotifyWrapper.notify)
}

// -------------------------------------------------------------------

// Ret

// int32 err = 1;
inline void Ret::clear_err() {
  err_ = 0;
}
inline ::google::protobuf::int32 Ret::err() const {
  // @@protoc_insertion_point(field_get:push.Ret.err)
  return err_;
}
inline void Ret::set_err(::google::protobuf::int32 value) {
  
  err_ = value;
  // @@protoc_insertion_point(field_set:push.Ret.err)
}

// string msg = 2;
inline void Ret::clear_msg() {
  msg_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Ret::msg() const {
  // @@protoc_insertion_point(field_get:push.Ret.msg)
  return msg_.GetNoArena();
}
inline void Ret::set_msg(const ::std::string& value) {
  
  msg_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:push.Ret.msg)
}
#if LANG_CXX11
inline void Ret::set_msg(::std::string&& value) {
  
  msg_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:push.Ret.msg)
}
#endif
inline void Ret::set_msg(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  msg_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:push.Ret.msg)
}
inline void Ret::set_msg(const char* value, size_t size) {
  
  msg_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:push.Ret.msg)
}
inline ::std::string* Ret::mutable_msg() {
  
  // @@protoc_insertion_point(field_mutable:push.Ret.msg)
  return msg_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Ret::release_msg() {
  // @@protoc_insertion_point(field_release:push.Ret.msg)
  
  return msg_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Ret::set_allocated_msg(::std::string* msg) {
  if (msg != NULL) {
    
  } else {
    
  }
  msg_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), msg);
  // @@protoc_insertion_point(field_set_allocated:push.Ret.msg)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace push

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_push_2eproto