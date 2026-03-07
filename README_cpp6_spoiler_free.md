# CPP Module 06 - C++ Casts (Spoiler-Free)

## The Four C++ Casts

C++ provides four explicit casts. Each serves a specific purpose.

---

### static_cast

**Purpose:** Compile-time checked conversions.

**Use when:**
- Converting between numeric types
- Upcasting in inheritance hierarchies
- Making implicit conversions explicit

```cpp
// Numeric example
double temperature = 98.6;
int rounded = static_cast<int>(temperature);

// Inheritance example
class Shape {};
class Circle : public Shape {};

Circle* circle = new Circle();
Shape* shape = static_cast<Shape*>(circle);
```

**Cannot:**
- Convert unrelated pointer types
- Remove const
- Safely downcast without knowing actual type

---

### reinterpret_cast

**Purpose:** Low-level bit reinterpretation.

**Use when:**
- Converting pointers to integers
- Converting integers to pointers
- System-level programming

```cpp
int* ptr = new int(100);
uintptr_t address = reinterpret_cast<uintptr_t>(ptr);
int* back = reinterpret_cast<int*>(address);
// ptr == back
```

**Warning:** No safety checks. The bits are simply reinterpreted as a different type.

---

### dynamic_cast

**Purpose:** Runtime type checking for polymorphic types.

**Requirements:**
- Base class must have at least one virtual function
- Only works with pointers or references

**Behavior:**
- **Pointer:** Returns `NULL` on failure
- **Reference:** Throws `std::bad_cast` on failure

```cpp
class Animal {
public:
    virtual ~Animal() {}
};

class Cat : public Animal {};
class Dog : public Animal {};

Animal* pet = new Cat();

// Pointer version
Cat* cat = dynamic_cast<Cat*>(pet);   // OK, returns valid pointer
Dog* dog = dynamic_cast<Dog*>(pet);   // Fails, returns NULL

// Reference version
try {
    Cat& catRef = dynamic_cast<Cat&>(*pet);  // OK
} catch (std::bad_cast&) {
    // Type mismatch
}
```

---

### const_cast

**Purpose:** Add or remove const qualifier.

```cpp
const int* constPtr = &value;
int* mutablePtr = const_cast<int*>(constPtr);
```

**Warning:** Modifying a truly const object is undefined behavior.

---

## Quick Reference

| Cast | Compile/Runtime | Safety |
|------|-----------------|--------|
| `static_cast` | Compile | Checked |
| `reinterpret_cast` | Compile | Unchecked |
| `dynamic_cast` | Runtime | Checked |
| `const_cast` | Compile | Unchecked |

---

## Exercise Requirements

### Exercise 00
- Create a class with a static method
- Class should not be instantiable
- Convert string input to different scalar types
- Handle special values (nan, inf)
- Display conversion results or "impossible"

### Exercise 01
- Create a class with two static methods
- Class should not be instantiable
- Work with a custom data structure
- Convert between pointers and integers
- Verify round-trip conversion works

### Exercise 02
- Create a base class with virtual destructor
- Create three derived classes
- Generate random instances
- Identify types using pointer parameter
- Identify types using reference parameter (no pointers allowed inside)
- Cannot use `<typeinfo>` header

---

## Useful Headers

```cpp
#include <cstdlib>   // atoi, strtol, strtod, strtof, rand
#include <climits>   // INT_MIN, INT_MAX
#include <cfloat>    // FLT_MIN, FLT_MAX
#include <cmath>     // isnan, isinf
#include <stdint.h>  // uintptr_t (C++98)
#include <cctype>    // isprint, isdigit
```

---

## Things to Consider

1. **Exercise 00:**
   - How do you detect what type the input string represents?
   - How do you handle overflow when converting?
   - What makes a character "displayable"?

2. **Exercise 01:**
   - What type can hold any pointer value?
   - Is the conversion reversible?

3. **Exercise 02:**
   - Why must Base have a virtual function?
   - How does pointer-based identification differ from reference-based?
   - What happens when a cast fails?
