//===================================================
//Name: Data Structures Assignment 2
//Author: Jackson Mukeshimana
//Version: 1.0
//Date Created: 04-11-2023
//Date Modified: 16-11-2023
//Description: A C++ program that Create a 
//               Virtual File System
//====================================================

#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <iomanip>
#include<sstream>
#include <cstddef>
#include <stdexcept>
#include<stdlib.h>

// Forward declaration of Vector class template
// A template class for a simplified implementation of a vector (dynamic array)
template <typename T>
class Vector {
private:
    T *data;                // Pointer to dynamically allocated array for storing elements
    size_t v_size;          // Number of elements currently in the vector
    size_t v_capacity;      // Allocated space for the vector, can be larger than v_size

public:

    // Returns an iterator pointing to the first element
    // Returns an iterator pointing to the past-the-end element

     // Iterator type
    using iterator = T*;

    // Method to get an iterator to a specific index
    iterator getIterator(size_t index) {
        if (index < v_size) {
            return &data[index];
        } else {
            return end(); // or handle this case as per your error handling strategy
        }
    }


    // Constructor: initializes a vector with a given capacity (default 0)
    explicit Vector(size_t cap = 0);     
    // Destructor: responsible for freeing the allocated memory
    ~Vector(); 

    // Returns the number of elements in the vector
    size_t size() const;                 
    // Returns the current capacity of the vector
    size_t capacity() const;             
    // Checks if the vector is empty (i.e., size is zero)
    bool empty() const;

    // Element access:
    const T& front() const;              // Access the first element
    const T& back() const;               // Access the last element
    T& operator[](size_t index);         // Access specified element without bounds checking
    T& at(size_t index);                 // Access specified element with bounds checking

    // Modifiers:
    void push_back(const T& element);    // Add element to the end of the vector
    void insert(size_t index, const T& element); // Insert element at specified index
    void erase(size_t index);            // Erase element at specified index
    void shrink_to_fit();                // Reduce capacity to fit the size exactly
    void display() const;                // Prints all elements for debugging

    // Disable copy construction and assignment for simplicity
    Vector(const Vector&) = delete;
    Vector& operator=(const Vector&) = delete;

    // Disable move construction and assignment for simplicity
    Vector(Vector&&) = delete;
    Vector& operator=(Vector&&) = delete;
    
    void clear() { v_size = 0; }
    const T* begin() const { return data; }
    const T* end() const { return data + v_size; }
   
};

// Constructor definition
template <typename T>
Vector<T>::Vector(size_t cap) : v_size(0), v_capacity(cap), data(new T[cap]) {
    // Ensuring there's always a non-zero capacity to avoid divisions by zero during resizing
    if (cap == 0) {
        v_capacity = 1;
    }
}

// Destructor definition
template <typename T>
Vector<T>::~Vector() {
    // Freeing the allocated memory
    delete[] data;
}

// Function to add an element at the end of the vector
template <typename T>
void Vector<T>::push_back(const T& element) {
    // Check if there is enough room for a new element
    if (v_size >= v_capacity) {
        // Not enough space: we need to allocate a larger array
        v_capacity *= 2; // Doubling the capacity
        T* new_data = new T[v_capacity];
        
        // Copying existing elements to the new array
        for (size_t i = 0; i < v_size; ++i) {
            new_data[i] = data[i];
        }

        // Deleting old array and updating the pointer
        delete[] data;
        data = new_data;
    }
    
    // Inserting the new element and incrementing size
    data[v_size++] = element;
}

// Function to insert an element at the specified index
template <typename T>
void Vector<T>::insert(size_t index, const T& element) {
    // Check for valid index
    if (index > v_size) {
        throw std::out_of_range("Index out of range");
    }

    // Check if the current capacity can accommodate the new element
    if (v_size >= v_capacity) {
        // Not enough space: we need to allocate a larger array
        v_capacity *= 2; // Doubling the capacity
        T* new_data = new T[v_capacity];

        // Copying elements up to the index
        for (size_t i = 0; i < index; ++i) {
            new_data[i] = data[i];
        }

        // Shifting the subsequent elements to make space for the new element
        for (size_t i = index; i < v_size; ++i) {
            new_data[i + 1] = data[i];
        }

        // Releasing old array and updating the pointer
        delete[] data;
        data = new_data;
    } else {
        // Enough space: just shift elements to make space
        for (size_t i = v_size; i > index; --i) {
            data[i] = data[i - 1];
        }
    }

    // Insert the new element and increment size
    data[index] = element;
    ++v_size;
}

