# CPP Module 08 - Templated Containers, Iterators, Algorithms

## Overview

This module teaches **STL usage** in C++:
- **Containers** - `vector`, `list`, `deque`, `stack`, and more
- **Iterators** - Traversing containers with a unified interface
- **Algorithms** - Generic operations from `<algorithm>` like `find`, `sort`, `min_element`

---

## Key Concepts Learned

### STL Containers

The Standard Template Library provides ready-made, well-tested data structures:

```cpp
#include <vector>
#include <list>
#include <deque>

std::vector<int> v;    // dynamic array — fast random access, slow middle insert
std::list<int>   l;    // doubly-linked list — fast insert/delete, no random access
std::deque<int>  d;    // double-ended queue — fast front/back, random access
```

**Choosing the right container:**
| Need | Use |
|------|-----|
| Random access by index | `vector` or `deque` |
| Frequent insert/delete in the middle | `list` |
| LIFO (last-in, first-out) | `stack` |
| Key-value pairs | `map` |

---

### Iterators

Iterators provide a uniform way to access container elements, decoupling algorithms from containers:

```cpp
std::vector<int> v;
v.push_back(10);
v.push_back(20);
v.push_back(30);

for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    std::cout << *it << " ";  // 10 20 30
```

**Iterator types exposed by containers:**
| Type | Access |
|------|--------|
| `iterator` | Read/write access |
| `const_iterator` | Read-only access |
| `reverse_iterator` | Traverse in reverse |
| `const_reverse_iterator` | Read-only reverse |

---

### STL Algorithms

Generic functions that work on any container through iterators:

```cpp
#include <algorithm>

std::vector<int> v;
// ... populate v ...

// Search
std::vector<int>::iterator it = std::find(v.begin(), v.end(), 42);

// Sort
std::sort(v.begin(), v.end());

// Min/Max
int lo = *std::min_element(v.begin(), v.end());
int hi = *std::max_element(v.begin(), v.end());
```

**`std::find` behavior:**
- Returns an iterator to the first occurrence of the value
- Returns `end()` if the value is not found — this is how you detect "not found"

---

### Container Adapters

`std::stack`, `std::queue`, and `std::priority_queue` are **adapters** — they wrap an underlying container and expose a restricted interface:

```cpp
// std::stack uses std::deque by default
template <class T, class Container = std::deque<T> >
class stack {
protected:
    Container c;   // the underlying container
public:
    void push(const T& x) { c.push_back(x); }
    void pop()             { c.pop_back(); }
    T& top()               { return c.back(); }
    // ...
};
```

**Critical detail:** The underlying container is stored as a `protected` member named `c`. A derived class can access `c` directly, including its iterators.

---

### Range-Based Insertion

Containers support inserting a range of elements from iterators:

```cpp
std::vector<int> src;
src.push_back(1);
src.push_back(2);
src.push_back(3);

std::vector<int> dst;
dst.insert(dst.end(), src.begin(), src.end());  // inserts {1, 2, 3}
```

This is far more efficient than calling `push_back()` in a loop, and it's how you implement "add many elements at once" functionality.

---

## Exercise 00: Easy find

### Goal
Write a function template `easyfind` that searches for an integer in any container of integers.

### Requirements

**Function:** `easyfind`
- First parameter: a container of type `T` (containing integers)
- Second parameter: an `int` to search for
- Returns/finds the first occurrence of the integer in the container
- If not found, throw an exception
- Associative containers don't need to be handled

### Implementation Guide

**easyfind.hpp:**
```cpp
#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm>
#include <stdexcept>

template <typename T>
typename T::iterator easyfind(T& container, int value)
{
    typename T::iterator it = std::find(container.begin(), container.end(), value);
    if (it == container.end())
        throw std::runtime_error("Value not found in container");
    return it;
}

#endif /* EASYFIND_HPP */
```

**Key implementation details:**

| Detail | Explanation |
|--------|-------------|
| `typename T::iterator` | The `typename` keyword is required because `T::iterator` is a dependent type — the compiler can't know it's a type until `T` is known |
| `std::find` | Searches `[begin, end)` for the value; returns `end()` if not found |
| Return iterator | Returning the iterator lets the caller access/modify the found element |
| `std::runtime_error` | A concrete exception type inheriting from `std::exception` |

