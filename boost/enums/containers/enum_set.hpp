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
 \file
 \brief  
 The header \c <boost/enums/containers/enum_set.hpp> defines a class template \c enum_set<T> for managing sets of enumeration and several
 //! related functions for representing and manipulating sets of enums. We can say that
 \c enum_set is the counterpart of \c std::bitset when the index are enums.
 */

#ifndef BOOST_ENUMS_CONTAINERS_ENUM_SET_HPP
#define BOOST_ENUMS_CONTAINERS_ENUM_SET_HPP

#include <boost/enums/ordinal/pos.hpp>
#include <boost/enums/ordinal/size.hpp>
#include <bitset>
#include <stdexcept>
#include <iosfwd>
#include <string>
#include <cstddef>
#include <climits>
#include <string>
#include <boost/functional/hash.hpp>

#include <boost/config.hpp>

namespace boost {
  namespace enums {

    /** 
      @TParams
      @Param{T,set's element ordinal enum}
      @Requires @c T must be a model of <em>OrdinalEnum</em>.
     
     The class template @c enum_set<T> describes an object that can store a sequence 
     consisting of a fixed number of bits, given by @c enums::meta::size<T>::value.
     
     Each bit represents either the value zero (reset) or one (set). To toggle 
     a bit is to change the value zero to one, or the value one to zero. Each 
     bit has a non-negative position pos. When converting between an object of 
     class enum_set<T> and a value of some integral type, bit position pos 
     corresponds to the bit value 1<<pos. The integral value corresponding to 
     two or more bits is the sum of their bit values.
     The functions described in this section can report three kinds of errors, 
     each associated with a distinct exception:
     - an invalid-argument error is associated with exceptions of type @c std::invalid_argument; 
     - an out-of-range error is associated with exceptions of type @c std::out_of_range; 
     - an overflow error is associated with exceptions of type @c std::overflow_error.

     */
    template<typename T>
    class enum_set;

    template<typename T>
    class enum_set
    {
    public:
      //! @brief A proxy class that acts as a reference to a single bit.
      
      //! It contains an assignment operator, a conversion to @c bool, 
      //! an @c operator~, and a member function @c flip. 
      //! It exists only as a helper class for @c enum_set's @c operator[]. 
      class reference {
        friend class enum_set<T>;
        enum_set<T>& ref_;
        T pos_;
        reference();
        reference(enum_set<T>& ref, T pos) 
        : ref_(ref), pos_(pos)
        { }        
      public:
        ~reference() 
        { }        
        
        //! assignement from bool
        reference& operator=(bool x) 
        { 
          ref_.set(pos_,x);
          return *this;
        }
        
        //! assignement from another reference
        reference& operator=(const reference& x) 
        { 
          ref_.set(pos_,x);
          return *this;
        }
        
        //! flip the bit 
        bool operator~() const  
        { 
          return ref_.flip(pos_);
        }
        
        //! implicit conversion to bool
        operator bool() const  
        { 
          return ref_.test(pos_);
        }
        
        //! flip the bit
        reference flip() const  
        { 
          return ref_.flip(pos_);
        }
      };
      //! @Effects Constructs an object of class \c enum_set<>, initializing all
      //! enumerations to zero.
      //! @NoExcept
      BOOST_CONSTEXPR enum_set()
      {
      }
      // BOOST_CONSTEXPR
      // Need to be refactored to be a constexpr
      // error: constexpr constructor does not have empty body
      explicit enum_set(T setting)
      {
        set(setting);
      }

      //! @Effects Constructs an object of class \c enum_set<>, initializing the
      //! first \c M bit positions to the corresponding bit values in \c val.
      //! \c M is the smaller of \c N and the number of bits in the value
      //! representation of \c unsigned \c long \c long. If \c M<N, the remaining bit
      //! positions are initialized to zero.
      //! @NoExcept

      BOOST_CONSTEXPR explicit enum_set(unsigned long long val)
        : bits(val)
      {
      }
      //#if defined(__GNUC__) &&  (__GNUC__ < 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ < 4 ))
      #if 1
      #else

