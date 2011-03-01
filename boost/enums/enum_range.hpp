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

#ifndef BOOST_ENUMS_ENUM_RANGE_HPP
#define BOOST_ENUMS_ENUM_RANGE_HPP

#include <boost/enums/enum_type.hpp>
#include <boost/enums/enum_traits.hpp>


#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/iterator_range.hpp>

namespace boost {
  namespace enums {
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
        template<typename EC, typename Traits=enum_traits<EC> >
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
                return Traits::val(index_);
            }

            friend class ::boost::iterator_core_access;
            int index_;
        };  
    } // namespace enums_detail
    
    template<typename EC, typename Traits=enum_traits<EC> >
    class enum_range
        : public iterator_range< enums_detail::enum_iterator<EC, Traits> >
    {
        typedef enums_detail::enum_iterator<EC, Traits> iterator_t;
        typedef iterator_range<iterator_t> base_t;
    public:
        enum_range()
            : base_t(iterator_t(Traits::first_index), iterator_t(Traits::last_index+1))
        {
        }
        enum_range(EC first, EC last)
            : base_t(iterator_t(Traits::pos(first)), 
                     iterator_t(Traits::pos(last)+1))
        {
        }
    };
            
    template<typename EC, typename Traits >
    enum_range<EC>
    make_range()
    {
        return enum_range<EC,Traits>();
    }
    template<typename EC, typename Traits >
    enum_range<EC>
    make_range(EC first, EC last)
    {
        return enum_range<EC,Traits>(first,last);
    }

  } // namespace enums
} // namespace boost

#endif
