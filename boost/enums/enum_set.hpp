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
#include <boost/functional/hash.hpp>

#include <boost/config.hpp>


//! The header <boost/enums/enum_set.hpp> defines a class template and several
//! related functions for representing and manipulating sets of enums.

namespace boost {
  namespace enums {

    template<typename EC /*,
             typename Traits=enum_subrange_traiter<EC>*/ >
    class enum_set
    {
    public:
      //! Effects: Constructs an object of class enum_set<>, initializing all
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

      //! Effects: Constructs an object of class enumset<>, initializing the
      //! first M bit positions to the corresponding bit values in val.
      //! M is the smaller of N and the number of bits in the value
      //! representation of unsigned long long. If M<N, the remaining bit
      //! positions are initialized to zero.
      BOOST_CONSTEXPR explicit enum_set(unsigned long long val)
        : bits(val)
      {
      }
      //#if defined(__GNUC__) &&  (__GNUC__ < 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ < 4 ))
      #if 1
      #else

      //! Requires: pos <= str.size().
      //! Throws: out_of_range if pos > str.size().
      //! Effects: Determines the effective length rlen of the initializing
      //! string as the smaller of n and str.size() - pos.
      //! The function then throws invalid_argument if any of the rlen
      //! characters in str beginning at position pos is other than zero or one.
      //! The function uses traits::eq() to compare the character values.
      //! Otherwise, the function constructs an object of class enum_set<EC>,
      //! initializing the first M bit positions to values determined from the
      //! corresponding characters in the string str. M is the smaller of N and
      //! rlen.
      //! An element of the constructed string has value zero if the
      //! corresponding character in str, beginning at position pos, is 0 zero.
      //! Otherwise, the element has the value 1. Character position pos + M - 1
      //! corresponds to bit position zero. Subsequent decreasing character
      //! positions correspond to increasing bit positions.
      //! If M < N, remaining bit positions are initialized to zero.
      template<class charT, class ch_traits, class TAllocator>
        explicit enum_set(const std::basic_string<charT,ch_traits,TAllocator>& str,
                          typename std::basic_string<charT,ch_traits,TAllocator>::size_type pos = 0,
                          typename std::basic_string<charT,ch_traits,TAllocator>::size_type n =
                                   std::basic_string<charT,ch_traits,TAllocator>::npos,
                          charT zero = charT('0'), charT one = charT('1'))
        : bits(str, pos, n, zero, one)
      {}

      //! Effects: Constructs an object of class enumset<N> as if by enumset(string(str)).
      template <class charT>
        explicit enum_set(const charT* str,
                          typename std::basic_string<charT>::size_type n = std::basic_string<charT>::npos,
                          charT zero = charT('0'), charT one = charT('1'))
        : bits(str,n, zero, one)
      {}
      #endif

      //! Effects: Clears each bit in *this for which the corresponding bit in
      //! rhs is clear, and leaves all other bits unchanged.
      //! Returns: *this.
      enum_set &operator&=(const enum_set &rhs)
      {
        bits &= rhs.bits;
        return *this;
      }

      //! Effects: Sets each bit in *this for which the corresponding bit in
      //! rhs is set, and leaves all other bits unchanged.
      //! Returns: *this.
      enum_set &operator|=(const enum_set &rhs)
      {
        bits |= rhs.bits;
        return *this;
      }

      //! Effects: Toggles each bit in *this for which the corresponding bit in
      //! rhs is set, and leaves all other bits unchanged.
      //! Returns: *this.
      enum_set &operator^=(const enum_set &rhs)
      {
        bits ^= rhs.bits;
        return *this;
      }

      //! Effects: Replaces each bit at position I in *this with a value determined as follows:
      //! - If I < pos, the new value is zero;
      //! - If I >= pos, the new value is the previous value of the bit at position I - pos.
      //! Returns: *this.
      enum_set &operator<<=(const enum_set &rhs)
      {
        bits <<= rhs.bits;
        return *this;
      }

      //! Effects: Replaces each bit at position I in *this with a value determined as follows:
      //! - If pos >= N - I, the new value is zero;
      //! - If pos < N - I, the new value is the previous value of the bit at position I + pos.
      //! Returns: *this.

