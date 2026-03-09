# CPP Module 07 - C++ Templates (Spoiler-Free)

## Templates in C++

Templates allow writing **generic code** that works with any data type. Instead of writing separate functions or classes for each type, you write one template and the compiler generates the specific versions.

---

### Function Templates

**Purpose:** Write a function once, use it with any type.

```cpp
template <typename T>
T add(T a, T b) {
    return a + b;
}

// Usage - compiler deduces T from arguments
int    x = add(1, 2);       // T = int
double y = add(1.5, 2.5);   // T = double
```

**Key points:**
- Defined in header files (compiler needs full definition at instantiation)
- The compiler generates a separate function for each type used
- Type is deduced from arguments or specified explicitly: `add<int>(1, 2)`

---

### Class Templates

**Purpose:** Write a class once, use it with any type.

```cpp
template <typename T>
class Container {
private:
    T _value;
public:
    Container(T val) : _value(val) {}
    T getValue() const { return _value; }
};

// Usage - must specify type explicitly
Container<int> intBox(42);
Container<std::string> strBox("hello");
```

**Key points:**
- Type must be specified explicitly: `Container<int>`
- Member functions defined outside the class need the template prefix
- Implementation typically goes in `.hpp` or `.tpp` files

---

### Defining Member Functions Outside the Class

```cpp
template <typename T>
class MyClass {
public:
    void doSomething(T param);
};

template <typename T>
void MyClass<T>::doSomething(T param) {
    // implementation
}
```

---

### Function Pointers as Template Parameters

Templates can accept function pointers, enabling generic algorithms:

```cpp
template <typename T>
void applyToEach(T* array, int size, void (*func)(T&)) {
    for (int i = 0; i < size; i++)
        func(array[i]);
}

void doubleValue(int& x) { x *= 2; }

int arr[] = {1, 2, 3};
applyToEach(arr, 3, doubleValue);
// arr is now {2, 4, 6}
```

---

### Template Specialization (Concept)

The compiler generates code for each type a template is used with. This is called **instantiation**. If a type doesn't support the operations used in the template (e.g., `<` operator), compilation will fail.

```cpp
template <typename T>
T bigger(T a, T b) {
    return (a > b) ? a : b;
}

// Works with int, double, std::string (all support >)
// Fails with types that don't define operator>
```

---

## Quick Reference

| Concept | Syntax |
|---------|--------|
| Function template | `template <typename T> T func(T a)` |
| Class template | `template <typename T> class MyClass {}` |
| Explicit instantiation | `func<int>(42)` |
| Type deduction | `func(42)` — compiler deduces `T = int` |

---

## Exercise Requirements

### Exercise 00
- Implement three function templates: `swap`, `min`, `max`
- They must work with any type that supports comparison operators
- If values are equal, `min` and `max` return the second one
- Templates must be defined in the header file

### Exercise 01
- Implement a function template `iter`
- Takes an array address, its length, and a function to apply
- The function is called on every element of the array
- Must work with any type of array
- The third parameter can be an instantiated function template
- Must support both const and non-const element references

### Exercise 02
- Develop a class template `Array` with elements of type `T`
- Default construction creates an empty array
- Construction with `unsigned int n` creates an array of `n` default-initialized elements
- Copy construction and assignment must create deep copies
- Must use `operator new[]` for allocation
- Access elements via `operator[]`, throw `std::exception` on out-of-bounds
- Provide a `size()` member function

---

## Things to Consider

1. **Exercise 00:**
   - Why must templates be defined in header files?
   - What happens when both values are equal?
   - Why use `::swap` instead of `swap`?

2. **Exercise 01:**
   - How do you handle both const and non-const arrays?
   - Can the third parameter itself be a template function?
   - What type should the length parameter be?

3. **Exercise 02:**
   - How does `new int()` differ from `new int`?
   - How do you ensure deep copy behavior?
   - What happens if you access index `n` in an array of size `n`?
   - Why is preventive allocation forbidden?