// Function to remove an element at the specified index
template <typename T>
void Vector<T>::erase(size_t index) {
    // Check for valid index
    if (index >= v_size) {
        throw std::out_of_range("Index out of range");
    }

    // Shift elements to fill the gap left by the removed element
    for (size_t i = index; i < v_size - 1; ++i) {
        data[i] = data[i + 1];
    }

    // Decrease size after removing the element
    --v_size;
}

// Function to access an element without bounds checking
template <typename T>
T& Vector<T>::operator[](size_t index) {
    return data[index];
}

// Function to access an element with bounds checking
template <typename T>
T& Vector<T>::at(size_t index) {
    if (index >= v_size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

// Function to get the first element with bounds checking
template <typename T>
const T& Vector<T>::front() const {
    if (empty()) {
        throw std::out_of_range("Vector is empty");
    }
    return data[0];
}

// Function to get the last element with bounds checking
template <typename T>
const T& Vector<T>::back() const {
    if (empty()) {
        throw std::out_of_range("Vector is empty");
    }
    return data[v_size - 1];
}

// Function to get the size of the vector
template <typename T>
size_t Vector<T>::size() const {
    return v_size;
}

// Function to get the capacity of the vector
template <typename T>
size_t Vector<T>::capacity() const {
    return v_capacity;
}

// Function to check if the vector is empty
template <typename T>
bool Vector<T>::empty() const {
    return v_size == 0;
}

// Function to reduce the vector's capacity to fit its size
template <typename T>
void Vector<T>::shrink_to_fit() {
    if (v_capacity > v_size) {
        T* new_data = new T[v_size];
        for (size_t i = 0; i < v_size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        v_capacity = v_size;
    }
}

// Function to print all elements of the vector
template <typename T>
void Vector<T>::display() const {
    for (size_t i = 0; i < v_size; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}


// Definition of Stack class template
template <typename T>
class Stack {
private:
    Vector<T> elements; // Using Vector to store stack elements

public:
    // Check if the stack is empty
    bool isEmpty() const {
        return elements.size() == 0;
    }

    // Push an element onto the stack
    void push(const T& element) {
        elements.push_back(element);
    }

    // Pop an element from the stack
    T pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack Underflow");
        }
        T topElement = elements.back();
        elements.erase(elements.size() - 1); // Removing the last element
        return topElement;
    }

    // Get the top element of the stack
    T top() const {
        if (isEmpty()) {
            throw std::out_of_range("Stack Underflow");
        }
        return elements.back();
    }
};


template <typename T>
class Queue {
    T* begin() { return nullptr; } // Dummy implementation
    T* end() { return nullptr; } // Dummy implementation
private:
    T *array;              // Dynamic array for storing queue elements
    int capacity;          // Maximum capacity of the queue
    int size;              // Size of the queue
    int front;             // Index of the front element in the queue
    int rear;              // Index where a new element will be added

public:
    explicit Queue(int capacity = 10); // Constructor with default capacity value
    // Method to get the size of the queue

     size_t getSize() const {
        // return the size of the queue
        return size;
    }
    
    ~Queue();                          // Destructor to free allocated memory

    void enqueue(T element);  // Add an element to the queue
    T dequeue();              // Remove and return the front element from the queue
    bool isEmpty() const;     // Check if the queue is empty
    bool isFull() const;      // Check if the queue is full
    T front_element() const;  // Get the front element of the queue

    // Display function should not be a friend, it can be a member or non-member function
    void display() const; // Print all elements in the queue for debugging
};

//================================================


// Implementation details follow

// Queue constructor implementation
template<typename T>
Queue<T>::Queue(int cap) : capacity(cap), size(0), front(0), rear(-1) {
    array = new T[capacity]; // Allocating memory for the queue's internal array
}

// Queue destructor implementation
template<typename T>
Queue<T>::~Queue() {
    delete[] array; // Freeing the dynamically allocated memory for the internal array
}

// Enqueue implementation - adds an element to the queue
template<typename T>
void Queue<T>::enqueue(T element) {
    if (isFull()) {
        throw std::runtime_error("Queue Full"); // Throwing an exception if the queue is full
    }
    rear = (rear + 1) % capacity; // Calculating the new rear position in a circular manner
    array[rear] = element; // Adding the element to the queue
    size++; // Incrementing the size of the queue
}

// Dequeue implementation - removes and returns the front element of the queue
template<typename T>
T Queue<T>::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("Queue Empty"); // Throwing an exception if the queue is empty
    }
    T element = array[front]; // Storing the front element to return
    front = (front + 1) % capacity; // Updating the front index in a circular manner
    size--; // Decrementing the size of the queue
    return element; // Returning the front element
}