      enum_set &operator>>=(const enum_set &rhs)
      {
        bits >>= rhs.bits;
        return *this;
      }

      //! Returns: A count of the number of bits set in *this.
      std::size_t count() const
      {
        return bits.count();
      }

      //! Returns: N.
      BOOST_CONSTEXPR std::size_t size() const
      {
        return bits.size();
      }

      //! Requires: pos shall be valid.
      //! Throws: nothing.
      //! Returns: true if the bit at position pos in *this has the value one,
      //! otherwise false.
      BOOST_CONSTEXPR bool operator[](EC testing) const
      {
        return bits.test(to_bit(testing));
      }

      //! Requires: pos shall be valid.
      //! Throws: nothing.
      //! Returns: An object of type enum_set<EC>::reference such that
      //! (*this)[pos] == this->test(pos), and such that (*this)[pos] = val is
      //! equivalent to this->set(pos, val).
      //! Remark: For the purpose of determining the presence of a data race,
      //! any access or update through the resulting reference potentially
      //! accesses or modifies, respectively, the entire underlying  bitset.
      //reference operator[](std::size_t pos);            // for b[i];

      //! Effects: Sets all bits in *this.
      //! Returns: *this.

      enum_set &set()
      {
        bits.set();
        return *this;
      }

      //! Requires: pos is valid
      //! Throws: out_of_range if pos does not correspond to a valid bit position.
      //! Effects: Stores a new value in the bit at position pos in *this.
      //! If val is nonzero, the stored value is one, otherwise it is zero.
      //! Returns: *this.
      enum_set &set(EC setting, bool value = true)
      {
        bits.set(to_bit(setting), value);
        return *this;
      }

      //! Effects: Resets all bits in *this.
      //! Returns: *this.
      enum_set &reset()
      {
        bits.reset();
        return *this;
      }

      //! Requires: pos is valid
      //! Throws: out_of_range if pos does not correspond to a valid bit position.
      //! Effects: Resets the bit at position pos in *this.
      //! Returns: *this.

      enum_set &reset(EC resetting)
      {
        bits.reset(to_bit(resetting));
        return *this;
      }

      //! Effects: Toggles all bits in *this.
      //! Returns: *this.
      enum_set &flip()
      {
        bits.flip();
        return *this;
      }

      //! Requires: pos is valid
      //! Throws: out_of_range if pos does not correspond to a valid bit position.
      //! Effects: Toggles the bit at position pos in *this.
      //! Returns: *this.
      enum_set &flip(EC flipping)
      {
        bits.flip(to_bit(flipping));
        return *this;
      }

      //! Throws: overflow_error if the integral value x corresponding to the
      //! bits in *this cannot be represented as type unsigned long.
      //! Returns: x.

      unsigned long to_ulong() const
      {
        return bits.to_ulong();
      }

      //! Throws: overflow_error if the integral value x corresponding to the
      //!  bits in *this cannot be represented as type unsigned long long.
      //! Returns: x.

      unsigned long long to_ullong() const
      {
        return bits.to_ulong();
      }

      //! Effects: Constructs a string object of the appropriate type and
      //! initializes it to a string of length N characters. Each character is
      //! determined by the value of its corresponding bit position in *this.
      //! Character position N - 1 corresponds to bit position zero.
      //! Subsequent decreasing character positions correspond to increasing
      //! bit positions. Bit value zero becomes the character zero, bit value
      //! one becomes the character one.
      //! Returns: The created object.
//      template <class charT = char,
//      class traits = char_traits<charT>,
//      class Allocator = allocator<charT> >
//      basic_string<charT, traits, Allocator>
//      to_string(charT zero = charT(’0’), charT one = charT(’1’)) const;

      //! Effects: Constructs an object x of class enum_set<EC> and initializes it with *this.
      //! Returns: x.flip().
      enum_set operator~() const
      {
        return enum_set(*this).flip();
      }

      //! Requires: pos is valid
      //! Throws: out_of_range if pos does not correspond to a valid bit position.
      //! Returns: true if the bit at position pos in *this has the value one.
//      bool test(size_t pos);

