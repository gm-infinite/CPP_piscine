# CPP Module 05 - Exceptions (try, catch, throw)

## Overview

This module teaches **exception handling** in C++:
- **Exceptions** - A way to handle errors that occur during program execution
- **try/catch blocks** - How to safely execute code that might fail
- **throw** - How to signal that an error occurred
- **Custom exception classes** - Creating your own error types

---

## Key Concepts Learned

### What Are Exceptions?

Exceptions are a mechanism to handle **runtime errors** gracefully. Instead of crashing or returning error codes, you can:
1. **Throw** an exception when something goes wrong
2. **Catch** it somewhere else and handle the error

**Without exceptions (C-style error handling):**
```cpp
int createGrade(int grade) {
    if (grade < 1 || grade > 150)
        return -1;  // Error code - caller must check!
    return grade;
}

int main() {
    int g = createGrade(0);
    if (g == -1)
        std::cout << "Error!";  // Easy to forget this check!
}
```

**With exceptions (C++ style):**
```cpp
int createGrade(int grade) {
    if (grade < 1)
        throw GradeTooHighException();  // Execution STOPS here
    if (grade > 150)
        throw GradeTooLowException();
    return grade;
}

int main() {
    try {
        int g = createGrade(0);  // Exception thrown!
        // This line NEVER executes
    } catch (std::exception& e) {
        std::cout << "Error: " << e.what();  // Handles the error
    }
}
```

---

### The `throw` Keyword

`throw` sends an exception up the call stack. When thrown:
1. Current function **immediately stops**
2. The exception travels up through calling functions
3. Until a `catch` block handles it (or program terminates)

```cpp
void validateGrade(int grade) {
    if (grade < 1)
        throw std::out_of_range("Grade too high!");  // THROWS exception
    // Code below this NEVER runs if exception is thrown
    std::cout << "Grade is valid";
}
```

**You can throw anything:**
```cpp
throw 42;                    // An integer
throw "Error message";       // A C-string
throw std::string("Error");  // A std::string
throw MyException();         // A custom exception object (RECOMMENDED)
```

---

### The `try` Block

A `try` block wraps code that **might throw** an exception:

```cpp
try {
    // Code that might fail goes here
    riskyFunction();
    anotherRiskyFunction();
}
```

If ANY line in the try block throws:
- Execution immediately jumps to the matching `catch` block
- Remaining code in try block is **skipped**

---

### The `catch` Block

A `catch` block handles exceptions thrown from the `try` block:

```cpp
try {
    riskyFunction();
} catch (ExceptionType& e) {
    // Handle the exception
    std::cout << "Error: " << e.what() << std::endl;
}
```

**Multiple catch blocks** (from most specific to most general):
```cpp
try {
    riskyFunction();
}
catch (GradeTooHighException& e) {
    std::cout << "Grade too high!";
}
catch (GradeTooLowException& e) {
    std::cout << "Grade too low!";
}
catch (std::exception& e) {
    std::cout << "Some other error: " << e.what();
}
catch (...) {  // Catches ANYTHING (including non-exception types)
    std::cout << "Unknown error occurred";
}
```

**Important:** `catch` blocks are checked **in order**. Put specific exceptions first, general ones last.

---

### The `std::exception` Base Class

C++ provides a base class for all exceptions: `std::exception`

```cpp
#include <exception>

class std::exception {
public:
    virtual const char* what() const throw();  // Returns error description
};
```

**The `what()` method:**
- Returns a C-string describing the error
- Should be overridden in your custom exceptions

---

## Creating Custom Exception Classes

### Method 1: Inherit from `std::exception`

```cpp
#include <exception>

class GradeTooHighException : public std::exception {
public:
    const char* what() const throw() {
        return "Grade is too high!";
    }
};
```

### Method 2: Nested Exception Classes (RECOMMENDED for CPP05)

The subject requires exceptions as **nested classes** inside Bureaucrat:

```cpp
class Bureaucrat {
public:
    // Nested exception class
    class GradeTooHighException : public std::exception {
    public:
        const char* what() const throw() {
            return "Grade is too high (minimum is 1)!";
        }
    };
    
    class GradeTooLowException : public std::exception {
    public:
        const char* what() const throw() {
            return "Grade is too low (maximum is 150)!";
        }
    };
    
    // ... rest of Bureaucrat
};
```

**Why nested classes?**
- Clearly shows these exceptions belong to Bureaucrat
- Avoids polluting global namespace
- Access as: `Bureaucrat::GradeTooHighException`

---

## The `throw()` Specifier (Exception Specification)

You'll see this syntax in older C++ code:
```cpp
const char* what() const throw();
```

The `throw()` after `const` means: "This function promises not to throw any exceptions"

**In C++11 and later**, use `noexcept` instead:
```cpp
const char* what() const noexcept override;
```

