# CPP Module 07 - C++ Templates

## Overview

This module teaches **templates** in C++:
- **Function templates** - Generic functions that work with any type
- **Class templates** - Generic classes parameterized by type
- **Template instantiation** - How the compiler generates type-specific code

---

## Key Concepts Learned

### What Are Templates?

Templates let you write **type-independent code**. The compiler generates the actual functions/classes for each type you use:

```cpp
// Without templates: write every version yourself
int    maxInt(int a, int b)       { return (a > b) ? a : b; }
float  maxFloat(float a, float b) { return (a > b) ? a : b; }
double maxDbl(double a, double b) { return (a > b) ? a : b; }

// With templates: write it once
template <typename T>
T max(T a, T b) { return (a > b) ? a : b; }
```

---

### Function Templates

A function template defines a **blueprint**. The compiler generates a concrete function for each type it's called with.

```cpp
template <typename T>
void printValue(const T& val) {
    std::cout << val << std::endl;
}

printValue(42);          // compiler generates printValue<int>
printValue(3.14);        // compiler generates printValue<double>
printValue("hello");     // compiler generates printValue<const char*>
```

**Why templates must be in headers:**
Templates are not real code until instantiated. The compiler needs the full definition wherever the template is used, so it must be in the header (or an included `.tpp` file).

---

### Class Templates

Class templates parameterize an entire class by type:

```cpp
template <typename T>
class Box {
private:
    T _content;
public:
    Box(T content) : _content(content) {}
    T getContent() const { return _content; }
};

// Must specify type explicitly
Box<int> intBox(42);
Box<std::string> strBox("hello");
```

**Member functions defined outside the class:**
```cpp
template <typename T>
T Box<T>::getContent() const {
    return _content;
}
```

---

### Function Pointers with Templates

Templates can accept and pass function pointers, enabling generic algorithms:

```cpp
template <typename T>
void forEach(T* arr, size_t len, void (*func)(T&)) {
    for (size_t i = 0; i < len; i++)
        func(arr[i]);
}
```

**Supporting both const and non-const:**
To allow the function to work with both const and non-const elements, you can either overload or use a second template parameter:

```cpp
// Option: two template parameters
template <typename T, typename F>
void iter(T* arr, size_t len, F func) {
    for (size_t i = 0; i < len; i++)
        func(arr[i]);
}
```

---

### operator new[] and Default Initialization

```cpp
int* a = new int[5];    // uninitialized (garbage values)
int* b = new int[5]();  // value-initialized (all zeros)
```

For class types, `new T[n]()` calls the default constructor for each element.

---

## Exercise 00: Start with a few functions

### Goal
Implement three function templates: `swap`, `min`, and `max` that work with any type supporting comparison operators.

### Requirements

**Function templates:**
| Function | Description |
|----------|-------------|
| `swap(a, b)` | Swaps two values, returns nothing |
| `min(a, b)` | Returns the smallest; if equal, returns the second |
| `max(a, b)` | Returns the greatest; if equal, returns the second |

- Must work with any type
- Both arguments must be the same type
- Type must support all comparison operators
- Templates must be defined in the header file

### Implementation Guide

**whatever.hpp:**
```cpp
#ifndef WHATEVER_HPP
#define WHATEVER_HPP

template <typename T>
void swap(T& a, T& b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

template <typename T>
const T& min(const T& a, const T& b)
{
    return (a < b) ? a : b;
}

template <typename T>
const T& max(const T& a, const T& b)
{
    return (a > b) ? a : b;
}

#endif /* WHATEVER_HPP */
```

**Why return `const T&`?**
- Parameters are `const T&` to avoid unnecessary copies
- When values are equal, `(a < b)` is false and `(a > b)` is false, so both return `b` (the second parameter), matching the subject requirement

**Why `::swap` in main?**
The `::` prefix ensures the global namespace version is called instead of `std::swap`.

### Testing Example (main.cpp)

```cpp
#include <iostream>
#include <string>
#include "whatever.hpp"

int main(void)
{
    int a = 2;
    int b = 3;

    ::swap(a, b);
    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "min( a, b ) = " << ::min(a, b) << std::endl;
    std::cout << "max( a, b ) = " << ::max(a, b) << std::endl;

    std::string c = "chaine1";
    std::string d = "chaine2";

    ::swap(c, d);
    std::cout << "c = " << c << ", d = " << d << std::endl;
    std::cout << "min( c, d ) = " << ::min(c, d) << std::endl;
    std::cout << "max( c, d ) = " << ::max(c, d) << std::endl;

    return 0;
}
```

