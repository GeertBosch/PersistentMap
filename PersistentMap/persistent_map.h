//
//  persistent_map.h
//  PersistentMap
//
//  Created by Geert Bosch on 11/27/15.
//  Copyright © 2015 MongoDB. All rights reserved.
//

#include <initializer_list>

namespace persistent {
    template <class Key, class T, class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T> > >
    class map {
        class node;
    public:
        // types:
        typedef Key                                                      key_type;
        typedef T                                                        mapped_type;
        typedef std::pair<const Key, T>                                  value_type;
        typedef Compare                                                  key_compare;
        typedef Allocator                                                allocator_type;
        typedef value_type&                                              reference;
        typedef const value_type&                                        const_reference;
        typedef node*                                                    iterator;
        typedef const node*                                              const_iterator;
        typedef size_t                                                   size_type;
        typedef std::ptrdiff_t                                           difference_type;
        typedef typename std::allocator_traits<Allocator>::pointer       pointer;
        typedef typename std::allocator_traits<Allocator>::const_pointer const_pointer;
        typedef std::reverse_iterator<iterator>                          reverse_iterator;
        typedef std::reverse_iterator<const_iterator>                    const_reverse_iterator;

        class value_compare {
            friend class map;
        protected:
            Compare comp;
            value_compare(Compare c) : comp(c) {}
        public:
            typedef bool        result_type;
            typedef value_type  first_argument_type;
            typedef value_type  second_argument_type;
            bool operator()(const value_type& x, const value_type& y) const {
                return comp(x.first, y.first);
            }
        };

        explicit map(const Compare& comp = Compare(),
                     const Allocator& = Allocator()) { };
        template <class InputIterator>
        map(InputIterator first, InputIterator last,
            const Compare& comp = Compare(), const Allocator& = Allocator());
        map(const map<Key,T,Compare,Allocator>& x);
        map(map<Key,T,Compare,Allocator>&& x);
        explicit map(const Allocator&);
        map(const map&, const Allocator&);
        map(map&&, const Allocator&);
        map(std::initializer_list<value_type>,
            const Compare& = Compare(),
            const Allocator& = Allocator());

        ~map() = default;

        map<Key,T,Compare,Allocator>& operator=(const map<Key,T,Compare,Allocator>& x);
        map<Key,T,Compare,Allocator>& operator=(map<Key,T,Compare,Allocator>&& x);
        map& operator=(std::initializer_list<value_type>);

        allocator_type get_allocator() const noexcept;

        // iterators:
        iterator                begin() noexcept;
        const_iterator          begin() const noexcept;
        iterator                end() noexcept;
        const_iterator          end() const noexcept;

        reverse_iterator        rbegin() noexcept;
        const_reverse_iterator  rbegin() const noexcept;
        reverse_iterator        rend() noexcept;
        const_reverse_iterator  rend() const noexcept;

        const_iterator          cbegin() noexcept;
        const_iterator          cend() noexcept;
        const_reverse_iterator  crbegin() const noexcept;
        const_reverse_iterator  crend() const noexcept;

        // capacity:
        bool      empty() const noexcept;
        size_type size() const noexcept;
        size_type max_size() const noexcept;

        // element access:
        T& operator[](const key_type& x);
        T& operator[](key_type&& x);
        T&       at(const key_type& x);
        const T& at(const key_type& x) const;

        // modifiers:
        template <class... Args> std::pair<iterator, bool> emplace(Args&&... args);
        template <class... Args>
        iterator emplace_hint(const_iterator position, Args&&... args);
        std::pair<iterator, bool> insert(const value_type& x);
        template <class P> std::pair<iterator, bool> insert(P&& x);
        iterator insert(const_iterator position, const value_type& x);
        template <class P>
        iterator insert(const_iterator position, P&&);
        template <class InputIterator>
        void insert(InputIterator first, InputIterator last);
        void insert(std::initializer_list<value_type>);

        iterator erase(const_iterator position);
        size_type erase(const key_type& x);
        iterator erase(const_iterator first, const_iterator last);
        void swap(map<Key,T,Compare,Allocator>&);
        void clear() noexcept;

        // observers:
        key_compare   key_comp() const;
        value_compare value_comp() const;

        //map operations:
        iterator        find(const key_type& x);
        const_iterator  find(const key_type& x) const;
        size_type       count(const key_type& x) const;
        
        iterator        lower_bound(const key_type& x);
        const_iterator  lower_bound(const key_type& x) const;
        iterator        upper_bound(const key_type& x);
        const_iterator  upper_bound(const key_type& x) const;
        
        std::pair<iterator,iterator> equal_range(const key_type& x);
        std::pair<const_iterator,const_iterator> equal_range(const key_type& x) const;
    };

    template <class Key, class T, class Compare, class Allocator>
    bool operator==(const map<Key,T,Compare,Allocator>& x,
                    const map<Key,T,Compare,Allocator>& y);
    template <class Key, class T, class Compare, class Allocator>
    bool operator< (const map<Key,T,Compare,Allocator>& x,
                    const map<Key,T,Compare,Allocator>& y);
    template <class Key, class T, class Compare, class Allocator>
    bool operator!=(const map<Key,T,Compare,Allocator>& x,
                    const map<Key,T,Compare,Allocator>& y);
    template <class Key, class T, class Compare, class Allocator>
    bool operator> (const map<Key,T,Compare,Allocator>& x,
                    const map<Key,T,Compare,Allocator>& y);
    template <class Key, class T, class Compare, class Allocator>
    bool operator>=(const map<Key,T,Compare,Allocator>& x,
                    const map<Key,T,Compare,Allocator>& y);
    template <class Key, class T, class Compare, class Allocator>
    bool operator<=(const map<Key,T,Compare,Allocator>& x,
                    const map<Key,T,Compare,Allocator>& y);

    template <class Key, class T, class Compare, class Allocator>
    void swap(map<Key,T,Compare,Allocator>& x,
              map<Key,T,Compare,Allocator>& y);

}