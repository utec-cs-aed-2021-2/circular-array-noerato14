#include "circulararray.h"

template <typename T>
class StackArray : public CircularArray<T> { 
    private: 
        //int* stackArray;
        int stack_capacity;
        int stack_size;
    
    public:
        StackArray();
        StackArray(int _capacity);
        void push(T data);
        int pop();
        void display();
        void resize(int* arr);
    
};

template <typename T>
StackArray<T>::StackArray() {
    StackArray(0);
}

template <typename T>
StackArray<T>::StackArray(int _capacity) {
    CircularArray(_capacity);
    this->stack_capacity = _capacity;
    this->stack_size = 0;
}

template <typename T>
void StackArray<T>::push(T data) {
    if (is_full()) {
        resize(array);
        push_back(data)
        stack_size++;
    } else {
        push_back(data)
        stack_size++;
    }
}

template <typename T>
int StackArray<T>::pop() {
    if (is_empty()) throw("error");
    return pop_back();
}

template <typename T>
void StackArray<T>::display() {
    to_string();
}

template <typename T>
void StackArray<T>::resize(int *arr) {
    int newSize = ( (size%capacity) * capacity) +1;
    int* newArr = new int [newSize];
    for (int i=0; i<size(); i++)
        *(newArr + i) = *(arr + i); 
    
    delete [] arr;
    arr = newArr;
}