// Implementation to check if the queue is empty
template<typename T>
bool Queue<T>::isEmpty() const {
    return size == 0; // Queue is empty if size is 0
}

// Implementation to check if the queue is full
template<typename T>
bool Queue<T>::isFull() const {
    return size == capacity; // Queue is full if size equals capacity
}

// Implementation to get the front element of the queue
template<typename T>
T Queue<T>::front_element() const {
    if (isEmpty()) {
        throw std::runtime_error("Queue Empty"); // Throwing an exception if the queue is empty
    }
    return array[front]; // Returning the front element
}

// Display function to print all elements of the queue
template<typename T>
void Queue<T>::display() const {
    for (int i = 0; i < size; ++i) {
        std::cout << array[(front + i) % capacity] << " "; // Printing elements in a circular manner
    }
    std::cout << std::endl;
}

class Inode {
public:
    enum class Type { File, Directory };
    Type type;
    std::string name;
    size_t size;  // Size of the file, or total size of files in the directory
    std::string date;  // For simplicity, the date is a string
    Inode* parent;
    Vector<Inode*> children;  // Only used if the inode is a directory

    // Constructor
    Inode(std::string name, Type type, size_t size = 0, std::string date = "", Inode* parent = nullptr)
        : name(name), type(type), size(size), date(date), parent(parent) {}

    // Add a child inode (only if it's a directory)
    void addChild(Inode* child) {
        if (this->type == Type::Directory) {
            children.push_back(child);
            child->parent = this;
            // Update the size of the directory inode
            this->size += child->size;
        }
    }

    // Method to get the full path of the inode
    std::string getFullPath() const {
        std::string path = "";
        const Inode* current = this;
        while (current) {
            if (!current->name.empty()) {
                path = "/" + current->name + path;
            }
            current = current->parent;
        }
        return path.empty() ? "/" : path;
    }

    // Destructor
    ~Inode() {
        for (size_t i = 0; i < children.size(); ++i) {
            delete children[i];
        }
    }

    // Disable copy construction and assignment for simplicity
    Inode(const Inode&) = delete;
    Inode& operator=(const Inode&) = delete;

    // Disable move construction and assignment for simplicity
    Inode(Inode&&) = delete;
    Inode& operator=(Inode&&) = delete;
};


// Definition of FileSystem class
class FileSystem {
private:
    Inode* rootInode;      // Root of the file system
    Inode* currentInode;   // Pointer to the current inode (directory)
    Inode* previousInode;  // Previous working directory for 'cd -'
    static const int MAXBIN = 10;
    Queue<Inode*> removalQueue; // Queue to store removed inodes



    std::string getCurrentDate() {
    // Get the current time as a time_point
    auto now = std::chrono::system_clock::now();

    // Convert it to a time_t object
    auto now_c = std::chrono::system_clock::to_time_t(now);

    // Convert time_t to tm struct
    std::tm now_tm = *std::localtime(&now_c);

    // Use stringstream for formatting
    std::stringstream ss;
    ss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");

    return ss.str();
}

 // Helper method to calculate the total size of a directory
    size_t calculateFolderSize(const Inode* node) const {
        if (!node || node->type == Inode::Type::File) {
            return node ? node->size : 0;
        }

        size_t totalSize = node->size; // Start with the directory's own size
        for (const auto& child : node->children) {
            totalSize += calculateFolderSize(child); // Recursively sum the sizes
        }
        return totalSize;
    }

    // This helper method constructs the full path of an inode
    // It starts from the given inode and traverses up to the root, appending each directory name to the path
    std::string constructPath(const Inode* inode) const {
        // If the inode is the root, its path is simply "/"
        if (inode->name == "/") {
            return "/";
        }

        // Initialize an empty string to hold the path
        std::string path;
        // Traverse up the tree until we reach the root
        while (inode != nullptr && inode->name != "/") {
            // Prepend the current directory name to the path
            path = "/" + inode->name + path;
            // Move up to the parent directory
            inode = inode->parent;
        }
        // Return the constructed path
        return path;
    }

