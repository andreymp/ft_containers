/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobject <jobject@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 21:37:27 by jobject           #+#    #+#             */
/*   Updated: 2022/01/26 21:40:07 by jobject          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft {
	template<typename T>
	void swap(T & a, T & b) {
		T tmp = a;
		a = b;
		b = tmp;
	}
}

#endif