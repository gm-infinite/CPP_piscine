# CPP Module 06 - C++ Casts

## Overview

This module teaches **type casting** in C++:
- **static_cast** - Compile-time checked conversions
- **reinterpret_cast** - Low-level bit reinterpretation
- **dynamic_cast** - Runtime polymorphic type checking
- **const_cast** - Add/remove const qualifier

---

## Key Concepts Learned

### What Are C++ Casts?

C-style casts `(type)value` are dangerous because they try multiple cast types silently. C++ provides four explicit casts that each serve a specific purpose:

```cpp
// C-style (avoid in C++)
int x = (int)3.14;

// C++ style (preferred)
int x = static_cast<int>(3.14);
```

---

### static_cast

Used for **well-defined, compile-time** conversions. The compiler checks if the conversion is valid.

**When to use:**
- Numeric conversions (int ↔ float ↔ double)
- Upcasting in inheritance (Derived* → Base*)
- Explicit conversions that would normally be implicit

```cpp
// Numeric conversion
double pi = 3.14159;
int truncated = static_cast<int>(pi);  // 3

// Upcast (always safe)
class Animal {};
class Dog : public Animal {};

Dog* dog = new Dog();
Animal* animal = static_cast<Animal*>(dog);  // OK

// String to number (using library functions)
std::string str = "42";
int num = std::atoi(str.c_str());  // Use atoi, strtol, etc.
```

**What static_cast CANNOT do:**
- Convert unrelated pointer types
- Remove const (use const_cast)
- Downcast without knowing the actual type

---

### reinterpret_cast

Used for **low-level bit reinterpretation**. Tells compiler "trust me, treat these bits as this type."

**When to use:**
- Converting pointers to integers and back
- Interfacing with hardware/system calls
- Serialization (storing pointers as numbers)

```cpp
// Pointer to integer
int* ptr = new int(42);
uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);

// Integer back to pointer
int* restored = reinterpret_cast<int*>(addr);

// Both point to same memory
std::cout << (*restored);  // 42
```

**Important:** `uintptr_t` (from `<cstdint>` or `<stdint.h>`) is an unsigned integer type guaranteed to hold any pointer.

**Warning:** reinterpret_cast does NO checking. The result is only valid if you know exactly what you're doing.

---

### dynamic_cast

Used for **runtime type checking** in polymorphic hierarchies. Only works with classes that have at least one virtual function.

**When to use:**
- Downcasting (Base* → Derived*) when you're not sure of the actual type
- Runtime type identification without typeinfo

```cpp
class Vehicle {
public:
    virtual ~Vehicle() {}  // MUST have virtual function
};

class Car : public Vehicle {
public:
    void honk() { std::cout << "Beep!"; }
};

class Boat : public Vehicle {
public:
    void sail() { std::cout << "Sailing!"; }
};

void identify(Vehicle* v) {
    // With pointers: returns NULL on failure
    if (Car* c = dynamic_cast<Car*>(v)) {
        c->honk();
    }
    else if (Boat* b = dynamic_cast<Boat*>(v)) {
        b->sail();
    }
}

void identifyRef(Vehicle& v) {
    // With references: throws std::bad_cast on failure
    try {
        Car& c = dynamic_cast<Car&>(v);
        c.honk();
    }
    catch (std::bad_cast&) {
        // Not a Car
    }
}
```

**Key behaviors:**
- **Pointer version:** Returns `NULL` if cast fails
- **Reference version:** Throws `std::bad_cast` if cast fails
- **Requires polymorphism:** Base class must have at least one virtual function

---

### const_cast

Used to **add or remove const** qualifier. Only cast that can do this.

```cpp
void legacyFunction(char* str) {
    // Old function that doesn't use const
}

const char* msg = "Hello";
legacyFunction(const_cast<char*>(msg));  // Remove const
```

**Warning:** Modifying a truly const object is undefined behavior. Only use const_cast when you know the underlying object is actually non-const.

---

### Which Cast to Use?

| Need | Cast |
|------|------|
| Numeric conversion | `static_cast` |
| Upcast (derived → base) | `static_cast` |
| Pointer ↔ integer | `reinterpret_cast` |
| Runtime type check | `dynamic_cast` |
| Remove/add const | `const_cast` |

---

## Exercise 00: Conversion of scalar types

### Goal
Create a `ScalarConverter` class with a static method that converts string literals to char, int, float, and double.

### Requirements

**Class:** `ScalarConverter`
- Not instantiable by users (private constructor or delete)
- Single static method: `convert(std::string literal)`

**Supported input types:**
| Type | Examples |
|------|----------|
| char | `'a'`, `'Z'`, `'*'` |
| int | `0`, `-42`, `42` |
| float | `0.0f`, `-4.2f`, `nanf`, `-inff`, `+inff` |
| double | `0.0`, `-4.2`, `nan`, `-inf`, `+inf` |