**For CPP05 (C++98 compatibility)**, use the `throw()` syntax.

---

## Exercise 00: Bureaucrat

### Goal
Create a `Bureaucrat` class that throws exceptions for invalid grades.

### Requirements

| Attribute | Description |
|-----------|-------------|
| `name` | `const std::string`, set at construction, never changes |
| `grade` | `int` from 1 (highest) to 150 (lowest) |

| Exception | When thrown |
|-----------|-------------|
| `GradeTooHighException` | When grade < 1 |
| `GradeTooLowException` | When grade > 150 |

| Method | Description |
|--------|-------------|
| `getName()` | Returns the name |
| `getGrade()` | Returns the grade |
| `incrementGrade()` | Decreases grade by 1 (grade 3 → grade 2) |
| `decrementGrade()` | Increases grade by 1 (grade 3 → grade 4) |

**Note:** Grade 1 is the HIGHEST (best), grade 150 is the LOWEST (worst).

### Implementation Guide

**Bureaucrat.hpp:**
```cpp
#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <string>
#include <exception>
#include <iostream>

class Bureaucrat {
public:
    // Orthodox Canonical Form
    Bureaucrat(void);
    Bureaucrat(const std::string& name, int grade);  // Parameterized constructor
    Bureaucrat(const Bureaucrat& other);
    Bureaucrat& operator=(const Bureaucrat& other);
    ~Bureaucrat(void);

    // Getters
    const std::string& getName(void) const;
    int getGrade(void) const;

    // Grade modifiers (can throw!)
    void incrementGrade(void);  // Makes grade better (lower number)
    void decrementGrade(void);  // Makes grade worse (higher number)

    // Nested exception classes
    class GradeTooHighException : public std::exception {
    public:
        const char* what() const throw();
    };

    class GradeTooLowException : public std::exception {
    public:
        const char* what() const throw();
    };

private:
    const std::string _name;
    int _grade;
};

// Overload for << operator (outside class)
std::ostream& operator<<(std::ostream& os, const Bureaucrat& b);

#endif
```

**Key implementation points in Bureaucrat.cpp:**

```cpp
// Constructor with grade validation
Bureaucrat::Bureaucrat(const std::string& name, int grade) : _name(name) {
    if (grade < 1)
        throw GradeTooHighException();
    if (grade > 150)
        throw GradeTooLowException();
    _grade = grade;
}

// Increment (grade gets BETTER = number gets smaller)
void Bureaucrat::incrementGrade(void) {
    if (_grade <= 1)
        throw GradeTooHighException();
    _grade--;
}

// Decrement (grade gets WORSE = number gets bigger)
void Bureaucrat::decrementGrade(void) {
    if (_grade >= 150)
        throw GradeTooLowException();
    _grade++;
}

// Exception what() implementations
const char* Bureaucrat::GradeTooHighException::what() const throw() {
    return "Grade is too high!";
}

const char* Bureaucrat::GradeTooLowException::what() const throw() {
    return "Grade is too low!";
}

// << operator overload
std::ostream& operator<<(std::ostream& os, const Bureaucrat& b) {
    os << b.getName() << ", bureaucrat grade " << b.getGrade();
    return os;
}
```

### Testing Example (main.cpp)

```cpp
#include "Bureaucrat.hpp"

int main() {
    // TEST 1: Create valid Bureaucrat
    try {
        Bureaucrat bob("Bob", 50);
        std::cout << bob << std::endl;  // "Bob, bureaucrat grade 50"
    }
    catch (std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // TEST 2: Grade too high (0 is invalid)
    try {
        Bureaucrat alice("Alice", 0);  // Throws GradeTooHighException!
    }
    catch (std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // TEST 3: Grade too low (151 is invalid)
    try {
        Bureaucrat charlie("Charlie", 151);  // Throws GradeTooLowException!
    }
    catch (std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // TEST 4: Increment past limit
    try {
        Bureaucrat dave("Dave", 1);  // Highest grade
        dave.incrementGrade();       // Throws! Can't go higher than 1
    }
    catch (std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // TEST 5: Decrement past limit
    try {
        Bureaucrat eve("Eve", 150);  // Lowest grade
        eve.decrementGrade();        // Throws! Can't go lower than 150
    }
    catch (std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}
```

---

## Exercise 01: Form

### Goal
Create a `Form` class that can be signed by a Bureaucrat. Learn how **two classes interact** through exceptions.

### New Concept: Class Interaction with Exceptions

In ex00, exceptions were self-contained in Bureaucrat. Now you'll learn:
- One class (Form) throws an exception
- Another class (Bureaucrat) catches and handles it
- Classes communicate through method calls that may fail

### Requirements

