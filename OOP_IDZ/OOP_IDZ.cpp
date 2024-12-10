#include <iostream>
using namespace std;

template <typename T>
class tvector {
private:
    T* data;          // Вказівник на динамічний масив
    size_t size;      // Поточний розмір масиву
    size_t capacity;  // Поточна ємність масиву

    // Метод для зміни ємності масиву
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
    // Конструктор за замовчуванням
    tvector() : data(nullptr), size(0), capacity(0) {}

    // Деструктор
    ~tvector() {
        delete[] data;
    }

    class iterator {
    private:
        T* ptr; // Вказівник на поточний елемент

    public:
        // Конструктор ініціалізує вказівник
        iterator(T* p) : ptr(p) {}

        // Оператор розіменування для доступу до елемента
        T& operator*() {
            return *ptr;
        }

        // Префіксний інкремент для переходу до наступного елемента
        iterator& operator++() {
            ++ptr;
            return *this;
        }

        // Оператор порівняння для перевірки нерівності ітераторів
        bool operator!=(const iterator& other) const {
            return ptr != other.ptr;
        }
    };

    // Повертає ітератор на початок контейнера
    iterator begin() {
        return iterator(data);
    }

    // Повертає ітератор на кінець контейнера
    iterator end() {
        return iterator(data + size);
    }

    // Додавання нового елемента
    void push_back(const T& value) {
        if (size == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = value;
    }

    // Видалення елемента за індексом
    void remove_at(size_t index) {
        if (index >= size) {
            cout << "Помилка: Індекс виходить за межі." << endl;
            return;
        }
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        --size;
    }

    // Пошук елемента
    int find(const T& value) const {
        for (size_t i = 0; i < size; ++i) {
            if (data[i] == value) {
                return static_cast<int>(i);
            }
        }
        return -1; // Елемент не знайдено
    }

    // Сортування масиву
    void sort() {
        quick_sort(0, static_cast<int>(size - 1)); // Запуск швидкого сортування для всього масиву
    }

    void quick_sort(int low, int high) {
        if (low < high) { // Перевіряємо, чи є хоча б один не відсортований елемент на цій ділянці масиву
            T pivot = data[high]; // Опорний елемент
            int i = low - 1;      // Індекс для менших елементів

            // Розбиття масиву
            for (int j = low; j < high; ++j) {
                if (data[j] <= pivot) {
                    ++i;
                    swap(data[i], data[j]); // Обмін менших елементів
                }
            }

            swap(data[i + 1], data[high]); // Розміщуємо pivot на своє місце
            int pi = i + 1;                // Індекс опорного елемента

            // Рекурсивне сортування лівої та правої частини
            quick_sort(low, pi - 1);
            quick_sort(pi + 1, high);
        }
    }

    // Реверс масиву
    void reverse() {
        for (size_t i = 0; i < size / 2; ++i) {
            swap(data[i], data[size - i - 1]);
        }
    }

    // Зміна значення за індексом
    void set(size_t index, const T& value) {
        if (index >= size) {
            cout << "Помилка: Індекс виходить за межі." << endl;
            return;
        }
        data[index] = value;
    }

    // Отримання значення за індексом
    T get(size_t index) const {
        if (index >= size) {
            cout << "Помилка: Індекс виходить за межі." << endl;
            return T();
        }
        return data[index];
    }

    // Копіювання у звичайний масив
    void copy_to_array(T* array) const {
        for (size_t i = 0; i < size; ++i) {
            array[i] = data[i];
        }
    }

    // Копіювання зі звичайного масиву
    void copy_from_array(const T* array, size_t array_size) {
        delete[] data;
        data = new T[array_size];
        size = capacity = array_size;
        for (size_t i = 0; i < array_size; ++i) {
            data[i] = array[i];
        }
    }

    // Отримання розміру масиву
    size_t get_size() const {
        return size;
    }

    // Перевантаження оператора [] для доступу до елементів
    T& operator[](size_t index) {
        if (index >= size) {
            cout << "Помилка: Індекс виходить за межі." << endl;
            exit(1);
        }
        return data[index];
    }
};

// Тестування класу tvector
int main()
{
    setlocale(LC_ALL, "");

    tvector<int> tv;
    tv.push_back(5);
    tv.push_back(3);
    tv.push_back(8);
    tv.push_back(1);

    cout << "Масив після додавання елементів (використовуючи ітератор): ";
    for (auto itr = tv.begin(); itr != tv.end(); ++itr) {
        cout << *itr << " ";
    }
    cout << endl;

    cout << "Масив після додавання елементів: ";
    for (size_t i = 0; i < tv.get_size(); ++i) {
        cout << tv[i] << " ";
    }
    cout << endl;

    tv.sort();
    cout << "Масив після сортування: ";
    for (size_t i = 0; i < tv.get_size(); ++i) {
        cout << tv[i] << " ";
    }
    cout << endl;

    tv.reverse();
    cout << "Масив після реверсу: ";
    for (size_t i = 0; i < tv.get_size(); ++i) {
        cout << tv[i] << " ";
    }
    cout << endl;

    // Копіювання у звичайний масив
    int* regular_array = new int[tv.get_size()];
    tv.copy_to_array(regular_array);

    cout << "Звичайний масив після копіювання: ";
    for (size_t i = 0; i < tv.get_size(); ++i) {
        cout << regular_array[i] << " ";
    }
    cout << endl;

    // Копіювання зі звичайного масиву
    int new_array[] = { 100, 200, 300, 400 };
    tv.copy_from_array(new_array, 4);

    cout << "Масив tvector після копіювання зі звичайного масиву: ";
    for (size_t i = 0; i < tv.get_size(); ++i) {
        cout << tv[i] << " ";
    }
    cout << endl;

    delete[] regular_array; // Звільняємо пам'ять

    return 0;
}