      //! Returns: count() == size()
      bool all() const
      {
        return bits.all();
      }

      //! Returns: count() != 0
      bool any() const
      {
        return bits.any();
      }

      //! Returns: count() == 0
      bool none() const
      {
        return bits.none();
      }

      //! Returns: enum_set<EC>(*this) <<= pos.
      enum_set operator<<(std::size_t pos) const
      {
        enum_set r = *this;
        r <<= pos;
        return r;
      }

      //! Returns: enum_set<EC>(*this) >>= pos.
      enum_set operator>>(std::size_t pos) const
      {
        enum_set r = *this;
        r >>= pos;
        return r;
      }

      //! Returns: A nonzero value if the value of each bit in *this equals the
      //! value of the corresponding bit in rhs.
//      bool operator==(const enum_set& rhs) const;

      //! Returns: A nonzero value if !(*this == rhs).
//      bool operator!=(const enum_set& rhs) const;
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

    //! Returns: enum_set<EC>(lhs) &= rhs.
    template <typename EC/*, typename Traits*/>
    enum_set<EC/*,Traits*/> operator&(const enum_set<EC/*,Traits*/>& x, const enum_set<EC/*,Traits*/>& y)
    {
      enum_set<EC/*,Traits*/> r = x;
      r &= y;
      return r;
    }

    //! Returns: enum_set<EC>>(lhs) |= rhs.
    template <typename EC/*, typename Traits*/ >
    enum_set<EC/*,Traits*/> operator|(const enum_set<EC/*,Traits*/>& x, const enum_set<EC/*,Traits*/>& y)
    {
      enum_set<EC/*,Traits*/> r = x;
      r |= y;
      return r;
    }

    //! Returns: enum_set<EC>(lhs) ˆ= rhs.
    template <typename EC/*, typename Traits*/ >
    enum_set<EC/*,Traits*/> operator^(const enum_set<EC/*,Traits*/>& x, const enum_set<EC/*,Traits*/>& y)
    {
      enum_set<EC/*,Traits*/> r = x;
      r ^= y;
      return r;
    }

    //! A formatted input function.
    //! Effects: Extracts up to N characters from is. Stores these characters
    //! in a temporary object str of type basic_string<charT, traits>, then
    //! evaluates the expression x = enum_set<EC>(str). Characters are extracted
    //! and stored until any of the following occurs:
    //! - N characters have been extracted and stored;
    //! - end-of-file occurs on the input sequence;
    //! - the next input character is neither is.widen(’0’) nor is.widen(’1’)
    //! (in which case the input character is not extracted).
    //! If no characters are stored in str, calls is.setstate(ios_base::failbit)
    //! (which may throw ios_- base::failure).
    //! Returns: is.
    template <class charT, class ch_traits, typename EC/*, typename Traits*/ >
    std::basic_istream<charT, ch_traits>&
    operator>>(std::basic_istream<charT, ch_traits>& is, enum_set<EC/*,Traits*/>& x)
    {
      return is >> x.detail_bits();
    }

    //! Returns:
    //! os << x.template to_string<charT,traits,allocator<charT> >(
    //! use_facet<ctype<charT> >(os.getloc()).widen(’0’),
    //! use_facet<ctype<charT> >(os.getloc()).widen(’1’))
    template <class charT, class ch_traits, typename EC/*, typename Traits*/ >
    std::basic_ostream<charT, ch_traits>&
    operator<<(std::basic_ostream<charT, ch_traits>& os, const enum_set<EC/*,Traits*/>& x)
    {
      return os << x.detail_bits();
    }


  } /* namespace enums */

  //! Requires: the template specialization shall meet the requirements of class template hash.
  template <typename EC/*, typename Traits*/ >
  struct hash<enums::enum_set<EC/*,Traits*/> >
  : public std::unary_function<enums::enum_set<EC/*,Traits*/>, std::size_t>
  {
    std::size_t operator()(const enums::enum_set<EC/*,Traits*/>& bs) const
    {
      return hash<std::bitset<enums::meta::size<EC>::size> >(bs.detail_bits());
    }
  };

} /* namespace boost */


#endif /*BOOST_ENUMS_ENUM_SET_HPP*/
