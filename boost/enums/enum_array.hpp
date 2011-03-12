//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2011.
// Distributed under the Boost
// Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Based on the boost/array.hpp implementation
//
// See http://www.boost.org/libs/enums for documentation.
//
//////////////////////////////////////////////////////////////////////////////

/*!
The header <boost/enums/enum_array> defines a class template for storing
sequences of objects fixed by the size of the enumeration. We can say that
enum_array is the counterpart of std::array when the index are enums.
*/

#ifndef BOOST_ENUMS_ENUM_ARRAY_HPP
#define BOOST_ENUMS_ENUM_ARRAY_HPP

#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)  
# pragma warning(push)  
# pragma warning(disable:4996) // 'std::equal': Function call with parameters that may be unsafe
# pragma warning(disable:4510) // boost::enums::enum_array<T,EC>' : default constructor could not be generated
# pragma warning(disable:4610) // warning C4610: class 'boost::enums::enum_array<T,EC>' can never be instantiated - user defined constructor required
#endif

#include <cstddef>
#include <stdexcept>
#include <boost/assert.hpp>
#include <boost/swap.hpp>

// Handles broken standard libraries better than <iterator>
#include <boost/detail/iterator.hpp>
#include <boost/throw_exception.hpp>
#include <algorithm>

#include <boost/enums/size.hpp>
#include <boost/enums/pos.hpp>
#include <boost/type_traits/integral_constant.hpp>

// FIXES for broken compilers + CONSTEXPR
#include <boost/config.hpp>

namespace boost
{
  namespace enums
  {

    /*!
    An enum_array supports random access iterators. An instance of enum_array<T, EC>
    stores as many elements of type T as enum literals are on the enum class EC,
    so that size() == meta::size<EC>::value is an invariant.

    The elements of an enum_array are stored contiguously, meaning that if a is an
    enum_array<T, EC>, then it obeys the identity

      &a[n] == &a[0] + n for all 0 <= n <  meta::size<EC>::value.

    An enum_array is an aggregate that can (????) be initialized with the syntax

      enum_array a<T, EC> = { initializer-list };

    where initializer-list is a comma separated list of up to meta::size<EC>::value
    elements whose types are convertible to T.

    An enum_array satisfies all of the requirements of a container and of a
    reversible container, except that a default constructed array object is not
    empty and that swap does not have constant complexity. An enum_array satisfies
    some of the requirements of a sequence container. Descriptions are provided
    here only for operations on enum_array that are not described in one of these
    tables and for operations where there is additional semantic information.

    Note: The member variable elems is shown for exposition only, to emphasize
    that enum_array is a class aggregate. The name elems is not part of
    enum_array’s interface
    */

    template<class T, typename EC>
    class enum_array {
      public:
        //! // exposition only
        T elems[meta::size<EC>::value];    // fixed-size array of elements of type T
        
      public:
        // type definitions
        typedef T              value_type;
        typedef T*             iterator;
        typedef const T*       const_iterator;
        typedef T&             reference;
        typedef const T&       const_reference;
        typedef value_type*                           pointer;
        typedef const value_type*                     const_pointer;
        typedef EC             key_type;        
        typedef std::size_t    size_type;
        typedef std::ptrdiff_t difference_type;
        static const std::size_t static_size = meta::size<EC>::value;
//        enum { static_size = static_size };
        /*!
         The conditions for an aggregate are met. Class enum_array relies on
         the implicitly-declared special member functions to conform to the
         container requirements
         */

        // iterator support
        //! Returns: iterator for the first element
        //! Throws: will not throw
        iterator        begin()       { return elems; }

        //! Returns: const iterator for the first element
        //! Throws: will not throw
        const_iterator  begin() const { return elems; }
        const_iterator cbegin() const { return elems; }
        
        //! Returns: iterator for position after the last element
        //! Throws: will not throw
        iterator        end()       { return elems+static_size; }

        //! Returns: const iterator for position after the last element
        //! Throws: will not throw
        const_iterator  end() const { return elems+static_size; }
        const_iterator cend() const { return elems+static_size; }