**Why `typename` is needed:**
When a name depends on a template parameter (like `T::iterator`), the compiler doesn't know if it refers to a type or a static member. `typename` explicitly tells the compiler it's a type.

**Alternative — return const_iterator for const containers:**
```cpp
template <typename T>
typename T::const_iterator easyfind(const T& container, int value)
{
    typename T::const_iterator it = std::find(container.begin(), container.end(), value);
    if (it == container.end())
        throw std::runtime_error("Value not found in container");
    return it;
}
```

### Testing Example (main.cpp)

```cpp
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include "easyfind.hpp"

int main(void)
{
    std::cout << "=== Vector ===" << std::endl;
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    try {
        std::vector<int>::iterator it = easyfind(v, 3);
        std::cout << "Found: " << *it << std::endl;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    try {
        std::vector<int>::iterator it = easyfind(v, 42);
        std::cout << "Found: " << *it << std::endl;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n=== List ===" << std::endl;
    std::list<int> l;
    l.push_back(10);
    l.push_back(20);
    l.push_back(30);

    try {
        std::list<int>::iterator it = easyfind(l, 20);
        std::cout << "Found: " << *it << std::endl;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n=== Deque ===" << std::endl;
    std::deque<int> d;
    d.push_back(100);
    d.push_back(200);
    d.push_back(300);

    try {
        std::deque<int>::iterator it = easyfind(d, 100);
        std::cout << "Found: " << *it << std::endl;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
```

**Expected output:**
```
=== Vector ===
Found: 3
Value not found in container

=== List ===
Found: 20

=== Deque ===
Found: 100
```

---

## Exercise 01: Span

### Goal
Develop a `Span` class that stores up to N integers and can compute the shortest and longest span (distance) between any two stored numbers.

### Requirements

| Feature | Description |
|---------|-------------|
| Constructor | Takes `unsigned int N` — maximum capacity |
| `addNumber(int)` | Adds a single number; throws if full |
| `shortestSpan()` | Returns smallest distance between any two numbers |
| `longestSpan()` | Returns largest distance between any two numbers |
| Range add | A member function to add multiple numbers via iterator range |
| Exceptions | Throw if adding to a full Span, or computing span with < 2 elements |

### Implementation Guide

**Span.hpp:**
```cpp
#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <climits>

class Span {

public:
    Span(unsigned int n);
    Span(const Span& other);
    ~Span(void);

    Span& operator=(const Span& other);

    void addNumber(int number);

    template <typename Iterator>
    void addRange(Iterator begin, Iterator end);

    unsigned int shortestSpan(void) const;
    unsigned int longestSpan(void) const;

private:
    Span(void);
    unsigned int      _maxSize;
    std::vector<int>  _numbers;
};

/* Template member function — must be in header */
template <typename Iterator>
void Span::addRange(Iterator begin, Iterator end)
{
    while (begin != end)
    {
        addNumber(*begin);
        ++begin;
    }
}

#endif /* SPAN_HPP */
```

**Span.cpp:**
```cpp
#include "Span.hpp"

/* ┌──────────────────┐ */
/* │   CONSTRUCTORS   │ */
/* └──────────────────┘ */

Span::Span(void) : _maxSize(0) {}

Span::Span(unsigned int n) : _maxSize(n) {}

Span::Span(const Span& other) : _maxSize(other._maxSize), _numbers(other._numbers) {}

Span::~Span(void) {}

/* ┌─────────────────────────┐ */
/* │   OPERATOR OVERLOADS    │ */
/* └─────────────────────────┘ */

Span& Span::operator=(const Span& other)
{
    if (this != &other)
    {
        _maxSize = other._maxSize;
        _numbers = other._numbers;
    }
    return *this;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

void Span::addNumber(int number)
{
    if (_numbers.size() >= _maxSize)
        throw std::overflow_error("Span is full");
    _numbers.push_back(number);
}

unsigned int Span::shortestSpan(void) const
{
    if (_numbers.size() < 2)
        throw std::logic_error("Not enough numbers to find a span");

    std::vector<int> sorted(_numbers);
    std::sort(sorted.begin(), sorted.end());

    unsigned int minSpan = static_cast<unsigned int>(sorted[1] - sorted[0]);
    for (size_t i = 2; i < sorted.size(); i++)
    {
        unsigned int diff = static_cast<unsigned int>(sorted[i] - sorted[i - 1]);
        if (diff < minSpan)
            minSpan = diff;
    }
    return minSpan;
}

unsigned int Span::longestSpan(void) const
{
    if (_numbers.size() < 2)
        throw std::logic_error("Not enough numbers to find a span");

    int minVal = *std::min_element(_numbers.begin(), _numbers.end());
    int maxVal = *std::max_element(_numbers.begin(), _numbers.end());
    return static_cast<unsigned int>(maxVal - minVal);
}
```

