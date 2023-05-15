#include <iostream>

template<typename T>
class MyVector
{
    public:
        MyVector() 
            : data(nullptr),size(0),capacity(0){}
        MyVector(int size_,T default_val)
                :data(new T[size_]),size(size_),capacity(size_)
            {
                for (size_t i = 0; i < size; i++)
                {
                   data[i] = default_val;
                } 
            }
        MyVector(const MyVector& second_vec) // конструктор копировования 
        {
            if(this == &second_vec)
            {
                return;
            }
            data = new T[second_vec.capacity];
            size = second_vec.size;
            capacity = second_vec.capacity;

            for (size_t i = 0; i < size; ++i)
            {
                data[i] = second_vec.data[i];
            }
        }    
        ~MyVector()
        {
            delete[] data;
        } 
        int Size() const
        {
            return this->size;
        }
        int Capacity() const
        {
            return this->capacity;
        }
        void Push_back(const T& new_val)
        {
            if(size + 1 > capacity)
            {
               T* new_data = new T[size == 0 ? 1 : size *2];
               for (size_t i = 0; i < size; i++)
               {
                 new_data[i] = std::move(data[i]);
               }
               delete[] data;
               data = new_data; 
               capacity = 2*size;
            }
            data[size] = std::move(new_val);
            size++;
        }
    const T& operator[](int index) const 
    {
        return data[index];
    }
    T& operator[](int index) //проверка что индекс не отрицательный
    {
        return data[index];
    }
    T& operator=(const MyVector& other)
    {
        if(this == &other)
        {
            return *this;
        }
        delete[] data;
        size = other.size();
        capacity = other.capacity();
        data = new T[capacity];
        for (size_t i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }
        return *this;
    }
    private:
        T* data;
        int size;
        int capacity;
};

int main()
{
   // добавить конструктор перемещения  
   // оператор присваивания
    MyVector<int> vec(5,5);
    std::cout << vec.Size()<<" " << vec.Capacity();
}