        // reverse iterator support
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) && !defined(BOOST_MSVC_STD_ITERATOR) && !defined(BOOST_NO_STD_ITERATOR_TRAITS)
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
#elif defined(_MSC_VER) && (_MSC_VER == 1300) && defined(BOOST_DINKUMWARE_STDLIB) && (BOOST_DINKUMWARE_STDLIB == 310)
        // workaround for broken reverse_iterator in VC7
        typedef std::reverse_iterator<std::_Ptrit<value_type, difference_type, iterator,
                                      reference, iterator, reference> > reverse_iterator;
        typedef std::reverse_iterator<std::_Ptrit<value_type, difference_type, const_iterator,
                                      const_reference, iterator, reference> > const_reverse_iterator;
#elif defined(_RWSTD_NO_CLASS_PARTIAL_SPEC) 
        typedef std::reverse_iterator<iterator, std::random_access_iterator_tag, 
              value_type, reference, iterator, difference_type> reverse_iterator; 
        typedef std::reverse_iterator<const_iterator, std::random_access_iterator_tag,
              value_type, const_reference, const_iterator, difference_type> const_reverse_iterator;
#else
        // workaround for broken reverse_iterator implementations
        typedef std::reverse_iterator<iterator,T> reverse_iterator;
        typedef std::reverse_iterator<const_iterator,T> const_reverse_iterator;
#endif

        //! Returns: reverse iterator for the first element of reverse iteration
        reverse_iterator rbegin() { 
          return reverse_iterator(end()); 
        }
        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end());
        }
        const_reverse_iterator crbegin() const {
            return const_reverse_iterator(end());
        }

        //! Returns: reverse iterator for position after the last element in reverse iteration
        reverse_iterator rend() { 
          return reverse_iterator(begin()); 
        }
        const_reverse_iterator rend() const {
            return const_reverse_iterator(begin());
        }
        const_reverse_iterator crend() const {
            return const_reverse_iterator(begin());
        }

        // operator[]
        //! Requires: k'pos < static_size
        //! Returns: reference to the element with key k
        //! Throws: will not throw.
        reference operator[](key_type k) 
        { 
            size_type i = pos(k);
            BOOST_ASSERT( i < static_size && "out of range" );
            return elems[i];
        }
        
        //! Requires: k'pos < static_size
        //! Returns: constant reference to the element with key k
        //! Throws: will not throw.
        const_reference operator[](key_type k) const 
        {     
            size_type i = pos(k);
            BOOST_ASSERT( i < static_size && "out of range" );
            return elems[i]; 
        }

        // at() with range check
        //! Returns: element with key k
        //! Throws: std::range_error if i >= static_size
        reference at(key_type k) 
        {             
          size_type i = rangecheck(k); 
          return elems[i]; 
        }
        const_reference at(key_type k) const 
        { 
          size_type i = rangecheck(k); 
          return elems[i]; 
        }
    
        // front() and back()
        //! Returns: reference to the first element
        //! Throws: will not throw
        reference front() 
        { 
            return elems[0]; 
        }
        
        //! Returns: const reference to the first element
        //! Throws: will not throw
        const_reference front() const 
        {
            return elems[0];
        }
        
        //! Returns: reference to the last element
        //! Throws: will not throw
        reference back() 
        { 
            return elems[static_size-1];
        }
        
        //! Returns: const reference to the last element
        //! Throws: will not throw
        const_reference back() const 
        { 
            return elems[static_size-1];
        }

        // size is constant
        BOOST_CONSTEXPR size_type size() 
        { 
          return static_size;
        }
        //! Returns: false
        //! Throws: will not throw
        static bool empty() 
        { 
          return false; 
        }

        //! Returns: linear in meta::size<EC>::value.
        BOOST_CONSTEXPR size_type max_size() 
        { 
          return static_size;
        }


        /*! Effects: swap_ranges(begin(), end(), y.begin())
            Throws: Nothing unless one of the element-wise swap calls throws an exception.
            Note: Unlike the swap function for other containers, enum_array::swap
            takes linear time, may exit via an exception, and does not cause
            iterators to become associated with the other container.
         */
        void swap (enum_array<T,EC>& y) 
        {
            for (size_type i = 0; i < static_size; ++i)
                boost::swap(elems[i],y.elems[i]);
        }

        // direct access to data (read-only)

        //! Returns: elems.
        const T* data() const { 
          return elems; 
        }
        //! Returns: elems.
        T* data() { 
          return elems; 
        }

        // use enum_array as C array (direct read/write access to data)
        T* c_array() { 
          return elems; 
        }

        // assignment with type conversion
        template <typename T2>
        enum_array<T,EC>& operator= (const enum_array<T2,EC>& rhs) {
            std::copy(rhs.begin(),rhs.end(), begin());
            return *this;
        }

        // A synonym for fill
        // assign one value to all elements
        //! Effects: std::fill_n(begin(), static_size, value)
        void assign (const T& value) { 
          fill ( value ); 
        }

        //! Effects: fill_n(begin(), static_size, u)
        void fill   (const T& value)
        {
            std::fill_n(begin(),size(),value);
        }

        // check range (may be private because it is static)
        static size_type rangecheck (key_type k) {
            size_type i = enums::pos(k);
            if (i >= static_size) {
                std::out_of_range e("array<>: index out of range");
                boost::throw_exception(e);
            }
            return i;
        }

    };



    // comparisons
    //! Returns: std::equal(x.begin(), x.end(), y.begin())
    template<class T, typename EC>
    bool operator== (const enum_array<T,EC>& x, const enum_array<T,EC>& y) 
    {
        return std::equal(x.begin(), x.end(), y.begin());
    }

    //! Returns: std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end())
    template<class T, typename EC>
    bool operator< (const enum_array<T,EC>& x, const enum_array<T,EC>& y) 
    {
        return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());
    }

    //! Returns : !(x == y)
    template<class T, typename EC>
    bool operator!= (const enum_array<T,EC>& x, const enum_array<T,EC>& y) 
    {
        return !(x==y);
    }

    //! Returns : y < x
    template<class T, typename EC>
    bool operator> (const enum_array<T,EC>& x, const enum_array<T,EC>& y) 
    {
        return y<x;
    }
    //! Returns : !(y<x)
    template<class T, typename EC>
    bool operator<= (const enum_array<T,EC>& x, const enum_array<T,EC>& y) 
    {
        return !(y<x);
    }
    //! Returns : !(x<y)
    template<class T, typename EC>
    bool operator>= (const enum_array<T,EC>& x, const enum_array<T,EC>& y) 
    {
        return !(x<y);
    }

    // global swap()
    //! Effects:
    //! x.swap(y);
    //! Complexity: linear in meta::size<EC>::value.

    template<class T, typename EC>
    inline void swap (enum_array<T,EC>& x, enum_array<T,EC>& y) 
    {
        x.swap(y);
    }

