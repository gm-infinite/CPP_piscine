# CPP Module 04 - Subtype Polymorphism, Abstract Classes, and Interfaces

## Overview

This module introduces **Object-Oriented Programming** concepts in C++:
- **Polymorphism** - Same interface, different behaviors
- **Virtual functions** - Runtime method resolution
- **Abstract classes** - Classes that cannot be instantiated
- **Deep copy** - Properly copying objects with dynamic memory

---

## Key Concepts Learned

### The `virtual` Keyword

The `virtual` keyword enables **runtime polymorphism** (also called dynamic dispatch).

**Without `virtual`:**
```cpp
class Animal {
    void makeSound() const;  // NOT virtual
};

Animal* cat = new Cat();
cat->makeSound();  // Calls Animal::makeSound() - WRONG!
```
The compiler decides at **compile time** which function to call based on the pointer type.

**With `virtual`:**
```cpp
class Animal {
    virtual void makeSound() const;  // Virtual
};

Animal* cat = new Cat();
cat->makeSound();  // Calls Cat::makeSound() - CORRECT!
```
The program decides at **runtime** which function to call based on the actual object type.

### Virtual Destructor

When deleting a derived class through a base class pointer, the destructor **must be virtual**:

```cpp
class Animal {
    virtual ~Animal();  // MUST be virtual
};

Animal* dog = new Dog();  // Dog allocates memory (Brain*)
delete dog;               // Without virtual: only ~Animal() runs = MEMORY LEAK!
                          // With virtual: ~Dog() runs first, then ~Animal() = CORRECT
```

### Pure Virtual Functions and Abstract Classes

A **pure virtual function** has no implementation in the base class:

```cpp
virtual void makeSound() const = 0;  // "= 0" makes it pure virtual
```

A class with at least one pure virtual function is **abstract** and cannot be instantiated:

```cpp
Animal a;              // ERROR: cannot instantiate abstract class
Animal* a = new Animal();  // ERROR
```

---

## Exercise Breakdown

### Exercise 00: Polymorphism

**Goal:** Learn how `virtual` enables polymorphism.

**Classes:**
| Class | Description |
|-------|-------------|
| `Animal` | Base class with `virtual makeSound()` and `virtual ~Animal()` |
| `Dog` | Inherits Animal, `makeSound()` prints "woof" |
| `Cat` | Inherits Animal, `makeSound()` prints "Meow" |
| `WrongAnimal` | Base class WITHOUT virtual (demonstrates wrong behavior) |
| `WrongCat` | Inherits WrongAnimal |

**Key Code in Animal.hpp:**
```cpp
virtual ~Animal(void);           // Virtual destructor
virtual void makeSound(void) const;  // Virtual for polymorphism
```

**Why WrongAnimal/WrongCat exist:**
They demonstrate what happens when you forget `virtual`:
- `WrongAnimal::makeSound()` is NOT virtual
- Calling `makeSound()` through `WrongAnimal*` pointer ALWAYS calls `WrongAnimal::makeSound()`
- Even if the actual object is a `WrongCat`

**main.cpp Tests Explained:**

| Test | What it demonstrates |
|------|---------------------|
| TEST 1 | Subject's given test - `Cat*` and `Dog*` stored as `Animal*` call their own `makeSound()` |
| TEST 2 | `WrongCat` through `WrongAnimal*` calls `WrongAnimal::makeSound()` (polymorphism fails) |
| TEST 3 | Direct call on object vs through pointer - shows the difference |
| TEST 4-5 | Orthodox Canonical Form - copy constructor and assignment operator work |
| TEST 6 | Destructor order - derived destructor runs before base destructor |

---

### Exercise 01: Brain and Deep Copy

**Goal:** Learn about memory management with inheritance and deep copying.

**New additions:**
| Addition | Purpose |
|----------|---------|
| `Brain` class | Contains `std::string ideas[100]` - dynamically allocated by Dog/Cat |
| `Brain* brain` in Dog/Cat | Private pointer to Brain, allocated with `new` |

**Key Changes from ex00:**

1. **Dog and Cat now have a Brain pointer:**
```cpp
class Dog : public Animal {
private:
    Brain* brain;  // Allocated in constructor, deleted in destructor
};
```

2. **Constructor allocates Brain:**
```cpp
Dog::Dog() : Animal("Dog"), brain(new Brain()) { }
```