**Key implementation details:**

| Detail | Explanation |
|--------|-------------|
| `std::vector<int>` for storage | Dynamic array, supports sorting and random access |
| Sort for `shortestSpan` | After sorting, the shortest span must be between two adjacent elements — O(n log n) instead of O(n²) |
| `min_element` / `max_element` for `longestSpan` | The longest span is simply `max - min` |
| Template `addRange` | Accepts any iterator type, calls `addNumber` for each element (reuses the overflow check) |
| `unsigned int` return type | Spans (distances) are always non-negative |

**Why sort for shortest span?**
Without sorting, you'd need to compare every pair — O(n²). After sorting, adjacent elements have the smallest differences, so you only check consecutive pairs — O(n log n).

**Alternative `addRange` using `insert`:**
```cpp
template <typename Iterator>
void Span::addRange(Iterator begin, Iterator end)
{
    if (_numbers.size() + std::distance(begin, end) > _maxSize)
        throw std::overflow_error("Not enough space to add range");
    _numbers.insert(_numbers.end(), begin, end);
}
```
This version checks capacity upfront and uses `vector::insert` for bulk insertion, which is more efficient.

### Testing Example (main.cpp)

```cpp
#include <iostream>
#include <vector>
#include <cstdlib>
#include "Span.hpp"

int main(void)
{
    std::cout << "=== Subject test ===" << std::endl;
    Span sp = Span(5);
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);

    std::cout << sp.shortestSpan() << std::endl;  // 2
    std::cout << sp.longestSpan() << std::endl;    // 14

    std::cout << "\n=== Overflow test ===" << std::endl;
    try {
        sp.addNumber(42);
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Too few elements ===" << std::endl;
    Span tiny(1);
    tiny.addNumber(1);
    try {
        std::cout << tiny.shortestSpan() << std::endl;
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== 10,000 numbers ===" << std::endl;
    Span big(10000);
    std::vector<int> nums;
    for (int i = 0; i < 10000; i++)
        nums.push_back(i);
    big.addRange(nums.begin(), nums.end());
    std::cout << "Shortest: " << big.shortestSpan() << std::endl;  // 1
    std::cout << "Longest:  " << big.longestSpan() << std::endl;   // 9999

    std::cout << "\n=== Random numbers ===" << std::endl;
    Span random(10000);
    std::srand(42);
    for (int i = 0; i < 10000; i++)
        random.addNumber(std::rand());
    std::cout << "Shortest: " << random.shortestSpan() << std::endl;
    std::cout << "Longest:  " << random.longestSpan() << std::endl;

    return 0;
}
```

**Expected output:**
```
=== Subject test ===
2
14

=== Overflow test ===
Exception: Span is full

=== Too few elements ===
Exception: Not enough numbers to find a span

=== 10,000 numbers ===
Shortest: 1
Longest:  9999

=== Random numbers ===
Shortest: <varies>
Longest:  <varies>
```

---

## Exercise 02: Mutated abomination

### Goal
Create a `MutantStack` class that makes `std::stack` iterable by exposing the underlying container's iterators.

### Requirements

