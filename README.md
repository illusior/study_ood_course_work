# OOD's course work

### **Build:**

1. `CMake` (tested for `MSVC`and `Ninja`)
```
cmake -S . -B build -G "Your Generator"
```
2. Go to `.\build`
3. Build with `make` or `Visual Studio`

### **Tasks:**

#### **Main:**
Develop an application using the MVC, MVP or MVVM pattern an application
that allows you to create a composition of geometric shapes:
rectangles, triangles, ellipses

#### **Additional:**

- History of actions: cancellation and repetition of operations <br>
    Using **Command Pattern** <br>
    *Not implemented*
- Saving a document in a convenient format _(`.json`, `.xml` ...)_ <br>
    Using Visitor? <br>
    *Not implemented*
- Inserting bitmap images <br>
    *Not implemented*
- Code coverage by tests <br>
    *Not implemented*

## **Stack:**

- [glfw](https://github.com/glfw/glfw)
- [imgui](https://github.com/ocornut/imgui)
- opengl
- [catch2](https://github.com/catchorg/Catch2)
- [boost](https://github.com/boostorg/boost) (_uuid_)
- my own fork of [ISpringTech's FastSignal](https://github.com/beta442/ispring_fast_signals)

## **Patterns:**

- Command
- Observer
- Composite
- Visitor
