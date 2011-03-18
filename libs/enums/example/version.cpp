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
#include <stdint.h>

BOOST_ENUM_CLASS_START(Version, uint8_t)
{ Ver1 = 1, Ver2 = 2 }
BOOST_ENUM_CLASS_END(Version, uint8_t)
BOOST_ENUMS_SPECIALIZATIONS(Version, uint8_t)

struct Packet {
  Version ver;	// ok, portable 
  Version getVersion() const { return ver; }
};


