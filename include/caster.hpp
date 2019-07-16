#pragma once

#include <type_traits>
#include <utility>

namespace caster {

template <typename T>
struct casted_type {};

template <typename T>
using casted_type_t = typename casted_type<T>::type;

template <typename T, typename P = casted_type_t<T>>
static inline P& cast(T& t) {
  return reinterpret_cast<P&>(t);
}

template <typename T, typename P = casted_type_t<T>>
static inline const P& cast(const T& t) {
  return reinterpret_cast<const P&>(t);
}

template <typename T, typename P = casted_type_t<T>>
static inline P&& cast(T&& t) {
  return reinterpret_cast<P&&>(t);
}

template <typename T, typename P = casted_type_t<T>>
static inline const P&& cast(const T&& t) {
  return reinterpret_cast<const P&&>(t);
}

template <typename T, typename P = casted_type_t<T>>
static inline P* cast(T* t) {
  return reinterpret_cast<P*>(t);
}

template <typename T, typename P = casted_type_t<T>>
static inline const P* cast(const T* t) {
  return reinterpret_cast<const P*>(t);
}

template <typename T, typename P = casted_type_t<T>>
static inline P** cast(T** t) {
  return reinterpret_cast<P**>(t);
}

template <typename T, typename P = casted_type_t<T>>
static inline const P** cast(const T** t) {
  return reinterpret_cast<const P**>(t);
}

template <typename, typename = void>
struct is_castable : std::false_type {};

template <typename T>
struct is_castable<T, std::void_t<decltype(cast(*(T*)0))>> : std::true_type {};

template <typename T>
constexpr bool is_castable_v = is_castable<T>::value;

template <typename T>
static inline decltype(auto) cast_decay(T&& t) {
  if constexpr (is_castable_v<std::remove_reference_t<T>>)
    return cast(std::forward<T>(t));
  else
    return std::forward<T>(t);
}

template <typename F, typename... Args>
static inline decltype(auto) invoke(F&& f, Args&&... args) {
  if constexpr (std::is_same_v<void, decltype(std::forward<F>(f)(cast_decay(
                                         std::forward<Args>(args))...))>)
    std::forward<F>(f)(cast_decay(std::forward<Args>(args))...);
  else
    return cast_decay(
        std::forward<F>(f)(cast_decay(std::forward<Args>(args))...));
}

}  // namespace caster
