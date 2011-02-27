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

#include <cstring>
#include <string>
#include <iostream>

#include "./EnumClass.hpp"
#include "./f.hpp"
#include <boost/detail/lightweight_test.hpp>

#define RUN_TIME
#define COMPILE_TIME

int main() {

  using namespace boost;
  using namespace boost::enums;


  { // The wrapper can be constructed from a valid const char* repressentation
    EnumClass e = convert_to<EnumClass>("Enum2");
    BOOST_TEST(e==EnumClass::Enum2);
  }
#ifdef COMPILE_TIME2
  { // Construction of the wrapper from const char * compile fails
    const char* ptr = 0;
    EnumClass e0=ptr;
  }
#endif
#ifdef RUN_TIME2
  { // The wrapper can not be constructed from an invalid const char* repressentation
    EnumClass e = convert_to<EnumClass>("CHASSE");
    // ... fail
  }
#endif
  { // The wrapper can be constructed from a valid std::string repressentation
    std::string str = "Enum2";
    EnumClass e = convert_to<EnumClass>(str);
    BOOST_TEST(e==EnumClass::Enum2);
    BOOST_TEST(strcmp(c_str(e),"EnumClass::Enum2")==0);
  }
#ifdef COMPILE_TIME2
  { // Construction of the wrapper from const char * compile fails
    std::string str;
    EnumClass e0 = str;
  }
#endif
#ifdef RUN_TIME2
  { // The wrapper can not be constructed from an invalid std::string repressentation
    std::string str = "CHASSE";
    EnumClass e = convert_to<EnumClass>(str);
    // ... fail
    BOOST_TEST(e==EnumClass::Enum2);
    BOOST_TEST(strcmp(c_str(e), "EnumClass::CHASSE")==0);
  }
#endif

  //~ { // Explicit conversion from valid int works
    //~ EnumClass e(convert_to<EnumClass>(u’\1);
    //~ BOOST_TEST(e==EnumClass::Enum1);
  //~ }
  //~ { // Explicit conversion from invalid int works also !!!
    //~ EnumClass e(convert_to<EnumClass>(u’\3);
    //~ // ... fail
  //~ }
  //~ { // Construction of the wrapper with a valid int works
    //~ EnumClass e(convert_to<EnumClass>(u’\2);
    //~ BOOST_TEST(e==EnumClass::Enum2);
  //~ }
  //~ { // Construction of the wrapper with an invalid ints results in run-time error
    //~ EnumClass e(convert_to<EnumClass>(u’\3);
    //~ //BOOST_TEST(e==3);
  //~ }
#if !defined(CTOR) &&  (BOOST_ENUMS_USE_CONSTRUCTORS==0)
  { // The wrapper can be used as member of a union as it is the case of the underlying enum (When constructors are not defined).
    union U {
      EnumClass e;
      int i;
    };
    U u;
    u.e = EnumClass::Enum1;
  }
#endif
  { // The wrapper can be used in switch through the function get only :(
    //~ EnumClass e = default_value<EnumClass>();
    EnumClass e ;
    switch (get_value(e)) { // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      case EnumClass::Enum1:
      case EnumClass::Enum2:
      case EnumClass::Default:
        std::cout << e << std::endl;
        break;
      default:
        std::cout << e << ":"<< get_value(e) << std::endl;
        ;
    }
  }
  return boost::report_errors();
}