**Output format:**
```
char: <value> or 'Non displayable' or 'impossible'
int: <value> or 'impossible'
float: <value>f or 'impossible'
double: <value> or 'impossible'
```

### Recommended Cast
**static_cast** - Converting between numeric types is exactly what static_cast does.

### Implementation Guide

**ScalarConverter.hpp:**
```cpp
#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>

class ScalarConverter {

public:
    static void convert(const std::string& literal);

private:
    // Private constructors - class cannot be instantiated
    ScalarConverter(void);
    ~ScalarConverter(void);
    ScalarConverter(const ScalarConverter& other);
    ScalarConverter& operator=(const ScalarConverter& other);
};

#endif /* SCALARCONVERTER_HPP */
```

**Key implementation logic:**

The subject says: "detect the type... convert it from string to **its actual type**, then convert it **explicitly** to the three other data types."

This means:
1. Parse CHAR input → `char` variable → cast to int, float, double
2. Parse INT input → `int` variable → cast to char, float, double
3. Parse FLOAT input → `float` variable → cast to char, int, double
4. Parse DOUBLE input → `double` variable → cast to char, int, float

**1. Detect the type of the input:**
```cpp
enum LiteralType { CHAR, INT, FLOAT, DOUBLE, INVALID };

static LiteralType detectType(const std::string& literal)
{
    if (literal.empty())
        return INVALID;
    if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'')
        return CHAR;
    if (literal == "+inf" || literal == "-inf" || literal == "nan")
        return DOUBLE;
    if (literal == "+inff" || literal == "-inff" || literal == "nanf")
        return FLOAT;
    
    // Validate numeric literal
    bool hasDecimal = false;
    bool hasF = false;
    size_t start = (literal[0] == '+' || literal[0] == '-') ? 1 : 0;
    
    if (start >= literal.length())
        return INVALID;
    
    for (size_t i = start; i < literal.length(); i++)
    {
        if (literal[i] == '.') {
            if (hasDecimal) return INVALID;
            hasDecimal = true;
        }
        else if (literal[i] == 'f' && i == literal.length() - 1)
            hasF = true;
        else if (!std::isdigit(literal[i]))
            return INVALID;
    }
    
    if (hasF) return FLOAT;
    if (hasDecimal) return DOUBLE;
    return INT;
}
```

**2. Create print functions for each source type:**

```cpp
static void printFromChar(char c)
{
    std::cout << "char: '" << c << "'" << std::endl;
    std::cout << "int: " << static_cast<int>(c) << std::endl;
    std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
    std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
}

static void printFromInt(int i)
{
    if (i < 0 || i > 127)
        std::cout << "char: impossible" << std::endl;
    else if (!std::isprint(i))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(i) << "'" << std::endl;
    
    std::cout << "int: " << i << std::endl;
    std::cout << "float: " << static_cast<float>(i) << ".0f" << std::endl;
    std::cout << "double: " << static_cast<double>(i) << ".0" << std::endl;
}

static void printFromFloat(float f)
{
    bool isSpecial = std::isnan(f) || std::isinf(f);

    if (isSpecial || f < 0 || f > 127)
        std::cout << "char: impossible" << std::endl;
    else if (!std::isprint(static_cast<int>(f)))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(f) << "'" << std::endl;
    
    if (isSpecial || f < static_cast<float>(INT_MIN) || f > static_cast<float>(INT_MAX))
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(f) << std::endl;

    std::cout << "float: " << f;
    if (!isSpecial && f == static_cast<int>(f))
        std::cout << ".0";
    std::cout << "f" << std::endl;
    
    std::cout << "double: " << static_cast<double>(f);
    if (!isSpecial && f == static_cast<int>(f))
        std::cout << ".0";
    std::cout << std::endl;
}

static void printFromDouble(double d)
{
    bool isSpecial = std::isnan(d) || std::isinf(d);
    
    if (isSpecial || d < 0 || d > 127)
        std::cout << "char: impossible" << std::endl;
    else if (!std::isprint(static_cast<int>(d)))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;

    if (isSpecial || d < INT_MIN || d > INT_MAX)
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(d) << std::endl;
    
    std::cout << "float: " << static_cast<float>(d);
    if (!isSpecial && d == static_cast<int>(d))
        std::cout << ".0";
    std::cout << "f" << std::endl;
    
    std::cout << "double: " << d;
    if (!isSpecial && d == static_cast<int>(d))
        std::cout << ".0";
    std::cout << std::endl;
}
```

**3. Main convert function:**

