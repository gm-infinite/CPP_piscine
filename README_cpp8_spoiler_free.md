# CPP Module 08 - Templated Containers, Iterators, Algorithms (Spoiler-Free)

## STL Containers, Iterators, and Algorithms

The **Standard Template Library (STL)** provides three core components that work together: **containers** store data, **iterators** traverse it, and **algorithms** operate on it. This module is your first opportunity to use them.

---

### STL Containers

**Purpose:** Ready-made data structures that manage their own memory.

| Category | Examples | Use Case |
|----------|----------|----------|
| Sequence | `vector`, `deque`, `list` | Ordered collections |
| Associative | `set`, `map`, `multiset`, `multimap` | Key-based lookup |
| Adapters | `stack`, `queue`, `priority_queue` | Restricted-access wrappers |

```cpp
#include <vector>
#include <list>
#include <map>

std::vector<int> v;
v.push_back(42);           // dynamic array

std::list<int> l;
l.push_back(10);            // doubly-linked list

std::map<std::string, int> m;
m["hello"] = 1;             // key-value store
```

**Key points:**
- Containers are templated — they work with any type
- They handle memory allocation and deallocation automatically
- Each container has different performance trade-offs (access, insertion, deletion)

---

### Iterators

**Purpose:** A uniform way to traverse any container, regardless of its internal structure.

```cpp
std::vector<int> v;
v.push_back(1);
v.push_back(2);
v.push_back(3);

// Iterate using iterators
for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    std::cout << *it << std::endl;
```

**Iterator categories:**
| Category | Capabilities | Example Containers |
|----------|--------------|--------------------|
| Input | Read forward | `istream_iterator` |
| Output | Write forward | `ostream_iterator` |
| Forward | Read/write forward | `forward_list` |
| Bidirectional | Forward + backward | `list`, `set`, `map` |
| Random Access | Bidirectional + jump | `vector`, `deque` |

**Key points:**
- `begin()` points to the first element, `end()` points past the last
- Dereferencing (`*it`) gives the element value
- Iterators abstract away the container's internal implementation

---

### STL Algorithms

**Purpose:** Generic operations that work on ranges defined by iterators.

```cpp
#include <algorithm>
#include <vector>

std::vector<int> v;
v.push_back(3);
v.push_back(1);
v.push_back(2);

// Sort
std::sort(v.begin(), v.end());           // {1, 2, 3}

// Find
std::vector<int>::iterator it = std::find(v.begin(), v.end(), 2);
if (it != v.end())
    std::cout << "Found: " << *it << std::endl;

// Min/Max
int minVal = *std::min_element(v.begin(), v.end());
int maxVal = *std::max_element(v.begin(), v.end());
```

**Key points:**
- Algorithms operate on iterator ranges `[begin, end)`
- They are container-agnostic — the same `std::find` works on `vector`, `list`, `deque`, etc.
- `std::find` returns `end()` if the element is not found

---

### Container Adapters and Underlying Containers

Container adapters like `std::stack`, `std::queue`, and `std::priority_queue` wrap an underlying container to provide a restricted interface:

```cpp
#include <stack>

std::stack<int> s;           // default: uses std::deque internally
s.push(1);
s.push(2);
std::cout << s.top();        // 2
s.pop();
```

**Key points:**
- `std::stack` only exposes `push()`, `pop()`, `top()`, `size()`, `empty()`
- By default, `std::stack` uses `std::deque` as its underlying container
- The underlying container is accessible via the `protected` member `c`
- Adapters intentionally **do not** provide iterators

---

### Range-Based Insertion

Many containers support inserting elements from a range of iterators:

```cpp
std::vector<int> source;
source.push_back(1);
source.push_back(2);
source.push_back(3);

std::vector<int> dest;
// Insert a range of elements at once
dest.insert(dest.end(), source.begin(), source.end());
```

**Key points:**
- `insert(position, first, last)` inserts elements from `[first, last)`
- More efficient than inserting elements one by one in a loop
- Works across different container types as long as iterator types are compatible

---

## Quick Reference

| Concept | Syntax |
|---------|--------|
| Vector declaration | `std::vector<int> v;` |
| Iterator loop | `for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)` |
| Find element | `std::find(v.begin(), v.end(), value)` |
| Sort container | `std::sort(v.begin(), v.end())` |
| Stack (adapter) | `std::stack<int> s;` |
| Range insert | `v.insert(v.end(), first, last)` |
| Min/Max element | `*std::min_element(v.begin(), v.end())` |

---

## Exercise Requirements

### Exercise 00
- Write a function template `easyfind` that accepts a type `T` and two parameters
- First parameter is of type `T` (a container of integers), second is an integer
- Find the first occurrence of the second parameter in the first parameter
- If not found, throw an exception or return an error value of your choice
- Study how standard containers behave for inspiration
- Associative containers do not need to be handled

### Exercise 01
- Develop a `Span` class that can store a maximum of N integers
- N is an `unsigned int` passed to the constructor
- `addNumber()` adds a single number; throws an exception if the Span is full
- `shortestSpan()` returns the smallest distance between any two stored numbers
- `longestSpan()` returns the largest distance between any two stored numbers
- Both span functions throw an exception if fewer than 2 numbers are stored
- Must also implement a way to add multiple numbers using a range of iterators
- Test with at least 10,000 numbers

### Exercise 02
- Create a `MutantStack` class that extends `std::stack` with iterator support
- Must offer all `std::stack` member functions plus iterators
- Replacing `MutantStack` with `std::list` in the test code should produce the same output
- The class is implemented in terms of `std::stack`

---

## Things to Consider

1. **Exercise 00:**
   - Which algorithm function searches for a value in a range?
   - What does that function return when the value is not found?
   - Why are associative containers excluded?
   - How do you make this generic enough to work with `vector`, `list`, `deque`, etc.?

2. **Exercise 01:**
   - How can you efficiently find the shortest span without an O(n²) approach?
   - What role does sorting play in finding distances?
   - How can you use iterator ranges to add multiple numbers at once?
   - What edge cases should your exceptions cover?

3. **Exercise 02:**
   - What is the underlying container of `std::stack` and how do you access it?
   - What does the `protected` member `c` in `std::stack` represent?
   - How do you expose the underlying container's iterators?
   - What are the relevant `typedef`s you need to provide?

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