      //! @Requires <tt>pos <= str.size()</tt>.
      //! @Throws std::out_of_range if <tt>pos > str.size()</tt>.
      //! @Effects Determines the effective length \c rlen of the initializing
      //! string as the smaller of \c n and <tt>str.size()-pos</tt>.
      //! The function then throws \c std::invalid_argument if any of the \c rlen
      //! characters in \c str beginning at position pos is other than zero or one.
      //! The function uses \c traits::eq() to compare the character values.
      //! Otherwise, the function constructs an object of class \c enum_set<T>,
      //! initializing the first \c M bit positions to values determined from the
      //! corresponding characters in the string \c str. \c M is the smaller of \c N and
      //! \c rlen.\n
      //! An element of the constructed string has value zero if the
      //! corresponding character in \c str, beginning at position \c pos, is \c 0 zero.
      //! Otherwise, the element has the value 1. Character position \c pos+M-1
      //! corresponds to bit position zero. Subsequent decreasing character
      //! positions correspond to increasing bit positions.
      //! If \c M<enums::meta::size<T>::value, remaining bit positions are initialized to zero.
      template<class charT, class traits, class TAllocator>
        explicit enum_set(const std::basic_string<charT,traits,TAllocator>& str,
                          typename std::basic_string<charT,traits,TAllocator>::size_type pos = 0,
                          typename std::basic_string<charT,traits,TAllocator>::size_type n =
                                   std::basic_string<charT,traits,TAllocator>::npos,
                          charT zero = charT('0'), charT one = charT('1'))
        : bits(str, pos, n, zero, one)
      {}

      //! @Effects Constructs an object of class enum_set<N> as if by enum_set(string(str)).
      template <class charT>
        explicit enum_set(const charT* str,
                          typename std::basic_string<charT>::size_type n = std::basic_string<charT>::npos,
                          charT zero = charT('0'), charT one = charT('1'))
        : bits(str,n, zero, one)
      {}
      #endif

      //! @Effects Clears each bit in \c *this for which the corresponding bit in
      //! \c rhs is clear, and leaves all other bits unchanged.
      //! @Returns \c *this.
      //! @NoExcept
      enum_set &operator&=(const enum_set &rhs)
      {
        bits &= rhs.bits;
        return *this;
      }

      //! @Effects Sets each bit in \c *this for which the corresponding bit in
      //! \c rhs is set, and leaves all other bits unchanged.
      //! @Returns \c *this.
      //! @NoExcept
      enum_set &operator|=(const enum_set &rhs)
      {
        bits |= rhs.bits;
        return *this;
      }

      //! @Effects Toggles each bit in \c *this for which the corresponding bit in
      //! \c rhs is set, and leaves all other bits unchanged.
      //! @Returns \c *this.
      //! @NoExcept
      enum_set &operator^=(const enum_set &rhs)
      {
        bits ^= rhs.bits;
        return *this;
      }

      //! @Effects Replaces each bit at position \c I in \c *this with a value determined as follows:
      //! - If \c I<pos, the new value is zero;
      //! - If \c I>=pos, the new value is the previous value of the bit at position \c I-pos.
      //! @Returns \c *this.
      //! @NoExcept
      enum_set &operator<<=(const enum_set &rhs)
      {
        bits <<= rhs.bits;
        return *this;
      }

      //! @Effects Replaces each bit at position \c I in \c *this with a value determined as follows:
      //! - If \c pos>=N-I, the new value is zero;
      //! - If \c pos<N-I, the new value is the previous value of the bit at position \c I+pos.
      //! @Returns \c *this.
      //! @NoExcept

      enum_set &operator>>=(const enum_set &rhs)
      {
        bits >>= rhs.bits;
        return *this;
      }

      //! @Returns A count of the number of bits set in \c *this.
      std::size_t count() const
      {
        return bits.count();
      }

      //! @Returns \c static_size.
      BOOST_CONSTEXPR std::size_t size() const
      {
        return bits.size();
      }

      //! @Requires \c pos shall be valid.
      //! @Throws std::invalid_argument if @c e does not have a valid position.
      //! @Returns \c true if the bit at the associated position of \c e in \c *this has the value one,
      //! otherwise \c false.
      BOOST_CONSTEXPR bool operator[](T e) const
      {
        return bits.test(to_bit(e));
      }

      //! @Requires \c pos shall be valid.
      //! @Throws std::invalid_argument if @c e does not have a valid position.
      //! @Returns An object of type \c enum_set<T>::reference such that
      //! <tt>(*this)[pos] == this->test(pos)</tt>, and such that <tt>(*this)[pos] = val</tt> is
      //! equivalent to <tt>this->set(pos, val)</tt>.
      //! @Note For the purpose of determining the presence of a data race,
      //! any access or update through the resulting reference potentially
      //! accesses or modifies, respectively, the entire underlying  bitset.
      reference operator[](T pos)
      {
        return reference(*this,pos);
      }
      //! @Effects Sets all bits in \c *this.
      //! @Returns \c *this.
      //! @NoExcept

