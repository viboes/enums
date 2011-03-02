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

#ifndef BOOST_ENUMS_ENUM_ARRAY_HPP
#define BOOST_ENUMS_ENUM_ARRAY_HPP

#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)  
# pragma warning(push)  
# pragma warning(disable:4996) // 'std::equal': Function call with parameters that may be unsafe
# pragma warning(disable:4510) // boost::enums::enum_array<T,N>' : default constructor could not be generated 
# pragma warning(disable:4610) // warning C4610: class 'boost::enums::enum_array<T,N>' can never be instantiated - user defined constructor required 
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
//#include <boost/tuples.hpp>
#include <boost/type_traits/integral_constant.hpp>

// FIXES for broken compilers
#include <boost/config.hpp>


namespace boost {
namespace enums {

    template<class T, typename EC>
    class enum_array {
      public:
        T elems[enums::meta::size<EC>::value];    // fixed-size array of elements of type T
        
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
        static const std::size_t N = enums::meta::size<EC>::value;

        // iterator support
        iterator        begin()       { return elems; }
        const_iterator  begin() const { return elems; }
        const_iterator cbegin() const { return elems; }
        
        iterator        end()       { return elems+N; }
        const_iterator  end() const { return elems+N; }
        const_iterator cend() const { return elems+N; }

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

        reverse_iterator rbegin() { return reverse_iterator(end()); }
        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end());
        }
        const_reverse_iterator crbegin() const {
            return const_reverse_iterator(end());
        }

        reverse_iterator rend() { return reverse_iterator(begin()); }
        const_reverse_iterator rend() const {
            return const_reverse_iterator(begin());
        }
        const_reverse_iterator crend() const {
            return const_reverse_iterator(begin());
        }

        // operator[]
        reference operator[](key_type k) 
        { 
            size_type i = enums::pos(k);
            BOOST_ASSERT( i < N && "out of range" ); 
            return elems[i];
        }
        
        const_reference operator[](key_type k) const 
        {     
            size_type i = enums::pos(k);
            BOOST_ASSERT( i < N && "out of range" ); 
            return elems[i]; 
        }

        // at() with range check
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
        reference front() 
        { 
            return elems[0]; 
        }
        
        const_reference front() const 
        {
            return elems[0];
        }
        
        reference back() 
        { 
            return elems[N-1]; 
        }
        
        const_reference back() const 
        { 
            return elems[N-1]; 
        }

        // size is constant
        BOOST_STATIC_CONSTEXPR size_type size() { return N; }
        static bool empty() { return false; }
        BOOST_STATIC_CONSTEXPR size_type max_size() { return N; }
        enum { static_size = N };

        // swap (note: linear complexity)
        void swap (enum_array<T,EC>& y) {
            for (size_type i = 0; i < N; ++i)
                boost::swap(elems[i],y.elems[i]);
        }

        // direct access to data (read-only)
        const T* data() const { return elems; }
        T* data() { return elems; }

        // use enum_array as C array (direct read/write access to data)
        T* c_array() { return elems; }

        // assignment with type conversion
        template <typename T2>
        enum_array<T,EC>& operator= (const enum_array<T2,EC>& rhs) {
            std::copy(rhs.begin(),rhs.end(), begin());
            return *this;
        }

        // assign one value to all elements
        void assign (const T& value) { fill ( value ); }    // A synonym for fill
        void fill   (const T& value)
        {
            std::fill_n(begin(),size(),value);
        }

        // check range (may be private because it is static)
        static size_type rangecheck (key_type k) {
        size_type i = rangecheck(k); 
            if (i >= size()) {
                std::out_of_range e("array<>: index out of range");
                boost::throw_exception(e);
            }
        return i;
        }

    };



    // comparisons
    template<class T, typename EC>
    bool operator== (const enum_array<T,EC>& x, const enum_array<T,EC>& y) {
        return std::equal(x.begin(), x.end(), y.begin());
    }
    template<class T, typename EC>
    bool operator< (const enum_array<T,EC>& x, const enum_array<T,EC>& y) {
        return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());
    }
    template<class T, typename EC>
    bool operator!= (const enum_array<T,EC>& x, const enum_array<T,EC>& y) {
        return !(x==y);
    }
    template<class T, typename EC>
    bool operator> (const enum_array<T,EC>& x, const enum_array<T,EC>& y) {
        return y<x;
    }
    template<class T, typename EC>
    bool operator<= (const enum_array<T,EC>& x, const enum_array<T,EC>& y) {
        return !(y<x);
    }
    template<class T, typename EC>
    bool operator>= (const enum_array<T,EC>& x, const enum_array<T,EC>& y) {
        return !(x<y);
    }

    // global swap()
    template<class T, typename EC>
    inline void swap (enum_array<T,EC>& x, enum_array<T,EC>& y) {
        x.swap(y);
    }

#if defined(__SUNPRO_CC)
//    Trac ticket #4757; the Sun Solaris compiler can't handle
//    syntax like 'T(&get_c_array(boost::array<T,N>& arg))[N]'
//    
//    We can't just use this for all compilers, because the 
//        borland compilers can't handle this form. 
    namespace detail {
       template <typename T, typename EC> struct c_array
       {
           typedef T type[N];
       };
    }
    
   // Specific for boost::enums::enum_array: simply returns its elems data member.
   template <typename T, typename EC>
   typename detail::c_array<T,N>::type& get_c_array(boost::enums::enum_array<T,EC>& arg)
   {
       return arg.elems;
   }

   // Specific for boost::enums::enum_array: simply returns its elems data member.
   template <typename T, typename EC>
   typename const detail::c_array<T,N>::type& get_c_array(const boost::enums::enum_array<T,EC>& arg)
   {
       return arg.elems;
   }
#else
// Specific for boost::enums::enum_array: simply returns its elems data member.
    template <typename T, typename EC>
    T(&get_c_array(boost::enums::enum_array<T,EC>& arg))[enums::meta::size<EC>::value]
    {
        return arg.elems;
    }
    
    // Const version.
    template <typename T, typename EC>
    const T(&get_c_array(const boost::enums::enum_array<T,EC>& arg))[enums::meta::size<EC>::value]
    {
        return arg.elems;
    }
#endif
    
#if 0
    
    template <class T, typename EC>
    class  tuple_size<enum_array<T, EC> >
        : public integral_constant<size_t, enums::meta::size<EC>::value> {};

    template <class T, typename EC>
    class  tuple_size<const enum_array<T, EC> >
        : public integral_constant<size_t, enums::meta::size<EC>::value> {};

    template <class T, typename EC, enums::enum_type<EC>::type K>
    class  tuple_element<enum_array<T, EC> >
    {
    public:
        typedef T type;
    };

    template <class T, typename EC, enums::enum_type<EC>::type K>
    class  tuple_element<const enum_array<T, EC> >
    {
    public:
        typedef const T type;
    };

    template <class T, typename EC, enums::enum_type<EC>::type K>
     inline
    T&
    get(enum_array<T, EC>& a)
    {
        return a[K];
    }

    template <class T, typename EC, enums::enum_type<EC>::type K>
    _LIBCPP_INLINE_VISIBILITY inline
    const T&
    get(const enum_array<T, EC>& a)
    {
        return a[K];
    }

    #ifndef BOOST_NO_RVALUE_REFERENCES

    template <class T, typename EC, enums::enum_type<EC>::type K>
    T&&
    get(array<T, enums::meta::size<EC>::value>&& a)
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
