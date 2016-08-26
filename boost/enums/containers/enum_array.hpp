//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2011,2015.
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
\file
\brief
The header \c <boost/enums/containers/enum_array.hpp> defines a class template for storing
sequences of objects fixed by the size of the enumeration.
We can say that
\c enum_array is the counterpart of \c std::array when the index are enums.
*/

#ifndef BOOST_ENUMS_CONTAINER_ENUM_ARRAY_HPP
#define BOOST_ENUMS_CONTAINER_ENUM_ARRAY_HPP

#include <boost/enums/config.hpp>
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

#include <boost/enums/ordinal/size.hpp>
#include <boost/enums/ordinal/pos.hpp>
#include <boost/type_traits/integral_constant.hpp>

// FIXES for broken compilers + CONSTEXPR
#include <boost/config.hpp>

namespace boost
{
  namespace enums
  {

    /*!
    An \c enum_array supports random access iterators. An instance of \c enum_array<T, EC>
    stores as many elements of type \c T as enum literals are on the ordinal enum \c EC,
    so that <tt>size() == meta::size<EC>::value</tt> is an invariant.

    The elements of an \c enum_array are stored contiguously, meaning that if \c a is an
    \c enum_array<T, EC>, then it obeys the identity

     \code
     &a[n] == &a[0] + n for all 0 <= n <  meta::size<EC>::value.
     \endcode

    An \c enum_array is an aggregate that can (????) be initialized with the syntax

     \code
      enum_array<T, EC> a = { initializer-list };
     \endcode

    where \e initializer-list is a comma separated list of up to \c meta::size<EC>::value
    elements whose types are convertible to \c T.

    An \c enum_array satisfies all of the requirements of a container and of a
    reversible container, except that a default constructed array object is not
    empty and that swap does not have constant complexity. An \c enum_array satisfies
    some of the requirements of a sequence container. Descriptions are provided
    here only for operations on enum_array that are not described in one of these
    tables and for operations where there is additional semantic information.

     The conditions for an aggregate are met. Class enum_array relies on
     the implicitly-declared special member functions to conform to the
     container requirements



    @Note The member variable elems is shown for exposition only, to emphasize
    that enum_array is a class aggregate. The name elems is not part of
    enum_array's interface.
    @TParams
    @Param{T,array's element type}
    @Param{EC,array's index ordinal enum}
  */

    template<class T, typename EC>
    class enum_array {
      public:
        //! For exposition only
        T elems[meta::size<EC>::value];    //! fixed-size array of elements of type T

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
        //enum_array() {}

        // iterator support
        //! @Returns iterator for the first element
        //! @Throws Nothing
        BOOST_ENUMS_CXX14_MUTABLE_CONSTEXPR iterator        begin() BOOST_NOEXCEPT     { return elems; }

        //! @Returns const iterator for the first element
        //! @Throws Nothing
        BOOST_CONSTEXPR const_iterator  begin() const BOOST_NOEXCEPT { return elems; }
        BOOST_CONSTEXPR const_iterator cbegin() const BOOST_NOEXCEPT { return elems; }

        //! @Returns iterator for position after the last element
        //! @Throws Nothing
        BOOST_ENUMS_CXX14_MUTABLE_CONSTEXPR iterator        end() BOOST_NOEXCEPT      { return elems+static_size; }

        //! @Returns const iterator for position after the last element
        //! @Throws Nothing
        BOOST_CONSTEXPR const_iterator  end() const BOOST_NOEXCEPT { return elems+static_size; }
        BOOST_CONSTEXPR const_iterator cend() const BOOST_NOEXCEPT { return elems+static_size; }

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

        //! @Returns reverse iterator for the first element of reverse iteration
        BOOST_ENUMS_CXX14_MUTABLE_CONSTEXPR reverse_iterator rbegin() BOOST_NOEXCEPT {
          return reverse_iterator(end());
        }
        BOOST_CONSTEXPR const_reverse_iterator rbegin() const BOOST_NOEXCEPT {
            return const_reverse_iterator(end());
        }
        BOOST_CONSTEXPR const_reverse_iterator crbegin() const BOOST_NOEXCEPT {
            return const_reverse_iterator(end());
        }