#if defined(__SUNPRO_CC)
//    Trac ticket #4757; the Sun Solaris compiler can't handle
//    syntax like 'T(&get_c_array(boost::array<T,static_size>& arg))[static_size]'
//    
//    We can't just use this for all compilers, because the 
//        borland compilers can't handle this form. 
    namespace detail {
       template <typename T, typename EC> struct c_array
       {
           typedef T type[meta::size];
       };
    }
    
   // Specific for boost::enums::enum_array: simply returns its elems data member.
   template <typename T, typename EC>
   typename detail::c_array<T,static_size>::type& get_c_array(enum_array<T,EC>& arg)
   {
       return arg.elems;
   }

   // Specific for boost::enums::enum_array: simply returns its elems data member.
   template <typename T, typename EC>
   typename const detail::c_array<T,static_size>::type& get_c_array(const enum_array<T,EC>& arg)
   {
       return arg.elems;
   }
#else
// Specific for boost::enums::enum_array: simply returns its elems data member.
    template <typename T, typename EC>
    T(&get_c_array(enum_array<T,EC>& arg))[meta::size<EC>::value]
    {
        return arg.elems;
    }
    
    // Const version.
    template <typename T, typename EC>
    const T(&get_c_array(const enum_array<T,EC>& arg))[meta::size<EC>::value]
    {
        return arg.elems;
    }
#endif
    
#if 0
    
    template <class T, typename EC>
    class  tuple_size<enum_array<T, EC> >
        : public integral_constant<size_t, meta::size<EC>::value> 
          {};

    template <class T, typename EC>
    class  tuple_size<const enum_array<T, EC> >
        : public integral_constant<size_t, meta::size<EC>::value> 
          {};

    template <class T, typename EC, enum_type<EC>::type K>
    class  tuple_element<enum_array<T, EC> >
    {
    public:
        typedef T type;
    };

    template <class T, typename EC, enum_type<EC>::type K>
    class  tuple_element<const enum_array<T, EC> >
    {
    public:
        typedef const T type;
    };

    template <class T, typename EC, enum_type<EC>::type K>
    inline
    T&
    get(enum_array<T, EC>& a)
    {
        return a[K];
    }

    template <class T, typename EC, enum_type<EC>::type K>
    inline
    const T&
    get(const enum_array<T, EC>& a)
    {
        return a[K];
    }

    #ifndef BOOST_NO_RVALUE_REFERENCES

    template <class T, typename EC, enum_type<EC>::type K>
    T&&
    get(array<T, meta::size<EC>::value>&& a)
    {
        return boost::move(a[K]);
    }

    #endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES    
#endif

} /* namespace enums */
} /* namespace boost */


#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)  
# pragma warning(pop)  
#endif 

#endif /*BOOST_ENUMS_ENUM_ARRAY_HPP*/