| Feature | Description |
|---------|-------------|
| Inherits from `std::stack` | All standard `stack` member functions available |
| Iterators | Must provide `begin()`, `end()`, `rbegin()`, `rend()` |
| Iterator types | Must expose `iterator`, `const_iterator`, `reverse_iterator`, `const_reverse_iterator` typedefs |
| Compatibility | Replacing `MutantStack` with `std::list` should produce the same output |

### Implementation Guide

**MutantStack.hpp:**
```cpp
#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>

template <typename T>
class MutantStack : public std::stack<T> {

public:
    MutantStack(void) {}
    MutantStack(const MutantStack& other) : std::stack<T>(other) {}
    ~MutantStack(void) {}

    MutantStack& operator=(const MutantStack& other)
    {
        if (this != &other)
            std::stack<T>::operator=(other);
        return *this;
    }

    typedef typename std::stack<T>::container_type::iterator               iterator;
    typedef typename std::stack<T>::container_type::const_iterator         const_iterator;
    typedef typename std::stack<T>::container_type::reverse_iterator       reverse_iterator;
    typedef typename std::stack<T>::container_type::const_reverse_iterator const_reverse_iterator;

    iterator               begin(void)        { return this->c.begin(); }
    iterator               end(void)          { return this->c.end(); }
    const_iterator         begin(void)  const { return this->c.begin(); }
    const_iterator         end(void)    const { return this->c.end(); }
    reverse_iterator       rbegin(void)       { return this->c.rbegin(); }
    reverse_iterator       rend(void)         { return this->c.rend(); }
    const_reverse_iterator rbegin(void) const { return this->c.rbegin(); }
    const_reverse_iterator rend(void)   const { return this->c.rend(); }
};

#endif /* MUTANTSTACK_HPP */
```

**Key implementation details:**

| Detail | Explanation |
|--------|-------------|
| `public std::stack<T>` | Inherits all of `stack`'s interface: `push()`, `pop()`, `top()`, `size()`, `empty()` |
| `this->c` | `c` is the `protected` member of `std::stack` — the underlying container (`std::deque<T>` by default) |
| `container_type` | A typedef inside `std::stack` that names the underlying container type |
| `typename` before nested types | Required because these are dependent types (depend on template parameter `T`) |
| All 8 iterator functions | 4 directions × 2 const-ness = 8 functions for full iterator support |

**How `std::stack` works internally:**

```
std::stack<int>
├── protected: container_type c;   (default: std::deque<int>)
│   ├── c.begin()    → iterator to first element (bottom of stack)
│   ├── c.end()      → past-the-end iterator
│   ├── c.rbegin()   → reverse iterator to last element (top of stack)
│   └── c.rend()     → reverse past-the-end iterator
├── public:
│   ├── push(x)      → c.push_back(x)
│   ├── pop()        → c.pop_back()
│   ├── top()        → c.back()
│   ├── size()       → c.size()
│   └── empty()      → c.empty()
```

**Why does this work?**
`std::stack` stores its data in a `protected` member `c`. Since `MutantStack` inherits from `std::stack`, it can access `c` and expose its iterators. The underlying `std::deque` (or any sequence container) already supports full iteration — `std::stack` just hides it.

### Testing Example (main.cpp)

```cpp
#include <iostream>
#include <list>
#include "MutantStack.hpp"

int main(void)
{
    std::cout << "=== MutantStack ===" << std::endl;
    MutantStack<int> mstack;

    mstack.push(5);
    mstack.push(17);

    std::cout << "Top: " << mstack.top() << std::endl;

    mstack.pop();

    std::cout << "Size: " << mstack.size() << std::endl;

    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();

    ++it;
    --it;

    std::cout << "Elements:" << std::endl;
    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }

    std::stack<int> s(mstack);

    std::cout << "\n=== Same test with std::list ===" << std::endl;
    std::list<int> lst;

    lst.push_back(5);
    lst.push_back(17);

    std::cout << "Back: " << lst.back() << std::endl;

    lst.pop_back();

    std::cout << "Size: " << lst.size() << std::endl;

    lst.push_back(3);
    lst.push_back(5);
    lst.push_back(737);
    lst.push_back(0);

    std::list<int>::iterator lit = lst.begin();
    std::list<int>::iterator lite = lst.end();

    ++lit;
    --lit;

    std::cout << "Elements:" << std::endl;
    while (lit != lite)
    {
        std::cout << *lit << std::endl;
        ++lit;
    }

    std::cout << "\n=== Reverse iteration ===" << std::endl;
    MutantStack<int> mstack2;
    mstack2.push(1);
    mstack2.push(2);
    mstack2.push(3);

    for (MutantStack<int>::reverse_iterator rit = mstack2.rbegin(); rit != mstack2.rend(); ++rit)
        std::cout << *rit << std::endl;

    std::cout << "\n=== Copy test ===" << std::endl;
    MutantStack<int> copy(mstack2);
    std::cout << "Copy size: " << copy.size() << std::endl;
    std::cout << "Copy top: " << copy.top() << std::endl;

    return 0;
}
```