        //! @Returns reverse iterator for position after the last element in reverse iteration
        BOOST_ENUMS_CXX14_MUTABLE_CONSTEXPR reverse_iterator rend() BOOST_NOEXCEPT {
          return reverse_iterator(begin());
        }
        BOOST_CONSTEXPR const_reverse_iterator rend() const BOOST_NOEXCEPT {
            return const_reverse_iterator(begin());
        }
        BOOST_CONSTEXPR const_reverse_iterator crend() const BOOST_NOEXCEPT {
            return const_reverse_iterator(begin());
        }

        // operator[]
        //! @Requires <tt>k'pos < static_size</tt>
        //! @Returns reference to the element with key @c k
        //! @Throws Nothing.
        BOOST_ENUMS_CXX14_MUTABLE_CONSTEXPR reference operator[](key_type k)
        {
            size_type i = pos(k);
            BOOST_ASSERT( i < static_size && "out of range" );
            return elems[i];
        }

        //! @Requires <tt>k'pos < static_size</tt>
        //! @Returns constant reference to the element with key k
        //! @Throws Nothing.
        BOOST_CONSTEXPR const_reference operator[](key_type k) const
        {
#if  ! defined BOOST_NO_CXX14_CONSTEXPR
            BOOST_ASSERT( pos(k) < static_size && "out of range" );
#endif
            return elems[pos(k)];
        }

        // at() with range check
        //! @Returns element with key k
        //! @Throws std::range_error if i >= static_size
        BOOST_ENUMS_CXX14_MUTABLE_CONSTEXPR reference at(key_type k)
        {
          return elems[rangecheck(k)];
        }
        BOOST_CONSTEXPR const_reference at(key_type k) const
        {
          return elems[rangecheck(k)];
        }

        // front() and back()
        //! @Returns reference to the first element
        //! @Throws Nothing
        BOOST_ENUMS_CXX14_MUTABLE_CONSTEXPR reference front() BOOST_NOEXCEPT
        {
            return elems[0];
        }

        //! @Returns const reference to the first element
        //! @Throws Nothing
        BOOST_CONSTEXPR const_reference front() const BOOST_NOEXCEPT
        {
            return elems[0];
        }

        //! @Returns reference to the last element
        //! @Throws Nothing
        BOOST_ENUMS_CXX14_MUTABLE_CONSTEXPR reference back() BOOST_NOEXCEPT
        {
            return elems[static_size-1];
        }

        //! @Returns const reference to the last element
        //! @Throws Nothing
        BOOST_CONSTEXPR const_reference back() const BOOST_NOEXCEPT
        {
            return elems[static_size-1];
        }

        // size is constant
        //! @Returns linear in meta::size<EC>::value.
        BOOST_CONSTEXPR size_type size() const BOOST_NOEXCEPT
        {
          return static_size;
        }
        //! @Returns false
        //! @Throws Nothing
        BOOST_CONSTEXPR  bool empty() const BOOST_NOEXCEPT
        {
          return false;
        }

        //! @Returns linear in meta::size<EC>::value.
        BOOST_CONSTEXPR size_type max_size() const BOOST_NOEXCEPT
        {
          return static_size;
        }


        /*! @Effects <tt>swap_ranges(begin(), end(), y.begin())</tt>
            @Throws Nothing unless one of the element-wise swap calls throws an exception.
            Note: Unlike the @c swap function for other containers, @c enum_array::swap
            takes linear time, may exit via an exception, and does not cause
            iterators to become associated with the other container.
         */
        void swap (enum_array<T,EC>& y) // BOOST_NOEXCEPT_IF(std::is_nothrow_swappable_v<T>)
        {
            for (size_type i = 0; i < static_size; ++i)
                boost::swap(elems[i],y.elems[i]);
        }

