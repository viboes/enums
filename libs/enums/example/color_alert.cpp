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

#include <boost/enums/scoped/emulation.hpp>
#include <boost/enums/pp/enum_declaration.hpp>

BOOST_ENUMS_ENUM_CLASS_DCL_CONS((Color), int,
                                ( (Red) )
                                ( (Orange)    )
                                ( (Yellow)    )
                                ( (Green)    )
                                ( (Blue)    )
                                ( (Violet)    )
                                , linear_enum_traiter)
//BOOST_ENUM_CLASS_START(Color, int)
//{ Red, Orange, Yellow, Green, Blue, Violet }
//BOOST_ENUM_CLASS_END(Color, int)
//BOOST_ENUMS_SPECIALIZATIONS(Color, int)


BOOST_ENUMS_ENUM_CLASS_DCL_CONS((Alert), int,
                                ( (Green) )
                                ( (Yellow)    )
                                ( (Red)    )
                                , linear_enum_traiter)
//BOOST_ENUM_CLASS_START(Alert, int)
//{ Green, Yellow, Red }
//BOOST_ENUM_CLASS_END(Alert, int)
//BOOST_ENUMS_SPECIALIZATIONS(Alert, int)

void compile_fail() { 
  Alert a = Alert::Green; 
  bool armWeapons = ( a >= Color::Yellow ); 
}

