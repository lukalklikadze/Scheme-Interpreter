# 🌀 Scheme Interpreter in C++

A simple Scheme interpreter implemented from scratch in modern C++. This project supports a core set of Lisp-like features including evaluation, arithmetic, list processing, lambdas, and control flow.

---

## ✨ Features

✅ Core expression evaluation: `eval`, `apply`  
✅ Arithmetic operations: `+`, `-`, `*`, `/`  
✅ Comparison operators: `=`, `<`, `>`, `<=`, `>=`  
✅ Logical operations: `and`, `or`  
✅ List processing: `car`, `cdr`, `cons`, `append`, `list`, `length`, `null?`  
✅ Functional programming: `define`, `lambda`, `map`  
✅ Conditional execution: `if`

---

## 🛠️ Implementation Highlights

- Fully written in **C++** using STL containers and `std::function` for functional dispatch  
- Recursive evaluation of nested S-expressions  
- First-class support for **closures** and **user-defined lambdas**  
- Custom `Value` class to store different Scheme types (symbols, numbers, lists, functions)  
- Modular structure for easy extensibility

---

## 📂 Project Structure

```
scheme-interpreter/
├── main.cpp             # Entry point
├── interpreter.h/.cpp   # Core interpreter logic
├── parser.h/.cpp        # S-expression parser
├── value.h/.cpp         # Data representation
├── env.h/.cpp           # Environment and scope handling
├── README.md            # Project documentation
├── .gitignore           # Ignore build and VS files
```

---

## 🧪 Example Usage

```scheme
(define square (lambda (x) (* x x)))
(map square (list 1 2 3 4))
; Output: (1 4 9 16)
```

---

## 🧱 Build Instructions

### Prerequisites

- A C++17 compatible compiler (e.g., GCC or MSVC)
- CMake (optional, if you're using a CMake setup)

### Compile and Run (GCC / Clang)

```bash
g++ -std=c++17 -o scheme main.cpp
./scheme
```

> If you use multiple `.cpp` files, include them all in the compile command.

---

## 🙋‍♂️ Author

Created by **Luka Liklikadze**