**Expected output:**
```
a = 3, b = 2
min( a, b ) = 2
max( a, b ) = 3
c = chaine2, d = chaine1
min( c, d ) = chaine1
max( c, d ) = chaine2
```

---

## Exercise 01: Iter

### Goal
Implement a function template `iter` that applies a function to every element of an array.

### Requirements

**Function:** `iter`
- First parameter: address of an array
- Second parameter: length of the array (const value)
- Third parameter: function called on every element
- Returns nothing
- Must work with any type of array
- Third parameter can be an instantiated function template
- Must support both const and non-const element references

### Implementation Guide

**iter.hpp:**
```cpp
#ifndef ITER_HPP
#define ITER_HPP

#include <cstddef>

template <typename T, typename F>
void iter(T* array, size_t length, F func)
{
    for (size_t i = 0; i < length; i++)
        func(array[i]);
}

#endif /* ITER_HPP */
```

**Why `typename F` for the function parameter?**
Using a separate template parameter `F` for the function allows `iter` to accept:
- Regular function pointers: `void (*func)(T&)`
- Function pointers to const: `void (*func)(const T&)`
- Instantiated function templates

If you used `void (*func)(T&)` directly, it wouldn't work with const arrays. With `typename F`, the compiler deduces the correct function signature automatically.

**Alternative approach (explicit overloads):**
```cpp
// Non-const version
template <typename T>
void iter(T* array, size_t length, void (*func)(T&))
{
    for (size_t i = 0; i < length; i++)
        func(array[i]);
}

// Const version
template <typename T>
void iter(const T* array, size_t length, void (*func)(const T&))
{
    for (size_t i = 0; i < length; i++)
        func(array[i]);
}
```

### Testing Example (main.cpp)

```cpp
#include <iostream>
#include <string>
#include "iter.hpp"

template <typename T>
void print(const T& x)
{
    std::cout << x << std::endl;
}

template <typename T>
void increment(T& x)
{
    x++;
}

int main(void)
{
    std::cout << "=== Int array ===" << std::endl;
    int intArr[] = {1, 2, 3, 4, 5};
    iter(intArr, 5, print<int>);

    std::cout << "\n=== After increment ===" << std::endl;
    iter(intArr, 5, increment<int>);
    iter(intArr, 5, print<int>);

    std::cout << "\n=== String array ===" << std::endl;
    std::string strArr[] = {"Hello", "World", "42"};
    iter(strArr, 3, print<std::string>);

    std::cout << "\n=== Const array ===" << std::endl;
    const double constArr[] = {1.1, 2.2, 3.3};
    iter(constArr, 3, print<double>);

    return 0;
}
```

---

## Exercise 02: Array

### Goal
Develop a class template `Array` that manages a dynamically allocated array of any type with bounds checking.

### Requirements

| Feature | Description |
|---------|-------------|
| Default constructor | Creates an empty array |
| `Array(unsigned int n)` | Creates array of `n` default-initialized elements |
| Copy constructor | Deep copy — modifying one doesn't affect the other |
| Assignment operator | Deep copy — modifying one doesn't affect the other |
| `operator[]` | Access elements; throws `std::exception` if out of bounds |
| `size()` | Returns number of elements; const member function |
| Memory | Must use `new[]`; no preventive allocation |

### Implementation Guide

**Array.hpp:**
```cpp
#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>
#include <stdexcept>

template <typename T>
class Array {

public:
    Array(void);
    Array(unsigned int n);
    Array(const Array& other);
    ~Array(void);

    Array& operator=(const Array& other);
    T& operator[](unsigned int index);
    const T& operator[](unsigned int index) const;
    unsigned int size(void) const;

private:
    T*           _array;
    unsigned int _size;
};

#include "Array.tpp"

#endif /* ARRAY_HPP */
```

