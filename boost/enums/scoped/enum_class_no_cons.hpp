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
 \file
 \brief  
 The header \c <boost/enums/scoped/enum_class_no_cons.hpp> defines the declaration of enum_class_no_cons<> template class.
 */
#error

#ifndef BOOST_ENUMS_SCOPED_ENUM_CLASS_NO_CONS_HPP
#define BOOST_ENUMS_SCOPED_ENUM_CLASS_NO_CONS_HPP

#include <boost/config.hpp>
#include <boost/conversion/explicit_convert_to.hpp>
#include <boost/enums/scoped/underlying_type.hpp>
#include <boost/enums/scoped/underlying_value.hpp>
#include <boost/enums/scoped/native_type.hpp>
#include <boost/enums/scoped/native_value.hpp>

namespace boost
{
  namespace enums
  {
    //! scoped enum class without constructors
    
    //! param @c ScopedEnum : Struct scoping the enum.\n
    //! param @c UT : the underlaying storage type.\n
    //! pre @c ScopedEnum must have a nested C++98 enum @c type.\n
    template <typename ScopedEnum, typename UT=int>
    class enum_class_no_cons : public ScopedEnum 
    {                    
    public:                                   
      //! c++98 enum type
      typedef typename ScopedEnum::type type;
      //! underlying type
      typedef UT underlying_type;                   
    private:                                        
      underlying_type val_;                         
    public:
      //! assignment
      enum_class_no_cons& operator=(enum_class_no_cons rhs)
      {
        val_=rhs.val_;
        return *this;
      }
      
      //! assignment from enum literals
      enum_class_no_cons& operator=(type rhs)
      {
        val_=static_cast<underlying_type>(rhs);
        return *this;
      }
      
      //! workaround when there are no constructors       
      static enum_class_no_cons default_value()
      {
        enum_class_no_cons res;
        res.val_=static_cast<underlying_type>(type());
        return res;  
      }
      
      static enum_class_no_cons explicit_convert_to(underlying_type v)
      {
        enum_class_no_cons res;
        res.val_=v;
        return res;
        
      }
      
      static enum_class_no_cons explicit_convert_to(type v)
      {
        enum_class_no_cons res;
        res.val_=static_cast<underlying_type>(v);
        return res;
      }
      
      //! explicit conversion function to enum type        
      type native_value() const
      {
        return type(val_);
      }
      
      //! explicit conversion function to underlying_type        
      underlying_type underlying_value() const
      {
        return val_;
      }
      
      //! equal operator
      friend bool operator==(enum_class_no_cons lhs, enum_class_no_cons rhs)
      {
        return lhs.val_ == rhs.val_;
      }
      //! equal operator
      friend bool operator==(type lhs, enum_class_no_cons rhs)
      {
        return lhs == rhs.val_;
      }
      //! equal operator
      friend bool operator==(enum_class_no_cons lhs, type rhs)
      {
        return lhs.val_ == rhs;
      }
      //! not_equal operator
      friend bool operator!=(enum_class_no_cons lhs, enum_class_no_cons rhs)
      {
        return lhs.val_ != rhs.val_;
      }
      //! not_equal operator
      friend bool operator!=(type lhs, enum_class_no_cons rhs)
      {
        return lhs != rhs.val_;
      }
      //! not_equal operator
      friend bool operator!=(enum_class_no_cons lhs, type rhs)
      {
        return lhs.val_ != rhs;
      }
      //! less_equal operator
      friend bool operator<=(enum_class_no_cons lhs, enum_class_no_cons rhs)
      {
        return lhs.val_ <= rhs.val_;
      }
      //! less_equal operator
      friend bool operator<=(type lhs, enum_class_no_cons rhs)
      {
        return lhs <= rhs.val_;
      }
      //! less_equal operator
      friend bool operator<=(enum_class_no_cons lhs, type rhs)
      {
        return lhs.val_ <= rhs;
      }
      //! less operator
      friend bool operator<(enum_class_no_cons lhs, enum_class_no_cons rhs)
      {
        return lhs.val_ < rhs.val_;
      }
      //! less operator
      friend bool operator<(type lhs, enum_class_no_cons rhs)
      {
        return lhs < rhs.val_;
      }
      //! less operator
      friend bool operator<(enum_class_no_cons lhs, type rhs)
      {
        return lhs.val_ < rhs;
      }
      //! greater_equal operator
      friend bool operator>=(enum_class_no_cons lhs, enum_class_no_cons rhs)
      {
        return lhs.val_ >= rhs.val_;
      }
      //! greater_equal operator
      friend bool operator>=(type lhs, enum_class_no_cons rhs)
      {
        return lhs >= rhs.val_;
      }
      //! greater_equal operator
      friend bool operator>=(enum_class_no_cons lhs, type rhs)
      {
        return lhs.val_ >= rhs;
      }
      //! greater operator
      friend bool operator>(enum_class_no_cons lhs, enum_class_no_cons rhs)
      {
        return lhs.val_ > rhs.val_;
      }
      //! greater operator
      friend bool operator>(type lhs, enum_class_no_cons rhs)
      {
        return lhs > rhs.val_;
      }
      //! greater operator
      friend bool operator>(enum_class_no_cons lhs, type rhs)
      {
        return lhs.val_ > rhs;
      }
      
      //! conversions from underlying_type to enum_class_no_cons following the Boost.Conversion protocol
      friend enum_class_no_cons explicit_convert_to(underlying_type v,
                                       boost::conversion::dummy::type_tag<enum_class_no_cons> const&)
      {
        enum_class_no_cons res;
        res.val_=v;
        return res;
      }
      
      //! friend conversions from type to enum_class_no_cons following the Boost.Conversion protocol
      friend enum_class_no_cons explicit_convert_to(type v,
                                       boost::conversion::dummy::type_tag<enum_class_no_cons> const&)
      {
        enum_class_no_cons res;
        res.val_=static_cast<underlying_type>(v);
        return res;
      }
      
      //! conversions from enum_class_no_cons to underlying_type following the Boost.Conversion protocol
      friend underlying_type explicit_convert_to(enum_class_no_cons v,
                                        boost::conversion::dummy::type_tag<underlying_type> const&)
      {
        return boost::enums::underlying_value(v);
      }
      
      //! conversions from enum_class_no_cons to type following the Boost.Conversion protocol
      friend type explicit_convert_to(enum_class_no_cons v,
                             boost::conversion::dummy::type_tag<type> const&)
      {
        return boost::enums::native_value(v);
      }
    };    
  }
}

#endif // BOOST_ENUMS_SCOPED_ENUM_TYPE_NO_CONS_HPP
