#ifndef BOO_STD_ALLOCATOR_HPP
#define BOO_STD_ALLOCATOR_HPP
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <cstddef>
#include <new>

#ifndef BOOLDOG_STD_NEW
#define BOOLDOG_STD_NEW(size) ::operator new(size, ::std::nothrow)
#endif
#ifndef BOOLDOG_STD_DELETE
#define BOOLDOG_STD_DELETE(ptr) ::operator delete(ptr)
#endif

namespace booldog {
  namespace std {
    template<typename T>
    class object_traits
    {
    public:

      typedef T type;

      template<typename U>
      struct rebind
      {
        typedef object_traits<U> other;
      };

      // Constructor
      object_traits(){}

      // Copy Constructor
      template<typename U>
      object_traits(object_traits<U> const& other){}

      // Address of object
      type* address(type& obj) const {return &obj;}
      type const* address(type const& obj) const {return &obj;}

      // Construct object
      void construct(type* ptr, type const& ref) const
      {
        // In-place copy construct
        new(ptr) type(ref);
      }

      // Destroy object
      void destroy(type* ptr) const
      {
        // Call destructor
        ptr->~type();
      }
    };
#define BOOLDOG_STD_ALLOCATOR_TRAITS(T)                \
typedef T                 type;            \
typedef type              value_type;      \
typedef value_type*       pointer;         \
typedef value_type const* const_pointer;   \
typedef value_type&       reference;       \
typedef value_type const& const_reference; \
typedef ::std::size_t       size_type;       \
typedef ::std::ptrdiff_t    difference_type;
    
    template<typename T>
    struct max_allocations {
      enum {
        value = static_cast< ::std::size_t >(-1) / sizeof(T)
      };
    };

    template<typename T>
    class heap {
    public:

      BOOLDOG_STD_ALLOCATOR_TRAITS(T)

      template<typename U>
      struct rebind {
        typedef heap<U> other;
      };

      // Default Constructor
      heap(){}

      // Copy Constructor
      template<typename U>
      heap(heap<U> const& other){}

      // Allocate memory
      pointer allocate(size_type count, const_pointer /* hint */ = 0) {
        if(count > max_size()) {
          throw ::std::bad_alloc();
        }
        return static_cast<pointer>(BOOLDOG_STD_NEW(count * sizeof(type)));
      }

      // Delete memory
      void deallocate(pointer ptr, size_type /* count */) {
        BOOLDOG_STD_DELETE(ptr);        
      }

      // Max number of objects that can be allocated in one call
      size_type max_size() const {
        return max_allocations<T>::value;
      }
    };
    #define BOOLDOG_STD_FORWARD_ALLOCATOR_TRAITS(C)                  \
typedef typename C::value_type      value_type;      \
typedef typename C::pointer         pointer;         \
typedef typename C::const_pointer   const_pointer;   \
typedef typename C::reference       reference;       \
typedef typename C::const_reference const_reference; \
typedef typename C::size_type       size_type;       \
typedef typename C::difference_type difference_type;

    template<typename T, typename PolicyT = heap<T>, typename TraitsT = object_traits<T> >
    class allocator : public PolicyT, public TraitsT {
    public:
      // Template parameters
      typedef PolicyT Policy;
      typedef TraitsT Traits;

      BOOLDOG_STD_FORWARD_ALLOCATOR_TRAITS(Policy)

      template<typename U>
      struct rebind {
        typedef allocator<U,
          typename Policy::template rebind<U>::other,
          typename Traits::template rebind<U>::other
          > other;
      };

      // Constructor
      allocator(){

      }

      // Copy Constructor
      template<typename U, typename PolicyU, typename TraitsU>
      allocator(allocator<U, PolicyU, TraitsU> const& other)
        : Policy(other), Traits(other) {          
      }
    };
  }
}

#endif