```cpp
void ScalarConverter::convert(const std::string& literal)
{
    LiteralType type = detectType(literal);
    
    switch(type)
    {
        case CHAR:
        {
            char c = literal[1];
            printFromChar(c);
            break;
        }
        case INT:
        {
            // Use strtod to detect overflow (handles numbers > LONG_MAX)
            double d = std::strtod(literal.c_str(), NULL);
            if (d < INT_MIN || d > INT_MAX) {
                std::cout << "integer overflow occurred." << std::endl;
                return;
            }
            int i = static_cast<int>(d);
            printFromInt(i);
            break;
        }
        case FLOAT:
        {
            float f = static_cast<float>(std::strtod(literal.c_str(), NULL));
            printFromFloat(f);
            break;
        }
        case DOUBLE:
        {
            double d = std::strtod(literal.c_str(), NULL);
            printFromDouble(d);
            break;
        }
        case INVALID:
            std::cout << "Invalid type entered." << std::endl;
            return;
    }
}
```

**Why this approach?**

| Detected Type | Stored As | Cast To Others |
|---------------|-----------|----------------|
| CHAR | `char c` | `static_cast<int>(c)`, `static_cast<float>(c)`, `static_cast<double>(c)` |
| INT | `int i` | `static_cast<char>(i)`, `static_cast<float>(i)`, `static_cast<double>(i)` |
| FLOAT | `float f` | `static_cast<char>(f)`, `static_cast<int>(f)`, `static_cast<double>(f)` |
| DOUBLE | `double d` | `static_cast<char>(d)`, `static_cast<int>(d)`, `static_cast<float>(d)` |

### Testing Example (main.cpp)

```cpp
#include "ScalarConverter.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cout << "Usage: ./convert <literal>" << std::endl;
        return 1;
    }
    
    ScalarConverter::convert(argv[1]);
    return 0;
}
```

**Test cases:**
```bash
./convert 0
./convert 42
./convert -42
./convert 42.0f
./convert 42.0
./convert 'a'
./convert nan
./convert nanf
./convert +inf
./convert -inff
```

---

## Exercise 01: Serialization

### Goal
Create a `Serializer` class that converts pointers to integers and back. Understand how pointers are just memory addresses.

### Requirements

**Class:** `Serializer`
- Not instantiable by users
- Two static methods:
  - `uintptr_t serialize(Data* ptr)` - pointer to integer
  - `Data* deserialize(uintptr_t raw)` - integer to pointer

**Data structure:**
- Must be non-empty (has data members)
- You define its contents

### Recommended Cast
**reinterpret_cast** - Converting pointers to integers is exactly what reinterpret_cast does.

### Implementation Guide

**Data.hpp:**
```cpp
#ifndef DATA_HPP
#define DATA_HPP

#include <string>

struct Data {
    int id;
    std::string name;
    double value;
};

#endif /* DATA_HPP */
```

**Serializer.hpp:**
```cpp
#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <stdint.h>  // For uintptr_t (C++98 compatible)
#include "Data.hpp"

class Serializer {

public:
    static uintptr_t serialize(Data* ptr);
    static Data* deserialize(uintptr_t raw);

private:
    // Private constructors - class cannot be instantiated
    Serializer(void);
    ~Serializer(void);
    Serializer(const Serializer& other);
    Serializer& operator=(const Serializer& other);
};

#endif /* SERIALIZER_HPP */
```

**Serializer.cpp:**
```cpp
#include "Serializer.hpp"

/* ┌──────────────────┐ */
/* │   CONSTRUCTORS   │ */
/* └──────────────────┘ */
Serializer::Serializer(void) {}
Serializer::Serializer(const Serializer& other) { (void)other; }
Serializer::~Serializer(void) {}
Serializer& Serializer::operator=(const Serializer& other) { (void)other; return *this; }

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */
uintptr_t Serializer::serialize(Data* ptr)
{
    return reinterpret_cast<uintptr_t>(ptr);
}

Data* Serializer::deserialize(uintptr_t raw)
{
    return reinterpret_cast<Data*>(raw);
}
```

### Testing Example (main.cpp)

```cpp
#include "Serializer.hpp"
#include <iostream>

int main()
{
    // Create Data object
    Data original;
    original.id = 42;
    original.name = "Test Data";
    original.value = 3.14159;
    
    std::cout << "=== Original Data ===" << std::endl;
    std::cout << "Address: " << &original << std::endl;
    std::cout << "ID: " << original.id << std::endl;
    std::cout << "Name: " << original.name << std::endl;
    std::cout << "Value: " << original.value << std::endl;
    
    // Serialize (pointer → integer)
    uintptr_t serialized = Serializer::serialize(&original);
    std::cout << "\n=== Serialized ===" << std::endl;
    std::cout << "Raw value: " << serialized << std::endl;
    
    // Deserialize (integer → pointer)
    Data* restored = Serializer::deserialize(serialized);
    std::cout << "\n=== Deserialized ===" << std::endl;
    std::cout << "Address: " << restored << std::endl;
    std::cout << "ID: " << restored->id << std::endl;
    std::cout << "Name: " << restored->name << std::endl;
    std::cout << "Value: " << restored->value << std::endl;
    
    // Verify pointers match
    std::cout << "\n=== Verification ===" << std::endl;
    if (restored == &original)
        std::cout << "SUCCESS: Pointers match!" << std::endl;
    else
        std::cout << "FAILURE: Pointers don't match!" << std::endl;
    
    return 0;
}
```

