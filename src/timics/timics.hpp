#pragma once
#include <atomic>
#include <concepts>
#include <cstdint>
#include <functional>
#include <type_traits>
#include <vector>
namespace timics {

typedef uint32_t EntityIdx;
typedef uint32_t ComponentIdx;

template <typename T>
concept Entity = requires(T t) {
  { t.components } -> std::integral;
};

template <typename T>
concept Component = requires(T t) {
  { t.mask } -> std::integral;
};

class IComponentArray {
  public:
    virtual ~IComponentArray() = default;
};

template<Component T>
class ComponentArray : public IComponentArray {
  std::vector<T> array;
};

template<Entity E>
class ECSSystem {
  using Mask = typename std::remove_reference<decltype(E::components)>;

  const Mask mask;
  std::vector<EntityIdx> group;
};

template<Entity E>
class ECSThread {
  std::vector<E> entities;
  IComponentArray components;
  std::atomic<uint32_t> entityCount; // for lockless lookup since std::vector length could be not atomic
};

template<Entity E>
class ECSSupervisor {
  std::vector<ECSThread<E>> threads;
};

} // namespace timics
