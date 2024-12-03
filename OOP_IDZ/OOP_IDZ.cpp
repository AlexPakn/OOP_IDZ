#include <iostream>
using namespace std;

template <typename T>
class tvector {
private:
    T* data;          // ��������� �� ������������ ������
    size_t size;      // ������� ������ �������
    size_t capacity;  // ������� ������� �������

    // ����� ��� ��������� ������� �������
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
    // ����������� �� ���������
    tvector() : data(nullptr), size(0), capacity(0) {}

    // ����������
    ~tvector() {
        delete[] data;
    }

    class iterator {
    private:
        T* ptr; // ��������� �� ������� �������

    public:
        // ����������� �������������� ���������
        iterator(T* p) : ptr(p) {}

        // �������� ������������� ��� ������� � ��������
        T& operator*() {
            return *ptr;
        }

        // ���������� ��������� ��� �������� � ���������� ��������
        iterator& operator++() {
            ++ptr;
            return *this;
        }

        // �������� ��������� ��� �������� ����������� ����������
        bool operator!=(const iterator& other) const {
            return ptr != other.ptr;
        }
    };

    // ���������� �������� �� ������ ����������
    iterator begin() {
        return iterator(data);
    }

    // ���������� �������� �� ����� ����������
    iterator end() {
        return iterator(data + size);
    }

    // ���������� ������ ��������
    void push_back(const T& value) {
        if (size == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = value;
    }

    // �������� �������� �� �������
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

    // ����� ��������
    int find(const T& value) const {
        for (size_t i = 0; i < size; ++i) {
            if (data[i] == value) {
                return static_cast<int>(i);
            }
        }
        return -1; // ������� �� ������
    }

    // ���������� �������
    void sort() {
        quick_sort(0, static_cast<int>(size - 1)); // ������ ������� ���������� ��� ����� �������
    }

    void quick_sort(int low, int high) {
        if (low < high) { // ��������� ���� �� ���� 1 ����������������� ������� �� ������ ������� �������
            T pivot = data[high]; // ������� �������
            int i = low - 1;      // ������ ��� ������� ���������

            // ��������� �������
            for (int j = low; j < high; ++j) {
                if (data[j] <= pivot) {
                    ++i;
                    swap(data[i], data[j]); // ����� ������� ���������
                }
            }

            swap(data[i + 1], data[high]); // �������� pivot �� ��� �����
            int pi = i + 1;                // ������ �������� ��������

            // ����������� ���������� ����� � ������ �����
            quick_sort(low, pi - 1);
            quick_sort(pi + 1, high);
        }
    }



    // ������ �������
    void reverse() {
        for (size_t i = 0; i < size / 2; ++i) {
            swap(data[i], data[size - i - 1]);
        }
    }

    // ��������� �������� �� �������
    void set(size_t index, const T& value) {
        if (index >= size) {
            cout << "Error: Index out of range." << endl;
            return;
        }
        data[index] = value;
    }

    // ��������� �������� �� �������
    T get(size_t index) const {
        if (index >= size) {
            cout << "Error: Index out of range." << endl;
            return T();
        }
        return data[index];
    }

    // ����������� � ������� ������
    void copy_to_array(T* array) const {
        for (size_t i = 0; i < size; ++i) {
            array[i] = data[i];
        }
    }

    // ����������� �� �������� �������
    void copy_from_array(const T* array, size_t array_size) {
        delete[] data;
        data = new T[array_size];
        size = capacity = array_size;
        for (size_t i = 0; i < array_size; ++i) {
            data[i] = array[i];
        }
    }

    // ��������� ������� �������
    size_t get_size() const {
        return size;
    }

    // ���������� ��������� [] ��� ������� � ���������
    T& operator[](size_t index) {
        if (index >= size) {
            cout << "Error: Index out of range." << endl;
            exit(1);
        }
        return data[index];
    }
};

// ������������ ������ tvector
int main() 
{
    setlocale(LC_ALL, "");

    tvector<int> tv;
    tv.push_back(5);
    tv.push_back(3);
    tv.push_back(8);
    tv.push_back(1);

    cout << "������ ����� ���������� ��������� (��������� ��������) : ";
    for (auto itr = tv.begin(); itr != tv.end(); ++itr) {
        cout << *itr << " ";
    }
    cout << endl;

    cout << "������ ����� ���������� ���������: ";
    for (size_t i = 0; i < tv.get_size(); ++i) {
        cout << tv[i] << " ";
    }
    cout << endl;

    tv.sort();
    cout << "������ ����� ����������: ";
    for (size_t i = 0; i < tv.get_size(); ++i) {
        cout << tv[i] << " ";
    }
    cout << endl;

    tv.reverse();
    cout << "������ ����� �������: ";
    for (size_t i = 0; i < tv.get_size(); ++i) {
        cout << tv[i] << " ";
    }
    cout << endl;

    // ����������� � ������� ������
    int* regular_array = new int[tv.get_size()];
    tv.copy_to_array(regular_array);

    cout << "������� ������ ����� �����������: ";
    for (size_t i = 0; i < tv.get_size(); ++i) {
        cout << regular_array[i] << " ";
    }
    cout << endl;

    // ����������� �� �������� �������
    int new_array[] = { 100, 200, 300, 400 };
    tv.copy_from_array(new_array, 4);

    cout << "������ tvector ����� ����������� �� �������� �������: ";
    for (size_t i = 0; i < tv.get_size(); ++i) {
        cout << tv[i] << " ";
    }
    cout << endl;

    delete[] regular_array; // ����������� ������

    return 0;
}
