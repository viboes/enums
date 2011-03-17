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

#include "./EnumClass.hpp"
#include <boost/detail/lightweight_test.hpp>
#include <boost/enums/containers/enum_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/irange.hpp>

int main() {

  using namespace boost;
  using namespace boost::enums;

  BOOST_CONCEPT_ASSERT(( SinglePassRangeConcept < enum_range<EnumClass> > ));
  BOOST_CONCEPT_ASSERT(( ForwardRangeConcept  < enum_range<EnumClass> > ));
//  BOOST_CONCEPT_ASSERT(( BidirectionalRangeConcept  < iterator_range< range_detail::integer_iterator<int> > > ));


//  BOOST_CONCEPT_ASSERT(( BidirectionalRangeConcept  < enum_range<EnumClass> > ));
//  BOOST_CONCEPT_ASSERT(( RandomAccessRangeConcept  < enum_range<EnumClass> > ));

  {
    enum_range<EnumClass> er;
    EnumClass e = *boost::begin(er);
    BOOST_TEST(e==EnumClass::Default);
  }
  return boost::report_errors();
}
