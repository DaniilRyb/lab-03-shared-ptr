// Copyright 2020 Daniil Rybakov <pochtaworld7@gmail.com>
#ifndef INCLUDE_SHAREDPOINTER_HPP_
#define INCLUDE_SHAREDPOINTER_HPP_
#endif  // INCLUDE_SHAREDPOINTER_HPP_
#include <atomic>
#include <memory>
#include <type_traits>
#include <utility>
template <typename T>
class SharedPointer {
  T* PointerOnObject;
  std::atomic_uint* CountOfPointer;

 public:
  SharedPointer();
  explicit SharedPointer(T* ptr);
  SharedPointer(const SharedPointer& r);
  SharedPointer(SharedPointer&& r) noexcept;
  ~SharedPointer();
  auto operator=(const SharedPointer& r) -> SharedPointer&;
  auto operator=(SharedPointer&& r) noexcept -> SharedPointer&;
  operator bool() const;
  auto operator*() const -> T&;
  auto operator->() const -> T*;
  auto get() -> T*;
  void reset();
  void reset(T* ptr);
  void swap(SharedPointer& r);
  auto use_count() const -> size_t;
};
template <class T>
SharedPointer<T>::SharedPointer() {
  PointerOnObject = nullptr;
  CountOfPointer = nullptr;
}
template <class T>
SharedPointer<T>::SharedPointer(T* ptr) {
  PointerOnObject = ptr;
  CountOfPointer = new std::atomic_uint{1};
}
template <class T>
SharedPointer<T>::SharedPointer(const SharedPointer& r) {
  PointerOnObject = r.PointerOnObject;
  CountOfPointer = r.CountOfPointer;
  ++(*CountOfPointer);
}
template <class T>
SharedPointer<T>::SharedPointer(SharedPointer&& r) noexcept {
  PointerOnObject = r.PointerOnObject;
  r.PointerOnObject = nullptr;
  CountOfPointer = r.CountOfPointer;
  r.CountOfPointer = nullptr;
}
template <class T>
SharedPointer<T>::~SharedPointer() {
  if (!CountOfPointer) {
    return;
  }
  if (--(*CountOfPointer) == 0) {
    delete PointerOnObject;
    delete CountOfPointer;
  }
  CountOfPointer = nullptr;
  PointerOnObject = nullptr;
}
template <class T>
auto SharedPointer<T>::operator=(const SharedPointer& r) -> SharedPointer& {
  if (this == &r) {
    return *this;
  }
  this->~SharedPointer();
  PointerOnObject = r.PointerOnObject;
  CountOfPointer = r.CountOfObject;
  ++(*CountOfPointer);
  return *this;
}
template <class T>
auto SharedPointer<T>::operator=(SharedPointer&& r) noexcept -> SharedPointer& {
  if (this == &r) {
    return *this;
  }
  this->~SharedPointer();
  PointerOnObject = r.PointerOnObject;
  CountOfPointer = r.CountOfPointer;
  r.PointerOnObject = nullptr;
  r.CountOfPointer = nullptr;
  return *this;
}
template <class T>
SharedPointer<T>::operator bool() const {
  if (CountOfPointer != nullptr) {
    return true;
  } else {
    return false;
  }
}
template <class T>
auto SharedPointer<T>::operator*() const -> T& {
  return *PointerOnObject;
}
template <class T>
auto SharedPointer<T>::operator->() const -> T* {
  return PointerOnObject;
}
template <class T>
auto SharedPointer<T>::get() -> T* {
  return PointerOnObject;
}
template <class T>
void SharedPointer<T>::reset() {
  *this = std::move(SharedPointer());
}
template <class T>
void SharedPointer<T>::reset(T* ptr) {
  *this = std::move(SharedPointer<T>(ptr));
}
template <class T>
void SharedPointer<T>::swap(SharedPointer& r) {
  std::swap(PointerOnObject, r.PointerOnObject);
  std::swap(CountOfPointer, r.CountOfPointer);
}
template <class T>
auto SharedPointer<T>::use_count() const -> size_t {
  return static_cast<size_t>(*CountOfPointer);
}
