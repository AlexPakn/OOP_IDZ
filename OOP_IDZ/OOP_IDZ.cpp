#include <iostream>
using namespace std;

template <typename T>
class tvector {
private:
    T* data;          // Указатель на динамический массив
    size_t size;      // Текущий размер массива
    size_t capacity;  // Текущая емкость массива

    // Метод для изменения емкости массива
    void resize(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    // Конструктор по умолчанию
    tvector() : data(nullptr), size(0), capacity(0) {}

    // Деструктор
    ~tvector() {
        delete[] data;
    }

    class iterator {
    private:
        T* ptr; // Указатель на текущий элемент

    public:
        // Конструктор инициализирует указатель
        iterator(T* p) : ptr(p) {}

        // Оператор разыменования для доступа к элементу
        T& operator*() {
            return *ptr;
        }

        // Префиксный инкремент для перехода к следующему элементу
        iterator& operator++() {
            ++ptr;
            return *this;
        }

        // Оператор сравнения для проверки неравенства итераторов
        bool operator!=(const iterator& other) const {
            return ptr != other.ptr;
        }
    };

    // Возвращает итератор на начало контейнера
    iterator begin() {
        return iterator(data);
    }

    // Возвращает итератор на конец контейнера
    iterator end() {
        return iterator(data + size);
    }

    // Добавление нового элемента
    void push_back(const T& value) {
        if (size == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = value;
    }

    // Удаление элемента по индексу
    void remove_at(size_t index) {
        if (index >= size) {
            cout << "Error: Index out of range." << endl;
            return;
        }
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        --size;
    }

    // Поиск элемента
    int find(const T& value) const {
        for (size_t i = 0; i < size; ++i) {
            if (data[i] == value) {
                return static_cast<int>(i);
            }
        }
        return -1; // Элемент не найден
    }

    // Сортировка массива
    void sort() {
        quick_sort(0, static_cast<int>(size - 1)); // Запуск быстрой сортировки для всего массива
    }

    void quick_sort(int low, int high) {
        if (low < high) { // Проверяем если ли хоть 1 неотсортированный элемент на данном участке массива
            T pivot = data[high]; // Опорный элемент
            int i = low - 1;      // Индекс для меньших элементов

            // Разбиение массива
            for (int j = low; j < high; ++j) {
                if (data[j] <= pivot) {
                    ++i;
                    swap(data[i], data[j]); // Обмен меньших элементов
                }
            }

            swap(data[i + 1], data[high]); // Помещаем pivot на его место
            int pi = i + 1;                // Индекс опорного элемента

            // Рекурсивная сортировка левой и правой части
            quick_sort(low, pi - 1);
            quick_sort(pi + 1, high);
        }
    }



    // Реверс массива
    void reverse() {
        for (size_t i = 0; i < size / 2; ++i) {
            swap(data[i], data[size - i - 1]);
        }
    }

    // Изменение значения по индексу
    void set(size_t index, const T& value) {
        if (index >= size) {
            cout << "Error: Index out of range." << endl;
            return;
        }
        data[index] = value;
    }

    // Получение значения по индексу
    T get(size_t index) const {
        if (index >= size) {
            cout << "Error: Index out of range." << endl;
            return T();
        }
        return data[index];
    }

    // Копирование в обычный массив
    void copy_to_array(T* array) const {
        for (size_t i = 0; i < size; ++i) {
            array[i] = data[i];
        }
    }

    // Копирование из обычного массива
    void copy_from_array(const T* array, size_t array_size) {
        delete[] data;
        data = new T[array_size];
        size = capacity = array_size;
        for (size_t i = 0; i < array_size; ++i) {
            data[i] = array[i];
        }
    }

    // Получение размера массива
    size_t get_size() const {
        return size;
    }

    // Перегрузка оператора [] для доступа к элементам
    T& operator[](size_t index) {
        if (index >= size) {
            cout << "Error: Index out of range." << endl;
            exit(1);
        }
        return data[index];
    }
};

// Тестирование класса tvector
int main() 
{
    setlocale(LC_ALL, "");

    tvector<int> tv;
    tv.push_back(5);
    tv.push_back(3);
    tv.push_back(8);
    tv.push_back(1);

    cout << "Массив после добавления элементов (используя итератор) : ";
    for (auto itr = tv.begin(); itr != tv.end(); ++itr) {
        cout << *itr << " ";
    }
    cout << endl;

    cout << "Массив после добавления элементов: ";
    for (size_t i = 0; i < tv.get_size(); ++i) {
        cout << tv[i] << " ";
    }
    cout << endl;

    tv.sort();
    cout << "Массив после сортировки: ";
    for (size_t i = 0; i < tv.get_size(); ++i) {
        cout << tv[i] << " ";
    }
    cout << endl;

    tv.reverse();
    cout << "Массив после реверса: ";
    for (size_t i = 0; i < tv.get_size(); ++i) {
        cout << tv[i] << " ";
    }
    cout << endl;

    // Копирование в обычный массив
    int* regular_array = new int[tv.get_size()];
    tv.copy_to_array(regular_array);

    cout << "Обычный массив после копирования: ";
    for (size_t i = 0; i < tv.get_size(); ++i) {
        cout << regular_array[i] << " ";
    }
    cout << endl;

    // Копирование из обычного массива
    int new_array[] = { 100, 200, 300, 400 };
    tv.copy_from_array(new_array, 4);

    cout << "Массив tvector после копирования из обычного массива: ";
    for (size_t i = 0; i < tv.get_size(); ++i) {
        cout << tv[i] << " ";
    }
    cout << endl;

    delete[] regular_array; // Освобождаем память

    return 0;
}
