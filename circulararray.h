#include <iostream>
using namespace std;

template <class T>
class CircularArray
{
private:
    T *array;
    int capacity;
    int back, front;
    
public:
    CircularArray(); //implemented
    CircularArray(int _capacity); //implemented
    virtual ~CircularArray(); //implemented
    void push_front(T data);
    void push_back(T data);
    void insert(T data, int pos);
    T pop_front();
    T pop_back();
    bool is_full();
    bool is_empty();
    int size();
    void clear();
    T &operator[](int);
    void sort();
    bool is_sorted();
    void reverse();
    string to_string(string sep=" "); //implemented

private:
    int next(int);
    int prev(int);
    void swap(int* x, int* y);
    int partition (int* arr, int lowIndex, int highIndex);
    void myQuickSort(int* arr, int lowIndex, int highIndex);
};

template <class T>
CircularArray<T>::CircularArray()
{
    CircularArray(0);
}

template <class T>
CircularArray<T>::CircularArray(int _capacity)
{
    this->array = new T[_capacity];
    this->capacity = _capacity;
    this->front = this->back = -1;
}

template <class T>
CircularArray<T>::~CircularArray()
{
    delete[] array;
}

template <class T>
int CircularArray<T>::prev(int index)
{
    return (index == 0) ? capacity - 1 : index - 1;
}

template <class T>
int CircularArray<T>::next(int index)
{
    return (index + 1) % capacity;
}

template <class T>
string CircularArray<T>::to_string(string sep)
{
    string result = ""; 
    for (int i = 0; i < size(); i++)
        result += std::to_string((*this)[i]) + sep;

    cout<<"Resultado to_string()"<< result <<endl;
    return result;    
}


/*-------- Noe Functions --------*/

template <class T>
void CircularArray<T>::push_front(T _data)
{
    if (!is_full()){
        bool _is_empty = is_empty();

        back  = _is_empty ? 0 : back;
        front = _is_empty ? 0 : prev(front);
        *(array + front) = _data;
    } else {
        cout<<"Error Array is full"<<endl;
        exit(0);
    }
    
}

template <class T>
void CircularArray<T>::push_back(T _data)
{
    if (!is_full()){
        bool _is_empty = is_empty();

        back  = _is_empty ? 0 : next(back);
        front = _is_empty ? 0 : front;
        *(array + back) = _data;
    } else {
        cout<<"Error Array is full"<<endl;
        exit(0);
    }
    to_string();
}

template <class T>
void CircularArray<T>::insert(T _data, int _pos)
{
    if (_pos < size()){
        *(array + (front + _pos)%capacity) = _data;
    } else {
        cout<<"Index out of the range"<<endl;
        exit(0);
    }
}

template <class T>
T CircularArray<T>::pop_front()
{
    if (!is_empty()){
        int temp = *(array + front);
        int _size = size();

        *(array + front) = 0;
        
        front = (_size == 1) ? -1 : next(front);
        back  = (_size == 1) ? -1 : back;

        return temp;

    } else {
        cout<<"The array is empty"<<endl;
        exit(0);
    }   
}

template <class T>
T CircularArray<T>::pop_back()
{
    if (!is_empty()){
        int temp = *(array + back);
        int _size = size();

        *(array + back) = 0;
        
        front = (_size == 1) ? -1 : front;
        back  = (_size == 1) ? -1 : prev(back);

        return temp;

    } else {
        cout<<"The array is empty"<<endl;
        exit(0);
    }
}

template <class T>
bool CircularArray<T>::is_full()
{
    return size() == capacity;
}


template <class T>
bool CircularArray<T>::is_empty()
{
    return size() == 0;
}

template <class T>
int CircularArray<T>::size()
{
    return (front == -1 && back == -1) ? 0 : ( -(front - back) + capacity * (front > back) + 1);
}

template <class T>
void CircularArray<T>::clear()
{
    for (int i = 0; i < size(); i++)
        *(array + i) = 0;
}

template <class T>
T& CircularArray<T>::operator[](int index)
{
    return *(array + (front + index)%capacity );
}

/* Sort Function */

template <class T>
void CircularArray<T>::sort()
{
    myQuickSort(array, 0, size()-1);
}

template <class T>
void CircularArray<T>::swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

template <class T>
int CircularArray<T>::partition (int* arr, int lowIndex, int highIndex)
{
    int pivot = (*this)[highIndex];
    int i = (lowIndex - 1);
    for (int j = lowIndex; j <= highIndex - 1; j++)
    {
        if ( (*this)[j] <= pivot )
        {
            i++; 
            swap((arr + (front + i)%capacity), (arr + (front + j)%capacity));
        }
        to_string();
    }
    swap((arr + (front + i + 1)%capacity), (arr + (front + highIndex)%capacity));
    return (i+1);
}

template <class T>
void CircularArray<T>::myQuickSort(int* arr, int lowIndex, int highIndex)
{
    
    if (lowIndex < highIndex)
    {
        int piv = partition(arr, lowIndex, highIndex);

        myQuickSort(arr, lowIndex, piv - 1);
        myQuickSort(arr, piv + 1, highIndex);
        
    }
}

template <class T>
bool CircularArray<T>::is_sorted()
{
    bool _is_sorted = false;
    T* tempArray = new T[capacity];

    for (int i = 0; i < size(); i++)
        *(tempArray + i) = *(array + i);

    myQuickSort(tempArray, 0, size()-1);

    for (int i = 0; i < size(); i++){
        if (*(tempArray + i) != *(array + i)) {
            _is_sorted = false;
            break;
        } else _is_sorted = true;
    }
        
    return _is_sorted;
}

template <class T>
void CircularArray<T>::reverse()
{
    int _size = size();
    int midIndex = _size%2 == 0 ? _size/2 - 1 : _size/2;
    for (int i = 0; i <= midIndex; i++){
        int temp = *(array + (front + i)%capacity);
        *(array + (front + i)%capacity) = *(array + (back - i)%capacity);
        *(array + (back - i)%capacity) = temp;
    }
}