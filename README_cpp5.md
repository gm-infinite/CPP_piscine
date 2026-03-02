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
    // Easy to forget to check the return value!
}
```

**With exceptions (C++ style):**
```cpp
int createGrade(int grade) {
    if (grade < 1)
        throw Bureaucrat::GradeTooHighException();
    if (grade > 150)
        throw Bureaucrat::GradeTooLowException();
    return grade;
}

int main() {
    try {
        int g = createGrade(0);  // This will throw
        std::cout << g;          // Never reached
    }
    catch (std::exception& e) {
        std::cout << e.what();   // Handles the error
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
        throw Bureaucrat::GradeTooHighException();
    if (grade > 150)
        throw Bureaucrat::GradeTooLowException();
    std::cout << "Grade is valid";
}
```

**You can throw anything:**
```cpp
throw 42;                                    // An integer
throw "Error message";                       // A C-string
throw std::string("Error");                  // A std::string
throw Bureaucrat::GradeTooHighException();   // A custom exception object (RECOMMENDED)
```

---

### The `try` Block

A `try` block wraps code that **might throw** an exception:

```cpp
try {
    // Code that might fail goes here
    Bureaucrat bob("Bob", 0);  // This throws!
    std::cout << bob;          // Never reached
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
    Bureaucrat bob("Bob", 0);
} catch (std::exception& e) {
    // Handle the exception
    std::cout << "Error: " << e.what() << std::endl;
}
```

**Multiple catch blocks** (from most specific to most general):
```cpp
try {
    Bureaucrat bob("Bob", 0);
}
catch (Bureaucrat::GradeTooHighException& e) {
    std::cout << "Grade too high!";
}
catch (Bureaucrat::GradeTooLowException& e) {
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
        return "Grade is too high (minimum is 1)";
    }
};
```

### Method 2: Nested Exception Classes (RECOMMENDED for CPP05)

The subject requires exceptions as **nested classes** inside Bureaucrat:

```cpp
class Bureaucrat {
public:
    // Nested exception classes
    class GradeTooHighException : public std::exception {
    public:
        const char* what() const throw() {
            return "Grade is too high (minimum is 1)";
        }
    };
    