**Expected output:**
```
=== MutantStack ===
Top: 17
Size: 1
Elements:
5
3
5
737
0

=== Same test with std::list ===
Back: 17
Size: 1
Elements:
5
3
5
737
0

=== Reverse iteration ===
3
2
1

=== Copy test ===
Copy size: 3
Copy top: 3
```

---

## Summary

| Exercise | Concept | Key Technique |
|----------|---------|---------------|
| ex00 | Function templates + STL algorithms | `std::find` on generic containers with `typename T::iterator` |
| ex01 | STL containers + algorithms | `std::vector` storage, `std::sort` for shortest span, `std::min/max_element` for longest |
| ex02 | Inheritance + container adapters | Inheriting `std::stack`, exposing `this->c` iterators via typedefs |

**Remember:**
- `std::find` returns `end()` when an element is not found — always check before dereferencing
- Sorting turns an O(n²) closest-pair search into O(n log n)
- `std::stack::c` is `protected` — derived classes can access the underlying container
- `typename` is required before dependent types like `T::iterator` or `container_type::iterator`
- Container adapters intentionally hide iterators — `MutantStack` "repairs" this by exposing them

---

## Evaluation Checklist

Before your defense, make sure you can check all of these:

| Check | Requirement |
|-------|-------------|
| ✅ | Code compiles with `c++ -Wall -Wextra -Werror` |
| ✅ | Code compiles with `-std=c++98` |
| ✅ | No `*printf()`, `*alloc()`, `free()` — only C++ equivalents |
| ✅ | No `using namespace` or `friend` keyword |
| ✅ | No functions implemented in headers (except templates) |
| ✅ | All non-interface classes in **Orthodox Canonical Form** (default ctor, copy ctor, assignment op, destructor) |
| ✅ | STL containers and `<algorithm>` are used — this is the whole point of Module 08 |
| ✅ | Sufficient tests in `main()` for every exercise |
| ✅ | No memory leaks (check with `valgrind` / `leaks`) |

---

## EXTRA — Exercise 00: Defense Deep-Dive

### What evaluators specifically check

> ⚠️ **Critical:** `easyfind` **MUST** use an STL algorithm (like `std::find`). If you manually loop with iterators to search, the evaluator will count it as **wrong** — even if it works.

### Potential defense questions

**Q: Why does `easyfind` need `typename` before `T::iterator`?**
> Because `T::iterator` is a **dependent name** — it depends on the template parameter `T`. The compiler doesn't know if `T::iterator` is a type or a static data member until `T` is instantiated. The `typename` keyword tells the compiler "this is a type, not a value."
>
> Without `typename`, the compiler assumes it's a value and you get a compilation error.

**Q: What's the difference between `std::find` and `container.find()`?**
> `std::find` (from `<algorithm>`) is a free function that works on any container via iterators — it does a **linear search** O(n). Some containers like `std::set` and `std::map` have their own `.find()` member function that uses the container's internal structure (e.g., balanced BST) for **O(log n)** lookup.
>
> For this exercise, `std::find` is appropriate because we're dealing with sequence containers.

**Q: Why are associative containers excluded?**
> Associative containers (`map`, `set`, `multimap`, `multiset`) don't store plain values in the same way — `std::map` stores `std::pair<const Key, Value>`, so `std::find` looking for a plain `int` wouldn't match. They also have their own `.find()` method which is more efficient than linear search.

