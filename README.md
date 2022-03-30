# ft_containers (42 project)
The standard C++ containers have all a specific usage. \
To understand them, let’s re-implement them!

## Description
This project aim was to implement 4 C++98 containers:
1. Vector (without implementation of std::vector<bool>)
2. Stack (Based on vector)
3. Map (Based on Red-Black search tree)
4. Set (Based on Red-Black search tree)

Some utilities:
1. iterators_traits
2. reverse_iterator
3. is_integral
4. equal
5. lexicographical_compare
6. std::pair
7. std::make_pair

Namespace to use is **ft**. Vector, map and set has iterator system. \
It was used allocator for memory allocation \

## Compiling
All containers compile with `c++ -Wall -Werror -Wextra -std=c++98`