     // This helper function navigates to a specified path and returns the inode at that path
     Inode* navigateToPath(const std::string& path) const {
         // If the path is empty or root, return the rootInode
         if (path.empty() || path == "/") {
             return rootInode;
         }

         // Start from the root if the path is absolute, else start from the current directory
         Inode* targetInode = (path[0] == '/') ? rootInode : currentInode;
         std::istringstream iss(path);
         std::string token;

         // Split the path by '/' and navigate through each directory
         while (std::getline(iss, token, '/')) {
             // Skip empty tokens and '.'
             if (token.empty() || token == ".") continue; 
             // If token is '..', move up to the parent directory but not above root
             if (token == "..") {
                 if (targetInode != rootInode) {
                     targetInode = targetInode->parent;
                 }
                 continue;
             }

             // Search for the directory in the current inode's children
             bool found = false;
             for (auto& child : targetInode->children) {
                 // If the directory is found, move to it
                 if (child->name == token && child->type == Inode::Type::Directory) {
                     targetInode = child;
                     found = true;
                     break;
                 }
             }

             // If the directory is not found in the path, return nullptr
             if (!found) {
                 return nullptr; 
             }
         }

         // Return the target inode
         return targetInode;
     }

public:
    // Constructor
    FileSystem(): removalQueue(MAXBIN) {
        // Initialize the root inode as the starting point
        rootInode = new Inode("/", Inode::Type::Directory);
        currentInode = rootInode;  // Set currentInode to the root
        previousInode = nullptr;   // Initialize previousInode

        // Create test inodes (as children of the root) for the ls Method
        Inode* file1 = new Inode("file1.txt", Inode::Type::File, 200, "2023-03-01");
        Inode* file2 = new Inode("file2.txt", Inode::Type::File, 200, "2023-03-02");
        Inode* dir1 = new Inode("dir1", Inode::Type::Directory);

        rootInode->addChild(file1);
        rootInode->addChild(file2);
        rootInode->addChild(dir1);
    }

    // Destructor
    ~FileSystem() {
        // Free the memory allocated for the root inode, which in turn
        // should recursively delete all child inodes
        delete rootInode;
    }

    // Public interface to calculate the size of the current directory
    // Method to get the size of a specific folder or file by name
    size_t size(const std::string& name) const {
        // Check if the name matches any child of the current inode
        for (const auto& child : currentInode->children) {
            if (child->name == name) {
                // Found the child, return its size
                return calculateFolderSize(child);
            }
        }

        // If the name doesn't match any child, handle as an error or return 0
        std::cout << "Error: No file or folder named '" << name << "' found." << std::endl;
        return 0;
    }

    // help method - displays help information
    void help() const {
        std::cout << "\nWelcome to the Virtual File System (VFS)!\n";
        std::cout << "Here are the available commands you can use:\n\n";
        std::cout << "help: Displays this help menu.\n";
        std::cout << "pwd: Shows the path of the current inode.\n";
        std::cout << "ls: Lists the children of the current inode.\n";
        std::cout << "mkdir <foldername>: Creates a new folder under the current folder.\n";
        std::cout << "touch <filename> <size>: Creates a new file under the current inode location with the specified size.\n";
        std::cout << "cd <foldername/filename/../-/>: Changes the current inode. Use '..' for parent folder, '-' for previous directory, and '/' for root.\n";
        std::cout << "rm <foldername/filename>: Removes the specified folder or file and puts it in the bin.\n";
        std::cout << "size <foldername/filename>: Returns the total size of the folder or file.\n";
        std::cout << "showbin: Displays the oldest inode in the bin.\n";
        std::cout << "emptybin: Empties the bin.\n";
        std::cout << "exit: Stops the program.\n\n";

        std::cout << "Optional commands:\n";
        std::cout << "mv <filename> <foldername>: Moves a file from the current inode location to the specified folder path.\n";
        std::cout << "recover: Reinstates the oldest inode back from the bin to its original position in the tree.\n";
        std::cout << "\nPlease enter a command to continue...\n";
       
    }



