//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2011.
// Distributed under the Boost
// Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/enums for documentation.
//
//////////////////////////////////////////////////////////////////////////////

/*!
 @file
 @brief  
 The header \c <boost/enums/scoped/enum_class_cons.hpp> defines the declaration of enum_class_cons<> template class.
 */

#ifndef BOOST_ENUMS_SCOPED_ENUM_CLASS_CONS_HPP
#define BOOST_ENUMS_SCOPED_ENUM_CLASS_CONS_HPP

#include <boost/config.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/enums/scoped/underlying_type.hpp>
#include <boost/enums/scoped/underlying_value.hpp>
#include <boost/enums/scoped/native_type.hpp>
#include <boost/enums/scoped/native_value.hpp>

namespace boost
{
  namespace enums
  {
    //! Scoped enum class with constructors.
    //!
    //! @TParams
    //! @Param{ScopedEnum,Struct scoping the enumerators}
    //! @Param{UT,the underlaying storage type}
    //! @Requires @c ScopedEnum must have a nested C++98 enum @c type.
    //!
    //! @c enum_class_cons wraps the underlying type @c UT providing only the 
    //! needed constructors, explicit conversion operations and comparison operators. 
    //! The inheritance to a scoping struct @ScopedEnum mak available the scoped 
    //! enumerators as if they where defined here.
    //!
    //! This class is not implicitly convertible to the underlying type, 
    //! neither to the enum type. Explicit conversion can be done using @c 
    //! underlying_value<>(e), @c native_value<>(e) or the @c converto_to<>(e).
    //! @Note This class can not be used inside a union with compilers that donesn't support unrestricted unions.
    
    template <typename ScopedEnum, typename UT=int>
    class enum_class_cons : public ScopedEnum 
    {                    
    public:     
      //! c++98 native enum type
      typedef typename ScopedEnum::type type;
      //! underlying type
      typedef UT underlying_type;                   
    private:
      //! storage for exposition only
      underlying_type val_;                         
    public:
      //! default construct 
      
      //! @Effects As if it was initialized using the default constructor of the native enum type.
      //! @Post type(this->val_) == type()
      enum_class_cons()
      : val_(static_cast<underlying_type>(type()))
      {
      }
      //! explicit constructor from underlying type
      //! @Post val_ == v
      explicit enum_class_cons(underlying_type v)
      : val_(v)
      {
      }
      //! constructor from enum type
      //! @Post type(val_) == v
      enum_class_cons(type v)
      : val_(static_cast<underlying_type>(v))
      {
      }
      //! assignment
      //! @Post val_ == rhs.val_
      //! @Returns @c *this
      enum_class_cons& operator=(enum_class_cons rhs)
      {
        val_=rhs.val_;
        return *this;
      }
      //! assignment from enum literals
      //! @Post type(val_) == rhs.val_
      //! @Returns @c *this
      enum_class_cons& operator=(type rhs)
      {
        val_=static_cast<underlying_type>(rhs);
        return *this;
      }
      
      //! default_value builder
      //!
      //! This function is provided to be uniform with scoped enums with no constructors.
      //! @Returns @c EC().
      static enum_class_cons default_value()
      {
        enum_class_cons res;
        res.val_=static_cast<underlying_type>(type());
        return res;  
      }
      
      //! explicit conversion function to enum type        

      //! @Returns @c type(val_).
      type native_value() const
      {
        return type(val_);
      }
      //! explicit conversion function to underlying_type        

      //! @Returns @c val_.
      underlying_type underlying_value() const
      {
        return val_;
      }
      
      //! equal operator

      //! @Returns <tt>lhs.val_ == rhs.val_</tt>.
      friend bool operator==(enum_class_cons lhs, enum_class_cons rhs)
      {
        return lhs.val_ == rhs.val_;
      }
      //! equal operator
      //! @Returns <tt>lhs == rhs.val_</tt>.
      friend bool operator==(type lhs, enum_class_cons rhs)
      {
        return lhs == rhs.val_;
      }
      //! equal operator
      
      //! @Returns <tt>lhs.val_ == rhs</tt>.      
      friend bool operator==(enum_class_cons lhs, type rhs)
      {
        return lhs.val_ == rhs;
      }
      //! not_equal operator
      //! @Returns <tt>lhs.val_ != rhs.val_</tt>.
      
