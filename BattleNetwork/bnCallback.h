#pragma once
#include <functional>

template<typename FnSig>
class Callback {
  std::function<FnSig> slot;
  bool use = false;
public:
  Callback() {
  }

  ~Callback() = default;

  void Slot(decltype(slot) slot) {
    Callback::slot = slot;
    use = true;
  }

  void Reset() {
    use = false;
  }

  void operator()() { if (!use) return;  slot ? slot() : 0; }
};