        //! direct access to data (read-only)

        //! @Returns elems.
        BOOST_CONSTEXPR const T* data() const {
          return elems;
        }
        //! @Returns elems.
        BOOST_ENUMS_CXX14_MUTABLE_CONSTEXPR T* data() {
          return elems;
        }

        //! use @c enum_array as C array (direct read/write access to data)
        T* c_array() {
          return elems;
        }

        //! assignment with type conversion
        template <typename T2>
        enum_array<T,EC>& operator= (const enum_array<T2,EC>& rhs) {
            std::copy(rhs.begin(),rhs.end(), begin());
            return *this;
        }

        //! A synonym for fill
        //! assign one value to all elements
        //! @Effects <tt>std::fill_n(begin(), static_size, value)</tt>
        void assign (const T& value) {
          fill ( value );
        }

        //! @Effects <tt>fill_n(begin(), static_size, u)</tt>
        void fill   (const T& value)
        {
            std::fill_n(begin(),size(),value);
        }

        //! check range (may be private because it is static)
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
    //! @Returns <tt>std::equal(x.begin(), x.end(), y.begin())</tt>
    template<class T, typename EC>
    bool operator== (const enum_array<T,EC>& x, const enum_array<T,EC>& y)
    {
        return std::equal(x.begin(), x.end(), y.begin());
    }

    //! @Returns <tt>std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end())</tt>
    template<class T, typename EC>
    bool operator< (const enum_array<T,EC>& x, const enum_array<T,EC>& y)
    {
        return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());
    }

    //! @Returns <tt>!(x == y)</tt>
    template<class T, typename EC>
    bool operator!= (const enum_array<T,EC>& x, const enum_array<T,EC>& y)
    {
        return !(x==y);
    }

    //! @Returns <tt>y < x</tt>
    template<class T, typename EC>
    bool operator> (const enum_array<T,EC>& x, const enum_array<T,EC>& y)
    {
        return y<x;
    }
    //! @Returns <tt>!(y<x)</tt>
    template<class T, typename EC>
    bool operator<= (const enum_array<T,EC>& x, const enum_array<T,EC>& y)
    {
        return !(y<x);
    }
    //! @Returns <tt>!(x<y)</tt>
    template<class T, typename EC>
    bool operator>= (const enum_array<T,EC>& x, const enum_array<T,EC>& y)
    {
        return !(x<y);
    }

    //! enum_array's swap

    //! <b>@Effects</b> As
    //! \code
    //!  x.swap(y);
    //! \endcode
    //! <b>Complexity:</b> linear in \c meta::size<EC>::value.

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
    template <typename T, typename EC>
    T(&get_c_array(enum_array<T,EC>& arg))[meta::size<EC>::value]
    {
        //! c_array conversion.
        return arg.elems;
    }

    template <typename T, typename EC>
    const T(&get_c_array(const enum_array<T,EC>& arg))[meta::size<EC>::value]
    {
        //! c_array const conversion.
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

    template <class T, typename EC, native_type<EC>::type K>
    class  tuple_element<enum_array<T, EC> >
    {
    public:
        typedef T type;
    };

    template <class T, typename EC, native_type<EC>::type K>
    class  tuple_element<const enum_array<T, EC> >
    {
    public:
        typedef const T type;
    };

    template <class T, typename EC, native_type<EC>::type K>
    inline
    T&
    get(enum_array<T, EC>& a)
    {
        return a[K];
    }

    template <class T, typename EC, native_type<EC>::type K>
    inline
    const T&
    get(const enum_array<T, EC>& a)
    {
        return a[K];
    }

    #ifndef BOOST_NO_RVALUE_REFERENCES

    template <class T, typename EC, native_type<EC>::type K>
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

#endif // BOOST_ENUMS_CONTAINER_ENUM_ARRAY_HPP