      friend bool operator!=(enum_class_cons lhs, enum_class_cons rhs)
      {
        return lhs.val_ != rhs.val_;
      }
      //! not_equal operator

      //! @Returns <tt>lhs != rhs.val_</tt>.
      friend bool operator!=(type lhs, enum_class_cons rhs)
      {
        return lhs != rhs.val_;
      }
      //! not_equal operator
      
      //! @Returns <tt>lhs.val_ != rhs</tt>.      
      friend bool operator!=(enum_class_cons lhs, type rhs)
      {
        return lhs.val_ != rhs;
      }
      //! less_equal operator
      //! @Returns <tt>lhs.val_ <= rhs.val_</tt>.
      friend bool operator<=(enum_class_cons lhs, enum_class_cons rhs)
      {
        return lhs.val_ <= rhs.val_;
      }
      //! less_equal operator
      //! @Returns <tt>lhs <= rhs.val_</tt>.
      friend bool operator<=(type lhs, enum_class_cons rhs)
      {
        return lhs <= rhs.val_;
      }
      //! less_equal operator
      //! @Returns <tt>lhs.val_ <= rhs</tt>.
      friend bool operator<=(enum_class_cons lhs, type rhs)
      {
        return lhs.val_ <= rhs;
      }
      //! less operator
      //! @Returns <tt>lhs.val_ < rhs.val_</tt>.     
      friend bool operator<(enum_class_cons lhs, enum_class_cons rhs)
      {
        return lhs.val_ < rhs.val_;
      }
      //! less operator
      //! @Returns <tt>lhs <= rhs.val_</tt>.
      friend bool operator<(type lhs, enum_class_cons rhs)
      {
        return lhs < rhs.val_;
      }
      //! less operator
      //! @Returns <tt>lhs.val_ <= rhs</tt>.
      friend bool operator<(enum_class_cons lhs, type rhs)
      {
        return lhs.val_ < rhs;
      }
      //! greater_equal operator
      //! @Returns <tt>lhs.val_ >= rhs.val_</tt>.
      friend bool operator>=(enum_class_cons lhs, enum_class_cons rhs)
      {
        return lhs.val_ >= rhs.val_;
      }
      //! greater_equal operator
      //! @Returns <tt>lhs >= rhs.val_</tt>.
      friend bool operator>=(type lhs, enum_class_cons rhs)
      {
        return lhs >= rhs.val_;
      }
      //! greater_equal operator
      //! @Returns <tt>lhs.val_ >= rhs</tt>.
      friend bool operator>=(enum_class_cons lhs, type rhs)
      {
        return lhs.val_ >= rhs;
      }
      //! greater operator
      //! @Returns <tt>lhs.val_ > rhs.val_</tt>.
      friend bool operator>(enum_class_cons lhs, enum_class_cons rhs)
      {
        return lhs.val_ > rhs.val_;
      }
      //! greater operator
      //! @Returns <tt>lhs > rhs.val_</tt>.
      friend bool operator>(type lhs, enum_class_cons rhs)
      {
        return lhs > rhs.val_;
      }
      //! greater operator
      //! @Returns <tt>lhs.val_ > rhs</tt>.
      friend bool operator>(enum_class_cons lhs, type rhs)
      {
        return lhs.val_ > rhs;
      }
      
      //! conversions from enum_class_cons to underlying_type following the Boost.Conversion protocol

      //! @Returns <tt>boost::enums::underlying_value(v)</tt>.
      friend underlying_type convert_to(enum_class_cons v, 
                                        boost::conversion::dummy::type_tag<underlying_type> const&)
      {
        return boost::enums::underlying_value(v);
      }
      
      //! conversions from enum_class_cons to type following the Boost.Conversion protocol

      //! @Returns <tt>boost::enums::native_value(v)</tt>.
      friend type convert_to(enum_class_cons v, 
                             boost::conversion::dummy::type_tag<type> const&)
      {
        return boost::enums::native_value(v);
      }
    };    
  }
}

#endif // BOOST_ENUMS_SCOPED_ENUM_TYPE_MIXIN_HPP