**Array.tpp:**
```cpp
#ifndef ARRAY_TPP
#define ARRAY_TPP

/* ┌──────────────────┐ */
/* │   CONSTRUCTORS   │ */
/* └──────────────────┘ */

template <typename T>
Array<T>::Array(void) : _array(NULL), _size(0) {}

template <typename T>
Array<T>::Array(unsigned int n) : _array(new T[n]()), _size(n) {}

template <typename T>
Array<T>::Array(const Array& other) : _array(NULL), _size(0)
{
    *this = other;
}

template <typename T>
Array<T>::~Array(void)
{
    delete[] _array;
}

/* ┌─────────────────────────┐ */
/* │   OPERATOR OVERLOADS    │ */
/* └─────────────────────────┘ */

template <typename T>
Array<T>& Array<T>::operator=(const Array& other)
{
    if (this != &other)
    {
        delete[] _array;
        _size = other._size;
        _array = new T[_size]();
        for (unsigned int i = 0; i < _size; i++)
            _array[i] = other._array[i];
    }
    return *this;
}

template <typename T>
T& Array<T>::operator[](unsigned int index)
{
    if (index >= _size)
        throw std::out_of_range("Array index out of bounds");
    return _array[index];
}

template <typename T>
const T& Array<T>::operator[](unsigned int index) const
{
    if (index >= _size)
        throw std::out_of_range("Array index out of bounds");
    return _array[index];
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

template <typename T>
unsigned int Array<T>::size(void) const
{
    return _size;
}

#endif /* ARRAY_TPP */
```

**Key implementation details:**

| Detail | Explanation |
|--------|-------------|
| `new T[n]()` | Value-initializes all elements (e.g., `int` gets 0) |
| `delete[] _array` | Must use `delete[]` to match `new[]` |
| Deep copy in `operator=` | Allocates new memory, copies each element |
| Two `operator[]` overloads | Non-const returns `T&` (read/write), const returns `const T&` (read-only) |
| `std::out_of_range` | Inherits from `std::exception`, satisfying the subject requirement |

**Why `#include "Array.tpp"` at the bottom of the header?**
Template implementations must be visible at the point of instantiation. Including the `.tpp` at the end of the header keeps the interface and implementation separate while ensuring the compiler sees everything it needs.

### Testing Example (main.cpp)

```cpp
#include <iostream>
#include <string>
#include "Array.hpp"

int main(void)
{
    std::cout << "=== Empty array ===" << std::endl;
    Array<int> empty;
    std::cout << "Size: " << empty.size() << std::endl;

    std::cout << "\n=== Int array ===" << std::endl;
    Array<int> numbers(5);
    for (unsigned int i = 0; i < numbers.size(); i++)
        numbers[i] = i * 10;
    for (unsigned int i = 0; i < numbers.size(); i++)
        std::cout << "numbers[" << i << "] = " << numbers[i] << std::endl;

    std::cout << "\n=== Deep copy test ===" << std::endl;
    Array<int> copy(numbers);
    copy[0] = 999;
    std::cout << "Original [0]: " << numbers[0] << std::endl;
    std::cout << "Copy [0]:     " << copy[0] << std::endl;

    std::cout << "\n=== Assignment test ===" << std::endl;
    Array<int> assigned;
    assigned = numbers;
    assigned[1] = 888;
    std::cout << "Original [1]: " << numbers[1] << std::endl;
    std::cout << "Assigned [1]: " << assigned[1] << std::endl;

    std::cout << "\n=== Out of bounds ===" << std::endl;
    try {
        numbers[10] = 42;
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== String array ===" << std::endl;
    Array<std::string> strings(3);
    strings[0] = "Hello";
    strings[1] = "World";
    strings[2] = "42";
    for (unsigned int i = 0; i < strings.size(); i++)
        std::cout << "strings[" << i << "] = " << strings[i] << std::endl;

    return 0;
}
```

---

## Summary

| Exercise | Concept | Key Technique |
|----------|---------|---------------|
| ex00 | Function templates | `template <typename T>` for generic swap/min/max |
| ex01 | Function template + function pointers | Passing functions as template parameters |
| ex02 | Class templates | Generic container with `new[]`, deep copy, bounds checking |

**Remember:**
- Templates must be defined in headers (compiler needs full definition at instantiation)
- `new T[n]()` value-initializes, `new T[n]` does not
- Deep copy means allocating new memory and copying values, not just pointers
- `typename` and `class` are interchangeable in template parameter lists
- The compiler only generates template code for types actually used

**Important for defense:** Be ready to explain how templates differ from macros, why implementations must be in headers, and how deep copy prevents shared-state bugs.
