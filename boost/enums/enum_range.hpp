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
 The header \c <boost/enums/enum_range.hpp> defines a class template \c enum_range for viewing an enumerations as a range.
 */

#ifndef BOOST_ENUMS_ENUM_RANGE_HPP
#define BOOST_ENUMS_ENUM_RANGE_HPP

#include <boost/enums/enum_type.hpp>
//#include <boost/enums/enum_range_traits.hpp>
#include <boost/enums/val.hpp>
#include <boost/enums/pos.hpp>
#include <boost/enums/size.hpp>


#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/iterator_range.hpp>

namespace boost {
  namespace enums {
    #ifndef BOOST_ENUMS_DOXYGEN_INVOKED
    namespace enums_detail {
        // enum_iterator is an iterator over an enum  that
        // is bounded only by the limits of the enum.
        //
        // This is useful for implementing the enum_range<E>()
        // function.
        //
        // Note:
        // This use of this iterator and enum_range<E>() is appreciably less
        // performant than the corresponding hand-written integer
        // loop on many compilers.

        //! enum_iterator is a model of RandomAccessIterator
        template<typename EC /* , typename Traits=enum_range_traits<EC> */ >
        class enum_iterator
            : public boost::iterator_facade<
                        enum_iterator<EC>,
                        EC,
                        boost::random_access_traversal_tag,
                        EC,
                        std::ptrdiff_t
                    >
        {
            typedef boost::iterator_facade<
                        enum_iterator<EC>,
                        EC,
                        boost::random_access_traversal_tag,
                        EC,
                        std::ptrdiff_t
                    > base_t;
        public:
            typedef typename base_t::value_type value_type;
            typedef typename base_t::difference_type difference_type;
            typedef typename base_t::reference reference;

            enum_iterator() : index_(0) {}
            explicit enum_iterator(int x) : index_(x) {}

        private:
            void increment()
            {
                ++index_;
            }

            void decrement()
            {
                --index_;
            }

            void advance(difference_type offset)
            {
                index_ += offset;
            }

            difference_type distance_to(const enum_iterator& other) const
            {
                return other.index_ - index_;
            }

            bool equal(const enum_iterator& other) const
            {
                return index_ == other.index_;
            }

            reference dereference() const
            {
                return enums::val<EC>(index_);
            }

            friend class ::boost::iterator_core_access;
            int index_;
        };  
    } // namespace enums_detail
    #endif
	  //! \c enum_range is a model of the \e RandomAccessRange Concept associated to the enumeration \c EC.
	  
	  
    template<typename EC/* , typename Traits=enum_range_traits<EC> */ >
    class enum_range
        : public iterator_range< enums_detail::enum_iterator<EC/*, Traits*/> >
    {
        typedef enums_detail::enum_iterator<EC/*, Traits*/> iterator_t;
        typedef iterator_range<iterator_t> base_t;
    public:
		//! builds a enum range 
        enum_range()
            : base_t(iterator_t(0), iterator_t(enums::meta::size<EC>::value))
        {
        }
		
		//! builds a enum sub-range 
        enum_range(EC first, EC last)
            : base_t(iterator_t(enums::pos(first)),
                     iterator_t(enums::pos(last)+1))
        {
        }
    };
            
    //! function to generate an enum range.

    //! \c make_range allows treating enums as a model of the \e RandomAccessRange Concept.
	  
    //! \pre \c EC is a model of the \e Enumeration Concept.

    template<typename EC /*, typename Traits*/ >
    enum_range<EC>
    make_range()
    {
        return enum_range<EC/*,Traits*/>();
    }
	
	  //! function to generate an enum sub-range.
	  
	  //! \c make_range allows treating enums as a model of the \e RandomAccessRange Concept.	  
	  //! It should be noted that the first and last parameters denoted a closed range.
	  //! \pre \c EC is a model of the \e Enumeration Concept.
	  //! \param first first element of the range
	  //! \param last last element of the range
    template<typename EC /*, typename Traits */ >
    enum_range<EC>
    make_range(EC first, EC last)
    {
        return enum_range<EC /*,Traits*/ >(first,last);
    }

  } // namespace enums
} // namespace boost

#endif