---

## Exercise 02: Identify real type

### Goal
Identify the actual type of a polymorphic object at runtime WITHOUT using `typeid` or `<typeinfo>`.

### Requirements

**Base class:**
- Only has public virtual destructor
- No Orthodox Canonical Form required

**Derived classes:** A, B, C
- Empty classes inheriting from Base
- No Orthodox Canonical Form required

**Functions:**
| Function | Description |
|----------|-------------|
| `Base* generate(void)` | Randomly creates A, B, or C, returns as Base* |
| `void identify(Base* p)` | Prints "A", "B", or "C" (using pointer) |
| `void identify(Base& p)` | Prints "A", "B", or "C" (using reference, no pointer inside) |

### Recommended Cast
**dynamic_cast** - Runtime type identification in polymorphic hierarchies.

### Key Concept: dynamic_cast Behavior

```cpp
// With pointers: returns NULL on failure
Base* base = new A();
A* a = dynamic_cast<A*>(base);  // Returns valid pointer
B* b = dynamic_cast<B*>(base);  // Returns NULL

// With references: throws std::bad_cast on failure
Base* base = new A();
try {
    A& a = dynamic_cast<A&>(*base);  // OK
    B& b = dynamic_cast<B&>(*base);  // Throws!
} catch (std::bad_cast&) {
    // Handle failure
}
```

### Implementation Guide

**Base.hpp:**
```cpp
#ifndef BASE_HPP
#define BASE_HPP

class Base {
public:
    virtual ~Base(void);
};

#endif /* BASE_HPP */
```

**Base.cpp:**
```cpp
#include "Base.hpp"

Base::~Base(void) {}
```

**A.hpp, B.hpp, C.hpp:** (similar structure)
```cpp
#ifndef A_HPP
#define A_HPP

#include "Base.hpp"

class A : public Base {};

#endif /* A_HPP */
```

**Functions implementation:**
```cpp
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <iostream>

Base* generate(void)
{
    int random = std::rand() % 3;
    
    switch (random) {
        case 0:
            return new A();
        case 1:
            return new B();
        default:
            return new C();
    }
}

// Using pointers: check for NULL
void identify(Base* p)
{
    if (dynamic_cast<A*>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout << "C" << std::endl;
    else
        std::cout << "Unknown type" << std::endl;
}

// Using references: catch exceptions
void identify(Base& p)
{
    try {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        return;
    } catch (...) {}
    
    try {
        (void)dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        return;
    } catch (...) {}
    
    try {
        (void)dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        return;
    } catch (...) {}
    
    std::cout << "Unknown type" << std::endl;
}
```

### Testing Example (main.cpp)

```cpp
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

// Function declarations
Base* generate(void);
void identify(Base* p);
void identify(Base& p);

int main()
{
    std::srand(std::time(0));
    
    std::cout << "=== Generating random objects ===" << std::endl;
    for (int i = 0; i < 10; i++) {
        Base* obj = generate();
        
        std::cout << "Object " << i + 1 << ": ";
        std::cout << "Pointer identify: ";
        identify(obj);
        
        std::cout << "         Reference identify: ";
        identify(*obj);
        
        delete obj;
    }
    
    std::cout << "\n=== Testing known types ===" << std::endl;
    Base* a = new A();
    Base* b = new B();
    Base* c = new C();
    
    std::cout << "A object: ";
    identify(a);
    std::cout << "B object: ";
    identify(b);
    std::cout << "C object: ";
    identify(c);
    
    delete a;
    delete b;
    delete c;
    
    return 0;
}
```

---

## Summary

| Exercise | Cast Used | Purpose |
|----------|-----------|---------|
| ex00 | `static_cast` | Numeric type conversions |
| ex01 | `reinterpret_cast` | Pointer ↔ integer conversion |
| ex02 | `dynamic_cast` | Runtime polymorphic type identification |

**Remember:**
- `static_cast` - Compile-time, safe numeric/inheritance conversions
- `reinterpret_cast` - Low-level bit reinterpretation, no safety checks
- `dynamic_cast` - Runtime type checking, requires virtual functions
- `const_cast` - Only way to add/remove const (not used in this module)

**Important for defense:** Be ready to explain WHY you chose each specific cast for each exercise.
