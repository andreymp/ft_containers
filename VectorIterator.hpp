/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobject <jobject@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:01:47 by jobject           #+#    #+#             */
/*   Updated: 2022/01/26 16:18:35 by jobject          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORITERATOR_HPP
# define VECTORITERATOR_HPP

namespace ft {
	template<class T>
    class VectorIterator {
        public:
            typedef T   value_type;
            typedef T&  reference;
            typedef T*  pointer;
        protected:
            pointer p;
        public:
            VectorIterator() {}
            ~VectorIterator() {}
            VectorIterator(pointer _ptr) : ptr(_ptr) {}
            VectorIterator(const VectorIterator & other) {*this = other;}
            VectorIterator & operator=(const VectorIterator & other) {
                if (this != &other)
                    p = other.p;
                return *this;
            }
            bool operator>(const VectorIterator & other) const {return p > other.p;}
            bool operator>=(const VectorIterator & other) const {return p >= other.p;}
            bool operator<(const VectorIterator & other) const {return p < other.p;}
            bool operator<=(const VectorIterator & other) const {return p <= other.p;}
            bool operator==(const VectorIterator & other) const {return p == other.p;}
            bool operator!=(const VectorIterator & other) const {return p != other.p;}
            reference operator*() {return *p;}
            pointer operator->() {return p;}
            VectorIterator & operator++() {p++; return *this;}
            VectorIterator & operator--() {p--; return *this;}
            VectorIterator operator++() {
                VectorIterator  res(*this);

                *this = operator++();
                return res;
            }
            VectorIterator operator--() {
                VectorIterator res(*this);

                *this = operator--();
                return res;
            }
            VectorIterator operator+(int n) {
                VectorIterator temp(*this);

                temp += n;
                return temp;
            }
            VectorIterator operator-(int n) {
                VectorIterator temp(*this);

                temp -= n;
                return temp;
            }
            VectorIterator & operator+=(int n) {
                if (n >= 0)
                    while (n--)
                        (*this)++;
                else
                    while (n++)
                        (*this)++;
            }
            VectorIterator & operator-=(int n) {
                if (n >= 0)
                    while (n--)
                        (*this)--;
                else
                    while (n++)
                        (*this)--;
            }
            reference operator[](int i) {return *(*this + i);}
    };
    
    template<class T>
    class ConstVectorIterator : public VectorIterator<T> {
        public:
            typedef const reference     const_reference;
            typedef const pointer       const_pointer;   

            ConstVectorIterator() {}
            ~ConstVectorIterator() {}
            ConstVectorIterator(pointer _p) : p(_p) {}
            ConstVectorIterator(const ConstVectorIterator & other) {*this = other;}
            ConstVectorIterator & operator=(const ConstVectorIterator & other) {
                if (this != &other)
                    p = other.p;
                return *this;
            }
            const_reference operator*() {return *p;}
            const_pointer operator->() {return p;}
            const_reference operator[](int i) {return *(*this + i);}
    };

    template<class T>
    class ReverseVectorIterator : public VectorIterator<T> {
        ReverseVectorIterator() {}
        ~ReverseVectorIterator() {}
        ReverseVectorIterator(pointer _p) : p(_p) {}
        ReverseVectorIterator(const ReverseVectorIterator & other) {*this = other;}
        ReverseVectorIterator & operator=(const ReverseVectorIterator & other) {
            if (this != &other)
                p = other.p;
            return *this;
        }
        bool operator>(const ReverseVectorIterator & other) const {return p > other.p;}
        bool operator>=(const ReverseVectorIterator & other) const {return p >= other.p;}
        bool operator<(const ReverseVectorIterator & other) const {return p < other.p;}
        bool operator<=(const ReverseVectorIterator & other) const {return p <= other.p;}
        bool operator==(const ReverseVectorIterator & other) const {return p == other.p;}
        bool operator!=(const ReverseVectorIterator & other) const {return p != other.p;}
        ReverseVectorIterator & operator++() {p--; return *this;}
        ReverseVectorIterator & operator--() {p++; return *this;}
        ReverseVectorIterator operator++() {
            ReverseVectorIterator  res(*this);
            *this = operator--();
            return res;
        }
        ReverseVectorIterator operator--() {
            ReverseVectorIterator res(*this);

            *this = operator++();
            return res;
        }
        ReverseVectorIterator operator+(int n) {
            ReverseVectorIterator temp(*this);

            temp -= n;
            return temp;
        }
        ReverseVectorIterator operator-(int n) {
            ReverseVectorIterator temp(*this);

            temp += n;
            return temp;
        }
        ReverseVectorIterator & operator+=(int n) {
            if (n >= 0)
                while (n--)
                    (*this)--;
            else
                while (n++)
                    (*this)--;
        }
        ReverseVectorIterator & operator-=(int n) {
            if (n >= 0)
                while (n--)
                    (*this)++;
            else
                while (n++)
                    (*this)++;
        }
        reference operator[](int i) {return *(*this - i);}
    };

    template<class T>
    class ConstReverseVectorIterator : public ReverseVectorIterator<T> {
        public:
            typedef const reference     const_reference;
            typedef const pointer       const_pointer;   

            ConstReverseVectorIterator() {}
            ~ConstReverseVectorIterator() {}
            ConstReverseVectorIterator(pointer _p) : p(_p) {}
            ConstReverseVectorIterator(const ConstReverseVectorIterator & other) {*this = other;}
            ConstReverseVectorIterator & operator=(const ConstReverseVectorIterator & other) {
                if (this != &other)
                    p = other.p;
                return *this;
            }
            const_reference operator*() {return *p;}
            const_pointer operator->() {return p;}
            const_reference operator[](int i) {return *(*this - i);}
    };
}

# endif