**Form Class Attributes (all private):**
| Attribute | Type | Description |
|-----------|------|-------------|
| `name` | `const std::string` | Name of the form |
| `isSigned` | `bool` | False at construction |
| `gradeToSign` | `const int` | Min grade needed to sign (1-150) |
| `gradeToExecute` | `const int` | Min grade needed to execute (1-150) |

**Form Exceptions:**
| Exception | When thrown |
|-----------|-------------|
| `Form::GradeTooHighException` | When grade < 1 |
| `Form::GradeTooLowException` | When grade > 150, OR when Bureaucrat tries to sign but grade is too low |

**Form Methods:**
| Method | Description |
|--------|-------------|
| `getName()` | Returns form name |
| `getIsSigned()` | Returns signed status |
| `getGradeToSign()` | Returns required grade to sign |
| `getGradeToExecute()` | Returns required grade to execute |
| `beSigned(Bureaucrat& b)` | Signs form if bureaucrat's grade is high enough |

**New Bureaucrat Method:**
| Method | Description |
|--------|-------------|
| `signForm(Form& f)` | Attempts to sign form, prints success/failure message |

### Key Concept: Who Throws vs Who Catches

```
Bureaucrat::signForm(Form& f)
    │
    └─► try {
            f.beSigned(*this);  ← Calls Form's method
            │
            └─► Form::beSigned(Bureaucrat& b)
                    │
                    └─► if (b.getGrade() > gradeToSign)
                            throw GradeTooLowException();  ← Form THROWS
                        │
                        │ Exception travels back
                        │
                        ▼
        } catch (std::exception& e) {  ← Bureaucrat CATCHES
            // Print failure message
        }
```

### Implementation Guide

**Form.hpp:**
```cpp
#ifndef FORM_HPP
#define FORM_HPP

#include <string>
#include <exception>
#include <iostream>

class Bureaucrat;  // Forward declaration (avoids circular include)

class Form {
public:
    // Orthodox Canonical Form
    Form(void);
    Form(const std::string& name, int gradeToSign, int gradeToExecute);
    Form(const Form& other);
    Form& operator=(const Form& other);
    ~Form(void);

    // Getters
    const std::string& getName(void) const;
    bool getIsSigned(void) const;
    int getGradeToSign(void) const;
    int getGradeToExecute(void) const;

    // Sign the form
    void beSigned(const Bureaucrat& b);

    // Nested exceptions
    class GradeTooHighException : public std::exception {
    public:
        const char* what() const throw();
    };

    class GradeTooLowException : public std::exception {
    public:
        const char* what() const throw();
    };

private:
    const std::string _name;
    bool _isSigned;
    const int _gradeToSign;
    const int _gradeToExecute;
};

std::ostream& operator<<(std::ostream& os, const Form& f);

#endif
```

**Key Form.cpp implementation:**
```cpp
// Constructor validates grades
Form::Form(const std::string& name, int gradeToSign, int gradeToExecute)
    : _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
    if (gradeToSign < 1 || gradeToExecute < 1)
        throw GradeTooHighException();
    if (gradeToSign > 150 || gradeToExecute > 150)
        throw GradeTooLowException();
}

// beSigned - called by Bureaucrat::signForm()
void Form::beSigned(const Bureaucrat& b) {
    if (b.getGrade() > _gradeToSign)  // Remember: lower number = higher grade
        throw GradeTooLowException();
    _isSigned = true;
}

// << operator
std::ostream& operator<<(std::ostream& os, const Form& f) {
    os << "Form: " << f.getName()
       << ", Signed: " << (f.getIsSigned() ? "yes" : "no")
       << ", Grade to sign: " << f.getGradeToSign()
       << ", Grade to execute: " << f.getGradeToExecute();
    return os;
}
```

**Add to Bureaucrat.hpp:**
```cpp
class Form;  // Forward declaration at top

// Add this method declaration
void signForm(Form& f);
```

**Add to Bureaucrat.cpp:**
```cpp
#include "Form.hpp"  // Need full definition now

void Bureaucrat::signForm(Form& f) {
    try {
        f.beSigned(*this);
        std::cout << _name << " signed " << f.getName() << std::endl;
    }
    catch (std::exception& e) {
        std::cout << _name << " couldn't sign " << f.getName()
                  << " because " << e.what() << std::endl;
    }
}
```

### Understanding Forward Declarations

**Problem:** Bureaucrat needs Form, Form needs Bureaucrat = circular dependency!

```cpp
// Bureaucrat.hpp
#include "Form.hpp"  // Form.hpp includes Bureaucrat.hpp = INFINITE LOOP!
```

**Solution:** Forward declaration tells compiler "this class exists, trust me"

```cpp
// Form.hpp
class Bureaucrat;  // Forward declaration - no #include needed

class Form {
    void beSigned(const Bureaucrat& b);  // Can use Bureaucrat& or Bureaucrat*
    // But NOT Bureaucrat b (by value) - compiler needs full definition
};
```