**Q: What does `std::find` actually return when the element is not found?**
> It returns an iterator equal to the `end()` iterator — the past-the-end position. This is the standard "sentinel" pattern in STL. You must **never dereference** the `end()` iterator.

**Q: Could you use `std::count` instead of `std::find`?**
> You could check `std::count(begin, end, value) > 0`, but it's less efficient because `count` always traverses the **entire** container, while `find` stops at the first match.

**Q: Why return an iterator instead of the value itself?**
> Returning `T::iterator` gives the caller more flexibility — they can modify the found element, erase it, or use it as a position for insertion. Returning just the value loses that positional information.

### Niche knowledge you might be asked about

- **Iterator invalidation:** Inserting/removing elements can invalidate iterators. For `std::vector`, any insertion may invalidate all iterators (due to reallocation). For `std::list`, only the erased element's iterator is invalidated.
- **`std::distance(first, last)`:** Returns the number of hops between two iterators. O(1) for random-access iterators, O(n) for others.
- **`std::advance(it, n)`:** Moves an iterator by `n` positions. Same complexity considerations as `std::distance`.
- **Why `++it` over `it++` for iterators?** `++it` (pre-increment) avoids creating a temporary copy. For heavy iterators this matters. It's considered best practice in C++.

---

## EXTRA — Exercise 01: Defense Deep-Dive

### What evaluators specifically check

> ⚠️ **Critical:** `shortestSpan` must compare **all** adjacent pairs after sorting — not just the two smallest numbers. Example: `{6, 3, 17, 9, 11}` → sorted: `{3, 6, 9, 11, 17}` → differences: `3, 3, 2, 6` → shortest = **2** (between 9 and 11). Just subtracting the two smallest (3 and 6 = 3) gives the **wrong answer**.

> ⚠️ **Critical:** Member functions must use **STL algorithms** as much as possible (`std::sort`, `std::min_element`, `std::max_element`, `std::adjacent_difference`, etc.).

> ⚠️ **Critical:** There must be a way to add numbers that's more practical than calling `addNumber()` repeatedly — i.e., a range-based method.

### Potential defense questions

**Q: Why can't you just subtract the two lowest numbers for `shortestSpan`?**
> Consider `{1, 100, 101}`. The two lowest are 1 and 100 (difference = 99), but the actual shortest span is between 100 and 101 (difference = 1). The shortest span can be between **any** two adjacent numbers in the sorted sequence, not necessarily the smallest ones.

**Q: Why sort before finding the shortest span?**
> After sorting, the shortest distance must be between two consecutive elements. This is because if `a ≤ b ≤ c`, then `c - a ≥ c - b` and `c - a ≥ b - a`. So you only need to check N-1 pairs instead of N×(N-1)/2 pairs. This reduces complexity from O(n²) to O(n log n).

**Q: What's the time complexity of your `shortestSpan` and `longestSpan`?**
> - `shortestSpan`: O(n log n) due to sorting, then O(n) for the linear scan = **O(n log n)** total
> - `longestSpan`: O(n) using `std::min_element` and `std::max_element` = **O(n)** total

**Q: Why use `unsigned int` for the return type of span functions?**
> Because a span (distance) is always non-negative. However, be careful with integer overflow: if you have `INT_MIN` and `INT_MAX` in your container, the difference overflows `int`. Using `unsigned int` or casting properly is important.

**Q: How does your range-add function work? Could you use `std::vector::insert` directly?**
> Yes. `_numbers.insert(_numbers.end(), first, last)` inserts the entire range at once. The alternative is looping and calling `addNumber()` for each, which reuses the overflow check but is slower.

**Q: What's the difference between `std::distance` and manual counting?**
> `std::distance(first, last)` returns the number of increments needed to go from `first` to `last`. For **random-access iterators** (like `vector::iterator`), it's O(1). For **bidirectional iterators** (like `list::iterator`), it's O(n).