    // pwd method - returns the current path as a string
    std::string pwd() {
        // Initialize a string to hold the full path
        std::string fullPath;
        // Start from the current inode
        Inode* node = currentInode;

        // If the current inode is the root, return "/"
        // This is a special case for the root directory
        if (node == rootInode) {
            return "/";
        }

        // Construct the path in reverse order, starting from the current inode and going up to the root
        // This is done by prepending the name of each inode to the path, separated by "/"
        while (node != rootInode && node != nullptr) {
            fullPath = "/" + node->name + fullPath;
            // Move up to the parent inode
            node = node->parent;
        }

        // Return the constructed path
        return fullPath;
    }
   
  
    // ls method - lists the contents of the current directory
    void ls() {
        // Check if the current inode is a directory
        if (currentInode->type != Inode::Type::Directory) {
            std::cout << "Error: Current inode is not a directory" << std::endl;
            return;
        }

        // Check if the directory is empty
        if (currentInode->children.empty()) {
            std::cout << "Directory is empty" << std::endl;
            return;
        }

        // Bubble sort children by size in descending order
        bool swapped;
        do {
            swapped = false;
            // Loop through each child
            for (size_t i = 0; i < currentInode->children.size() - 1; ++i) {
                // If the current child is smaller than the next one, swap them
                if (currentInode->children[i]->size < currentInode->children[i + 1]->size) {
                    std::swap(currentInode->children[i], currentInode->children[i + 1]);
                    swapped = true;
                }
            }
        } while (swapped); // Continue until no more swaps are needed

        // Print details of each child
        for (size_t i = 0; i < currentInode->children.size(); ++i) {
            Inode* child = currentInode->children[i];
            // Determine the type of the child (directory or file)
            std::string fileType = (child->type == Inode::Type::Directory) ? "dir" : "file";
            // Print the child's details
            std::cout << fileType << "\t" << child->name << "\t" << child->size << "\t" << child->date << std::endl;
        }
    }

     // Method to create a new directory
     void mkdir(const std::string& folderName) {
         // Loop through the children of the current inode to check if a directory with the same name already exists
         for (auto& child : currentInode->children) {
             // If a directory with the same name exists, print an error message and return
             if (child->name == folderName && child->type == Inode::Type::Directory) {
                 std::cout << "Error: Directory '" << folderName << "' already exists." << std::endl;
                 return;
             }
         }

         // If the current inode is not a directory, print an error message and return
         if (currentInode->type != Inode::Type::Directory) {
             std::cout << "Error: Cannot create directory here. Current location is not a directory." << std::endl;
             return;
         }

         // Create a new directory inode with the given name and a default size of 10
         Inode* newDir = new Inode(folderName, Inode::Type::Directory, 10); // Default size for a directory is 10
         // Add the new directory to the children of the current inode
         currentInode->addChild(newDir);
     }

    // Method to create a new file
    void touch(const std::string& filename, size_t size) {
        // Loop through the children of the current inode to check if a file or directory with the same name already exists
        for (auto& child : currentInode->children) {
            if (child->name == filename) {
                // If a file or directory with the same name exists, print an error message and return
                std::cout << "Error: A file or directory with the name '" << filename << "' already exists." << std::endl;
                return;
            }
        }

        // If the current inode is not a directory, print an error message and return
        if (currentInode->type != Inode::Type::Directory) {
            std::cout << "Error: Current inode is not a directory. Cannot create file here." << std::endl;
            return;
        }

        // Get the current date and time
        std::string currentDate = getCurrentDate(); // This function fetches the current date and time

        // Create a new file inode with the given name, size and current date
        Inode* newFile = new Inode(filename, Inode::Type::File, size, currentDate);
        // Add the new file to the children of the current inode
        currentInode->addChild(newFile);
    }



