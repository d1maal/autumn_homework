#include "rmq.h"
#include <iostream>
#include <vector>
#include <cassert>

void TestRMQ() {
    // Тест 1: Простой массив
    {
        std::cout << "Test 1: Simple array\n";
        std::vector<int> arr = {1, 3, 2, 7, 9, 11, 5};
        RMQ rmq(arr);
        
        assert(rmq.Query(0, 2) == 1);   // min(1,3,2) = 1
        assert(rmq.Query(1, 4) == 2);   // min(3,2,7,9) = 2
        assert(rmq.Query(3, 6) == 5);   // min(7,9,11,5) = 5
        std::cout << "Test 1 passed\n";
    }
    
    // Тест 2: Обновления
    {
        std::cout << "Test 2: With updates\n";
        std::vector<int> arr = {5, 3, 7, 3, 2};
        RMQ rmq(arr);
        
        assert(rmq.Query(1, 4) == 2);   // min(3,7,3,2) = 2
        
        rmq.Update(2, 1);  // arr[2] = 1
        assert(rmq.Query(1, 4) == 1);   // min(3,1,3,2) = 1
        
        rmq.Update(4, 10); // arr[4] = 10
        assert(rmq.Query(0, 4) == 1);   // min(5,3,1,3,10) = 1
        std::cout << "Test 2 passed\n";
    }
    
    // Тест 3: Все одинаковые элементы
    {
        std::cout << "Test 3: All equal elements\n";
        std::vector<int> arr = {5, 5, 5, 5, 5};
        RMQ rmq(arr);
        
        assert(rmq.Query(0, 4) == 5);
        
        rmq.Update(2, 3);
        assert(rmq.Query(0, 4) == 3);
        std::cout << "Test 3 passed\n";
    }
    
    // Тест 4: Один элемент
    {
        std::cout << "Test 4: Single element\n";
        std::vector<int> arr = {42};
        RMQ rmq(arr);
        
        assert(rmq.Query(0, 0) == 42);
        
        rmq.Update(0, 100);
        assert(rmq.Query(0, 0) == 100);
        std::cout << "Test 4 passed\n";
    }
    
    // Тест 5: Большой диапазон
    {
        std::cout << "Test 5: Large range\n";
        std::vector<int> arr = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        RMQ rmq(arr);
        
        assert(rmq.Query(0, 9) == 0);
        assert(rmq.Query(0, 4) == 5);
        assert(rmq.Query(5, 8) == 1);
        
        rmq.Update(9, 5);
        assert(rmq.Query(0, 9) == 1);
        std::cout << "Test 5 passed\n";
    }
    
    std::cout << "All RMQ tests passed!\n";
}

int main() {
    TestRMQ();
    return 0;
}