/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobject <jobject@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:01:47 by jobject           #+#    #+#             */
/*   Updated: 2022/02/16 12:32:50 by jobject          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORITERATOR_HPP
# define VECTORITERATOR_HPP

# include "utils.hpp"

namespace ft {
	template<class T>
    class VectorIterator {
        public:
            typedef typename ft::iterator_traits<T *>::value_type 			value_type;
			typedef typename ft::iterator_traits<T *>::reference 			reference;
			typedef typename ft::iterator_traits<T *>::pointer				pointer;
			typedef typename ft::iterator_traits<T *>::difference_type		difference_type;
			typedef typename ft::iterator_traits<T *>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<T *>::pointer				iterator_type;
        protected:
            pointer p;
        public:
            VectorIterator() {}
            ~VectorIterator() {}
            VectorIterator(pointer _ptr) : p(_ptr) {}
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
            reference operator*() {return *this->p;}
            pointer operator->() {return &p;}
            VectorIterator & operator++() {p++; return *this;}
            VectorIterator & operator--() {p--; return *this;}
            VectorIterator operator++(int) {
                VectorIterator  res(*this);

                *this = operator++();
                return res;
            }
            VectorIterator operator--(int) {
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
				return *this;
            }
            VectorIterator & operator-=(int n) {
                if (n >= 0)
                    while (n--)
                        (*this)--;
                else
                    while (n++)
                        (*this)--;
				return *this;
            }
            reference operator[](int i) {return *(*this + i);}
    };
    
    template<class T>
    class ConstVectorIterator: public VectorIterator<T> {
        public:
		 	typedef typename VectorIterator<T>::reference     		reference;
            typedef typename VectorIterator<T>::pointer       		pointer;   
            typedef const typename VectorIterator<T>::reference     const_reference;
            typedef const typename VectorIterator<T>::pointer       const_pointer;   
            ConstVectorIterator() {}
            ~ConstVectorIterator() {}
            ConstVectorIterator(pointer _p) : VectorIterator<T>(_p) {}
            ConstVectorIterator(const ConstVectorIterator & other) {*this = other;}
            ConstVectorIterator & operator=(const ConstVectorIterator & other) {
                if (this != &other)
                    this->p = other.p;
                return *this;
            }
            const_reference operator*() {return *this->p;}
            const_pointer operator->() {return this->p;}
            const_reference operator[](int i) {return *(*this + i);}
    };

    template<class T>
    class ReverseVectorIterator : public VectorIterator<T> {
		public:
			typedef typename VectorIterator<T>::reference     		reference;
			typedef typename VectorIterator<T>::pointer       		pointer;   
			typedef const typename VectorIterator<T>::reference     const_reference;
			typedef const typename VectorIterator<T>::pointer       const_pointer;   
			ReverseVectorIterator() {}
			~ReverseVectorIterator() {}
			ReverseVectorIterator(pointer _p) : VectorIterator<T>(_p) {}
			ReverseVectorIterator(const ReverseVectorIterator & other) {*this = other;}
			ReverseVectorIterator & operator=(const ReverseVectorIterator & other) {
				if (this != &other)
					this->p = other.p;
				return *this;
			}
			bool operator>(const ReverseVectorIterator & other) const {return this->p > other.p;}
			bool operator>=(const ReverseVectorIterator & other) const {return this->p >= other.p;}
			bool operator<(const ReverseVectorIterator & other) const {return this->p < other.p;}
			bool operator<=(const ReverseVectorIterator & other) const {return this->p <= other.p;}
			bool operator==(const ReverseVectorIterator & other) const {return this->p == other.p;}
			bool operator!=(const ReverseVectorIterator & other) const {return this->p != other.p;}
			ReverseVectorIterator & operator++() {this->p--; return *this;}
			ReverseVectorIterator & operator--() {this->p++; return *this;}
			ReverseVectorIterator operator++(int) {
				ReverseVectorIterator  res(*this);
				*this = operator--();
				return res;
			}
			ReverseVectorIterator operator--(int) {
				ReverseVectorIterator res(*this);

				*this = operator++();
				return res;
			}
			ReverseVectorIterator operator+(int n) {
				ReverseVectorIterator temp(*this);

				temp += n;
				return temp;
			}
			ReverseVectorIterator operator-(int n) {
				ReverseVectorIterator temp(*this);

				temp -= n;
				return temp;
			}
			ReverseVectorIterator & operator+=(int n) {
				if (n >= 0)
					while (n--)
						(*this)--;
				else
					while (n++)
						(*this)--;
				return *this;
			}
			ReverseVectorIterator & operator-=(int n) {
				if (n >= 0)
					while (n--)
						(*this)++;
				else
					while (n++)
						(*this)++;
				return *this;
			}
			reference operator[](int i) {return *(*this - i);}
    };

    template<class T>
    class ConstReverseVectorIterator : public ReverseVectorIterator<T> {
        public:
          	typedef typename VectorIterator<T>::reference     		reference;
        	typedef typename VectorIterator<T>::pointer       		pointer;   
        	typedef const typename VectorIterator<T>::reference     const_reference;
        	typedef const typename VectorIterator<T>::pointer       const_pointer;   
            ConstReverseVectorIterator() {}
            ~ConstReverseVectorIterator() {}
            ConstReverseVectorIterator(pointer _p) : ReverseVectorIterator<T>(_p) {}
            ConstReverseVectorIterator(const ConstReverseVectorIterator & other) {*this = other;}
            ConstReverseVectorIterator & operator=(const ConstReverseVectorIterator & other) {
                if (this != &other)
                    this->p = other.p;
                return *this;
            }
            const_reference operator*() {return *this->p;}
            const_pointer operator->() {return this->p;}
            const_reference operator[](int i) {return *(*this - i);}
    };
}

# endif