      enum_set &set()
      {
        bits.set();
        return *this;
      }

      //! @Requires \c setting is valid
      //! @Throws @c std::invalid_argument if @c setting does have a invalid bit position.
      //! @Effects Stores a new value in the bit at the position associated to \c setting in \c *this.
      //! If \c value is nonzero, the stored value is one, otherwise it is zero.
      //! @Returns \c *this.
      enum_set &set(T setting, bool value = true)
      {
        bits.set(to_bit(setting), value);
        return *this;
      }

      //! @Effects Resets all bits in \c *this.
      //! @Returns \c *this.
      //! @NoExcept
      enum_set &reset()
      {
        bits.reset();
        return *this;
      }

      //! @Requires \c resetting is valid
      //! @Throws @c std::invalid_argument if \c resetting does not correspond to a valid enum.
      //! @Effects Resets the bit at the position associated to \c resetting in \c *this.
      //! @Returns \c *this.

      enum_set &reset(T resetting)
      {
        bits.reset(to_bit(resetting));
        return *this;
      }

      //! @Effects Toggles all bits in \c *this.
      //! @Returns \c *this.
      //! @NoExcept
      enum_set &flip()
      {
        bits.flip();
        return *this;
      }

      //! @Requires \c flipping is valid
      //! @Throws std::invalid_argument if \c flipping does not correspond to a valid enum.
      //! @Effects Toggles the bit at position associated to \c pos in \c *this.
      //! @Returns \c *this.
      enum_set &flip(T flipping)
      {
        bits.flip(to_bit(flipping));
        return *this;
      }

      //! \c <tt>unsigned long</tt> conversion
      //! @Throws @c std::overflow_error if the integral value \c x corresponding to the
      //! bits in \c *this cannot be represented as type <<tt>unsigned long</tt>.
      //! @Returns \c x.

      unsigned long to_ulong() const
      {
        return bits.to_ulong();
      }

      //! \c <tt>unsigned long long</tt> conversion
      //! @Throws @c std::overflow_error if the integral value \c x corresponding to the
      //!  bits in \c *this cannot be represented as type <tt>unsigned long long</tt>.
      //! @Returns \c x.
      unsigned long long to_ullong() const
      {
        return bits.to_ulong();
      }
#ifdef BOOST_ENUMS_DOXYGEN_INVOKED

      //! @Effects Constructs a string object of the appropriate type and
      //! initializes it to a string of length \c N characters. Each character is
      //! determined by the value of its corresponding bit position in \c *this.
      //! Character position \c N-1 corresponds to bit position zero.
      //! Subsequent decreasing character positions correspond to increasing
      //! bit positions. Bit value zero becomes the character zero, bit value
      //! one becomes the character one.
      //! @Returns The created object.
      template <class charT = char,
        class traits = std::char_traits<charT>,
        class Allocator = std::allocator<charT> >
        std::basic_string<charT, traits, Allocator>
      to_string(charT zero = charT('0'), charT one = charT('1')) const;
#endif
      //! @Effects Constructs an object @c x of class @c enum_set<T> and initializes it with @c *this.
      //! @Returns \c x.flip().
      //! @NoExcept
      enum_set operator~() const
      {
        return enum_set(*this).flip();
      }

      //! @Requires \c testing is valid
      //! @Throws out_of_range if the associated position of \c testing does not correspond to a valid bit position.
      //! @Returns \c true if the bit at position \c pos in \c *this has the value one.
      bool test(T testing)
      {
        return bits.test(to_bit(testing));
      }
      
      //! @Returns <tt>count() == size()</tt>
      //! @NoExcept
      bool all() const
      {
        return bits.all();
      }

      //! @Returns <tt>count() != 0</tt>
      //! @NoExcept
      bool any() const
      {
        return bits.any();
      }

      //! @Returns <tt>count() == 0</tt>
      //! @NoExcept
      bool none() const
      {
        return bits.none();
      }

      //! @Returns <tt>enum_set<T>(*this) <<= pos</tt>.
      //! @NoExcept
      enum_set operator<<(std::size_t pos) const
      {
        enum_set r = *this;
        r <<= pos;
        return r;
      }

