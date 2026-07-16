# CPP Module 09 — Complete Guide
## STL in Practice: Maps, Stacks, and Sorting Algorithms

> **Who is this for?** This guide is written for students who have completed CPP08 and are tackling CPP Module 09 of the 42 piscine. It explains every concept from the ground up, teaches you how to solve each exercise, and gives you the deep knowledge you need to explain your code to evaluators.

> **⚠️ Container Exclusivity Rule:** This module has a **unique constraint** — each exercise must use a **different** STL container. The container you use in ex00 is **forbidden** in ex01, and the containers used in ex00 and ex01 are **both forbidden** in ex02. Plan your container choices before writing a single line of code.

---

## Table of Contents

1. [The Big Picture — What is CPP09 About?](#1-the-big-picture--what-is-cpp09-about)
2. [New STL Tools for This Module](#2-new-stl-tools-for-this-module)
3. [The Ford-Johnson Algorithm (Merge-Insertion Sort)](#3-the-ford-johnson-algorithm-merge-insertion-sort)
4. [Container Choice Strategy](#4-container-choice-strategy)
5. [Exercise 00 — Bitcoin Exchange](#5-exercise-00--bitcoin-exchange)
6. [Exercise 01 — Reverse Polish Notation](#6-exercise-01--reverse-polish-notation)
7. [Exercise 02 — PmergeMe](#7-exercise-02--pmergeme)
8. [Defense Preparation — Full Q&A](#8-defense-preparation--full-qa)
9. [Niche Trivia & Deep Knowledge](#9-niche-trivia--deep-knowledge)
10. [Evaluation Checklist](#10-evaluation-checklist)

---

## 1. The Big Picture — What is CPP09 About?

CPP08 introduced you to **what** the STL is. CPP09 forces you to **use it deliberately** for real tasks:

```
Exercise 00 — Bitcoin Exchange
    Read a CSV database, look up date-key prices using a sorted map, handle every edge case.
    Teaches: std::map, file parsing, lower_bound lookups.

Exercise 01 — Reverse Polish Notation
    Evaluate a math expression given as a string of tokens.
    Teaches: std::stack for expression evaluation.

Exercise 02 — PmergeMe
    Sort a large sequence using Ford-Johnson (Merge-Insertion Sort) with TWO different containers.
    Teaches: Algorithm implementation, performance comparison, std::deque vs std::vector.
```

The three exercises share a theme: **choosing the right container for the right job**. That choice is not arbitrary — evaluators will specifically ask you to justify it.

---

## 2. New STL Tools for This Module

### 2.1 `std::map` — The Sorted Key-Value Store

```cpp
#include <map>

std::map<std::string, double> priceDB;
priceDB["2011-01-03"] = 0.30;
priceDB["2011-01-09"] = 0.32;
priceDB["2012-01-11"] = 7.10;

// Look up a key:
double rate = priceDB["2011-01-03"];  // 0.30

// Check if a key exists:
if (priceDB.count("2011-01-03"))
    std::cout << "Key exists" << std::endl;
```

**Key properties of `std::map`:**
| Property | Detail |
|----------|--------|
| Keys are always sorted | Internally a Red-Black Tree (BST) |
| Lookup / insert / erase | O(log n) |
| Keys are unique | Duplicate keys are silently ignored |
| Iterating is sorted | `begin()` → smallest key, `end()` → past-largest |

**Why `std::map` is ideal for ex00:**
- The database (data.csv) is a price-per-date mapping → perfect key-value structure
- You need to find the **closest earlier date**: `map` supports O(log n) `lower_bound()`
- All keys (dates stored as strings in `YYYY-MM-DD` format) sort lexicographically in the correct chronological order

### 2.2 `lower_bound()` — Finding the Closest Date

This is the **single most important technique** in ex00.

```cpp
std::map<std::string, double> db;
// ... loaded from data.csv ...

std::string inputDate = "2011-01-05";  // Does NOT exist in db

// lower_bound returns an iterator to the first key >= inputDate
std::map<std::string, double>::iterator it = db.lower_bound(inputDate);

// Since "2011-01-05" doesn't exist, it points to "2011-01-07" (next higher)
// We need the LOWER date, so we go back one step:
if (it == db.begin()) {
    std::cerr << "Error: date precedes database range." << std::endl;
} else {
    --it;  // now points to "2011-01-03" — the closest lower date
    double result = value * it->second;
    std::cout << inputDate << " => " << value << " = " << result << std::endl;
}
```

**`lower_bound` vs `upper_bound`:**
| Function | Returns |
|----------|---------|
| `lower_bound(key)` | First iterator where `key_in_map >= key` |
| `upper_bound(key)` | First iterator where `key_in_map > key` |

For ex00: use `lower_bound`. If the exact date exists, `lower_bound` points directly at it (no need to go back). If not, it points one past — go back one step.

```cpp
it = db.lower_bound(inputDate);
if (it != db.end() && it->first == inputDate) {
    // Exact match — use directly
} else if (it == db.begin()) {
    // Error: date is before all data
} else {
    --it;  // Use the nearest lower date
}
```

### 2.3 `std::stack` — LIFO Data Structure

```cpp
#include <stack>

std::stack<int> s;
s.push(8);
s.push(9);
s.push(42);

std::cout << s.top();  // 42 (last pushed, first popped)
s.pop();               // remove 42
std::cout << s.top();  // 9
std::cout << s.size(); // 2
std::cout << s.empty(); // false
```

**Stack interface:**
| Method | Description |
|--------|-------------|
| `push(val)` | Add element to top |
| `pop()` | Remove top element (no return value!) |
| `top()` | Read (or modify) the top element |
| `size()` | Number of elements |
| `empty()` | True if no elements |

> ⚠️ **Critical:** `pop()` does **not** return the removed element. Always call `top()` first to read the value, then `pop()` to remove it.

**Why `std::stack` is ideal for ex01 (RPN):**
The core algorithm for Reverse Polish Notation:
1. Read tokens left to right
2. If token is a **number** → push onto stack
3. If token is an **operator** → pop 2 values, apply operator, push result
4. At the end, one value remains on the stack → the result

The LIFO nature of the stack perfectly models how operands are consumed by operators in RPN.

### 2.4 `std::deque` — Double-Ended Queue

```cpp
#include <deque>

std::deque<int> d;
d.push_back(10);   // [10]
d.push_front(5);   // [5, 10]
d.push_back(20);   // [5, 10, 20]

d[0];               // 5  — O(1) random access
d.pop_front();      // remove 5
d.pop_back();       // remove 20
```

**Why `std::deque` is a strong choice for ex02:**
- Supports O(1) random access (like `vector`)
- Supports O(1) front AND back insertion/deletion (unlike `vector`)
- `std::deque` iterators are random-access, so `std::sort` works on it
- Its non-contiguous memory layout means no costly reallocation when inserting at front

---

## 3. The Ford-Johnson Algorithm (Merge-Insertion Sort)

Exercise 02 specifically requires the **Ford-Johnson algorithm** (also called Merge-Insertion Sort). This is a classical algorithm designed to minimize the number of comparisons needed to sort n elements.

### 3.1 Why Ford-Johnson?

Standard `std::sort` uses introsort (mix of quicksort/heapsort). It is fast in practice but does not minimize comparisons. Ford-Johnson was proven to require fewer comparisons than any other algorithm for certain input sizes. The subject requires it explicitly.

### 3.2 The Algorithm — Step by Step

Given an unsorted sequence of positive integers:

**Step 1 — Pair Up Elements**
Group elements into pairs `(a, b)` where `a < b`. If there's an odd element left over, keep it aside (the "straggler").

```
Input: [3, 5, 9, 7, 4, 1, 8, 6, 2]
Pairs: (3,5), (7,9), (1,4), (6,8), (2, ?)
Straggler: 2 (if odd count) — actually depends on your grouping
```

**Step 2 — Sort Each Pair**
For each pair, ensure the larger element is at position "high" and smaller at "low". This needs only 1 comparison per pair → at most ⌊n/2⌋ comparisons.

**Step 3 — Recursively Sort the "Highs"**
Take all the larger elements of each pair and sort them recursively using Ford-Johnson. This gives you the **main chain** — the sorted sequence of larger elements.

**Step 4 — Insert the "Lows" (and Straggler) Using Binary Insertion**
The smaller element of each pair (called "pend" elements) must now be inserted into the main chain. The key insight: since `low_i < high_i` and `high_i` is already in the sorted main chain, you know each `low_i` must be inserted somewhere **before** `high_i`.

Insert the pend elements in a specific order defined by **Jacobsthal numbers** to minimize worst-case comparisons.

**Jacobsthal Numbers:**
```
J(0) = 0
J(1) = 1
J(n) = J(n-1) + 2 * J(n-2)

Sequence: 0, 1, 1, 3, 5, 11, 21, 43, 85, ...
```

The insertion order derived from Jacobsthal numbers ensures each binary search is bounded optimally. Elements are inserted in groups: group sizes follow the differences of consecutive Jacobsthal numbers: `1, 2, 2, 6, 10, 22, 42, ...`

**Binary Insertion into the Main Chain:**
When inserting a pend element, use binary search to find its position. Because of the constraint (`pend_i < high_i`, and `high_i` is already placed), you search only the subrange **before** `high_i`'s position, reducing the search space.

### 3.3 Concrete Example

```
Input: [3, 5, 9, 7, 4]

Step 1 — Pair and sort pairs:
  Pairs: (3,5), (7,9)  →  highs=[5,9], lows=[3,7], straggler=4

Step 2 — Recursively sort the highs:
  [{5,9}] is already 2 elements — one comparison: 5 < 9 ✓
  Main chain after sorting highs: [5, 9]

Step 3 — Insert lows and straggler using Jacobsthal order:
  Pends to insert: low[0]=3 (paired with 5), low[1]=7 (paired with 9), straggler=4
  Jacobsthal insertion order for 3 pends: insert pend[0], then pend[1] (backwards), then straggler

  Insert 3: search [0, pos(5)] = [0,1] → binary search → insert before 5
    Chain: [3, 5, 9]

  Insert 7: 7 is paired with 9 (at index 2), so search [0, 2] → binary search → insert between 5 and 9
    Chain: [3, 5, 7, 9]

  Insert 4 (straggler): search full chain → binary search → insert between 3 and 5
    Chain: [3, 4, 5, 7, 9]  ✓
```

### 3.4 Implementation Skeleton

```cpp
// Two-container approach (required by subject)
// ex: std::vector and std::deque

#include <vector>
#include <deque>

// For std::vector version:
void fordJohnsonVector(std::vector<int>& seq);

// For std::deque version:
void fordJohnsonDeque(std::deque<int>& seq);
```

Key helper you will need:

```cpp
// Binary insertion into a sorted range [begin, end)
// Inserts 'val' at the correct sorted position
template <typename Container>
void binaryInsert(Container& chain, 
                  typename Container::iterator begin, 
                  typename Container::iterator end, 
                  int val)
{
    typename Container::iterator lo = begin;
    typename Container::iterator hi = end;
    while (lo < hi)
    {
        typename Container::iterator mid = lo + std::distance(lo, hi) / 2;
        if (*mid < val)
            lo = mid + 1;
        else
            hi = mid;
    }
    chain.insert(lo, val);
}
```

> **Note:** The subject says to implement the algorithm **separately** for each container (not as a generic template). This lets the evaluator see that you understood the algorithm applied to each container's specific iterator/access patterns.

---

## 4. Container Choice Strategy

> ⚠️ **The most critical planning decision of the whole module.**

The module forbids reusing a container across exercises. Here is the standard mapping used by most students:

| Exercise | Typical Choice | Why |
|----------|---------------|-----|
| ex00 | `std::map` | Sorted key-value, O(log n) `lower_bound` |
| ex01 | `std::stack` | LIFO is the exact model for RPN evaluation |
| ex02 | `std::vector` + `std::deque` | Both support random access (needed for Ford-Johnson binary search) |

**Alternative valid choices:**
- ex00: `std::map` is almost mandatory — it's the ideal data structure
- ex01: Could use `std::vector` as a manual stack (push to back, pop from back), but `std::stack` is cleaner
- ex02: Must use **two** different containers — `vector`+`deque`, or `vector`+`list` (harder since `list` has no random access)

> ⚠️ **Do not use `std::map` in ex01 or ex02.** Do not use `std::stack` in ex02. Plan ahead.

---

## 5. Exercise 00 — Bitcoin Exchange

### Goal
Build a program `btc` that:
1. Loads a Bitcoin price database (`data.csv`) — format: `date,exchange_rate`
2. Reads an input file given as argument — format: `date | value`
3. For each line, multiplies the value by the Bitcoin price on that date (or nearest lower date)
4. Outputs the result or an error message

### Files Required
- `Makefile` (program name: `btc`)
- `main.cpp`
- `BitcoinExchange.hpp`
- `BitcoinExchange.cpp`

### Understanding the Data

**data.csv (the database):**
```
date,exchange_rate
2009-01-02,0
2009-01-05,0
...
2011-01-03,0.30
2011-01-09,0.32
2012-01-11,7.10
...
```
1,614 entries spanning 2009–2022. The database is loaded once at program start.

**input.txt (the user's query file):**
```
date | value
2011-01-03 | 3
2011-01-09 | 1
2012-01-11 | -1
2001-42-42
2012-01-11 | 1
2012-01-11 | 2147483648
```

### Implementation Guide

**BitcoinExchange.hpp:**
```cpp
#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

class BitcoinExchange {
public:
    BitcoinExchange(void);
    BitcoinExchange(const BitcoinExchange& other);
    ~BitcoinExchange(void);
    BitcoinExchange& operator=(const BitcoinExchange& other);

    void loadDatabase(const std::string& filename);
    void processInput(const std::string& filename) const;

private:
    std::map<std::string, double> _db;  // key: "YYYY-MM-DD", value: exchange rate

    bool        isValidDate(const std::string& date) const;
    bool        isValidValue(const std::string& valStr, double& outVal) const;
    double      getRate(const std::string& date) const;
};

#endif /* BITCOINEXCHANGE_HPP */
```

**BitcoinExchange.cpp — Loading the Database:**
```cpp
void BitcoinExchange::loadDatabase(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
        throw std::runtime_error("Error: could not open database file.");

    std::string line;
    std::getline(file, line); // skip header: "date,exchange_rate"

    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        size_t comma = line.find(',');
        if (comma == std::string::npos) continue;

        std::string date = line.substr(0, comma);
        std::string rateStr = line.substr(comma + 1);

        double rate = std::strtod(rateStr.c_str(), NULL);
        _db[date] = rate;
    }
}
```

**BitcoinExchange.cpp — Finding the Rate (lower_bound trick):**
```cpp
double BitcoinExchange::getRate(const std::string& date) const
{
    // lower_bound gives us the first key >= date
    std::map<std::string, double>::const_iterator it = _db.lower_bound(date);

    if (it == _db.end() || it->first != date)
    {
        // Exact date not found — use closest lower date
        if (it == _db.begin())
            throw std::runtime_error("Error: date out of range.");
        --it; // step back to the largest key that is still < date
    }
    return it->second;
}
```

**BitcoinExchange.cpp — Processing Input File:**
```cpp
void BitcoinExchange::processInput(const std::string& filename) const
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // skip header: "date | value"

    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        // Check format: must have " | " separator
        size_t sep = line.find(" | ");
        if (sep == std::string::npos)
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::string dateStr = line.substr(0, sep);
        std::string valStr  = line.substr(sep + 3);

        // Validate date
        if (!isValidDate(dateStr))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        // Parse and validate value
        double value;
        if (!isValidValue(valStr, value))
            continue; // error already printed inside isValidValue

        // Look up rate and print result
        try {
            double rate = getRate(dateStr);
            std::cout << dateStr << " => " << value << " = " << value * rate << std::endl;
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}
```

**Validation helpers:**
```cpp
bool BitcoinExchange::isValidDate(const std::string& date) const
{
    // Expected format: YYYY-MM-DD (exactly 10 chars)
    if (date.size() != 10)        return false;
    if (date[4] != '-')           return false;
    if (date[7] != '-')           return false;

    // Check all other chars are digits
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!std::isdigit(date[i])) return false;
    }

    // Basic range checks
    int year  = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day   = std::atoi(date.substr(8, 2).c_str());

    if (year < 2009)         return false;  // before database start
    if (month < 1 || month > 12) return false;
    if (day < 1   || day > 31)   return false;
    return true;
}

bool BitcoinExchange::isValidValue(const std::string& valStr, double& outVal) const
{
    char* end;
    outVal = std::strtod(valStr.c_str(), &end);

    if (end == valStr.c_str() || *end != '\0') {
        std::cerr << "Error: bad input => " << valStr << std::endl;
        return false;
    }
    if (outVal < 0) {
        std::cerr << "Error: not a positive number." << std::endl;
        return false;
    }
    if (outVal > 1000) {
        std::cerr << "Error: too large a number." << std::endl;
        return false;
    }
    return true;
}
```

**main.cpp:**
```cpp
#include "BitcoinExchange.hpp"

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    try {
        BitcoinExchange btc;
        btc.loadDatabase("data.csv");
        btc.processInput(argv[1]);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
```

### Expected Output vs Input

```
$> ./btc input.txt
2011-01-03 => 3 = 0.9        (rate on 2011-01-03 = 0.30, 3 * 0.30 = 0.9)
2011-01-03 => 2 = 0.6
2011-01-03 => 1 = 0.3
2011-01-03 => 1.2 = 0.36
2011-01-09 => 1 = 0.32       (rate on 2011-01-09 = 0.32)
Error: not a positive number. (value was -1)
Error: bad input => 2001-42-42
2012-01-11 => 1 = 7.1        (rate on 2012-01-11 = 7.1)
Error: too large a number.   (value was 2147483648)
```

### Common Mistakes

| Mistake | Problem |
|---------|---------|
| Using `_db[date]` for lookup instead of `lower_bound` | If date not found, `operator[]` **inserts** a zero entry, corrupting the DB |
| Not skipping the CSV header line | First entry parsed as a malformed date |
| Not handling `it == _db.begin()` before `--it` | Undefined behavior / crash when input date is before all data |
| Checking `> 1000` but allowing `1000.1` through a float parse | Off-by-one in boundary conditions |
| Stopping on first error instead of continuing | Subject says process the **whole** file |

---

## 6. Exercise 01 — Reverse Polish Notation

### Goal
Build a program `RPN` that:
1. Takes a single string argument: a Reverse Polish Notation (RPN) expression
2. Evaluates it and prints the result
3. Handles operators: `+`, `-`, `/`, `*`
4. Errors go to standard error

### What is Reverse Polish Notation?

In standard (infix) notation: `(3 + 4) * 2`
In RPN (postfix): `3 4 + 2 *`

The key insight: **no brackets needed** because operand order is explicit. Operators always apply to the two most recent operands.

```
Expression: "8 9 * 9 - 9 - 9 - 4 - 1 +"

Token | Stack after
  8   | [8]
  9   | [8, 9]
  *   | [72]        (8 * 9 = 72)
  9   | [72, 9]
  -   | [63]        (72 - 9 = 63)
  9   | [63, 9]
  -   | [54]        (63 - 9 = 54)
  9   | [54, 9]
  -   | [45]        (54 - 9 = 45)
  4   | [45, 4]
  -   | [41]        (45 - 4 = 41)
  1   | [41, 1]
  +   | [42]        (41 + 1 = 42)

Result: 42 ✓
```

### Files Required
- `Makefile` (program name: `RPN`)
- `main.cpp`
- `RPN.hpp`
- `RPN.cpp`

### Implementation Guide

**RPN.hpp:**
```cpp
#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>

class RPN {
public:
    RPN(void);
    RPN(const RPN& other);
    ~RPN(void);
    RPN& operator=(const RPN& other);

    int evaluate(const std::string& expression);

private:
    std::stack<int> _stack;  // <-- the one container for this exercise
};

#endif /* RPN_HPP */
```

**RPN.cpp:**
```cpp
#include "RPN.hpp"

RPN::RPN(void) {}
RPN::RPN(const RPN& other) : _stack(other._stack) {}
RPN::~RPN(void) {}
RPN& RPN::operator=(const RPN& other) {
    if (this != &other)
        _stack = other._stack;
    return *this;
}

int RPN::evaluate(const std::string& expression)
{
    // Clear stack from any previous call
    while (!_stack.empty())
        _stack.pop();

    std::istringstream iss(expression);
    std::string token;

    while (iss >> token)
    {
        if (token.size() == 1 && std::string("+-*/").find(token[0]) != std::string::npos)
        {
            // It's an operator — need at least 2 values on stack
            if (_stack.size() < 2)
                throw std::runtime_error("Error");

            int b = _stack.top(); _stack.pop();  // right operand
            int a = _stack.top(); _stack.pop();  // left operand

            if      (token[0] == '+') _stack.push(a + b);
            else if (token[0] == '-') _stack.push(a - b);
            else if (token[0] == '*') _stack.push(a * b);
            else if (token[0] == '/') {
                if (b == 0)
                    throw std::runtime_error("Error: division by zero.");
                _stack.push(a / b);
            }
        }
        else
        {
            // Should be a single digit (subject: numbers always < 10)
            if (token.size() != 1 || !std::isdigit(token[0]))
                throw std::runtime_error("Error");
            _stack.push(token[0] - '0');
        }
    }

    if (_stack.size() != 1)
        throw std::runtime_error("Error");

    return _stack.top();
}
```

**main.cpp:**
```cpp
#include "RPN.hpp"

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "Usage: RPN \"<expression>\"" << std::endl;
        return 1;
    }

    try {
        RPN rpn;
        int result = rpn.evaluate(argv[1]);
        std::cout << result << std::endl;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
```

### Test Cases from the Evaluation Page

```
$> ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
42

$> ./RPN "7 7 * 7 -"
42

$> ./RPN "1 2 * 2 / 2 * 2 4 - +"
0

$> ./RPN "9 8 * 4 * 4 / 2 + 9 - 8 - 8 - 1 - 6 -"
42

$> ./RPN "1 2 * 2 / 2 + 5 * 6 - 1 3 * - 4 5 * * 8 /"
15

$> ./RPN "(1 + 1)"
Error
```

### Operator Ordering — A Critical Detail

When you pop two values to apply a binary operator:
```cpp
int b = _stack.top(); _stack.pop();  // popped SECOND → right operand
int a = _stack.top(); _stack.pop();  // popped FIRST  → left operand
// Apply: a OP b
```
For `+` and `*` this doesn't matter (commutative). For `-` and `/` it does:
- Expression `3 4 -` should give `3 - 4 = -1`, NOT `4 - 3 = 1`
- The first number pushed (`3`) is the left operand

### Common Mistakes

| Mistake | Problem |
|---------|---------|
| Reversing operand order for `-` and `/` | Produces wrong results silently |
| Not checking for division by zero | Undefined behavior or crash |
| Accepting numbers ≥ 10 as input | Subject says input numbers are always < 10 |
| Not clearing the stack between calls | State bleeds between evaluations |
| Stack size ≠ 1 at end not treated as error | Malformed expressions slip through |

---

## 7. Exercise 02 — PmergeMe

### Goal
Build a program `PmergeMe` that:
1. Takes a sequence of positive integers as command-line arguments
2. Sorts them using the **Ford-Johnson (Merge-Insertion Sort)** algorithm
3. Uses **two different containers** to perform the sort independently
4. Displays: unsorted sequence, sorted sequence, and time taken for each container

### Files Required
- `Makefile` (program name: `PmergeMe`)
- `main.cpp`
- `PmergeMe.hpp`
- `PmergeMe.cpp`

### Display Format

```
Before: 3 5 9 7 4
After:  3 4 5 7 9
Time to process a range of 5 elements with std::vector : 0.00031 us
Time to process a range of 5 elements with std::deque  : 0.00014 us
```

### Timing Your Sort (C++98 Compatible)

```cpp
#include <sys/time.h>

struct timeval start, end;

gettimeofday(&start, NULL);
// ... sort using container 1 ...
gettimeofday(&end, NULL);

double elapsed = (end.tv_sec - start.tv_sec) * 1000000.0
               + (end.tv_usec - start.tv_usec);
// elapsed is in microseconds
```

### Implementation Guide

**PmergeMe.hpp:**
```cpp
#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <sys/time.h>

class PmergeMe {
public:
    PmergeMe(void);
    PmergeMe(const PmergeMe& other);
    ~PmergeMe(void);
    PmergeMe& operator=(const PmergeMe& other);

    void parse(int argc, char** argv);
    void sort(void);

private:
    std::vector<int> _vec;
    std::deque<int>  _deq;

    // Ford-Johnson for vector
    void fordJohnsonVec(std::vector<int>& seq);
    void binaryInsertVec(std::vector<int>& chain,
                         std::vector<int>::iterator begin,
                         std::vector<int>::iterator end,
                         int val);

    // Ford-Johnson for deque
    void fordJohnsonDeq(std::deque<int>& seq);
    void binaryInsertDeq(std::deque<int>& chain,
                         std::deque<int>::iterator begin,
                         std::deque<int>::iterator end,
                         int val);

    // Jacobsthal sequence generator
    static int jacobsthal(int n);

    // Print sequence
    template <typename T>
    void printSeq(const T& seq) const;
};

#endif /* PMERGEME_HPP */
```

**Jacobsthal number generator:**
```cpp
int PmergeMe::jacobsthal(int n)
{
    if (n == 0) return 0;
    if (n == 1) return 1;
    int a = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        int c = b + 2 * a;
        a = b;
        b = c;
    }
    return b;
}
```

**Ford-Johnson for std::vector (key logic):**
```cpp
void PmergeMe::fordJohnsonVec(std::vector<int>& seq)
{
    int n = seq.size();
    if (n <= 1) return;

    // Step 1 — Make pairs and sort each pair (larger first)
    std::vector<std::pair<int,int> > pairs;
    int straggler = -1;
    bool hasStraggler = (n % 2 != 0);

    for (int i = 0; i + 1 < n; i += 2) {
        int lo = seq[i], hi = seq[i + 1];
        if (lo > hi) std::swap(lo, hi);
        pairs.push_back(std::make_pair(lo, hi)); // (small, large)
    }
    if (hasStraggler)
        straggler = seq[n - 1];

    // Step 2 — Recursively sort the "highs"
    std::vector<int> highs;
    for (size_t i = 0; i < pairs.size(); i++)
        highs.push_back(pairs[i].second);
    fordJohnsonVec(highs);  // recursive call

    // Step 3 — Build main chain from sorted highs, prepend smallest low
    // The low of the pair whose high is first in the chain is guaranteed
    // to be smallest — insert it directly at front
    std::vector<int> chain(highs);

    // Map highs to their corresponding lows
    std::vector<int> pends;
    for (size_t i = 0; i < highs.size(); i++) {
        // Find the pair whose high == highs[i]
        for (size_t j = 0; j < pairs.size(); j++) {
            if (pairs[j].second == highs[i]) {
                pends.push_back(pairs[j].first);
                break;
            }
        }
    }

    // Insert pend[0] at front (it's <= chain[0] since it was paired with chain[0])
    chain.insert(chain.begin(), pends[0]);

    // Step 4 — Insert remaining pends in Jacobsthal order
    // Build the insertion order
    std::vector<int> insertOrder;
    int k = 2;
    int prev = 1;
    while (prev < (int)pends.size()) {
        int curr = jacobsthal(k);
        if (curr > (int)pends.size())
            curr = (int)pends.size();
        // Insert from curr-1 down to prev (inclusive), 0-indexed into pends
        for (int idx = curr - 1; idx >= prev; idx--) {
            if (idx < (int)pends.size())
                insertOrder.push_back(idx);
        }
        prev = curr;
        k++;
    }

    for (size_t i = 0; i < insertOrder.size(); i++) {
        int pendIdx = insertOrder[i];
        int val = pends[pendIdx];

        // The bound: val < highs[pendIdx], which is now at position pendIdx+1 in chain
        // (because pends[0] was inserted at front, shifting everything by 1)
        std::vector<int>::iterator bound = std::find(chain.begin(), chain.end(), highs[pendIdx]);

        binaryInsertVec(chain, chain.begin(), bound, val);
    }

    // Insert straggler if present
    if (hasStraggler)
        binaryInsertVec(chain, chain.begin(), chain.end(), straggler);

    seq = chain;
}
```

**Binary insert helper for std::vector:**
```cpp
void PmergeMe::binaryInsertVec(std::vector<int>& chain,
                                std::vector<int>::iterator begin,
                                std::vector<int>::iterator end,
                                int val)
{
    std::vector<int>::iterator lo = begin;
    std::vector<int>::iterator hi = end;

    while (lo < hi) {
        std::vector<int>::iterator mid = lo + (std::distance(lo, hi) / 2);
        if (*mid < val)
            lo = mid + 1;
        else
            hi = mid;
    }
    chain.insert(lo, val);
}
```

> **For `std::deque`:** Write the exact same logic using `std::deque<int>` and `std::deque<int>::iterator`. The algorithm is identical — only the container type changes. This explicit duplication is required by the subject.

### Parsing Input in main.cpp

```cpp
void PmergeMe::parse(int argc, char** argv)
{
    for (int i = 1; i < argc; i++) {
        std::string arg(argv[i]);
        for (size_t j = 0; j < arg.size(); j++) {
            if (!std::isdigit(arg[j])) {
                std::cerr << "Error" << std::endl;
                exit(1);
            }
        }
        int val = std::atoi(arg.c_str());
        if (val <= 0) {
            std::cerr << "Error" << std::endl;
            exit(1);
        }
        _vec.push_back(val);
        _deq.push_back(val);
    }
    if (_vec.empty()) {
        std::cerr << "Error" << std::endl;
        exit(1);
    }
}
```

**sort() — full orchestration:**
```cpp
void PmergeMe::sort(void)
{
    // Print before
    std::cout << "Before:";
    for (size_t i = 0; i < _vec.size(); i++)
        std::cout << " " << _vec[i];
    std::cout << std::endl;

    // Sort with vector and time it
    struct timeval start, end;
    gettimeofday(&start, NULL);
    fordJohnsonVec(_vec);
    gettimeofday(&end, NULL);
    double vecTime = (end.tv_sec - start.tv_sec) * 1000000.0
                   + (end.tv_usec - start.tv_usec);

    // Sort with deque and time it
    gettimeofday(&start, NULL);
    fordJohnsonDeq(_deq);
    gettimeofday(&end, NULL);
    double deqTime = (end.tv_sec - start.tv_sec) * 1000000.0
                   + (end.tv_usec - start.tv_usec);

    // Print after (using sorted vector)
    std::cout << "After: ";
    for (size_t i = 0; i < _vec.size(); i++)
        std::cout << " " << _vec[i];
    std::cout << std::endl;

    // Print times
    std::cout << "Time to process a range of " << _vec.size()
              << " elements with std::vector : " << vecTime << " us" << std::endl;
    std::cout << "Time to process a range of " << _deq.size()
              << " elements with std::deque  : " << deqTime << " us" << std::endl;
}
```

### Testing with the Required Commands

```bash
# Small test (5-10 elements)
./PmergeMe 3 5 9 7 4

# Linux — 3000 random elements from 1..1000
./PmergeMe `shuf -i 1-1000 -n 3000 | tr "\n" " "`

# Error cases
./PmergeMe "-1" "2"
./PmergeMe "abc"
./PmergeMe "3 3 5"   # duplicates — handling is at your discretion
```

### Common Mistakes

| Mistake | Problem |
|---------|---------|
| Using `std::sort` instead of Ford-Johnson | Subject explicitly requires Ford-Johnson — instant fail |
| Using only a generic template for both containers | Subject says implement separately for each container |
| Not measuring the **full** sort time (including data management) | Must measure total time including parsing/copying |
| Using a container already used in ex00 or ex01 | Forbidden — evaluation stops |
| Not handling the odd-element straggler | Will fail on odd-length input |
| Incorrect operand order in binary insert (using `<=` vs `<`) | May produce unstable or wrong sort |

---

## 8. Defense Preparation — Full Q&A

### Exercise 00 — Bitcoin Exchange

**Q: Why did you use `std::map` and not another container?**
> `std::map` is the ideal container for a key-value database with date-based lookup. Dates in `YYYY-MM-DD` format sort lexicographically in the correct chronological order, so `std::map`'s natural key ordering gives us chronological sorting for free. Most importantly, `map` provides `lower_bound()` — an O(log n) operation that finds the closest matching date without linear search.

**Q: How does `lower_bound` work, and why do you decrement the iterator?**
> `map::lower_bound(key)` returns an iterator to the **first** entry whose key is `>= key`. If the exact date exists, it points directly to it. If not, it points to the first date *after* the input — so we need to step back one position (`--it`) to get the closest *lower* date. We must check `it != db.begin()` before decrementing to avoid undefined behavior.

**Q: What happens if you used `_db[date]` instead of `lower_bound`?**
> `operator[]` on a `std::map` **inserts** a default-constructed value (0.0) if the key does not exist. This would corrupt the database for every missing date query — a serious bug.

**Q: How do you validate that a value isn't too large?**
> Values must be between 0 and 1000. After parsing with `strtod`, we check `val < 0` (error: not a positive number) and `val > 1000` (error: too large a number). We also check the `strtod` end pointer to detect non-numeric input.

**Q: Does the program stop on the first error?**
> No. The subject explicitly says to process the **whole** input file. Errors are printed with `std::cerr`, but processing continues to the next line.

---

### Exercise 01 — Reverse Polish Notation

**Q: Why did you use `std::stack`?**
> The RPN algorithm is fundamentally LIFO: the most recently pushed operand is always the first consumed by the next operator. `std::stack` models this exactly — it's the textbook data structure for expression evaluation. Any other container would require manually managing a "top" index.

**Q: Why is the container from ex00 forbidden here?**
> The module enforces real understanding of container selection. If you used `std::map` for ex00, using it in ex01 would be inappropriate (a map is not a stack) — the restriction forces you to pick the right tool.

**Q: Walk me through evaluating `"7 7 * 7 -"`:**
> - Token `7` → push: stack = `[7]`
> - Token `7` → push: stack = `[7, 7]`
> - Token `*` → pop 7 and 7, compute `7 * 7 = 49`, push: stack = `[49]`
> - Token `7` → push: stack = `[49, 7]`
> - Token `-` → pop 7 (right), pop 49 (left), compute `49 - 7 = 42`, push: stack = `[42]`
> - End: stack has exactly 1 element → result is `42`

**Q: What happens with `"(1 + 1)"`?**
> The `(` and `)` characters are not single digits, so `token.size() == 1 && !isdigit(token[0])` — they're also not valid operators (`+-*/`). Both paths reject the token and throw `"Error"`.

**Q: What if the stack is empty but we encounter an operator?**
> We check `if (_stack.size() < 2)` before popping. If fewer than 2 elements are present, we throw `"Error"`.

---

### Exercise 02 — PmergeMe

**Q: Why did you use `std::vector` and `std::deque`?**
> Both are required for Ford-Johnson because the algorithm needs **binary search**, which requires random-access iterators (to compute midpoints in O(1) by `lo + distance/2`). `std::vector` and `std::deque` both provide random-access iterators. `std::list` does not, making binary search O(n) per step. The two containers also give an interesting performance comparison since `deque` has more complex internal memory management.

**Q: Explain the Ford-Johnson algorithm.**
> Ford-Johnson (Merge-Insertion Sort) works by:
> 1. Pairing up all elements and sorting each pair (⌊n/2⌋ comparisons)
> 2. Recursively sorting the larger element of each pair
> 3. Building a main chain from the sorted larger elements
> 4. Inserting the smaller elements (and any straggler) back into the chain using binary insertion, in an order determined by **Jacobsthal numbers** to minimize worst-case comparisons
>
> The Jacobsthal-ordered insertion ensures that each binary search covers at most a power-of-2 range, making every insertion use the minimum number of comparisons.

**Q: What are Jacobsthal numbers and why do they matter?**
> Jacobsthal numbers follow the recurrence `J(n) = J(n-1) + 2*J(n-2)`, giving the sequence `0, 1, 1, 3, 5, 11, 21, 43, ...`. In Ford-Johnson, they define the optimal order and grouping for inserting pend elements. By processing groups defined by Jacobsthal boundaries, each binary search is guaranteed to search at most a 2^k length range, making the comparison count optimal.

**Q: What is the difference in time between `std::vector` and `std::deque`?**
> `std::vector` stores elements in a single contiguous block of memory — excellent cache locality. `std::deque` stores them in multiple fixed-size chunks — better for front insertions but worse cache locality. For sorting (which does many insertions in the middle), `vector` typically has better performance because of cache efficiency, even though `deque::insert` is theoretically the same complexity. The actual difference is visible with 3000+ elements.

**Q: Why does the subject say "do not use a generic function" for the two containers?**
> To demonstrate you understand the algorithm well enough to implement it specifically for each container's API, rather than just wrapping a template. It proves you didn't just copy-paste with typedefs.

**Q: How do you handle the straggler (odd element)?**
> If the input has an odd number of elements, after pairing, one element remains unpaired. This "straggler" is saved aside and inserted into the final chain using binary search after all pend elements are inserted.

---

## 9. Niche Trivia & Deep Knowledge

### std::map internals

- `std::map` is implemented as a **Red-Black Tree** — a self-balancing binary search tree
- All operations (insert, find, erase, lower_bound) are O(log n)
- **Iterator stability:** Inserting or erasing elements does NOT invalidate iterators to other elements (unlike `vector`)
- Keys are stored in sorted order — iterating yields keys in ascending order
- `std::map::value_type` is `std::pair<const Key, Value>` — the key is `const` even in a non-const iterator

### `lower_bound` vs member function

- `db.lower_bound(key)` — **member function**, uses the tree structure: O(log n)
- `std::lower_bound(db.begin(), db.end(), key)` — **generic algorithm**, does linear search on map (range iteration): O(n)
- Always use the **member function** `lower_bound` for maps!

### RPN and Expression Parsing

- RPN is used internally by many compilers as an intermediate representation
- Converting infix to RPN uses the **Shunting-Yard Algorithm** (Dijkstra, 1961)
- Integer overflow: `3 * 2147483647` overflows `int`. The subject says inputs are < 10, but intermediate results can be large

### Ford-Johnson — Theoretical Depth

- Ford-Johnson is proven optimal in comparisons for n ≤ 15 elements
- For larger n, its comparison count is very close to the theoretical minimum `⌈log₂(n!)⌉`
- In practice, real-world sort performance is dominated by **cache efficiency**, not comparison count — which is why `std::sort` (introsort) is faster on modern hardware even though Ford-Johnson makes fewer comparisons

### Performance Difference: `vector` vs `deque`

| Aspect | `std::vector` | `std::deque` |
|--------|--------------|-------------|
| Memory layout | Single contiguous block | Multiple fixed-size chunks |
| Cache behavior | Excellent | Good |
| Middle insertion | O(n) — shifts elements | O(n) — shifts within chunk |
| Front insertion | O(n) — shifts all | O(1) |
| Random access | O(1) | O(1) |
| Reallocation | May reallocate (invalidates all iterators) | Never reallocates |

For Ford-Johnson, middle insertions dominate → `vector` often wins due to cache locality.

---

## 10. Evaluation Checklist

Before your defense, verify every item below:

### Compilation
| Check | Requirement |
|-------|-------------|
| ✅ | Compiles with `c++ -Wall -Wextra -Werror` |
| ✅ | Compiles with `-std=c++98` |
| ✅ | No C functions: `printf`, `malloc`, `free` |
| ✅ | No `using namespace std` or `friend` |
| ✅ | No functions implemented in headers (except templates) |

### Ex00 — Bitcoin Exchange
| Check | Requirement |
|-------|-------------|
| ✅ | Program named `btc` |
| ✅ | Takes file as argument, errors if no argument |
| ✅ | Uses `std::map` (or another container — must justify choice) |
| ✅ | Loads `data.csv` database at startup |
| ✅ | Handles empty file without crashing |
| ✅ | Handles bad dates (wrong format, invalid month/day) |
| ✅ | Handles negative values → `Error: not a positive number.` |
| ✅ | Handles values > 1000 → `Error: too large a number.` |
| ✅ | Continues processing after each error (doesn't stop) |
| ✅ | Uses nearest **lower** date if exact date not in DB |
| ✅ | Does NOT use `operator[]` for database lookup |

### Ex01 — Reverse Polish Notation
| Check | Requirement |
|-------|-------------|
| ✅ | Program named `RPN` |
| ✅ | Uses a **different** container from ex00 |
| ✅ | Can justify container choice |
| ✅ | Handles all four operators: `+ - * /` |
| ✅ | Division by zero handled gracefully |
| ✅ | Correct operand order for `-` and `/` |
| ✅ | `(1 + 1)` → `Error` |
| ✅ | All evaluation examples from subject produce correct results |
| ✅ | All advanced examples from evaluation page pass |

### Ex02 — PmergeMe
| Check | Requirement |
|-------|-------------|
| ✅ | Program named `PmergeMe` |
| ✅ | Uses **two** different containers, both different from ex00 and ex01 |
| ✅ | Uses Ford-Johnson (Merge-Insertion Sort) — NOT `std::sort` |
| ✅ | Algorithm implemented **separately** for each container |
| ✅ | Can explain Jacobsthal numbers and their role |
| ✅ | Handles odd-length sequences (straggler) |
| ✅ | Handles 3000 randomized integers without errors |
| ✅ | Output shows: before sequence, after sequence, time for each container |
| ✅ | Time measurement covers **full** operation (parse + sort) |
| ✅ | Negative numbers rejected with `Error` |
| ✅ | Non-numeric input rejected with `Error` |
| ✅ | All non-interface classes in **Orthodox Canonical Form** |
| ✅ | No memory leaks (check with `valgrind`) |

### Quick Test Commands

```bash
# Ex00
make -C ex00 && cd ex00 && ./btc input.txt

# Ex01
make -C ex01 && cd ex01
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"   # should print 42
./RPN "7 7 * 7 -"                     # should print 42
./RPN "1 2 * 2 / 2 + 5 * 6 - 1 3 * - 4 5 * * 8 /"  # should print 15
./RPN "(1 + 1)"                       # should print Error

# Ex02
make -C ex02 && cd ex02
./PmergeMe 3 5 9 7 4
./PmergeMe `shuf -i 1-1000 -n 3000 | tr "\n" " "`
./PmergeMe "-1" "2"    # should print Error

# Memory leaks
valgrind --leak-check=full ./btc input.txt
valgrind --leak-check=full ./RPN "7 7 * 7 -"
valgrind --leak-check=full ./PmergeMe 3 5 9 7 4
```
