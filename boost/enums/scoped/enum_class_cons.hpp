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
 The header \c <boost/enums/scoped/enum_class_cons.hpp> defines the declaration of enum_class_cons<> template class.
 */

#ifndef BOOST_ENUMS_SCOPED_ENUM_TYPE_CONS_HPP
#define BOOST_ENUMS_SCOPED_ENUM_TYPE_CONS_HPP

#include <boost/config.hpp>

namespace boost
{
  namespace enums
  {
    //! scoped enum class with constructors
    
    //! param @c ScopedEnum : Struct scoping the enum.\n
    //! param @c UT : the underlaying storage type.\n
    //! pre @c ScopedEnum must have a nested C++98 enum @c type.\n
    
    template <typename ScopedEnum, typename UT=int>
    class enum_class_cons : public ScopedEnum 
    {                    
    public:     
      //! c++98 enum type
      typedef typename ScopedEnum::type type;
      //! underlying type
      typedef UT underlying_type;                   
    private:
      underlying_type val_;                         
    public:
      //! default constructor
      enum_class_cons()
      : val_(static_cast<underlying_type>(type()))
      {
      }
      //! explicit constructor from underlying type
      explicit enum_class_cons(underlying_type v)
      : val_(v)
      {
      }
      //! constructor from enum type
      enum_class_cons(type v)
      : val_(static_cast<underlying_type>(v))
      {
      }
      //! assignment
      enum_class_cons& operator=(enum_class_cons rhs)
      {
        val_=rhs.val_;
        return *this;
      }
      //! assignment from enum literals
      enum_class_cons& operator=(type rhs)
      {
        val_=static_cast<underlying_type>(rhs);
        return *this;
      }
      //! workaround when there are no constructors       
      static enum_class_cons default_value()
      {
        enum_class_cons res;
        res.val_=static_cast<underlying_type>(type());
        return res;  
      }
      
      static enum_class_cons convert_to(underlying_type v)
      {
        enum_class_cons res;
        res.val_=v;
        return res;
        
      }
      static enum_class_cons convert_to(type v)
      {
        enum_class_cons res;
        res.val_=static_cast<underlying_type>(v);
        return res;
      }
      //! explicit conversion function to enum type        
      type enum_value() const
      {
        return type(val_);
      }
      //! explicit conversion function to underlying_type        
      underlying_type underlying_value() const
      {
        return val_;
      }
      
      //! equal operator
      friend bool operator==(enum_class_cons lhs, enum_class_cons rhs)
      {
        return lhs.val_ == rhs.val_;
      }
      //! equal operator
      friend bool operator==(type lhs, enum_class_cons rhs)
      {
        return lhs == rhs.val_;
      }
      //! equal operator
      friend bool operator==(enum_class_cons lhs, type rhs)
      {
        return lhs.val_ == rhs;
      }
      //! not_equal operator
      friend bool operator!=(enum_class_cons lhs, enum_class_cons rhs)
      {
        return lhs.val_ != rhs.val_;
      }
      //! not_equal operator
      friend bool operator!=(type lhs, enum_class_cons rhs)
      {
        return lhs != rhs.val_;
      }
      //! not_equal operator
      friend bool operator!=(enum_class_cons lhs, type rhs)
      {
        return lhs.val_ != rhs;
      }
      //! less_equal operator
      friend bool operator<=(enum_class_cons lhs, enum_class_cons rhs)
      {
        return lhs.val_ <= rhs.val_;
      }
      //! less_equal operator
      friend bool operator<=(type lhs, enum_class_cons rhs)
      {
        return lhs <= rhs.val_;
      }
      //! less_equal operator
      friend bool operator<=(enum_class_cons lhs, type rhs)
      {
        return lhs.val_ <= rhs;
      }
      //! less operator
      friend bool operator<(enum_class_cons lhs, enum_class_cons rhs)
      {
        return lhs.val_ < rhs.val_;
      }
      //! less operator
      friend bool operator<(type lhs, enum_class_cons rhs)
      {
        return lhs < rhs.val_;
      }
      //! less operator
      friend bool operator<(enum_class_cons lhs, type rhs)
      {
        return lhs.val_ < rhs;
      }
      //! greater_equal operator
      friend bool operator>=(enum_class_cons lhs, enum_class_cons rhs)
      {
        return lhs.val_ >= rhs.val_;
      }
      //! greater_equal operator
      friend bool operator>=(type lhs, enum_class_cons rhs)
      {
        return lhs >= rhs.val_;
      }
      //! greater_equal operator
      friend bool operator>=(enum_class_cons lhs, type rhs)
      {
        return lhs.val_ >= rhs;
      }
      //! greater operator
      friend bool operator>(enum_class_cons lhs, enum_class_cons rhs)
      {
        return lhs.val_ > rhs.val_;
      }
      //! greater operator
      friend bool operator>(type lhs, enum_class_cons rhs)
      {
        return lhs > rhs.val_;
      }
      //! greater operator
      friend bool operator>(enum_class_cons lhs, type rhs)
      {
        return lhs.val_ > rhs;
      }
#if 0
        //! conversions from underlying_type to enum_type_cons following the Boost.Conversion protocol
      friend enum_class_cons convert_to(underlying_type v, 
                                       boost::dummy::type_tag<enum_class_cons> const&)
      {
        enum_class_cons res;
        res.val_=v;
        return res;
        
      }

      //! friend conversions from type to enum_type_cons following the Boost.Conversion protocol
      friend enum_class_cons convert_to(type v, 
                                       boost::dummy::type_tag<enum_class_cons> const&)
      {
        enum_class_cons res;
        res.val_=static_cast<underlying_type>(v);
        return res;
      }
#endif
      //! conversions from enum_type_cons to underlying_type following the Boost.Conversion protocol
      friend underlying_type convert_to(enum_class_cons v, 
                                        boost::dummy::type_tag<underlying_type> const&)
      {
        return boost::enums::underlying_value(v);
      }
      
      //! conversions from enum_type_cons to type following the Boost.Conversion protocol
      friend type convert_to(enum_class_cons v, 
                             boost::dummy::type_tag<type> const&)
      {
        return boost::enums::enum_value(v);
      }
    };    
  }
}

#endif // BOOST_ENUMS_SCOPED_ENUM_TYPE_MIXIN_HPP