**Q: Why do you copy the vector before sorting in `shortestSpan`?**
> Sorting modifies the container in-place. If we sorted `_numbers` directly, the original insertion order would be lost. Creating a copy preserves the original data. This is especially important if the user calls `shortestSpan()` multiple times or adds more numbers later.

### Niche knowledge you might be asked about

- **`std::adjacent_difference`** (from `<numeric>`): Computes differences between consecutive elements. Could be used for `shortestSpan` after sorting:
  ```cpp
  std::vector<int> diffs(sorted.size());
  std::adjacent_difference(sorted.begin(), sorted.end(), diffs.begin());
  // diffs[0] = sorted[0], diffs[i] = sorted[i] - sorted[i-1] for i > 0
  unsigned int shortest = *std::min_element(diffs.begin() + 1, diffs.end());
  ```
- **`std::vector::reserve(n)`:** Pre-allocates memory for `n` elements without changing `size()`. Avoids reallocations when you know the final size.
- **`std::vector::capacity()` vs `std::vector::size()`:** `size()` = number of elements stored. `capacity()` = number of elements that can be stored before reallocation.
- **`static_cast<unsigned int>(maxVal - minVal)`:** Be aware of signed integer overflow. If `maxVal` is large positive and `minVal` is large negative, `maxVal - minVal` can overflow `int`. A safer approach: `static_cast<unsigned int>(static_cast<long>(maxVal) - minVal)`.
- **Why `std::vector` over `std::list` for storage?** `std::sort` requires random-access iterators, which `std::list` doesn't provide. `std::list` has its own `.sort()` member function, but using `std::vector` + `std::sort` is idiomatic.

---

## EXTRA — Exercise 02: Defense Deep-Dive

### What evaluators specifically check

> ⚠️ **Critical:** `MutantStack` must **inherit** from `std::stack` — not just wrap it.

> ⚠️ **Critical:** It must provide **iterators** and all operations from the subject's example must work.

> ⚠️ **Critical:** Tests must go **beyond** the subject's example — evaluators check for a more comprehensive `main()`.

### Potential defense questions

**Q: How does `std::stack` store its elements internally?**
> `std::stack` has a `protected` member named `c` of type `container_type` (which defaults to `std::deque<T>`). All `stack` operations (`push`, `pop`, `top`, `size`, `empty`) are thin wrappers around `c.push_back()`, `c.pop_back()`, `c.back()`, `c.size()`, and `c.empty()`.

**Q: Why is `c` protected and not private?**
> Making it `protected` was a deliberate design choice in the C++ standard. It allows derived classes to access the underlying container. If it were `private`, creating something like `MutantStack` would be impossible without `friend`.

**Q: What is `container_type` in `std::stack`?**
> It's a public typedef inside `std::stack` that names the underlying container type. By default it's `std::deque<T>`, but you can specify a different one: `std::stack<int, std::vector<int>>` uses a `vector` internally.

**Q: Why use `this->c` instead of just `c`?**
> In a template class inheriting from a template base, the compiler doesn't automatically look in the base class for names. `this->c` or `std::stack<T>::c` forces the compiler to look in the base class. Without `this->`, the compiler may not find `c` and give an error.

**Q: What does the `++it; --it;` in the subject's test do?**
> It tests that the iterator supports both **increment** and **decrement** — i.e., it's at least a **bidirectional iterator**. The net effect is no movement, but it proves the iterator has the required capabilities.

**Q: Can you construct a `std::stack` from a `MutantStack`? Why?**
> Yes: `std::stack<int> s(mstack);` works because `MutantStack` inherits from `std::stack`, so it IS-A `std::stack`. The copy constructor of `std::stack` accepts a `const std::stack&`, and `MutantStack` implicitly converts to that.

**Q: Why does replacing MutantStack with std::list give the same output?**
> Because `std::list` supports `push_back`, `pop_back`, `back` (analogous to `push`, `pop`, `top`), `size`, `empty`, and full iterator support. The subject maps `push()` → `push_back()`, `top()` → `back()`, etc.