    // Method to change the current directory
    void cd(const std::string& path) {
        // If the path is empty or root ("/"), change to root directory
        if (path.empty() || path == "/") {
            previousInode = currentInode; // Save the current directory
            currentInode = rootInode; // Change to root directory
            return;
        }

        // If the path is "-", change to the previous directory
        if (path == "-") {
            if (previousInode) { // If there is a previous directory
                currentInode = previousInode; // Change to the previous directory
            }
            return;
        }

        // If the path is "..", change to the parent directory
        if (path == "..") {
            if (currentInode != rootInode) {  // Prevent moving above root
                previousInode = currentInode; // Save the current directory
                currentInode = currentInode->parent; // Change to parent directory
            }
            return;
        }

        // Handle absolute or relative path
        // If the path starts with "/", it's an absolute path, start from root
        // Otherwise, it's a relative path, start from the current directory
        Inode* targetInode = (path[0] == '/') ? rootInode : currentInode;
        std::istringstream iss(path);
        std::string token;

        // Split the path by "/"
        while (std::getline(iss, token, '/')) {
            // Skip empty tokens and "."
            if (token.empty() || token == ".") continue;

            // If the token is "..", move up to the parent directory, but not above root
            if (token == "..") {
                if (targetInode != rootInode) {
                    targetInode = targetInode->parent;
                }
                continue;
            }

            // Search for the directory in the current inode's children
            bool found = false;
            for (auto& child : targetInode->children) {
                if (child->name == token && child->type == Inode::Type::Directory) {
                    targetInode = child; // Found the directory, change to it
                    found = true;
                    break;
                }
            }

            // If the directory is not found, print an error message and return
            if (!found) {
                std::cout << "Directory not found: " << token << std::endl;
                return;
            }
        }

        // Change to the target directory
        previousInode = currentInode; // Save the current directory
        currentInode = targetInode; // Change to the target directory
    }

    // Method to remove a file or directory
    void rm(const std::string& name) {
        // Initialize index to -1
        size_t index = -1;
        // Loop through the children of the current inode
        for (size_t i = 0; i < currentInode->children.size(); ++i) {
            // If a child with the given name is found, save its index and break the loop
            if (currentInode->children[i]->name == name) {
                index = i;
                break;
            }
        }

        // If no child with the given name is found, print an error message and return
        if (index == -1) {
            std::cout << "Error: File or directory '" << name << "' not found." << std::endl;
            return;
        }

        // Get the inode to be removed
        Inode* toBeRemoved = currentInode->children[index];

        // If the removal queue is full, print an error message and return
        if (removalQueue.isFull()) {
            std::cout << "Error: Removal queue is full." << std::endl;
            // Optionally, delete toBeRemoved to prevent memory leak, if it won't be used elsewhere
            delete toBeRemoved;
            return;
        }

        // Add the inode to the removal queue
        removalQueue.enqueue(toBeRemoved);

        // Remove the inode from the children vector
        currentInode->children.erase(index);

        // Print a success message
        std::cout << "Removed '" << name << "'." << std::endl;
    }

    // This method displays the oldest inode in the bin
    void showbin() const {
        // Check if the removal queue is empty
        if (removalQueue.isEmpty()) {
            // If empty, print a message
            std::cout << "Bin is empty." << std::endl;
        } else {
            // If not empty, get the oldest inode
            Inode* oldest = removalQueue.front_element();
            // Print the name of the oldest inode
            std::cout << "Oldest inode in the bin: " << oldest->name << std::endl;
            // Print the path of the oldest inode
            std::cout << "Path: " << constructPath(oldest) << std::endl;
        }
    }


    // This method recovers the oldest inode from the bin
    void recover() {
        // Check if the removal queue is empty
        if (removalQueue.isEmpty()) {
            // If empty, print an error message and return
            std::cout << "Error: Bin is empty." << std::endl;
            return;
        }

        // Dequeue the oldest inode from the removal queue
        Inode* inodeToRecover = removalQueue.dequeue();
        // Get the full path of the inode to be recovered
        std::string originalPath = inodeToRecover->getFullPath();
        // Extract the parent path from the original path
        std::string parentPath = originalPath.substr(0, originalPath.find_last_of('/'));

        // Navigate to the parent inode
        Inode* parentInode = navigateToPath(parentPath);
        // Check if the parent inode exists and is a directory
        if (!parentInode || parentInode->type != Inode::Type::Directory) {
            // If not, print an error message, clean up the inode to be recovered, and return
            std::cout << "Error: Original path does not exist anymore." << std::endl;
            delete inodeToRecover;
            return;
        }

        // Add the inode to be recovered to the parent inode's children
        parentInode->addChild(inodeToRecover);
        // Print a success message
        std::cout << "Recovered '" << inodeToRecover->name << "' to its original location." << std::endl;
    }

