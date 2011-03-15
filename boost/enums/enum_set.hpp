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
 The header \c <boost/enums/enum_set.hpp> defines a class template \c enum_set<EC> for managing sets of enumeration and several
 //! related functions for representing and manipulating sets of enums. We can say that
 \c enum_set is the counterpart of \c std::bitset when the index are enums.
 */

#ifndef BOOST_ENUMS_ENUM_SET_HPP
#define BOOST_ENUMS_ENUM_SET_HPP

//#include <boost/enums/enum_traits.hpp>
//#include <boost/enums/val.hpp>
#include <boost/enums/pos.hpp>
#include <boost/enums/size.hpp>
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

    template<typename EC /*,
             typename Traits=enum_subrange_traiter<EC>*/ >
    class enum_set
    {
    public:
      struct reference {
      };
      //! <b> Effects:</b> Constructs an object of class \c enum_set<>, initializing all
      //! enumerations to zero.
      BOOST_CONSTEXPR enum_set()
      {
      }
      //~ BOOST_CONSTEXPR
      // Need to be refactored to be a constexpr
      //~ error: constexpr constructor does not have empty body
      explicit enum_set(EC setting)
      {
        set(setting);
      }

      //! <b> Effects:</b> Constructs an object of class \c enum_set<>, initializing the
      //! first \c M bit positions to the corresponding bit values in \c val.
      //! \c M is the smaller of \c N and the number of bits in the value
      //! representation of \c unsigned \c long \c long. If \c M<N, the remaining bit
      //! positions are initialized to zero.
      BOOST_CONSTEXPR explicit enum_set(unsigned long long val)
        : bits(val)
      {
      }
      //#if defined(__GNUC__) &&  (__GNUC__ < 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ < 4 ))
      #if 1
      #else

      //! \pre <tt>pos <= str.size()</tt>.
      //! \throws out_of_range if <tt>pos > str.size()</tt>.
      //! <b> Effects:</b> Determines the effective length \c rlen of the initializing
      //! string as the smaller of \c n and <tt>str.size()-pos</tt>.
      //! The function then throws \c invalid_argument if any of the \c rlen
      //! characters in \c str beginning at position pos is other than zero or one.
      //! The function uses \c ch_traits::eq() to compare the character values.
      //! Otherwise, the function constructs an object of class \c enum_set<EC>,
      //! initializing the first \c M bit positions to values determined from the
      //! corresponding characters in the string \c str. \c M is the smaller of \c N and
      //! \c rlen.\n
      //! An element of the constructed string has value zero if the
      //! corresponding character in \c str, beginning at position \c pos, is \c 0 zero.
      //! Otherwise, the element has the value 1. Character position \c pos+M-1
      //! corresponds to bit position zero. Subsequent decreasing character
      //! positions correspond to increasing bit positions.
      //! If \c M<N, remaining bit positions are initialized to zero.
      template<class charT, class ch_traits, class TAllocator>
        explicit enum_set(const std::basic_string<charT,ch_traits,TAllocator>& str,
                          typename std::basic_string<charT,ch_traits,TAllocator>::size_type pos = 0,
                          typename std::basic_string<charT,ch_traits,TAllocator>::size_type n =
                                   std::basic_string<charT,ch_traits,TAllocator>::npos,
                          charT zero = charT('0'), charT one = charT('1'))
        : bits(str, pos, n, zero, one)
      {}

      //! <b> Effects:</b> Constructs an object of class enum_set<N> as if by enum_set(string(str)).
      template <class charT>
        explicit enum_set(const charT* str,
                          typename std::basic_string<charT>::size_type n = std::basic_string<charT>::npos,
                          charT zero = charT('0'), charT one = charT('1'))
        : bits(str,n, zero, one)
      {}
      #endif

      //! <b> Effects:</b> Clears each bit in \c *this for which the corresponding bit in
      //! \c rhs is clear, and leaves all other bits unchanged.
      //! \returns \c *this.
      enum_set &operator&=(const enum_set &rhs)
      {
        bits &= rhs.bits;
        return *this;
      }

      //! <b> Effects:</b> Sets each bit in \c *this for which the corresponding bit in
      //! \c rhs is set, and leaves all other bits unchanged.
      //! \returns \c *this.
      enum_set &operator|=(const enum_set &rhs)
      {
        bits |= rhs.bits;
        return *this;
      }

      //! <b> Effects:</b> Toggles each bit in \c *this for which the corresponding bit in
      //! \c rhs is set, and leaves all other bits unchanged.
      //! \returns \c *this.
      enum_set &operator^=(const enum_set &rhs)
      {
        bits ^= rhs.bits;
        return *this;
      }

      //! <b> Effects:</b> Replaces each bit at position \c I in \c *this with a value determined as follows:
      //! - If \c I<pos, the new value is zero;
      //! - If \c I>=pos, the new value is the previous value of the bit at position \c I-pos.
      //! \returns \c *this.
      enum_set &operator<<=(const enum_set &rhs)
      {
        bits <<= rhs.bits;
        return *this;
      }

      //! <b> Effects:</b> Replaces each bit at position \c I in \c *this with a value determined as follows:
      //! - If \c pos>=N-I, the new value is zero;
      //! - If \c pos<N-I, the new value is the previous value of the bit at position \c I+pos.
      //! \returns \c *this.

      enum_set &operator>>=(const enum_set &rhs)
      {
        bits >>= rhs.bits;
        return *this;
      }

      //! \returns A count of the number of bits set in \c *this.
      std::size_t count() const
      {
        return bits.count();
      }

      //! \returns \c static_size.
      BOOST_CONSTEXPR std::size_t size() const
      {
        return bits.size();
      }

      //! \pre \c pos shall be valid.
      //! \throws nothing.
      //! \returns \c true if the bit at position \c pos in \c *this has the value one,
      //! otherwise \c false.
      BOOST_CONSTEXPR bool operator[](EC testing) const
      {
        return bits.test(to_bit(testing));
      }

      //! \pre \c pos shall be valid.
      //! \throws nothing.
      //! \returns An object of type \c enum_set<EC>::reference such that
      //! <tt>(*this)[pos] == this->test(pos)</tt>, and such that <tt>(*this)[pos] = val</tt> is
      //! equivalent to <tt>this->set(pos, val)</tt>.
      //! \note For the purpose of determining the presence of a data race,
      //! any access or update through the resulting reference potentially
      //! accesses or modifies, respectively, the entire underlying  bitset.
      reference operator[](std::size_t pos);            // for b[i];

      //! <b> Effects:</b> Sets all bits in \c *this.
      //! \returns \c *this.

      enum_set &set()
      {
        bits.set();
        return *this;
      }

      //! \pre \c setting is valid
      //! \throws out_of_range if \c pos does not correspond to a valid bit position.
      //! <b> Effects:</b> Stores a new value in the bit at the position associated to \c setting in \c *this.
      //! If \c value is nonzero, the stored value is one, otherwise it is zero.
      //! \returns \c *this.
      enum_set &set(EC setting, bool value = true)
      {
        bits.set(to_bit(setting), value);
        return *this;
      }

      //! <b> Effects:</b> Resets all bits in \c *this.
      //! \returns \c *this.
      enum_set &reset()
      {
        bits.reset();
        return *this;
      }

      //! \pre \c resetting is valid
      //! \throws out_of_range if \c resetting does not correspond to a valid enum.
      //! <b> Effects:</b> Resets the bit at the position associated to \c resetting in \c *this.
      //! \returns \c *this.

      enum_set &reset(EC resetting)
      {
        bits.reset(to_bit(resetting));
        return *this;
      }

      //! <b> Effects:</b> Toggles all bits in \c *this.
      //! \returns \c *this.
      enum_set &flip()
      {
        bits.flip();
        return *this;
      }

      //! \pre \c flipping is valid
      //! \throws out_of_range if \c flipping does not correspond to a valid enum.
      //! <b> Effects:</b> Toggles the bit at position associated to \c pos in \c *this.
      //! \returns \c *this.
      enum_set &flip(EC flipping)
      {
        bits.flip(to_bit(flipping));
        return *this;
      }

      //! \c <tt>unsigned long</tt> conversion
      //! \throws overflow_error if the integral value \c x corresponding to the
      //! bits in \c *this cannot be represented as type <<tt>unsigned long</tt>.
      //! \returns \c x.

      unsigned long to_ulong() const
      {
        return bits.to_ulong();
      }

      //! \c <tt>unsigned long long</tt> conversion
      //! \throws overflow_error if the integral value \c x corresponding to the
      //!  bits in \c *this cannot be represented as type <tt>unsigned long long</tt>.
      //! \returns \c x.
      unsigned long long to_ullong() const
      {
        return bits.to_ulong();
      }
#ifdef BOOST_ENUMS_DOXYGEN_INVOKED

      //! <b> Effects:</b> Constructs a string object of the appropriate type and
      //! initializes it to a string of length \c N characters. Each character is
      //! determined by the value of its corresponding bit position in \c *this.
      //! Character position \c N-1 corresponds to bit position zero.
      //! Subsequent decreasing character positions correspond to increasing
      //! bit positions. Bit value zero becomes the character zero, bit value
      //! one becomes the character one.
      //! \returns The created object.
      template <class charT = char,
        class traits = std::char_traits<charT>,
        class Allocator = std::allocator<charT> >
        std::basic_string<charT, traits, Allocator>
      to_string(charT zero = charT('0'), charT one = charT('1')) const;
#endif
      //! <b> Effects:</b> Constructs an object x of class enum_set<EC> and initializes it with *this.
      //! \returns \c x.flip().
      enum_set operator~() const
      {
        return enum_set(*this).flip();
      }

      //! \pre \c testing is valid
      //! \throws out_of_range if the associated position of \c testing does not correspond to a valid bit position.
      //! \returns \c true if the bit at position \c pos in \c *this has the value one.
      bool test(EC testing);

      //! \returns <tt>count() == size()</tt>
      bool all() const
      {
        return bits.all();
      }

      //! \returns <tt>count() != 0</tt>
      bool any() const
      {
        return bits.any();
      }

      //! \returns <tt>count() == 0</tt>
      bool none() const
      {
        return bits.none();
      }

      //! \returns <tt>enum_set<EC>(*this) <<= pos</tt>.
      enum_set operator<<(std::size_t pos) const
      {
        enum_set r = *this;
        r <<= pos;
        return r;
      }

      //! \returns <tt>enum_set<EC>(*this) >>= pos</tt>.
      enum_set operator>>(std::size_t pos) const
      {
        enum_set r = *this;
        r >>= pos;
        return r;
      }

      //! \returns A nonzero value if the value of each bit in \c *this equals the
      //! value of the corresponding bit in \c rhs.
      bool operator==(const enum_set& rhs) const;

      //! \returns A nonzero value if <tt>!(*this == rhs)</tt>.
      bool operator!=(const enum_set& rhs) const;
    private:

      static std::size_t to_bit(EC value)
      {
        return enums::pos(value);
      }

      std::bitset<enums::meta::size<EC>::value> bits;

    public:

      std::bitset<enums::meta::size<EC>::value> detail_bits() { return bits; }
    };

    // enum_set operators:

    //! Intersection
      
    //! \returns enum_set<EC>(lhs) &= rhs.
    template <typename EC/*, typename Traits*/>
    enum_set<EC/*,Traits*/> operator&(const enum_set<EC/*,Traits*/>& x, const enum_set<EC/*,Traits*/>& y)
    {
      enum_set<EC/*,Traits*/> r = x;
      r &= y;
      return r;
    }

    //! Union
      
    //! \returns enum_set<EC>>(lhs) |= rhs.
    template <typename EC/*, typename Traits*/ >
    enum_set<EC/*,Traits*/> operator|(const enum_set<EC/*,Traits*/>& x, const enum_set<EC/*,Traits*/>& y)
    {
      enum_set<EC/*,Traits*/> r = x;
      r |= y;
      return r;
    }

    //! Exclusive union

    //! \returns enum_set<EC>(lhs) ^= rhs.
    template <typename EC/*, typename Traits*/ >
    enum_set<EC/*,Traits*/> operator^(const enum_set<EC/*,Traits*/>& x, const enum_set<EC/*,Traits*/>& y)
    {
      enum_set<EC/*,Traits*/> r = x;
      r ^= y;
      return r;
    }

    //! A formatted input function.
      
      //! \details <b> Effects:</b> Extracts up to \c N characters from is. Stores these characters
    //! in a temporary object \c str of type <tt>basic_string<charT, traits></tt>, then
    //! evaluates the expression <tt>x = enum_set<EC>(str)</tt>. Characters are extracted
    //! and stored until any of the following occurs:
    //! - \c N characters have been extracted and stored;
    //! - end-of-file occurs on the input sequence;
    //! - the next input character is neither \c is.widen('0') nor \c is.widen('1')
    //! (in which case the input character is not extracted).\n
    //! If no characters are stored in \c str, calls \c is.setstate(ios_base::failbit)
    //! (which may throw <tt>ios_- base::failure</tt>).
      //! \param is the input stream.
      //! \param x the \c enum_set.
      //! \returns \c is.
      
    template <class charT, class ch_traits, typename EC/*, typename Traits*/ >
    std::basic_istream<charT, ch_traits>&
    operator>>(std::basic_istream<charT, ch_traits>& is, enum_set<EC/*,Traits*/>& x)
    {
      return is >> x.detail_bits();
    }

      //! A formatted output function.

      //! \param os the output stream.
      //! \param x the \c enum_set.
    //! \returns <tt>os << x.template to_string<charT,traits,allocator<charT> >(
    //! use_facet<ctype<charT> >(os.getloc()).widen('0'),
    //! use_facet<ctype<charT> >(os.getloc()).widen('1'))</tt>
    template <class charT, class ch_traits, typename EC/*, typename Traits*/ >
    std::basic_ostream<charT, ch_traits>&
    operator<<(std::basic_ostream<charT, ch_traits>& os, const enum_set<EC/*,Traits*/>& x)
    {
      return os << x.detail_bits();
    }


  } /* namespace enums */

  //! hash template specialization
    
  template <typename EC/*, typename Traits*/ >
  struct hash<enums::enum_set<EC/*,Traits*/> >
  : public std::unary_function<enums::enum_set<EC/*,Traits*/>, std::size_t>
  {
    //! \details the template specialization meets the requirements of class template \c hash.
    std::size_t operator()(const enums::enum_set<EC/*,Traits*/>& bs) const
    {
      return hash<std::bitset<enums::meta::size<EC>::size> >(bs.detail_bits());
    }
  };

} /* namespace boost */


#endif /*BOOST_ENUMS_ENUM_SET_HPP*/
