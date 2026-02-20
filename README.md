# CPP_piscine
A collection of projects from 42 schools, where you learn about C++ from the ground up.

---

## CPP03 - Inheritance

### Exercise 00: ClapTrap (The Foundation)

A basic robot class with:

```
ClapTrap
├── Private Attributes:
│   ├── Name (string)
│   ├── Hit_points (10) - health
│   ├── Energy_points (10) - fuel for actions
│   └── Attack_damage (0) - damage dealt
│
├── Constructors/Destructor:
│   ├── Default constructor
│   ├── String constructor (takes name)
│   ├── Copy constructor
│   └── Destructor
│
└── Member Functions:
    ├── Attack() - costs 1 energy
    ├── TakeDamage() - reduces HP
    ├── beRepaired() - costs 1 energy, gains HP
    └── Getters/Setters
```

**Key Logic:**
- Can't act with 0 HP or 0 Energy
- Attack and repair consume energy

---

### Exercise 01: ScavTrap (Inheritance Introduced)

#### What Changed in ClapTrap?

Attributes changed from `private` to `protected`:

```cpp
class ClapTrap
{
protected:  // <-- Changed from private!
    std::string Name;
    int Hit_points;
    int Energy_points;
    int Attack_damage;
```

**Why?** 
- `private`: Only ClapTrap can access
- `protected`: ClapTrap AND its children (ScavTrap) can access

#### What's New in ScavTrap?

```cpp
class ScavTrap : public ClapTrap  // <-- Inherits from ClapTrap
{
public:
    // Own constructors (different messages)
    ScavTrap(void);
    ScavTrap(const std::string& Name);
    
    // Overridden function (different behavior)
    void Attack(const std::string& Target);
    
    // New special ability
    void GuardGate(void);
};
```

**Different default values:**
| Attribute | ClapTrap | ScavTrap |
|-----------|----------|----------|
| Hit points | 10 | **100** |
| Energy points | 10 | **50** |
| Attack damage | 0 | **20** |

**Construction Chain:**
```
Creating ScavTrap "Bob":
1. ClapTrap constructor runs FIRST
2. ScavTrap constructor runs SECOND

Destroying ScavTrap "Bob":
1. ScavTrap destructor runs FIRST
2. ClapTrap destructor runs SECOND
```

---

### Exercise 02: FragTrap (Another Child)

Another class inheriting from ClapTrap, similar to ScavTrap:

```cpp
class FragTrap : public ClapTrap
{
public:
    FragTrap(void);
    FragTrap(const std::string& Name);
    
    // Different special ability
    void highFivesGuys(void);
};
```

**Different default values:**
| Attribute | ClapTrap | ScavTrap | FragTrap |
|-----------|----------|----------|----------|
| Hit points | 10 | 100 | **100** |
| Energy points | 10 | 50 | **100** |
| Attack damage | 0 | 20 | **30** |

**Class Hierarchy So Far:**
```
        ClapTrap
        /      \
   ScavTrap   FragTrap
```

---

### Exercise 03: DiamondTrap (The Diamond Problem)

#### The Problem

DiamondTrap inherits from BOTH ScavTrap AND FragTrap:

```
        ClapTrap
        /      \
   ScavTrap   FragTrap
        \      /
       DiamondTrap
```

**Without virtual inheritance**, DiamondTrap would have TWO ClapTrap instances inside it! This causes:
- Ambiguity: Which `Name` to use?
- Wasted memory
- Undefined behavior

#### The Solution: Virtual Inheritance

Modified ScavTrap and FragTrap:

```cpp
class ScavTrap : virtual public ClapTrap  // <-- Added 'virtual'
{
    // ...
};

class FragTrap : virtual public ClapTrap  // <-- Added 'virtual'
{
    // ...
};
```

**What `virtual` does:**
- Ensures only ONE ClapTrap exists in DiamondTrap
- DiamondTrap directly initializes ClapTrap (not through parents)

#### New Helper Functions Added

Static functions to get default values:

```cpp
class ScavTrap : virtual public ClapTrap
{
public:
    static int GetDefaultEnergypoints(void);  // Returns 50
};

class FragTrap : virtual public ClapTrap
{
public:
    static int GetDefaultHitpoints(void);     // Returns 100
    static int GetDefaultAttackdamage(void);  // Returns 30
};
```

**Why?** DiamondTrap needs to pick specific values from each parent:

| Attribute | Source | Value |
|-----------|--------|-------|
| Hit points | FragTrap | 100 |
| Energy points | ScavTrap | 50 |
| Attack damage | FragTrap | 30 |
| attack() | ScavTrap | - |

#### DiamondTrap's Own Name

```cpp
class DiamondTrap : public ScavTrap, public FragTrap
{
private:
    std::string Name;  // <-- Same variable name as ClapTrap::Name
    
public:
    void whoAmI();  // Prints both names
};
```

**The Trick:**
- DiamondTrap has its OWN `Name`
- ClapTrap also has `Name`
- In constructor: `ClapTrap::Name = Name + "_clap_name"`

```cpp
DiamondTrap::DiamondTrap(const std::string& Name) : 
    ClapTrap(Name + "_clap_name"),  // ClapTrap gets modified name
    ScavTrap(Name),
    FragTrap(Name),
    Name(Name)                       // DiamondTrap keeps original
{
    // Set mixed attributes
    this->Hit_points = FragTrap::GetDefaultHitpoints();      // 100
    this->Energy_points = ScavTrap::GetDefaultEnergypoints(); // 50
    this->Attack_damage = FragTrap::GetDefaultAttackdamage(); // 30
}
```

---

### Summary Diagram

```
Exercise 00:  ClapTrap (standalone class)
                 │
Exercise 01:     │──── ScavTrap (inherits, protected attrs)
                 │
Exercise 02:     │──── FragTrap (another child)
                 │
Exercise 03:     └──── DiamondTrap (multiple inheritance)
                       - virtual inheritance to solve diamond
                       - mixed attributes from both parents
                       - two Name variables (own + ClapTrap's)
```