    // Method to move a file to a different folder
    void mv(const std::string& filename, const std::string& foldername) {
        // Initialize pointers to the file and folder nodes
        Inode* fileNode = nullptr;
        Inode* folderNode = nullptr;

        // Loop through the children of the current inode to find the file and folder nodes
        for (auto& child : currentInode->children) {
            // If a child node matches the filename and is a file, assign it to fileNode
            if (child->name == filename && child->type == Inode::Type::File) {
                fileNode = child;
            } 
            // If a child node matches the foldername and is a directory, assign it to folderNode
            else if (child->name == foldername && child->type == Inode::Type::Directory) {
                folderNode = child;
            }
        }

        // Check if the file and folder nodes were found
        if (!fileNode) {
            // If the file node was not found, print an error message and return
            std::cout << "Error: File '" << filename << "' not found." << std::endl;
            return;
        }
        if (!folderNode) {
            // If the folder node was not found, print an error message and return
            std::cout << "Error: Folder '" << foldername << "' not found." << std::endl;
            return;
        }

        // Add the file node to the folder node's children
        folderNode->addChild(fileNode);

        // Loop through the current inode's children to find and remove the file node
        for (size_t i = 0; i < currentInode->children.size(); ++i) {
            // If a child node matches the file node, remove it from the current inode's children
            if (currentInode->children[i] == fileNode) {
                currentInode->children.erase(i); // Assuming your Vector class has an erase method that takes an index
                // Print a success message and return
                std::cout << "Successfully moved '" << filename << "' to '" << foldername << "'." << std::endl;
                return; // Exit the function after moving the file
            }
        }
    }



    // This method is used to empty the bin
    void emptybin() {
        // While loop will run until the removalQueue is not empty
        while (!removalQueue.isEmpty()) {
            // Dequeue the inode from the removalQueue and assign it to removedInode
            Inode* removedInode = removalQueue.dequeue();
            delete removedInode; // Memory allocated to the inode is freed here
        }
    }


    // exit method - handles exiting the program
    void exit() {
        std::cout << "Exiting the Virtual File System. Goodbye!\n";
    }

};

int main() {
    FileSystem vfs; // Create a FileSystem instance

    vfs.help(); // Display help information at the start of the program

    while (true) {
        std::string user_input;
        std::string command;
        std::cout << ">";
        std::getline(std::cin, user_input);

        std::stringstream sstr(user_input);
        sstr >> command;

        try {
            // If the command is 'help', call the help function
            if (command == "help")        vfs.help();
            // If the command is 'pwd', print the current path
            else if (command == "pwd")    std::cout << "Current path: " << vfs.pwd() << std::endl;
            // If the command is 'ls', list the files in the current directory
            else if (command == "ls")     vfs.ls();
            // If the command is 'mkdir', create a new directory
            else if (command == "mkdir")  {
                std::string folderName;
                sstr >> folderName;
                if (!folderName.empty()) {
                    vfs.mkdir(folderName);
                } else {
                    std::cout << "Usage: mkdir <foldername>" << std::endl;
                }
            }
            // If the command is 'touch', create a new file
            else if (command == "touch")  {
                std::string filename;
                size_t size;
                sstr >> filename >> size;
                vfs.touch(filename, size);
            }
            // If the command is 'cd', change the current directory
            else if (command == "cd")     {
                std::string path;
                sstr >> path;
                vfs.cd(path);
            }
            // If the command is 'rm', remove a file or directory
            else if (command == "rm") {
                std::string name;
                sstr >> name;
                vfs.rm(name);
            }
            // If the command is 'size', print the size of a file or directory
            else if (command == "size") {
                std::string name;
                sstr >> name;
                std::cout << "Size of '" << name << "': " << vfs.size(name) << " bytes\n";
            }
            // If the command is 'showbin', show the oldest inode in the bin
            else if (command == "showbin") {
            vfs.showbin();
        }
            // If the command is 'recover', recover the oldest inode from the bin
            else if (command == "recover") {
                vfs.recover();
            }
            // If the command is 'mv', move a file to a different directory
            else if (command == "mv") {
            std::string filename, foldername;
            sstr >> filename >> foldername;
            vfs.mv(filename, foldername);
            } 
            // If the command is 'emptybin', empty the bin
            else if (command == "emptybin") {
                vfs.emptybin();
                std::cout << "Bin emptied successfully." << std::endl;
            }
            // If the command is 'exit', exit the program
            else if (command == "exit")   { 
                vfs.exit(); return(EXIT_SUCCESS); 
                }
            // If the command is not recognized, print an error message
            else                          std::cout << command << ": command not found" << std::endl;
        }
        // If an exception is thrown, print the exception message
        catch (std::exception &e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }
    }
}









