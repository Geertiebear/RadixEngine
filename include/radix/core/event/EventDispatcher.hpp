#ifndef DISPATCHER_HPP
#define DISPATCHER_HPP

#include <functional>
#include <list>
#include <unordered_map>
#include <utility>

#include <radix/core/event/Event.hpp>

namespace radix {

class EventDispatcher {
public:
  using Callback = std::function<void(const Event&)>;
  using CallbackList = std::list<Callback>;
  using ObserverMap = std::unordered_map<EventType, CallbackList>;
  using CallbackPointer = std::pair<EventType, CallbackList::iterator>;

  class CallbackHolder final : public CallbackPointer {
  private:
    EventDispatcher *dispatcher;

  public:
    CallbackHolder() :
      dispatcher(nullptr) {
    }

    CallbackHolder(EventDispatcher *dispatcher, EventType &et, CallbackList::iterator &it) :
      CallbackPointer(et, it),
      dispatcher(dispatcher) {
    }

    // Handy call operator to directly call the callback
    void operator()(const Event &e) {
      (*second)(e);
    }

    // No copy
    CallbackHolder(CallbackHolder&) = delete;
    CallbackHolder& operator=(CallbackHolder&) = delete;

    // Allow movement
    CallbackHolder(CallbackHolder &&o) :
      CallbackPointer(o),
      dispatcher(o.dispatcher) {
      o.dispatcher = nullptr;
    }
    CallbackHolder& operator=(CallbackHolder &&o) {
      CallbackPointer::operator=(o);
      dispatcher = o.dispatcher;
      o.dispatcher = nullptr;
      return *this;
    }

    ~CallbackHolder() {
      if (dispatcher) {
        dispatcher->removeObserver(*this);
      }
    }
  };

private:
  ObserverMap observerMap;
  CallbackList wildcardObservers;

public:
  EventDispatcher();


  /* Observers */
  CallbackHolder  addObserver(EventType type, const Callback &method);
  CallbackPointer addObserverRaw(EventType type, const Callback &method);

  void removeObserver(const CallbackPointer &ptr);
  template<class... CPTypes>
  void removeObserver(CallbackPointer cb0, const CPTypes & ...cbN) {
    removeObserver(cb0);
    removeObserver(cbN...);
  }


  /* Wildcard observers */
  CallbackHolder  observeWildcard(const Callback &method);
  CallbackPointer observeWildcardRaw(const Callback &method);

  void unobserveWildcard(const CallbackPointer &ptr);
  // Templated unobserveWildcard intentionally unimplemented: wildcard is a debug feature.


  /* Event dispatching */
  void dispatch(const Event &event);
};

} /* namespace radix */
#endif /* DISPATCHER_HPP */
