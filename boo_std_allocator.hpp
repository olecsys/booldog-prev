#ifndef BOO_STD_ALLOCATOR_HPP
#define BOO_STD_ALLOCATOR_HPP
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <cstddef>
#include <limits>
#include <new>
#include <memory>

#ifndef BDOG_STD_NEW
#define BDOG_STD_NEW(size) ::operator new(size, ::std::nothrow)
#endif
#ifndef BDOG_STD_DELETE
#define BDOG_STD_DELETE(ptr) ::operator delete(ptr)
#endif

namespace booldog
{
namespace std
{
template <typename T>
class object_traits
{
public:
  typedef T type;

  template <typename U>
  struct rebind
  {
    typedef object_traits<U> other;
  };

  // Constructor
  inline explicit object_traits() {}
  inline ~object_traits() {}

  // Copy Constructor
  template <typename U>
  inline explicit object_traits(object_traits<U> const &other) { (void)other; }

  // Address of object
  inline type *address(type &obj) const { return &obj; }
  inline type const *address(type const &obj) const { return &obj; }

  // Construct object
  inline void construct(type *ptr) const
  {
    // In-place copy construct
    new (static_cast<void *>(ptr)) type();
  }
  inline void construct(type *ptr, type const &ref) const
  {
    // In-place copy construct
    new (static_cast<void *>(ptr)) type(ref);
  }

  // template <typename U, class... Args>
  // void construct(U *p, Args &&... args) { ::std::allocator<type>().construct(p, ::std::forward<Args>(args)...); }

  // Destroy object
  inline void destroy(type *ptr) const
  {
    // Call destructor
    ptr->~type();
  }
};
#define BDOG_STD_ALLOCATOR_TRAITS(T)         \
  typedef T type;                            \
  typedef type value_type;                   \
  typedef value_type *pointer;               \
  typedef value_type const *const_pointer;   \
  typedef value_type &reference;             \
  typedef value_type const &const_reference; \
  typedef ::std::size_t size_type;           \
  typedef ::std::ptrdiff_t difference_type;

template <typename T>
class heap
{
public:
  BDOG_STD_ALLOCATOR_TRAITS(T)

  template <typename U>
  struct rebind
  {
    typedef heap<U> other;
  };

  // Default Constructor
  inline explicit heap() {}
  inline ~heap() {}
  inline explicit heap(heap const &other) { (void)other; }

  // Copy Constructor
  template <typename U>
  inline explicit heap(heap<U> const &other) { (void)other; }

  // Allocate memory
  inline pointer allocate(size_type count, const_pointer /* hint */ = 0)
  {
    if (count > max_size())
    {
      throw ::std::bad_alloc();
    }
    return static_cast<pointer>(BDOG_STD_NEW(count * sizeof(type)));
  }

  // Delete memory
  inline void deallocate(pointer ptr, size_type /* count */) { BDOG_STD_DELETE(ptr); }

  // Max number of objects that can be allocated in one call
  inline size_type max_size() const
  {
    return (::std::numeric_limits<size_type>::max)() / sizeof(value_type);
  }
};
template <typename T, typename U>
inline bool operator==(heap<T> const &,
                       heap<U> const &)
{
  return true;
}
template <typename T, typename OtherAllocator>
inline bool operator==(heap<T> const &,
                       OtherAllocator const &)
{
  return false;
}

#define BDOG_STD_FORWARD_ALLOCATOR_TRAITS(C)           \
  typedef typename C::value_type value_type;           \
  typedef typename C::pointer pointer;                 \
  typedef typename C::const_pointer const_pointer;     \
  typedef typename C::reference reference;             \
  typedef typename C::const_reference const_reference; \
  typedef typename C::size_type size_type;             \
  typedef typename C::difference_type difference_type;

template <typename T, typename PolicyT = heap<T>, typename TraitsT = object_traits<T>>
class allocator : public PolicyT, public TraitsT
{
public:
  // Template parameters
  typedef PolicyT Policy;
  typedef TraitsT Traits;

  BDOG_STD_FORWARD_ALLOCATOR_TRAITS(Policy)

  template <typename U>
  struct rebind
  {
    typedef allocator<U, typename Policy::template rebind<U>::other,
                      typename Traits::template rebind<U>::other>
        other;
  };

  // Constructor
  inline explicit allocator() {}
  inline ~allocator() {}

  // Copy Constructor
  template <typename U, typename PolicyU, typename TraitsU>
  inline allocator(allocator<U, PolicyU, TraitsU> const &other) : Policy(other), Traits(other) {}
  template <typename U>
  inline allocator(allocator<U> const &other) { (void)other; }
  inline allocator(allocator const &other) : Policy(other), Traits(other) {}

  // template <typename U>
  // inline allocator<T>& operator=(const allocator<U>&)
  // {	// assign from a related MyAllocator (do nothing)
  // 	return (*this);
  // }

  // inline allocator<T, PolicyT, TraitsT> select_on_container_copy_construction() const
  // {	// return this MyAllocator
  // 	return (*this);
  // }
};

template <typename T, typename PolicyT, typename TraitsT>
inline bool operator==(allocator<T, PolicyT,
                                 TraitsT> const &lhs,
                       allocator<T,
                                 PolicyT, TraitsT> const &rhs)
{
  return operator==(static_cast<const PolicyT &>(lhs),
                    static_cast<const PolicyT &>(rhs));
}
template <typename T, typename PolicyT, typename TraitsT,
          typename U, typename PolicyU, typename TraitsU>
inline bool operator==(allocator<T, PolicyT,
                                 TraitsT> const &lhs,
                       allocator<U, PolicyU, TraitsU> const &rhs)
{
  return operator==(static_cast<const PolicyT &>(lhs),
                    static_cast<const PolicyU &>(rhs));
}
template <typename T, typename PolicyT, typename TraitsT, typename OtherAllocator>
inline bool operator==(allocator<T, PolicyT,
                                 TraitsT> const &lhs,
                       OtherAllocator const &rhs)
{
  return operator==(static_cast<const PolicyT &>(lhs), rhs);
}
template <typename T, typename PolicyT, typename TraitsT>
inline bool operator!=(allocator<T, PolicyT, TraitsT> const &lhs,
                       allocator<T, PolicyT, TraitsT> const &rhs)
{
  return !operator==(lhs, rhs);
}
template <typename T, typename PolicyT, typename TraitsT,
          typename U, typename PolicyU, typename TraitsU>
inline bool operator!=(allocator<T, PolicyT, TraitsT> const &lhs,
                       allocator<U, PolicyU, TraitsU> const &rhs)
{
  return !operator==(lhs, rhs);
}
template <typename T, typename PolicyT, typename TraitsT,
          typename OtherAllocator>
inline bool operator!=(allocator<T, PolicyT,
                                 TraitsT> const &lhs,
                       OtherAllocator const &rhs)
{
  return !operator==(lhs, rhs);
}
} // namespace std
} // namespace booldog

#endif