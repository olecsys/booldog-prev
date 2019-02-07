#ifndef BOO_STD_ALLOCATOR_HPP
#define BOO_STD_ALLOCATOR_HPP
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <cstddef>
#include <new>

#ifndef BDOG_STD_NEW
#define BDOG_STD_NEW(size) ::operator new(size, ::std::nothrow)
#endif
#ifndef BDOG_STD_DELETE
#define BDOG_STD_DELETE(ptr) ::operator delete(ptr)
#endif

namespace booldog {
  namespace std {
    template <typename T> class object_traits {
    public:
      typedef T type;

      template <typename U> struct rebind { typedef object_traits<U> other; };

      // Constructor
      object_traits() {}

      // Copy Constructor
      template <typename U> object_traits(object_traits<U> const& other) { (void)other; }

      // Address of object
      type* address(type& obj) const { return &obj; }
      type const* address(type const& obj) const { return &obj; }

      // Construct object
      void construct(type* ptr, type const& ref) const {
        // In-place copy construct
        new(ptr) type(ref);
      }

      // Destroy object
      void destroy(type* ptr) const {
        // Call destructor
        ptr->~type();
      }
    };
#define BDOG_STD_ALLOCATOR_TRAITS(T)                                                               \
  typedef T type;                                                                                  \
  typedef type value_type;                                                                         \
  typedef value_type* pointer;                                                                     \
  typedef value_type const* const_pointer;                                                         \
  typedef value_type& reference;                                                                   \
  typedef value_type const& const_reference;                                                       \
  typedef ::std::size_t size_type;                                                                 \
  typedef ::std::ptrdiff_t difference_type;

    template <typename T> struct max_allocations {
      enum { value = static_cast< ::std::size_t>(-1) / sizeof(T) };
    };

    template <typename T> class heap {
    public:
      BDOG_STD_ALLOCATOR_TRAITS(T)

      template <typename U> struct rebind { typedef heap<U> other; };

      // Default Constructor
      heap() {}

      // Copy Constructor
      template <typename U> heap(heap<U> const& other) { (void)other; }

      // Allocate memory
      pointer allocate(size_type count, const_pointer /* hint */ = 0) {
        if(count > max_size()) {
          throw ::std::bad_alloc();
        }
        return static_cast<pointer>(BDOG_STD_NEW(count * sizeof(type)));
      }

      // Delete memory
      void deallocate(pointer ptr, size_type /* count */) { BDOG_STD_DELETE(ptr); }

      // Max number of objects that can be allocated in one call
      size_type max_size() const { return max_allocations<T>::value; }
    };
#define BDOG_STD_FORWARD_ALLOCATOR_TRAITS(C)                                                       \
  typedef typename C::value_type value_type;                                                       \
  typedef typename C::pointer pointer;                                                             \
  typedef typename C::const_pointer const_pointer;                                                 \
  typedef typename C::reference reference;                                                         \
  typedef typename C::const_reference const_reference;                                             \
  typedef typename C::size_type size_type;                                                         \
  typedef typename C::difference_type difference_type;

    template <typename T, typename PolicyT = heap<T>, typename TraitsT = object_traits<T> >
    class allocator : public PolicyT, public TraitsT {
    public:
      // Template parameters
      typedef PolicyT Policy;
      typedef TraitsT Traits;

      BDOG_STD_FORWARD_ALLOCATOR_TRAITS(Policy)

      template <typename U> struct rebind {
        typedef allocator<U, typename Policy::template rebind<U>::other,
                          typename Traits::template rebind<U>::other>
          other;
      };

      // Constructor
      allocator() {}

      // Copy Constructor
      template <typename U, typename PolicyU, typename TraitsU>
      allocator(allocator<U, PolicyU, TraitsU> const& other) : Policy(other), Traits(other) {}
    };
  } // namespace std
} // namespace booldog

template <typename T, typename PolicyT, typename TraitsT, typename U, typename PolicyU,
          typename TraitsU>
bool operator==(booldog::std::allocator<T, PolicyT, TraitsT> const& left,
                booldog::std::allocator<U, PolicyU, TraitsU> const& right) {
  return false;
}

// Also implement inequality
template <typename T, typename PolicyT, typename TraitsT, typename U, typename PolicyU,
          typename TraitsU>
bool operator!=(booldog::std::allocator<T, PolicyT, TraitsT> const& left,
                booldog::std::allocator<U, PolicyU, TraitsU> const& right) {
  return !(left == right);
}

// Comparing an allocator to anything else should not show equality
template <typename T, typename PolicyT, typename TraitsT, typename OtherAllocator>
bool operator==(booldog::std::allocator<T, PolicyT, TraitsT> const& left,
                OtherAllocator const& right) {
  return false;
}

// Also implement inequality
template <typename T, typename PolicyT, typename TraitsT, typename OtherAllocator>
bool operator!=(booldog::std::allocator<T, PolicyT, TraitsT> const& left,
                OtherAllocator const& right) {
  return !(left == right);
}

// Specialize for the heap policy
template <typename T, typename TraitsT, typename U, typename TraitsU>
bool operator==(booldog::std::allocator<T, booldog::std::heap<T>, TraitsT> const& left,
                booldog::std::allocator<U, booldog::std::heap<U>, TraitsU> const& right) {
  return true;
}

// Also implement inequality
template <typename T, typename TraitsT, typename U, typename TraitsU>
bool operator!=(booldog::std::allocator<T, booldog::std::heap<T>, TraitsT> const& left,
                booldog::std::allocator<U, booldog::std::heap<U>, TraitsU> const& right) {
  return !(left == right);
}

#endif