    class GradeTooLowException : public std::exception {
    public:
        const char* what() const throw() {
            return "Grade is too low (maximum is 150)";
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
| `Name` | `const std::string`, set at construction, never changes |
| `grade` | `int` from 1 (highest) to 150 (lowest) |

| Exception | When thrown |
|-----------|-------------|
| `GradeTooHighException` | When grade < 1 |
| `GradeTooLowException` | When grade > 150 |

| Method | Description |
|--------|-------------|
| `getName()` | Returns the name |
| `getGrade()` | Returns the grade |
| `setGrade()` | Sets the grade (with validation) |
| `incrementGrade()` | Decreases grade by 1 (grade 3 → grade 2) |
| `decrementGrade()` | Increases grade by 1 (grade 3 → grade 4) |

**Note:** Grade 1 is the HIGHEST (best), grade 150 is the LOWEST (worst).

### Implementation Guide

**Bureaucrat.hpp:**
```cpp
#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <string>
#include <iostream>
#include <exception>

class Bureaucrat {

public:
    // Orthodox Canonical Form
    Bureaucrat(void);
    ~Bureaucrat(void);
    Bureaucrat(const std::string& name, int grade);
    Bureaucrat(const Bureaucrat& other);
    Bureaucrat& operator=(const Bureaucrat& other);

    // Getters & Setters
    std::string getName(void) const;
    int getGrade(void) const;
    void setGrade(const int grade);

    // Grade modifiers
    void incrementGrade(void);
    void decrementGrade(void);

    // Nested exception classes
    class GradeTooHighException : public std::exception {
    public:
        const char* what() const throw() {
            return "Grade is too high (minimum is 1)";
        }
    };
    
    class GradeTooLowException : public std::exception {
    public:
        const char* what() const throw() {
            return "Grade is too low (maximum is 150)";
        }
    };

private:
    const std::string Name;
    int grade;
};

// Overload for << operator (outside class)
std::ostream& operator<<(std::ostream& os, const Bureaucrat& obj);

#endif /* BUREAUCRAT_HPP */
```

**Key implementation points in Bureaucrat.cpp:**

```cpp
/* ┌──────────────────┐ */
/* │   CONSTRUCTORS   │ */
/* └──────────────────┘ */
Bureaucrat::Bureaucrat(void) : Name("random_employe"), grade(150)
{ }

Bureaucrat::Bureaucrat(const Bureaucrat& other) : Name(other.Name), grade(other.grade)
{ }

// Constructor with grade validation
Bureaucrat::Bureaucrat(const std::string& name, int grade) : Name(name)
{
    if (grade < 1)
        throw GradeTooHighException();
    else if (grade > 150)
        throw GradeTooLowException();
    this->grade = grade;
}

/* ┌───────────────────┐ */
/* │   DESTRUCTOR     │ */
/* └───────────────────┘ */
Bureaucrat::~Bureaucrat(void)
{ }

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */
Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other)
{
    if (this != &other)
        this->grade = other.grade;
    return *this;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

// Increment (grade gets BETTER = number gets smaller)
void Bureaucrat::incrementGrade(void)
{
    if (grade - 1 < 1)
        throw GradeTooHighException();
    this->grade--;
}

// Decrement (grade gets WORSE = number gets bigger)
void Bureaucrat::decrementGrade(void)
{
    if (grade + 1 > 150)
        throw GradeTooLowException();
    this->grade++;
}

std::string Bureaucrat::getName(void) const {
    return this->Name;
}

int Bureaucrat::getGrade(void) const {
    return this->grade;
}

void Bureaucrat::setGrade(const int grade) {
    if (grade < 1)
        throw GradeTooHighException();
    else if (grade > 150)
        throw GradeTooLowException();
    this->grade = grade;
}

// << operator overload
std::ostream& operator<<(std::ostream& os, const Bureaucrat& obj) 
{
    os << obj.getName() << ", bureaucrat grade " << obj.getGrade() << ".";  
    return os;
}
```

### Testing Example (main.cpp)

```cpp
#include "Bureaucrat.hpp"

int main()
{
    std::cout << "--- Test 1: Valid bureaucrat ---" << std::endl;
    try {
        Bureaucrat bob("Bob", 50);
        std::cout << bob << std::endl;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n--- Test 2: Grade too high (0) ---" << std::endl;
    try {
        Bureaucrat alice("Alice", 0);
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n--- Test 3: Grade too low (151) ---" << std::endl;
    try {
        Bureaucrat charlie("Charlie", 151);
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n--- Test 4: Increment at grade 1 ---" << std::endl;
    try {
        Bureaucrat dave("Dave", 1);
        std::cout << dave << std::endl;
        dave.incrementGrade();
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n--- Test 5: Decrement at grade 150 ---" << std::endl;
    try {
        Bureaucrat eve("Eve", 150);
        std::cout << eve << std::endl;
        eve.decrementGrade();
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n--- Test 6: Normal increment/decrement ---" << std::endl;
    try {
        Bureaucrat frank("Frank", 75);
        std::cout << frank << std::endl;
        frank.incrementGrade();
        std::cout << frank << std::endl;
        frank.decrementGrade();
        std::cout << frank << std::endl;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
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
| `Name` | `const std::string` | Name of the form |
| `IsSigned` | `bool` | False at construction |
| `SignGrade` | `const int` | Min grade needed to sign (1-150) |
| `ExecuteGrade` | `const int` | Min grade needed to execute (1-150) |

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
| `getSignGrade()` | Returns required grade to sign |
| `getExecuteGrade()` | Returns required grade to execute |
| `beSigned(const Bureaucrat& b)` | Signs form if bureaucrat's grade is high enough |

**New Bureaucrat Method:**
| Method | Description |
|--------|-------------|
| `signForm(Form& f)` | Attempts to sign form, prints success/failure message |

### Key Concept: Who Throws vs Who Catches

```
Bureaucrat::signForm(Form& f)
    │
    ├── calls f.beSigned(*this)
    │       │
    │       └── Form checks grade
    │               │
    │               ├── OK → IsSigned = true
    │               │
    │               └── FAIL → throw GradeTooLowException
    │
    └── catches exception, prints error message
```

### Implementation Guide

**Form.hpp:**
```cpp
#ifndef FORM_HPP
#define FORM_HPP

#include <string>

class Bureaucrat;  // Forward declaration (avoids circular include)

class Form {

public:
    // Orthodox Canonical Form
    Form(void);
    ~Form(void);
    Form(const std::string& name, int SignGrade, int ExecuteGrade);
    Form(const Form& other);
    Form& operator=(const Form& other);

    // Getters
    std::string getName(void) const;
    bool getIsSigned(void) const;
    int getSignGrade(void) const;
    int getExecuteGrade(void) const;

    // Sign method
    void beSigned(const Bureaucrat& b);

    // Nested exception classes
    class GradeTooHighException : public std::exception {
    public:
        const char* what() const throw() {
            return "Form: Grade is too high (minimum is 1)";
        }
    };
    
    class GradeTooLowException : public std::exception {
    public:
        const char* what() const throw() {
            return "Form: Grade is too low (maximum is 150)";
        }
    };

private:
    const std::string Name;
    bool IsSigned;
    const int SignGrade;
    const int ExecuteGrade;
};

std::ostream& operator<<(std::ostream& os, const Form& form);

#endif /* FORM_HPP */
```

**Key Form.cpp implementation:**
```cpp
#include "Form.hpp"
#include "Bureaucrat.hpp"

/* ┌──────────────────┐ */
/* │   CONSTRUCTORS   │ */
/* └──────────────────┘ */
Form::Form(void) : 
Name("default"), 
IsSigned(false), 
SignGrade(1), 
ExecuteGrade(1)
{ }

Form::Form(const Form& other) :
Name(other.Name), 
IsSigned(other.IsSigned), 
SignGrade(other.SignGrade), 
ExecuteGrade(other.ExecuteGrade)
{ }

// Constructor validates grades
Form::Form(const std::string& name, int SignGrade, int ExecuteGrade): 
Name(name),
IsSigned(false),
SignGrade(SignGrade),
ExecuteGrade(ExecuteGrade)
{
    if (SignGrade < 1 || ExecuteGrade < 1)
        throw Form::GradeTooHighException();
    if (SignGrade > 150 || ExecuteGrade > 150)
        throw Form::GradeTooLowException();
}

/* ┌───────────────────┐ */
/* │   DESTRUCTOR     │ */
/* └───────────────────┘ */
Form::~Form(void)
{ }

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */
Form& Form::operator=(const Form& other)
{
    if (this != &other)
        this->IsSigned = other.IsSigned;
    return *this;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

// beSigned - called by Bureaucrat::signForm()
void Form::beSigned(const Bureaucrat& b)
{
    if (this->IsSigned)
        throw std::runtime_error("Form is already signed");
    if (!(b.getGrade() <= this->SignGrade))  // Remember: lower number = higher grade
        throw Form::GradeTooLowException();
    std::cout << "the form has been signed" << std::endl;
    this->IsSigned = true;
}

std::string Form::getName(void) const {
    return this->Name;
}

bool Form::getIsSigned(void) const {
    return this->IsSigned;
}

int Form::getSignGrade(void) const {
    return this->SignGrade;
}

int Form::getExecuteGrade(void) const {
    return this->ExecuteGrade;
}

// << operator
std::ostream& operator<<(std::ostream& os, const Form& form) {
    os << "Form: " << form.getName() << '\n'
       << "Signed: " << (form.getIsSigned() ? "yes" : "no") << '\n'
       << "Grade to sign: " << form.getSignGrade() << '\n'
       << "Grade to execute: " << form.getExecuteGrade() << std::endl;
    return os;
}
```

**Add to Bureaucrat.hpp:**
```cpp
class Form;  // Forward declaration at top

// Add this method declaration
void signForm(Form& f) const;
```

**Add to Bureaucrat.cpp:**
```cpp
#include "Form.hpp"  // Need full definition now

void Bureaucrat::signForm(Form& f) const
{
    try {
        f.beSigned(*this);
    }
    catch (std::exception& e) {
        std::cout << e.what() << '\n' 
                  << " ^^ the bureaucrat catched an error from form::beSigned() in signForm()" 
                  << std::endl;
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

int main()
{
    std::cout << "--- Test 1: Create valid Form ---" << std::endl;
    try {
        Form taxForm("Tax Form", 50, 25);
        std::cout << taxForm << std::endl;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n--- Test 2: Form grade too high (0) ---" << std::endl;
    try {
        Form badForm("Bad Form", 0, 25);
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n--- Test 3: Form grade too low (151) ---" << std::endl;
    try {
        Form badForm("Bad Form", 151, 25);
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n--- Test 4: Bureaucrat signs Form successfully ---" << std::endl;
    try {
        Bureaucrat boss("Boss", 10);
        Form easyForm("Easy Form", 50, 25);
        std::cout << boss << std::endl;
        std::cout << easyForm << std::endl;
        boss.signForm(easyForm);
        std::cout << easyForm << std::endl;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n--- Test 5: Bureaucrat fails to sign (grade too low) ---" << std::endl;
    try {
        Bureaucrat intern("Intern", 100);
        Form hardForm("Hard Form", 10, 5);
        std::cout << intern << std::endl;
        std::cout << hardForm << std::endl;
        intern.signForm(hardForm);
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n--- Test 6: Bureaucrat at exact grade limit ---" << std::endl;
    try {
        Bureaucrat exactGrade("ExactGrade", 50);
        Form exactForm("Exact Form", 50, 25);
        std::cout << exactGrade << std::endl;
        std::cout << exactForm << std::endl;
        exactGrade.signForm(exactForm);
        std::cout << exactForm << std::endl;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
```

---

## Exercise 02: No, you need form 28B, not 28C...

### Goal
Transform `Form` into an **abstract base class** (`AForm`) and create concrete form classes that actually do something when executed. Learn about **abstract classes**, **pure virtual functions**, and **polymorphism** with exceptions.

### New Concepts: Abstract Classes & Pure Virtual Functions

**What is an Abstract Class?**
An abstract class is a class that:
- Cannot be instantiated directly
- Contains at least one **pure virtual function**
- Serves as a base class for derived classes

**Pure Virtual Function:**
A function declared with `= 0` - it has no implementation in the base class and MUST be overridden by derived classes.

```cpp
class AForm {
public:
    // Pure virtual function - makes AForm abstract
    virtual void execute(Bureaucrat const & executor) const = 0;
};

// This will NOT compile:
AForm form;  // ERROR! Cannot instantiate abstract class

// This WILL compile:
ShrubberyCreationForm form("home");  // OK! Concrete class
```

**Why use Abstract Classes?**
- Defines a common interface that all derived classes must follow
- Ensures derived classes implement required functionality
- Allows polymorphism - use base class pointers/references to work with any derived class

### Requirements

**Files to Submit:**
- `Makefile`
- `main.cpp`
- `Bureaucrat.hpp`, `Bureaucrat.cpp`
- `AForm.hpp`, `AForm.cpp`
- `ShrubberyCreationForm.hpp`, `ShrubberyCreationForm.cpp`
- `RobotomyRequestForm.hpp`, `RobotomyRequestForm.cpp`
- `PresidentialPardonForm.hpp`, `PresidentialPardonForm.cpp`

### Changes to Form → AForm

**Rename Form to AForm and make it abstract:**
| Change | Description |
|--------|-------------|
| Rename class | `Form` → `AForm` |
| Add `execute()` | Pure virtual function to execute the form's action |
| Add `setIsSigned()` | Setter for derived classes |
| Keep attributes private | All attributes stay in base class |

**AForm Attributes (all private, inherited from ex01):**
| Attribute | Type | Description |
|-----------|------|-------------|
| `Name` | `const std::string` | Name of the form |
| `IsSigned` | `bool` | False at construction |
| `SignGrade` | `const int` | Min grade needed to sign (1-150) |
| `ExecuteGrade` | `const int` | Min grade needed to execute (1-150) |

**New AForm Methods:**
| Method | Description |
|--------|-------------|
| `execute(Bureaucrat const & executor) const` | Pure virtual - executes the form's action |
| `setIsSigned(const bool a)` | Setter for IsSigned (used in derived class copy) |

**New AForm Exception:**
| Exception | When thrown |
|-----------|-------------|
| `AForm::FormNotSignedException` | When attempting to execute an unsigned form |

### Concrete Form Classes

All concrete forms inherit from `AForm` and take only ONE parameter: **Target** (std::string).

| Form Class | Grade to Sign | Grade to Execute | Action |
|------------|---------------|------------------|--------|
| `ShrubberyCreationForm` | 145 | 137 | Creates file `<Target>_shrubbery` with ASCII trees |
| `RobotomyRequestForm` | 72 | 45 | 50% chance: "<Target> has been robotomized" or "robotomy failed" |
| `PresidentialPardonForm` | 25 | 5 | "<Target> has been pardoned by Zaphod Beeblebrox" |

### New Bureaucrat Method

| Method | Description |
|--------|-------------|
| `executeForm(AForm const & form) const` | Attempts to execute form, prints success/error message |

### Implementation Guide

**AForm.hpp:**
```cpp
#ifndef AFORM_HPP
#define AFORM_HPP

#include <string>
#include <iostream>

class Bureaucrat;

class AForm {

public:
    // Orthodox Canonical Form
    AForm(void);
    ~AForm(void);
    AForm(const std::string& name, int SignGrade, int ExecuteGrade);
    AForm(const AForm& other);
    AForm& operator=(const AForm& other);

    // Getters & Setters
    std::string getName(void) const;
    bool getIsSigned(void) const;
    int getSignGrade(void) const;
    int getExecuteGrade(void) const;
    void setIsSigned(const bool a);

    // Sign and Execute
    void beSigned(const Bureaucrat& b);
    virtual void execute(const Bureaucrat& executor) const = 0;  // Pure virtual

    // Nested exception classes
    class GradeTooHighException : public std::exception {
    public:
        const char* what() const throw() {
            return "AForm: Grade is too high (minimum is 1)";
        }
    };
    
    class GradeTooLowException : public std::exception {
    public:
        const char* what() const throw() {
            return "AForm: Grade is too low (maximum is 150)";
        }
    };

    class FormNotSignedException : public std::exception {
    public:
        const char* what() const throw() {
            return "AForm: Form is not signed!";
        }
    };

private:
    const std::string Name;
    bool IsSigned;
    const int SignGrade;
    const int ExecuteGrade;
};

std::ostream& operator<<(std::ostream& os, const AForm& form);

#endif /* AFORM_HPP */
```

**ShrubberyCreationForm.hpp:**
```cpp
#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"

class ShrubberyCreationForm : public AForm {

public:
    ShrubberyCreationForm(void);
    ~ShrubberyCreationForm(void);
    ShrubberyCreationForm(const std::string Target);
    ShrubberyCreationForm(const ShrubberyCreationForm& other);
    ShrubberyCreationForm& operator=(const ShrubberyCreationForm& other);

    std::string getTarget(void) const;

    void execute(Bureaucrat const& executor) const;

private:
    std::string Target;
};

std::ostream& operator<<(std::ostream& os, const ShrubberyCreationForm& form);

#endif /* SHRUBBERYCREATIONFORM_HPP */
```

**ShrubberyCreationForm.cpp:**
```cpp
#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"
#include <fstream>

/* ┌──────────────────┐ */
/* │   CONSTRUCTORS   │ */
/* └──────────────────┘ */
ShrubberyCreationForm::ShrubberyCreationForm(void):
AForm("Shrubbery_Creation_Form", 145, 137),
Target("default")
{ }

ShrubberyCreationForm::ShrubberyCreationForm(const std::string Target) :
AForm("Shrubbery_Creation_Form", 145, 137),
Target(Target)
{ }

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other) :
AForm(other),
Target(other.Target)
{ }

/* ┌───────────────────┐ */
/* │   DESTRUCTOR     │ */
/* └───────────────────┘ */
ShrubberyCreationForm::~ShrubberyCreationForm(void)
{ }

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */
ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other)
{
    if (this != &other) {
        this->setIsSigned(other.getIsSigned());
        this->Target = other.Target;
    }
    return *this;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */
void ShrubberyCreationForm::execute(const Bureaucrat& b) const
{
    if (!this->getIsSigned())
        throw FormNotSignedException();
    if (this->getExecuteGrade() < b.getGrade())
        throw GradeTooLowException();
    
    std::ofstream file((this->Target + "_shrubbery").c_str());
    if (!file.is_open())
        throw std::runtime_error("Could not create file");
    
    file << "       _-_" << std::endl;
    file << "    /~~   ~~\\" << std::endl;
    file << " /~~         ~~\\" << std::endl;
    file << "{               }" << std::endl;
    file << " \\  _-     -_  /" << std::endl;
    file << "   ~  \\\\ //  ~" << std::endl;
    file << "_- -   | | _- _" << std::endl;
    file << "  _ -  | |   -_" << std::endl;
    file << "      // \\\\" << std::endl;

    file.close();
}

std::string ShrubberyCreationForm::getTarget(void) const {
    return this->Target;
}

std::ostream& operator<<(std::ostream& os, const ShrubberyCreationForm& f)
{
    os << "Form: " << f.getName() << '\n'
       << "Signed: " << (f.getIsSigned() ? "yes" : "no") << '\n'
       << "Grade to sign: " << f.getSignGrade() << '\n'
       << "Grade to execute: " << f.getExecuteGrade() << '\n'
       << "Target: " << f.getTarget() << std::endl;
    return os;
}
```

**RobotomyRequestForm execute:**
```cpp
void RobotomyRequestForm::execute(const Bureaucrat& b) const
{
    if (!this->getIsSigned())
        throw FormNotSignedException();
    if (this->getExecuteGrade() < b.getGrade())
        throw GradeTooLowException();
    
    std::cout << "* DRILLING NOISES * Bzzzz... Vrrrr..." << std::endl;
    
    if (std::rand() % 2 == 0)
        std::cout << this->Target << " has been robotomized successfully!" << std::endl;
    else
        std::cout << "Robotomy failed on " << this->Target << "!" << std::endl;
}
```

**PresidentialPardonForm execute:**
```cpp
void PresidentialPardonForm::execute(const Bureaucrat& b) const
{
    if (!this->getIsSigned())
        throw FormNotSignedException();
    if (this->getExecuteGrade() < b.getGrade())
        throw GradeTooLowException();
    
    std::cout << this->Target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}
```

**Add to Bureaucrat (ex02):**
```cpp
// In Bureaucrat.hpp
class AForm;  // Forward declaration

void signForm(AForm& f) const;
void executeForm(AForm const & form) const;

// In Bureaucrat.cpp
void Bureaucrat::signForm(AForm& f) const
{
    try {
        f.beSigned(*this);
    }
    catch (std::exception& e) {
        std::cout << e.what() << '\n' 
                  << " ^^ the bureaucrat catched an error from form::beSigned() in signForm()" 
                  << std::endl;
    }
}

void Bureaucrat::executeForm(const AForm& form) const
{
    try {
        form.execute(*this);
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n' 
                  << " ^^ the bureaucrat catched an error from AForm::execute() in executeForm()" 
                  << std::endl;
    }
}
```

### Testing Example (main.cpp)

```cpp
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <cstdlib>
#include <ctime>

int main()
{
    std::srand(std::time(0));

    std::cout << "=== Test 1: ShrubberyCreationForm - Execute Success ===" << std::endl;
    try {
        Bureaucrat bob("Bob", 1);
        ShrubberyCreationForm shrub("home");
        std::cout << shrub << std::endl;
        bob.signForm(shrub);
        bob.executeForm(shrub);
        std::cout << "Check for 'home_shrubbery' file!" << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 2: Execute unsigned form ===" << std::endl;
    try {
        Bureaucrat alice("Alice", 1);
        ShrubberyCreationForm shrub("garden");
        alice.executeForm(shrub);
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 3: Execute with grade too low ===" << std::endl;
    try {
        Bureaucrat intern("Intern", 140);
        Bureaucrat boss("Boss", 1);
        ShrubberyCreationForm shrub("office");
        boss.signForm(shrub);
        intern.executeForm(shrub);
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 4: RobotomyRequestForm - 50% success ===" << std::endl;
    try {
        Bureaucrat scientist("Scientist", 1);
        RobotomyRequestForm robot("Bender");
        std::cout << robot << std::endl;
        scientist.signForm(robot);
        std::cout << "Attempt 1:" << std::endl;
        scientist.executeForm(robot);
        std::cout << "Attempt 2:" << std::endl;
        scientist.executeForm(robot);
        std::cout << "Attempt 3:" << std::endl;
        scientist.executeForm(robot);
        std::cout << "Attempt 4:" << std::endl;
        scientist.executeForm(robot);
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 5: PresidentialPardonForm ===" << std::endl;
    try {
        Bureaucrat president("President", 1);
        PresidentialPardonForm pardon("Arthur Dent");
        std::cout << pardon << std::endl;
        president.signForm(pardon);
        president.executeForm(pardon);
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 6: PresidentialPardonForm - grade too low to sign ===" << std::endl;
    try {
        Bureaucrat clerk("Clerk", 100);
        PresidentialPardonForm pardon("Ford Prefect");
        clerk.signForm(pardon);
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 7: RobotomyRequestForm - grade too low to execute ===" << std::endl;
    try {
        Bureaucrat signer("Signer", 50);
        Bureaucrat executor("Executor", 50);
        RobotomyRequestForm robot("Target");
        signer.signForm(robot);
        executor.executeForm(robot);
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 8: Execute at exact grade limit ===" << std::endl;
    try {
        Bureaucrat exact("ExactGrade", 137);
        Bureaucrat signer("Signer", 1);
        ShrubberyCreationForm shrub("exact");
        signer.signForm(shrub);
        exact.executeForm(shrub);
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
```

---

## Exercise 03: At least this beats coffee-making

### Goal
Implement an `Intern` class that can create forms. Learn about **factory patterns** and avoiding messy if/else structures using **function pointers** or **lookup tables**.

### New Concept: Factory Pattern

A **factory** is a function or class that creates objects for you. Instead of:
```cpp
AForm* form;
if (name == "shrubbery creation")
    form = new ShrubberyCreationForm(target);
else if (name == "robotomy request")
    form = new RobotomyRequestForm(target);
else if (name == "presidential pardon")
    form = new PresidentialPardonForm(target);
```

You use a factory:
```cpp
AForm* form = intern.makeForm("robotomy request", "Bender");
```

**Why factories?**
- Centralizes object creation logic
- Caller doesn't need to know concrete class names
- Easy to add new form types without changing calling code

### Requirements

**Files to Submit:**
- All files from ex02
- `Intern.hpp`, `Intern.cpp`

**Intern Class:**
| Attribute | Description |
|-----------|-------------|
| None | Interns have no name, no grade, no unique characteristics |

| Method | Description |
|--------|-------------|
| `makeForm(std::string formName, std::string target)` | Creates and returns a pointer to the requested form |

**makeForm() behavior:**
- Takes form name and target as parameters
- Returns `AForm*` pointing to the created form
- Prints: `Intern creates <form>`
- If form name doesn't exist: prints error message

**Valid form names:**
| Input String | Creates |
|--------------|---------|
| `"shrubbery creation"` | `ShrubberyCreationForm` |
| `"robotomy request"` | `RobotomyRequestForm` |
| `"presidential pardon"` | `PresidentialPardonForm` |

### Key Concept: Avoiding if/else Chains

The subject explicitly forbids messy if/else structures. A clean approach is to use a **loop + switch** pattern.

**Note:** In C++98, `switch` only works with integers, not strings. So we first find the index of the form name, then use switch on that index.

#### Loop + Switch Pattern (Recommended)

```cpp
AForm* Intern::makeForm(std::string formName, std::string target)
{
    // Array of valid form names
    std::string formNames[] = {
        "shrubbery creation",
        "robotomy request",
        "presidential pardon"
    };
    
    // Find the index of the form name
    int formIndex = -1;
    for (int i = 0; i < 3; i++) {
        if (formNames[i] == formName) {
            formIndex = i;
            break;
        }
    }
    
    // Use switch on the index
    AForm* form = NULL;
    switch (formIndex) {
        case 0:
            form = new ShrubberyCreationForm(target);
            break;
        case 1:
            form = new RobotomyRequestForm(target);
            break;
        case 2:
            form = new PresidentialPardonForm(target);
            break;
        default:
            std::cout << "Error: Form '" << formName << "' does not exist" << std::endl;
            return NULL;
    }
    
    std::cout << "Intern creates " << formName << std::endl;
    return form;
}
```

**Why this works:**
1. The loop finds which form was requested (returns an integer index)
2. The switch creates the correct form based on that index
3. Clean, readable, and avoids messy if/else chains

### Implementation Guide

**Intern.hpp:**
```cpp
#ifndef INTERN_HPP
#define INTERN_HPP

#include "AForm.hpp"

class Intern {

public:
    // Orthodox Canonical Form
    Intern(void);
    ~Intern(void);
    Intern(const Intern& other);
    Intern& operator=(const Intern& other);

    // The intern's only ability
    AForm* makeForm(std::string formName, std::string target);

};

#endif /* INTERN_HPP */
```

**Intern.cpp:**
```cpp
#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

/* ┌──────────────────┐ */
/* │   CONSTRUCTORS   │ */
/* └──────────────────┘ */
Intern::Intern(void)
{ }

Intern::Intern(const Intern& other)
{
    (void)other;  // Nothing to copy
}

/* ┌───────────────────┐ */
/* │   DESTRUCTOR     │ */
/* └───────────────────┘ */
Intern::~Intern(void)
{ }

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */
Intern& Intern::operator=(const Intern& other)
{
    (void)other;  // Nothing to assign
    return *this;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */
AForm* Intern::makeForm(std::string formName, std::string target)
{
    // Array of valid form names
    std::string formNames[] = {
        "shrubbery creation",
        "robotomy request",
        "presidential pardon"
    };
    
    // Find the index of the form name
    int formIndex = -1;
    for (int i = 0; i < 3; i++) {
        if (formNames[i] == formName) {
            formIndex = i;
            break;
        }
    }
    
    // Use switch on the index
    AForm* form = NULL;
    switch (formIndex) {
        case 0:
            form = new ShrubberyCreationForm(target);
            break;
        case 1:
            form = new RobotomyRequestForm(target);
            break;
        case 2:
            form = new PresidentialPardonForm(target);
            break;
        default:
            std::cout << "Error: Intern cannot create form '" << formName 
                      << "' - form does not exist" << std::endl;
            return NULL;
    }
    
    std::cout << "Intern creates " << formName << std::endl;
    return form;
}
```

### Testing Example (main.cpp)

```cpp
#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <cstdlib>
#include <ctime>

int main()
{
    std::srand(std::time(0));
    
    Intern someRandomIntern;
    Bureaucrat boss("Boss", 1);
    
    std::cout << "=== Test 1: Intern creates RobotomyRequestForm ===" << std::endl;
    {
        AForm* rrf = someRandomIntern.makeForm("robotomy request", "Bender");
        if (rrf) {
            std::cout << *rrf << std::endl;
            boss.signForm(*rrf);
            boss.executeForm(*rrf);
            delete rrf;
        }
    }
    
    std::cout << "\n=== Test 2: Intern creates ShrubberyCreationForm ===" << std::endl;
    {
        AForm* scf = someRandomIntern.makeForm("shrubbery creation", "garden");
        if (scf) {
            boss.signForm(*scf);
            boss.executeForm(*scf);
            delete scf;
        }
    }
    
    std::cout << "\n=== Test 3: Intern creates PresidentialPardonForm ===" << std::endl;
    {
        AForm* ppf = someRandomIntern.makeForm("presidential pardon", "Marvin");
        if (ppf) {
            boss.signForm(*ppf);
            boss.executeForm(*ppf);
            delete ppf;
        }
    }
    
    std::cout << "\n=== Test 4: Intern tries to create invalid form ===" << std::endl;
    {
        AForm* invalid = someRandomIntern.makeForm("coffee request", "Office");
        if (!invalid) {
            std::cout << "Form creation failed as expected" << std::endl;
        }
    }
    
    return 0;
}
```

### Important Notes

1. **Memory Management**: `makeForm()` returns a pointer to `new`'d memory. The caller is responsible for `delete`ing it!

2. **Return NULL on failure**: If the form name doesn't exist, return `NULL` (not throw an exception, unless you prefer that approach).

3. **Case sensitivity**: Form names should match exactly. You could add case-insensitive comparison if you want.

---

## Summary

| Exercise | Key Concepts |
|----------|--------------|
| ex00 | Basic exceptions, nested exception classes, throw/try/catch |
| ex01 | Class interaction, forward declarations, one class throws another catches |
| ex02 | Abstract classes, pure virtual functions, polymorphism |
| ex03 | Factory pattern, loop + switch for string matching |

**Remember:**
- Grade 1 = HIGHEST (best), Grade 150 = LOWEST (worst)
- Exceptions use `what()` to return error messages
- Nested classes keep exceptions organized
- Forward declarations prevent circular includes
- Pure virtual functions (`= 0`) make classes abstract
- Switch doesn't work with strings in C++98 - use loop to find index first
- Factory pattern centralizes object creation