      //! @Returns <tt>enum_set<T>(*this) >>= pos</tt>.
      //! @NoExcept
      enum_set operator>>(std::size_t pos) const
      {
        enum_set r = *this;
        r >>= pos;
        return r;
      }

      //! @Returns A nonzero value if the value of each bit in \c *this equals the
      //! value of the corresponding bit in \c rhs.
      //! @NoExcept
      bool operator==(const enum_set& rhs) const;

      //! @Returns A nonzero value if <tt>!(*this == rhs)</tt>.
      //! @NoExcept
      bool operator!=(const enum_set& rhs) const;
    private:

      static std::size_t to_bit(T value)
      {
        return enums::pos(value);
      }

      std::bitset<enums::meta::size<T>::value> bits;

    public:

      std::bitset<enums::meta::size<T>::value> detail_bits() { return bits; }
      std::bitset<enums::meta::size<T>::value> detail_bits() const { return bits; }
    };

    // enum_set operators:

    //! Intersection
      
    //! @Returns <tt>enum_set<T>(lhs) &= rhs</tt>.
    //! @NoExcept
    template <typename T>
    enum_set<T> operator&(const enum_set<T>& x, const enum_set<T>& y)
    {
      enum_set<T> r = x;
      r &= y;
      return r;
    }

    //! Union
      
    //! @Returns <tt>enum_set<T>>(lhs) |= rhs</tt>.
    //! @NoExcept
    template <typename T >
    enum_set<T> operator|(const enum_set<T>& x, const enum_set<T>& y)
    {
      enum_set<T> r = x;
      r |= y;
      return r;
    }

    //! Exclusive union

    //! @Returns <tt>enum_set<T>(lhs) ^= rhs</tt>.
    //! @NoExcept
    template <typename T >
    enum_set<T> operator^(const enum_set<T>& x, const enum_set<T>& y)
    {
      enum_set<T> r = x;
      r ^= y;
      return r;
    }

    //! A formatted input function.
      
      //! @Effects Extracts up to \c N characters from is. Stores these characters
    //! in a temporary object \c str of type <tt>basic_string<charT, traits></tt>, then
    //! evaluates the expression <tt>x = enum_set<T>(str)</tt>. Characters are extracted
    //! and stored until any of the following occurs:
    //! - \c N characters have been extracted and stored;
    //! - end-of-file occurs on the input sequence;
    //! - the next input character is neither \c is.widen('0') nor \c is.widen('1')
    //! (in which case the input character is not extracted).\n
    //! If no characters are stored in \c str, calls \c is.setstate(ios_base::failbit)
    //! (which may throw <tt>ios_- base::failure</tt>).
    //! @Params
    //! @Param{is, the input stream}
    //! @Param{x, the \c enum_set}
    //! @Returns \c is.
      
    template <class charT, class traits, typename T >
    std::basic_istream<charT, traits>&
    operator>>(std::basic_istream<charT, traits>& is, enum_set<T>& x)
    {
      return is >> x.detail_bits();
    }

    //! A formatted output function.

    //! @Params
    //! @Param{os, the output stream}
    //! @Param{x, the \c enum_set}
    //! @Returns the result of the following expression
    //! @code
    //! os << x.template to_string<charT,traits,allocator<charT> >(
    //!         use_facet<ctype<charT> >(os.getloc()).widen('0'),
    //!         use_facet<ctype<charT> >(os.getloc()).widen('1')
    //!       )
    //! @endcode
    template <class charT, class traits, typename T >
    std::basic_ostream<charT, traits>&
    operator<<(std::basic_ostream<charT, traits>& os, const enum_set<T>& x)
    {
      return os << x.detail_bits();
    }


  } /* namespace enums */

  //! enum_set hash template specialization
    
  template <typename T >
  struct hash<enums::enum_set<T> >
  : public std::unary_function<enums::enum_set<T>, std::size_t>
  {
    //! \details The template specialization meets the requirements of class template \c hash.
    //! @Params
    //! @Param{es, the @c enum_set}
    //! @Returns the hash associated to the underlying bitset.
    std::size_t operator()(const enums::enum_set<T>& es) const
    {
      return hash<std::bitset<enums::meta::size<T>::size> >(es.detail_bits());
    }
  };

} /* namespace boost */


#endif /*BOOST_ENUMS_ENUM_SET_HPP*/
