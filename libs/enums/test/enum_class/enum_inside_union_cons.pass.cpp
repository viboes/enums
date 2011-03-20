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

#define MyNS_EC (Ex)(EC_Cons)
#define MyENUMS ( (E0)(3) ) ( (E1)    ) ( (E2)    )


BOOST_ENUM_NS_CLASS_START(MyNS_EC, int)                              
{                                                                 
  BOOST_ENUMS_ENUMERATOR_LIST_GENERATE(MyENUMS)                        
}                                                                 
BOOST_ENUM_NS_CLASS_CONS_END(MyNS_EC, int)                           
BOOST_ENUMS_ENUM_DCL_SPE(MyNS_EC, MyENUMS, linear_enum_traiter)

#else


BOOST_ENUMS_ENUM_CLASS_DCL_CONS((Ex)(EC_Cons), int,                  
                                ( (E0)(3) )
                                ( (E1)    )
                                ( (E2)    )
                                , linear_enum_traiter)


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