**Q: What additional tests should you have beyond the subject example?**
> - Reverse iteration with `rbegin()`/`rend()`
> - Const iterators on a `const MutantStack`
> - Copy constructor and assignment operator
> - Different types (not just `int` — try `std::string`, `float`)
> - Modifying elements through iterators (`*it = newValue`)
> - Empty stack edge cases

### Niche knowledge you might be asked about

- **`std::stack` has no virtual destructor.** This means if you delete a `MutantStack` through a `std::stack*` pointer, you get **undefined behavior**. STL containers are generally not designed for polymorphic inheritance. In this exercise it's fine because we never use base-class pointers.
- **`std::stack` template signature:** `template <class T, class Container = std::deque<T>> class stack;` — The second parameter lets you swap the underlying container:
  ```cpp
  std::stack<int, std::vector<int>> vectorStack;
  std::stack<int, std::list<int>>   listStack;
  ```
  Your `MutantStack` could also support this with a second template parameter.
- **Why `std::deque` is the default, not `std::vector`:** `std::deque` supports efficient front insertion (`push_front`), which `std::queue` needs. Since `std::stack`, `std::queue`, and `std::priority_queue` share the adapter pattern, `std::deque` serves as a common default.
- **Iterator categories matter:** `std::deque::iterator` is a **random-access iterator** (supports `+`, `-`, `[]`, `<`). `std::list::iterator` is only **bidirectional** (supports `++`, `--` but not `+` or `[]`). If your `MutantStack` wraps a `deque`, its iterators support random access. If wrapping a `list`, only bidirectional.
- **Reverse iterators:** `rbegin()` points to the last element (top of stack), `rend()` points before the first. A `reverse_iterator` is an adapter itself — it wraps a normal iterator and reverses the direction. `rbegin()` internally holds `end()`, and dereferencing it accesses `*(end() - 1)`.
- **Why no `const` versions of `push`, `pop`?** These modify the container, so they can't be `const`. But `size()`, `empty()`, and `top()` (returning `const T&`) can be — though `std::stack::top()` has both `const` and non-`const` overloads.
- **Object slicing:** If you pass a `MutantStack` by value to a function expecting `std::stack`, the `MutantStack`-specific parts are sliced off. Always pass by reference or pointer to preserve the derived type.

---

## EXTRA — General STL Knowledge for Defense

These concepts cut across all exercises and could come up at any point during evaluation:

### Orthodox Canonical Form (OCF)

Every non-interface class must have:
1. **Default constructor**
2. **Copy constructor**
3. **Copy assignment operator** (`operator=`)
4. **Destructor**

For `Span`: all four are required. For `MutantStack`: all four, calling the base class versions. For `easyfind`: it's a function template, no class — OCF doesn't apply.

### STL Exception Hierarchy

```
std::exception
├── std::logic_error
│   ├── std::invalid_argument
│   ├── std::domain_error
│   ├── std::length_error
│   └── std::out_of_range
├── std::runtime_error
│   ├── std::range_error
│   ├── std::overflow_error
│   └── std::underflow_error
└── std::bad_alloc
```

You can use any of these. Catching `std::exception&` in tests catches all of them.

### Iterator Traits (Niche)

Every iterator exposes traits like `value_type`, `difference_type`, `pointer`, `reference`, and `iterator_category` through `std::iterator_traits<Iterator>`. This is how algorithms like `std::sort` decide whether they can use random-access optimizations.

### `const_iterator` vs `iterator`

- `iterator` → you can read **and modify** the element: `*it = 42;`
- `const_iterator` → read-only: `*it = 42;` won't compile
- A `const` container only provides `const_iterator` through `begin()`/`end()`

### Functor / Function Objects (May come up)

In C++98, a functor is an object with `operator()` overloaded. STL algorithms accept functors as predicates:
```cpp
struct IsEven {
    bool operator()(int n) const { return n % 2 == 0; }
};

std::vector<int>::iterator it = std::find_if(v.begin(), v.end(), IsEven());
```
This is the C++98 way to pass "lambda-like" behavior to algorithms.

**Important for defense:** Be ready to explain why sorting helps `shortestSpan`, how `std::stack` hides its underlying container, why `typename` is needed for dependent types, and the difference between `std::find` on sequence vs. associative containers.