```cpp
// Form.cpp
#include "Bureaucrat.hpp"  // NOW we include it (in .cpp, not .hpp)
```

### Testing Example (main.cpp)

```cpp
#include "Bureaucrat.hpp"
#include "Form.hpp"

int main() {
    // Test 1: Create valid form
    try {
        Form taxForm("Tax Form", 50, 25);
        std::cout << taxForm << std::endl;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    // Test 2: Form with invalid grade
    try {
        Form badForm("Bad Form", 0, 25);  // Throws GradeTooHighException
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    // Test 3: Bureaucrat signs form successfully
    try {
        Bureaucrat boss("Boss", 10);
        Form easyForm("Easy Form", 50, 25);
        boss.signForm(easyForm);  // Should succeed (10 <= 50)
        std::cout << easyForm << std::endl;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    // Test 4: Bureaucrat fails to sign (grade too low)
    try {
        Bureaucrat intern("Intern", 100);
        Form hardForm("Hard Form", 10, 5);
        intern.signForm(hardForm);  // Should fail (100 > 10)
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
```

### Expected Output
```
Form: Tax Form, Signed: no, Grade to sign: 50, Grade to execute: 25
Grade is too high!
Boss signed Easy Form
Form: Easy Form, Signed: yes, Grade to sign: 50, Grade to execute: 25
Intern couldn't sign Hard Form because Grade is too low!
```

---

## Common Mistakes to Avoid

### 1. Catching by Value (Creates a Copy)
```cpp
// BAD - catches a copy, can cause slicing
catch (std::exception e) { }

// GOOD - catches by reference
catch (std::exception& e) { }
```

### 2. Catching General Before Specific
```cpp
// BAD - specific catch is never reached
catch (std::exception& e) { }
catch (GradeTooHighException& e) { }  // NEVER reached!

// GOOD - specific first
catch (GradeTooHighException& e) { }
catch (std::exception& e) { }
```

### 3. Forgetting to Include `<exception>`
```cpp
#include <exception>  // Required for std::exception
```

### 4. Not Using `const throw()` in what()
```cpp
// BAD - might not compile or might have undefined behavior
const char* what() { return "Error"; }

// GOOD - matches std::exception's signature
const char* what() const throw() { return "Error"; }
```

### 5. Throwing in Destructor
```cpp
// VERY BAD - can cause undefined behavior!
~Bureaucrat() {
    throw SomeException();  // NEVER DO THIS
}
```

---

## Exception Flow Visualization

```
main()
  │
  └─► try {
        │
        └─► Bureaucrat("Bob", 0)    ← Constructor called
              │
              └─► if (grade < 1)
                    throw GradeTooHighException()  ← EXCEPTION THROWN!
                    │
                    │ Exception travels UP the call stack
                    │
                    ▼
      } catch (std::exception& e) {  ← CAUGHT HERE
          std::cout << e.what();     ← "Grade is too high!"
      }
```

---

## Quick Reference

| Keyword | Purpose |
|---------|---------|
| `throw` | Throws an exception, stops current function |
| `try` | Wraps code that might throw |
| `catch` | Handles thrown exceptions |
| `what()` | Returns exception description (override in custom exceptions) |
| `throw()` | Exception specification (function promises not to throw) |

---

## Exercises Summary

| Exercise | New Concept | Classes |
|----------|-------------|---------|
| ex00 | Basic exceptions | Bureaucrat |
| ex01 | More exception practice | Form (signed by Bureaucrat) |
| ex02 | Abstract classes + exceptions | AForm, ShrubberyCreationForm, RobotomyRequestForm, PresidentialPardonForm |
| ex03 | Factory pattern + exceptions | Intern (creates forms) |

---

## Memory and Exception Safety

When an exception is thrown, C++ **unwinds the stack**:
- Local variables in the try block are destroyed (destructors called)
- This is called RAII (Resource Acquisition Is Initialization)

```cpp
try {
    Bureaucrat bob("Bob", 50);  // bob is created
    throw SomeException();      // Exception thrown!
    // ~Bureaucrat() is automatically called for bob
}
catch (...) {
    // bob has already been destroyed
}
```

**Important:** If you have raw pointers, they won't be cleaned up automatically:
```cpp
try {
    Bureaucrat* bob = new Bureaucrat("Bob", 50);
    throw SomeException();
    delete bob;  // NEVER EXECUTED = MEMORY LEAK!
}
```

Solution: Use RAII (smart pointers) or ensure cleanup in catch:
```cpp
try {
    Bureaucrat* bob = new Bureaucrat("Bob", 50);
    throw SomeException();
}
catch (...) {
    // Can't access bob here! It's out of scope!
}
```

---

## Compilation

Make sure your Makefile includes:
```makefile
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
```

Good luck with your exceptions! 🎯
