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

#include <boost/enums/scoped.hpp>
#include <boost/enums/ordinal.hpp>
#include <boost/enums/pp/enumerator_list.hpp>
#include <boost/enums/pp/enum_declaration.hpp>

#if 0

namespace Ex {
  BOOST_ENUM_CLASS_START(EC_Cons, int) {
    E0 = 3,
    E1,
    E2
  } BOOST_ENUM_CLASS_CONS_END(EC_Cons, int)
}
BOOST_ENUMS_SPECIALIZATIONS(Ex::EC_Cons, int)

enum ExtrinsecEnum {
  Default = 3,
  Enum1,
  Enum2
};

struct UNS {
enum type {
    Default = 3,
    Enum1,
    Enum2
};
};

template <typename E>
struct NS
{
  typedef E type;
};


template <typename E>
struct EC1 : NS<E>
{
};

template <typename SE>
struct EC2 : SE
{
};

typedef EC2<UNS> ScopedEnum2;
static const ScopedEnum2::type e1 = ScopedEnum2::Enum1;
typedef EC1<ExtrinsecEnum> ScopedEnum1;
//static const ScopedEnum1::type e2 = ScopedEnum1::Enum1; //error: ‘Enum1’ is not a member of ‘ScopedEnum1’


#else
#if 0
BOOST_ENUM_NS_CLASS_START((Ex)(EC_Cons), int) {
  E0 = 3,
  E1,
  E2
}
BOOST_ENUM_NS_CLASS_CONS_END( (Ex)(EC_Cons), int)




#define MyNS_EC (Ex)(EC_Cons)
#define MyENUMS ( (E0)(3) ) ( (E1)    ) ( (E2)    )


BOOST_ENUM_NS_CLASS_START(MyNS_EC, int)
{
  BOOST_ENUMS_ENUMERATOR_LIST_GENERATE(MyENUMS)
}
BOOST_ENUM_NS_CLASS_CONS_END(MyNS_EC, int)
BOOST_ENUMS_ENUM_DCL_SPE(MyNS_EC, MyENUMS, linear_enum_traiter)
namespace boost {
  namespace enums {
    namespace meta {
      BOOST_ENUMS_ENUM_DCL_SIZE_SPE(MyNS_EC, MyENUMS)
      BOOST_PP_SEQ_FOR_EACH(
                            BOOST_ENUMS_ENUM_DCL_POS_VAL_SPE,
                            BOOST_ENUMS_NAMESPACES_CLASS_QNAME(MyNS_EC),
                            MyENUMS
                            )
      BOOST_ENUMS_ENUM_DCL_TRAITS_SPE(MyNS_EC, linear_enum_traiter)
    }
  }
}
#else


BOOST_ENUMS_ENUM_CLASS_DCL_CONS((Ex)(EC_Cons), int,
                                ( (E0)(3) )
                                ( (E1)    )
                                ( (E2)    )
                                , linear_enum_traiter)


//~ namespace Ex {
  //~ enum class EC_Cons : int { E0 = 3 , E1 , E2 } ;
  //~ inline bool operator ==(EC_Cons lhs, EC_Cons rhs) { return (int)(lhs) == (int)(rhs); }
  //~ inline bool operator !=(EC_Cons lhs, EC_Cons rhs) { return (int)(lhs) != (int)(rhs); }
  //~ inline bool operator <(EC_Cons lhs, EC_Cons rhs) { return (int)(lhs) < (int)(rhs); }
  //~ inline bool operator <=(EC_Cons lhs, EC_Cons rhs) { return (int)(lhs) <= (int)(rhs); }
  //~ inline bool operator >(EC_Cons lhs, EC_Cons rhs) { return (int)(lhs) > (int)(rhs); }
  //~ inline bool operator >=(EC_Cons lhs, EC_Cons rhs) { return (int)(lhs) >= (int)(rhs);}
//~ }
      //~ namespace boost {
        //~ namespace enums {
          //~ namespace meta {
            //~ template <> struct underlying_type<Ex::EC_Cons> { typedef int type; };
            //~ }
            //~ }
            //~ }
//~ namespace Ex {
      //~ inline EC_Cons convert_to(int v , boost::dummy::type_tag<EC_Cons> const& ) { return EC_Cons(v); }
      //~ inline EC_Cons convert_to(boost::enums::native_type<EC_Cons>::type v , boost::dummy::type_tag<EC_Cons> const& ) { return v; }
      //~ inline int convert_to(EC_Cons v , boost::dummy::type_tag<int> const& ) { return boost::enums::underlying_value(v); }
//~ }
            //~ namespace boost {
              //~ namespace enums {
                //~ namespace meta {
                  //~ template <> struct size<Ex :: EC_Cons> { static const std::size_t value=3; };
                  //~ template <> struct pos<Ex :: EC_Cons, Ex :: EC_Cons :: E0> { static const std::size_t value = 0; };
                  //~ template <> struct val<Ex :: EC_Cons, 0> { static const boost::enums::native_type<Ex :: EC_Cons>::type value = Ex :: EC_Cons::E0; };
                  //~ template <> struct pos<Ex :: EC_Cons, Ex :: EC_Cons :: E1> { static const std::size_t value = 1; };
                  //~ template <> struct val<Ex :: EC_Cons, 1> { static const boost::enums::native_type<Ex :: EC_Cons>::type value = Ex :: EC_Cons::E1; };
                  //~ template <> struct pos<Ex :: EC_Cons, Ex :: EC_Cons :: E2> { static const std::size_t value = 2; };
                  //~ template <> struct val<Ex :: EC_Cons, 2> { static const boost::enums::native_type<Ex :: EC_Cons>::type value = Ex :: EC_Cons::E2; };
                  //~ template <> struct enum_traits<Ex :: EC_Cons> : linear_enum_traiter<Ex :: EC_Cons> {};
                    //~ }
                    //~ }
                    //~ }
                    //~ namespace Ex {
                      //~ inline EC_Cons convert_to( const char* str, boost::dummy::type_tag<EC_Cons> const& ) { if (strcmp( str, "E0" ) == 0) { return boost::conversion::convert_to<EC_Cons>( EC_Cons::E0 ); } if (strcmp( str, "E1" ) == 0) { return boost::conversion::convert_to<EC_Cons>( EC_Cons::E1 ); } if (strcmp( str, "E2" ) == 0) { return boost::conversion::convert_to<EC_Cons>( EC_Cons::E2 ); } throw "invalid string for " "EC_Cons"; }
                        //~ inline EC_Cons convert_to( const std::string& str, boost::dummy::type_tag<EC_Cons> const& ) { return boost::conversion::convert_to<EC_Cons>( str.c_str() ); }
                        //~ inline const char* c_str(EC_Cons e) {
                          //~ switch (boost::enums::native_value(e)) {
                            //~ case EC_Cons::E0 : return("E0");
                            //~ case EC_Cons::E1 : return("E1");
                            //~ case EC_Cons::E2 : return("E2");
                            //~ default: throw "invalid value for " "EC_Cons";
                          //~ }
                          //~ }
                          //~ }


#endif
#endif

#if defined(BOOST_NO_ENUM_UNRESTRICTED_UNION)
//#warning "not applicable as unrestricted union not available"
#else
// The ENUM can NOT be used as member of a union as it is the case of the underlying enum.
union U {
  Ex::EC_Cons e;
  int i;
};
#endif
