//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <array>

// template <class T, typename EC >
// struct enum_array
// {
//     // types:
//     typedef T& reference;
//     typedef const T& const_reference;
//     typedef implementation defined iterator;
//     typedef implementation defined const_iterator;
//     typedef T value_type;
//     typedef T* pointer;
//     typedef size_t size_type;
//     typedef ptrdiff_t difference_type;
//     typedef T value_type;
//     typedef boost::reverse_iterator<iterator> reverse_iterator;
//     typedef boost::reverse_iterator<const_iterator> const_reverse_iterator;

#include <boost/enums/enum_array.hpp>
#include "./Ex.hpp"
#include <boost/detail/lightweight_test.hpp>
#include <iterator>
#include <boost/type_traits.hpp>
#include <boost/static_assert.hpp>

int main()
{
    {
        typedef double T;
        typedef boost::enums::enum_array<T, EC3> C;
        BOOST_STATIC_ASSERT((boost::is_same<C::reference, T&>::value));
        BOOST_STATIC_ASSERT((boost::is_same<C::const_reference, const T&>::value));
        BOOST_STATIC_ASSERT((boost::is_same<C::iterator, T*>::value));
        BOOST_STATIC_ASSERT((boost::is_same<C::const_iterator, const T*>::value));
        BOOST_STATIC_ASSERT((boost::is_same<C::pointer, T*>::value));
        BOOST_STATIC_ASSERT((boost::is_same<C::const_pointer, const T*>::value));
        BOOST_STATIC_ASSERT((boost::is_same<C::size_type, std::size_t>::value));
        BOOST_STATIC_ASSERT((boost::is_same<C::difference_type, std::ptrdiff_t>::value));
        BOOST_STATIC_ASSERT((boost::is_same<C::reverse_iterator, std::reverse_iterator<C::iterator> >::value));
        BOOST_STATIC_ASSERT((boost::is_same<C::const_reverse_iterator, std::reverse_iterator<C::const_iterator> >::value));
    }
}
