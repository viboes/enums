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
 The header \c <boost/enums/scoped/enum_type_cons.hpp> defines the declaration of enum_type_cons<> template class.
 */

#ifndef BOOST_ENUMS_SCOPED_ENUM_TYPE_CONS_HPP
#define BOOST_ENUMS_SCOPED_ENUM_TYPE_CONS_HPP

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

    //! scoped enum type with constructors
    
    //! param @c ScopedEnum : Struct scoping the enum.\n
    //! param @c UT : the underlaying storage type.\n
    //! pre @c ScopedEnum must have a nested C++98 enum @c type.\n
    template <typename ScopedEnum, typename UT=int>
    class enum_type_cons : public  ScopedEnum
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
      enum_type_cons()
      : val_(static_cast<underlying_type>(type()))
      {
      }
      
      //! explicit constructor from underlying type
      explicit enum_type_cons(underlying_type v)
      : val_(v)
      {
      }
      
      //! constructor from enum type
      enum_type_cons(type v)
      : val_(static_cast<underlying_type>(v))
      {
      }
      
   
      //! implicit conversion to enum type
      operator type()
      {
        return type(val_);
      }
      
      //! assignment
      enum_type_cons& operator=(enum_type_cons rhs)
      {
        val_=rhs.val_;
        return *this;
      }
      //! assignment from enum literals
      enum_type_cons& operator=(type rhs)
      {
        val_=static_cast<underlying_type>(rhs);
        return *this;
      }
      //! workaround in case there are no constructors       
      static enum_type_cons default_value()
      {
        enum_type_cons res;
        res.val_=static_cast<underlying_type>(type());
        return res;  
      }
      
      static enum_type_cons explicit_convert_to(underlying_type v)
      {
        enum_type_cons res;
        res.val_=v;
        return res;
        
      }
      
      static enum_type_cons explicit_convert_to(type v)
      {
        enum_type_cons res;
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

        //! conversions from enum_type_cons to underlying_type following the Boost.Conversion protocol
      friend underlying_type explicit_convert_to(enum_type_cons v,
                                        boost::conversion::dummy::type_tag<underlying_type> const&)
      {
        return boost::enums::underlying_value(v);
      }
      //! conversions from enum_type_cons to type following the Boost.Conversion protocol
      friend type explicit_convert_to(enum_type_cons v,
                             boost::conversion::dummy::type_tag<type> const&)
      {
        return boost::enums::native_value(v);
      }
    };    
  }
}

#endif // BOOST_ENUMS_SCOPED_ENUM_TYPE_CONS_HPP
