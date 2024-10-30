# Flex Array

The Flex Array data structure offers an alternative to the basic C/C++ array, which requires a fixed size upon creation. Unlike standard arrays, the Flex Array is dynamically resizable, making it more adaptable for various data-handling needs. This was an assignment completed for a module in the final year of my bachelor's degree.

## Data Structure Overview

The Flex Array uses a dynamically-allocated internal array to store elements, allowing it to manage additional storage space flexibly on both ends of the element block (known as "headroom" and "tailroom"). This design ensures efficient insertions and deletions at both ends of the array.

- **Capacity**: The total size of the internal array.
- **Size**: The actual number of elements currently stored.
- **Headroom & Tailroom**: Empty spaces allocated before or after the stored elements for efficient expansion and contraction.

Elements are stored contiguously within the array, with no empty space between them. For example, a Flex Array containing `[31, 41, 59, 26, 53]` might look like `[X, X, X, 31, 41, 59, 26, 53, X]`, where `X` denotes empty space. Here, `size` is 5, `capacity` is 9, `headroom` is 3, and `tailroom` is 1.

## Supported Operations

### Basic Class Functions

- **`FlexArray()`**: Default constructor initializing the FlexArray with size 0 and a default capacity (`INITIALCAP = 5`).
- **`FlexArray(const int* arr, int size)`**: Parameterized constructor that initializes the FlexArray with elements from an existing integer array.
- **`~FlexArray()`**: Destructor that releases allocated memory.
- **`FlexArray(const FlexArray& other)`**: Copy constructor to duplicate an existing FlexArray object.
- **`FlexArray& operator=(const FlexArray& other)`**: Copy assignment operator to assign one FlexArray object to another.

### Printing & Size Information

- **`string print()`**: Returns a string listing all elements in sequence.
- **`string printAll()`**: Returns a string listing all elements in sequence, including empty spaces.
- **`int getSize()`**: Retrieves the number of stored elements.
- **`int getCapacity()`**: Retrieves the total capacity of the internal array.

### Getters & Setters

- **`int get(int i)`**: Returns the value at index `i` in the FlexArray.
- **`bool set(int i, int v)`**: Sets the value `v` at index `i`, replacing the existing value. Returns `true` if successful, or `false` if `i` is out of bounds.

### Structural Modifiers

- **`void push_back(int v)`**: Adds the integer `v` after the last element.
- **`bool pop_back()`**: Removes the last element.
- **`void push_front(int v)`**: Inserts the integer `v` at the start, shifting other elements as needed.
- **`bool pop_front()`**: Removes the first element.
- **`bool insert(int i, int v)`**: Inserts the integer `v` at index `i`.
- **`bool erase(int i)`**: Removes the element at index `i`, shifting subsequent elements leftward.

This Flex Array structure combines the simplicity of arrays with dynamic resizing, providing efficient storage management and versatile element manipulation options.
