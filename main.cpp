#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define ld long double
#define all(a) a.begin(),a.end()
#define ios ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define ull unsigned long long
#define ll long long
using namespace std;

const int mod = 1e9 + 7;
const int N = 2e5 + 10;

using namespace std;

// Структура для представлення елемента списку
struct Node {
    int data=0;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// Клас, що представляє хеш-таблицю
class HashTable {
private:
    vector<Node*> table;
    int size=0;
    int operationsCount=0; // Змінна для відслідковування кількості операцій

    // Функція для обчислення хешу
    int hashFunction(int key) {
        operationsCount++; // кожен виклик hashFunction - 1 операція
        return key % size;
    }

public:
    HashTable(int tableSize) : size(tableSize), operationsCount(0) {
        operationsCount=size;
        table.resize(size, nullptr);
    }

    // Функція для додавання елемента в таблицю
    void insert(int key) {
        int index = hashFunction(key);
        operationsCount++;
        Node* newNode = new Node(key);
        operationsCount+=6; // для операції hashFunction
        if (table[index] == nullptr) {
            table[index] = newNode;
            operationsCount+=2; // присвоєння table[index] = newNode
        } else {
            Node* temp = table[index];
            operationsCount+=2;
            while (temp->next != nullptr) {
                temp = temp->next;
                operationsCount += 2; // Читання temp->next та інкрементування temp
            }
            temp->next = newNode;
            operationsCount++; // присвоєння temp->next = newNode
        }
    }

    // Функція для визначення довжини списку за заданим індексом
    int getListLength(int index) {
        int length = 0;
        Node* temp = table[index];
        operationsCount+=2;
        while (temp != nullptr) {
            length++;
            temp = temp->next;
            operationsCount += 3; // Читання temp->next та інкрементування temp
        }
        return length;
    }

    // Функція для виведення кількості операцій
    int getOperationsCount() {
        return operationsCount;
    }

    // Функція для виведення довжини найкоротшого та найдовшого списків
    void printMinMaxListLength() {
        int minListLength = INT_MAX;
        int maxListLength = 0;
        operationsCount+=2;
        operationsCount+=2*size;
        for (int i = 0; i < size; i++) {
            int length = getListLength(i);
            if (length > maxListLength) {
                maxListLength = length;
                operationsCount++;
            }
            if (length < minListLength && length != 0) {
                minListLength = length;
                operationsCount++;
            }
            operationsCount+=3;
        }
//        cout << "Shortest list: " << minListLength << " elements" << endl;
//        cout << "Longest list: " << maxListLength << " elements" << endl;
    }
};

struct TestResult {
    double TestTime=0;
    int OperationsCount=0;
};

TestResult test(int N) {
    TestResult result;

    HashTable hashTable(N / 10); // Розмір таблиці N/10
    //cout << "N = " << N << endl;

    // Вставка випадкових чисел у таблицю
    auto start = std::chrono::high_resolution_clock::now();
    result.OperationsCount+=2*N;
    for (int i = 0; i < N; i++) {
        result.OperationsCount++;
        hashTable.insert(rand());
    }

    // Виведення довжини найкоротшого та найдовшого списків
    hashTable.printMinMaxListLength();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    double testTime = duration.count();
    result.OperationsCount+=hashTable.getOperationsCount();
    result.TestTime = testTime;
    result.OperationsCount*=2;
    return result;
}

int main() {
    srand(time(0));

    // Задання значень N
    vector<int> N_values = {103, 104, 105, 106};
    cout<<fixed<<setprecision(2);
    double sumTimeOnOperation = 0;
    int experimentsCount = 0;
    for (int N : N_values) {
        int M = 100000;
        int fA=0;
        double tSum = 0;
        for (int i = 0; i < M; i++) {
            TestResult result = test(N);
            tSum += result.TestTime;
            fA+=result.OperationsCount;
        }
        double timeOnOperation = tSum/fA;
        sumTimeOnOperation += timeOnOperation;
        ++experimentsCount;
        double globalTimeOnOperation = sumTimeOnOperation/experimentsCount;
        cout << "N = " << N << " Average operations = " << fA/M << " Sum time = " << tSum << ' '<<"Time on operation = " << timeOnOperation*1e9 <<"ns"<< " Global time on operation = " << globalTimeOnOperation*1e9 <<"ns"<<endl;
    }

    return 0;
}