// Copyright 2020 Daniil Rybakov <pochtaworld7@gmail.com>
#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#endif // INCLUDE_HEADER_HPP_
#include <atomic>
#include <memory>
#include <utility>
template <typename T>
class SharedPointer {
  T* PointerOnObject;
  std::atomic_size_t *CountOfPointer;
 public:
  SharedPointer();
  SharedPointer(T* ptr);
  SharedPointer(const SharedPointer& r);
  SharedPointer(SharedPointer&& r);
  ~SharedPointer();
  auto operator=(const SharedPointer& r) -> SharedPointer&;
  auto operator=(SharedPointer&& r) -> SharedPointer&;
  operator bool() const;
  auto operator*() const -> T&;
  auto operator->() const -> T*;
  auto get() -> T*;
  void reset();
  void reset(T* ptr);
  void swap(SharedPointer& r);
  auto use_count() const -> size_t;
};
template <typename T>
SharedPointer<T>::SharedPointer() {
  PointerOnObject = nullptr;
  CountOfPointer = nullptr;
}
template <typename T>
SharedPointer<T>::SharedPointer(T* ptr) {
  ptr = PointerOnObject;
  CountOfPointer = new std::atomic_size_t (1); // to stay is one
}
template <typename T>
SharedPointer<T>::SharedPointer(const SharedPointer &r) {
  PointerOnObject = r.PointerOnObject;
  CountOfPointer = nullptr;
  CountOfPointer = r.CountOfObject;
  CountOfPointer = new std::atomic_size_t(1);  // to stay is one
}
template <typename T>
SharedPointer<T>::SharedPointer(SharedPointer &&r) {}
template <class T>
SharedPointer<T>::~SharedPointer()  {
  if ((*CountOfPointer) == 0) {
    delete PointerOnObject;
    delete CountOfPointer;
  }
  else return;
}
template <typename T>
auto SharedPointer<T>::operator=(const SharedPointer &r) -> SharedPointer & {
  if (this == &r) {
    return *this;
  }
  this->~SharedPtr();
  PointerOnObject = r.PointerOnObject;
  CountOfPointer = r.CountOfObject;
  (*CountOfPointer)++;
  return *this;
}
template <typename T>
auto SharedPointer<T>::operator=(SharedPointer &&r)  -> SharedPointer & {
  if (this == &r) {
    return *this;
  }
  this->~SharedPtr();
  PointerOnObject = r.PointerOnObject;
  CountOfPointer = r.CountOfObject;
  r.PointerOnObject = nullptr;
  r.CountOfObject = nullptr;
  return *this;
}
template <typename T>
SharedPointer<T>::operator bool() const {
  if (CountOfPointer != nullptr) {
    return true;
  } else { return false; }
  }
template <typename T>
auto SharedPointer<T>::operator*() const -> T & {
  return *PointerOnObject;
}
template <typename T>
auto SharedPointer<T>::operator->() const -> T * {
  return PointerOnObject;
}
template <typename T>
auto SharedPointer<T>::get() -> T * {
  return CountOfPointer;
}
template <typename T>
void SharedPointer<T>::reset() {
  *this = std::move(SharedPointer());
}
template <typename T>
void SharedPointer<T>::reset(T *ptr) {
  *this = std::move(SharedPointer<T>(ptr));
}
template <typename T>
void SharedPointer<T>::swap(SharedPointer &r) {
  std::swap(PointerOnObject, r.PointerOnObject);
  std::swap(CountOfPointer, r.CountOfPointer);
}
template <typename T>
auto SharedPointer<T>::use_count() const -> size_t {
  return static_cast<size_t>(*CountOfPointer);
}