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
 The header \c <boost/enums/enum_type_cons.hpp> defines the declaration of enum_type_cons<> template class.
 */

#ifndef BOOST_ENUMS_ENUM_TYPE_CONS_HPP
#define BOOST_ENUMS_ENUM_TYPE_CONS_HPP

#include <boost/config.hpp>

namespace boost
{
  namespace enums
  {
    template <typename ScopedEnum, typename UT=typename ScopedEnum::type>
    class enum_type_cons : public ScopedEnum 
    {                    
    public:                                         
      typedef typename ScopedEnum::type type;                                   
      typedef UT underlying_type;                   
    private:                                        
      underlying_type val_;                         
    public:
        // default constructor
      enum_type_cons()
      : val_(static_cast<underlying_type>(type()))
      {
      }
        // explicit constructor from underlying type
      explicit enum_type_cons(underlying_type v)
      : val_(v)
      {
      }
        // constructor from enum type
      enum_type_cons(type v)
      : val_(static_cast<underlying_type>(v))
      {
      }
      // implicit conversion to underlying_type
      operator underlying_type()
      {
        return val_;
      }
      // implicit conversion to enum type
      operator type()
      {
        return type(val_);
      }
      // assignment
      enum_type_cons& operator=(enum_type_cons rhs)
      {
        val_=rhs.val_;
        return *this;
      }
      // assignment from enum literals
      enum_type_cons& operator=(type rhs)
      {
        val_=static_cast<underlying_type>(rhs);
        return *this;
      }
      // workaround in case there are no constructors       
      static enum_type_cons default_value()
      {
        enum_type_cons res;
        res.val_=static_cast<underlying_type>(type());
        return res;  
      }
      static enum_type_cons convert_to(underlying_type v)
      {
        enum_type_cons res;
        res.val_=v;
        return res;
        
      }
      static enum_type_cons convert_to(type v)
      {
        enum_type_cons res;
        res.val_=static_cast<underlying_type>(v);
        return res;
      }
      // explicit conversion in case explicit conversions are not available        
      type enum_value() const
      {
        return type(val_);
      }
      underlying_type underlying_value() const
      {
        return val_;
      }
      //! equal operator
      friend bool operator==(enum_type_cons lhs, enum_type_cons rhs)
      {
        return lhs.val_ == rhs.val_;
      }
      //! equal operator
      friend bool operator==(type lhs, enum_type_cons rhs)
      {
        return lhs == rhs.val_;
      }
      //! equal operator
      friend bool operator==(enum_type_cons lhs, type rhs)
      {
        return lhs.val_ == rhs;
      }
      //! not_equal operator
      friend bool operator!=(enum_type_cons lhs, enum_type_cons rhs)
      {
        return lhs.val_ != rhs.val_;
      }
      //! not_equal operator
      friend bool operator!=(type lhs, enum_type_cons rhs)
      {
        return lhs != rhs.val_;
      }
      //! not_equal operator
      friend bool operator!=(enum_type_cons lhs, type rhs)
      {
        return lhs.val_ != rhs;
      }
      //! less_equal operator
      friend bool operator<=(enum_type_cons lhs, enum_type_cons rhs)
      {
        return lhs.val_ <= rhs.val_;
      }
      //! less_equal operator
      friend bool operator<=(type lhs, enum_type_cons rhs)
      {
        return lhs <= rhs.val_;
      }
      //! less_equal operator
      friend bool operator<=(enum_type_cons lhs, type rhs)
      {
        return lhs.val_ <= rhs;
      }
      //! less operator
      friend bool operator<(enum_type_cons lhs, enum_type_cons rhs)
      {
        return lhs.val_ < rhs.val_;
      }
      //! less operator
      friend bool operator<(type lhs, enum_type_cons rhs)
      {
        return lhs < rhs.val_;
      }
      //! less operator
      friend bool operator<(enum_type_cons lhs, type rhs)
      {
        return lhs.val_ < rhs;
      }
      //! greater_equal operator
      friend bool operator>=(enum_type_cons lhs, enum_type_cons rhs)
      {
        return lhs.val_ >= rhs.val_;
      }
      //! greater_equal operator
      friend bool operator>=(type lhs, enum_type_cons rhs)
      {
        return lhs >= rhs.val_;
      }
      //! greater_equal operator
      friend bool operator>=(enum_type_cons lhs, type rhs)
      {
        return lhs.val_ >= rhs;
      }
      //! greater operator
      friend bool operator>(enum_type_cons lhs, enum_type_cons rhs)
      {
        return lhs.val_ > rhs.val_;
      }
      //! greater operator
      friend bool operator>(type lhs, enum_type_cons rhs)
      {
        return lhs > rhs.val_;
      }
      //! greater operator
      friend bool operator>(enum_type_cons lhs, type rhs)
      {
        return lhs.val_ > rhs;
      }
      
#if 0
      //! conversions from underlying_type to enum_type_cons following the Boost.Conversion protocol
      friend enum_type_cons convert_to(underlying_type v, 
                                       boost::dummy::type_tag<enum_type_cons> const&)
      {
        enum_type_cons res;
        res.val_=v;
        return res;
        
      }
      
      //! friend conversions from type to enum_type_cons following the Boost.Conversion protocol
      friend enum_type_cons convert_to(type v, 
                                       boost::dummy::type_tag<enum_type_cons> const&)
      {
        enum_type_cons res;
        res.val_=static_cast<underlying_type>(v);
        return res;
      }
#endif
        //! conversions from enum_type_cons to underlying_type following the Boost.Conversion protocol
      friend underlying_type convert_to(enum_type_cons v, 
                                        boost::dummy::type_tag<underlying_type> const&)
      {
        return boost::enums::underlying_value(v);
      }
      //! conversions from enum_type_cons to type following the Boost.Conversion protocol
      friend type convert_to(enum_type_cons v, 
                             boost::dummy::type_tag<type> const&)
      {
        return boost::enums::enum_value(v);
      }
    };    
  }
}

#endif // BOOST_ENUMS_ENUM_TYPE_MIXIN_HPP