3. **Destructor deletes Brain:**
```cpp
Dog::~Dog() {
    delete brain;  // Without virtual destructor in Animal, this NEVER runs!
}
```

4. **Deep copy in copy constructor:**
```cpp
Dog::Dog(const Dog& other) : Animal(other), brain(new Brain(*other.brain)) { }
//                                          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//                                          Creates NEW Brain with copied content
```

**Why Deep Copy Matters:**

**Shallow copy (BAD):**
```cpp
Dog::Dog(const Dog& other) : brain(other.brain) { }  // Both point to SAME Brain!
// When one Dog is destroyed, the other has a dangling pointer = CRASH
```

**Deep copy (GOOD):**
```cpp
Dog::Dog(const Dog& other) : brain(new Brain(*other.brain)) { }
// Each Dog has its OWN Brain = Safe
```

**main.cpp Tests Explained:**

| Test | What it demonstrates |
|------|---------------------|
| TEST 1 | Deleting Dog/Cat through `Animal*` - Brain destructor must run (no leak) |
| TEST 2 | Array of 10 Animals (5 Dogs, 5 Cats) - polymorphic calls and proper deletion |
| TEST 3 | Cat deep copy - Brain addresses are DIFFERENT after copy |
| TEST 4 | Dog deep copy - same verification |
| TEST 5 | Assignment operator deep copy - modifying copy doesn't affect original |

---

### Exercise 02: Abstract Class

**Goal:** Learn how to make a class uninstantiable using pure virtual functions.

**The Change:**
```cpp
// ex01:
virtual void makeSound(void) const;      // Can create Animal objects

// ex02:
virtual void makeSound(void) const = 0;  // "= 0" makes Animal ABSTRACT
```

**Why Make Animal Abstract?**

The subject says: *"Creating Animal objects doesn't make sense after all. It's true, they make no sound!"*

An `Animal` is a concept, not a real thing. You can have a Dog or a Cat, but what is just an "Animal"? What sound does it make?

By making `makeSound() = 0`:
1. You CANNOT create `Animal` objects
2. Any class inheriting from `Animal` MUST implement `makeSound()`
3. You can still use `Animal*` pointers to hold Dog/Cat objects

**main.cpp Tests Explained:**

| Test | What it demonstrates |
|------|---------------------|
| TEST 1 | Shows that `Animal a;` and `new Animal()` cause compile errors |
| TEST 2 | Dog and Cat work normally - polymorphism still functions |
| TEST 3 | Array of Animals - can still store Dog/Cat as `Animal*` |
| TEST 4 | Deep copy still works |
| TEST 5 | Summary comparing ex01 vs ex02 |

---

### Exercise 03: Interfaces

**Goal:** Learn about interfaces in C++ using pure abstract classes.

You're building a **simple RPG materia system**:
- **Characters** can equip up to 4 **Materias** (like magic spells)
- **Materias** can be cloned, equipped, unequipped, and used on targets
- **MateriaSource** is a factory that learns and creates materias

**Class Hierarchy:**

```
INTERFACES (pure virtual only, prefix "I")
├── ICharacter          → defines what a Character must do
└── IMateriaSource      → defines what a MateriaSource must do

ABSTRACT CLASS (prefix "A")
└── AMateria            → base for all materia types (Ice, Cure)
        ├── Ice         → concrete materia
        └── Cure        → concrete materia

CONCRETE CLASSES
├── Character           → implements ICharacter
└── MateriaSource       → implements IMateriaSource
```

**What is an Interface?**

An **interface** in C++ is a class with:
- **Only pure virtual functions** (all methods = 0)
- **No member variables** (just function declarations)
- **Virtual destructor**

```cpp
class ICharacter
{
public:
    virtual ~ICharacter() {}                                      // Virtual destructor
    virtual std::string const & getName() const = 0;              // Pure virtual
    virtual void equip(AMateria* m) = 0;                          // Pure virtual
    virtual void unequip(int idx) = 0;                            // Pure virtual
    virtual void use(int idx, ICharacter& target) = 0;            // Pure virtual
};
```

**Files You Need to Create:**

| File | Type |
|------|------|
| `ICharacter.hpp` | Interface (header only) |
| `IMateriaSource.hpp` | Interface (header only) |
| `AMateria.hpp` / `AMateria.cpp` | Abstract class |
| `Ice.hpp` / `Ice.cpp` | Concrete materia |
| `Cure.hpp` / `Cure.cpp` | Concrete materia |
| `Character.hpp` / `Character.cpp` | Implements ICharacter |
| `MateriaSource.hpp` / `MateriaSource.cpp` | Implements IMateriaSource |

**Class Details:**

**1. ICharacter (Interface)**
| Function | What it does |
|----------|--------------|
| `getName()` | Returns character's name |
| `equip(m)` | Put materia in first empty slot (0-3) |
| `unequip(idx)` | Remove materia from slot (DON'T delete it!) |
| `use(idx, target)` | Use materia at slot idx on target |

**2. IMateriaSource (Interface)**
```cpp
class IMateriaSource
{
public:
    virtual ~IMateriaSource() {}
    virtual void learnMateria(AMateria*) = 0;
    virtual AMateria* createMateria(std::string const & type) = 0;
};
```
| Function | What it does |
|----------|--------------|
| `learnMateria(m)` | Store a materia template (max 4) |
| `createMateria(type)` | Return a NEW clone of learned materia matching type |

**3. AMateria (Abstract Class)**
```cpp
class AMateria
{
protected:
    std::string type;                    // "ice" or "cure"

public:
    AMateria();
    AMateria(std::string const & type);
    AMateria(const AMateria& other);
    AMateria& operator=(const AMateria& other);
    virtual ~AMateria();

    std::string const & getType() const; // Returns the type (NOT virtual)
    
    virtual AMateria* clone() const = 0;                    // PURE VIRTUAL
    virtual void use(ICharacter& target);                   // VIRTUAL (has default)
};
```

| Member | Virtual? | Why? |
|--------|----------|------|
| `~AMateria()` | YES | Derived classes need proper destruction |
| `getType()` | NO | Same behavior for all materias |
| `clone()` | PURE VIRTUAL | Each materia must create its own copy |
| `use()` | VIRTUAL | Each materia has different effect, but can have default |

**4. Ice (Concrete Materia)**
```cpp
class Ice : public AMateria
{
public:
    Ice();
    Ice(const Ice& other);
    Ice& operator=(const Ice& other);
    ~Ice();

    AMateria* clone() const;             // Returns new Ice()
    void use(ICharacter& target);        // Prints: "* shoots an ice bolt at <name> *"
};
```

**5. Cure (Concrete Materia)**
```cpp
class Cure : public AMateria
{
public:
    Cure();
    Cure(const Cure& other);
    Cure& operator=(const Cure& other);
    ~Cure();

    AMateria* clone() const;             // Returns new Cure()
    void use(ICharacter& target);        // Prints: "* heals <name>'s wounds *"
};
```

**6. Character (Implements ICharacter)**
```cpp
class Character : public ICharacter
{
private:
    std::string name;
    AMateria*   inventory[4];            // 4 slots, initialize to NULL

public:
    Character();
    Character(std::string const & name);
    Character(const Character& other);   // DEEP COPY the inventory!
    Character& operator=(const Character& other);  // DEEP COPY!
    ~Character();                        // Delete all materias in inventory

    std::string const & getName() const;
    void equip(AMateria* m);
    void unequip(int idx);               // Don't delete! Just remove from slot
    void use(int idx, ICharacter& target);
};
```

**Memory Management Rules:**
| Action | Memory Responsibility |
|--------|----------------------|
| `equip()` | Character now "owns" the materia |
| `unequip()` | Materia must NOT be deleted (it's "dropped on floor") |
| `~Character()` | Delete all equipped materias |
| Copy/Assignment | DEEP COPY - new materias for new character |

**7. MateriaSource (Implements IMateriaSource)**
```cpp
class MateriaSource : public IMateriaSource
{
private:
    AMateria* templates[4];              // Can learn up to 4 materias

public:
    MateriaSource();
    MateriaSource(const MateriaSource& other);  // Deep copy templates
    MateriaSource& operator=(const MateriaSource& other);
    ~MateriaSource();                    // Delete all templates

    void learnMateria(AMateria* m);      // Store materia (or its clone)
    AMateria* createMateria(std::string const & type);  // Return clone of matching type
};
```

**Summary: Virtual vs Pure Virtual:**

| Class | Method | Type | Reason |
|-------|--------|------|--------|
| `ICharacter` | ALL methods | Pure Virtual (`= 0`) | Interface - no implementation |
| `IMateriaSource` | ALL methods | Pure Virtual (`= 0`) | Interface - no implementation |
| `AMateria` | `clone()` | Pure Virtual (`= 0`) | Each materia clones differently |
| `AMateria` | `use()` | Virtual | Can override, has default behavior |
| `AMateria` | `~AMateria()` | Virtual | Derived destructors must run |
| `Ice/Cure` | `clone()`, `use()` | Override | Implement the pure virtual |
| `Character` | All ICharacter methods | Override | Implement the interface |
| `MateriaSource` | All IMateriaSource methods | Override | Implement the interface |

**Expected main.cpp Test:**

```cpp
int main()
{
    IMateriaSource* src = new MateriaSource();
    src->learnMateria(new Ice());
    src->learnMateria(new Cure());
    
    ICharacter* me = new Character("me");
    
    AMateria* tmp;
    tmp = src->createMateria("ice");
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);
    
    ICharacter* bob = new Character("bob");
    
    me->use(0, *bob);  // "* shoots an ice bolt at bob *"
    me->use(1, *bob);  // "* heals bob's wounds *"
    
    delete bob;
    delete me;
    delete src;
    
    return 0;
}
```

**Tricky Parts to Watch Out For:**

| Issue | Solution |
|-------|----------|
| Unequipped materias leak | Store them somewhere (floor array) or accept the leak |
| Equipping to full inventory | Ignore the materia (don't equip) |
| Using empty slot | Do nothing |
| Invalid index | Do nothing |
| Deep copy in Character | Clone each materia in inventory |

---

## File Structure

```
CPP04/
├── ex00/                    # Polymorphism basics
│   ├── Animal.hpp/cpp       # Base class (virtual makeSound, virtual destructor)
│   ├── Dog.hpp/cpp          # Derived class
│   ├── Cat.hpp/cpp          # Derived class
│   ├── WrongAnimal.hpp/cpp  # Base WITHOUT virtual (for comparison)
│   ├── WrongCat.hpp/cpp     # Derived from WrongAnimal
│   ├── main.cpp             # Tests polymorphism
│   └── Makefile
│
├── ex01/                    # Deep copy with dynamic memory
│   ├── (all ex00 files)
│   ├── Brain.hpp/cpp        # NEW: 100-string array class
│   ├── Dog.hpp/cpp          # MODIFIED: has Brain* member
│   ├── Cat.hpp/cpp          # MODIFIED: has Brain* member
│   └── main.cpp             # Tests deep copy, memory leaks
│
├── ex02/                    # Abstract class
│   ├── (all ex01 files)
│   ├── Animal.hpp           # MODIFIED: makeSound() = 0 (pure virtual)
│   └── main.cpp             # Tests that Animal cannot be instantiated
│
└── ex03/                    # Interfaces
    ├── ICharacter.hpp       # Interface for characters
    ├── IMateriaSource.hpp   # Interface for materia factory
    ├── AMateria.hpp/cpp     # Abstract base for materias
    ├── Ice.hpp/cpp          # Concrete materia (ice bolt)
    ├── Cure.hpp/cpp         # Concrete materia (healing)
    ├── Character.hpp/cpp    # Implements ICharacter
    ├── MateriaSource.hpp/cpp# Implements IMateriaSource
    ├── main.cpp             # Tests materia system
    └── Makefile
```

---

## Summary Table

| Exercise | Key Concept | What's New |
|----------|-------------|------------|
| ex00 | Polymorphism | `virtual` keyword, `WrongAnimal` comparison |
| ex01 | Memory Management | `Brain` class, deep copy, virtual destructor importance |
| ex02 | Abstract Classes | Pure virtual `= 0`, uninstantiable base class |
| ex03 | Interfaces | `I` prefix classes, clone pattern, materia system |

---

## Common Mistakes to Avoid

1. **Forgetting `virtual` on destructor** → Memory leaks when deleting through base pointer
2. **Forgetting `virtual` on overridden methods** → Polymorphism doesn't work
3. **Shallow copy with pointers** → Double-free crashes, dangling pointers
4. **Not implementing pure virtual functions** → Derived class also becomes abstract
5. **Deleting materia in `unequip()`** → Subject says don't delete, it's "dropped on floor"
6. **Forgetting to clone in `createMateria()`** → Returning same pointer = shared ownership problems
