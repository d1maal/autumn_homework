#include "johnson.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <climits>

void TestJohnson() {
    // Тест 1: Простой граф
    {
        std::cout << "Test 1: Simple graph\n";
        std::vector<std::vector<int>> edges = {
            {0, 1, 2},
            {0, 2, 5},
            {1, 2, 1},
            {1, 3, 3},
            {2, 3, 2}
        };
        
        Johnson johnson(4, edges);
        auto result = johnson.Run();
        
        assert(!result.empty());
        assert(result[0][3] == 5);  // 0->1->2->3 = 2+1+2 = 5
        assert(result[0][2] == 3);  // 0->1->2 = 2+1 = 3
        std::cout << "Test 1 passed\n";
    }
    
    // Тест 2: Граф с отрицательными весами (без отрицательных циклов)
    {
        std::cout << "Test 2: Graph with negative weights\n";
        std::vector<std::vector<int>> edges = {
            {0, 1, 3},
            {0, 2, 8},
            {1, 3, 1},
            {1, 4, 7},
            {2, 1, 4},
            {3, 2, -5},
            {3, 4, 2},
            {4, 0, 2}
        };
        
        Johnson johnson(5, edges);
        auto result = johnson.Run();
        
        assert(!result.empty());
        assert(result[0][4] == 6);  // 0->1->3->2->1->3->4 = ?
        std::cout << "Test 2 passed\n";
    }
    
    // Тест 3: Граф с отрицательным циклом
    {
        std::cout << "Test 3: Graph with negative cycle\n";
        std::vector<std::vector<int>> edges = {
            {0, 1, 1},
            {1, 2, -3},
            {2, 0, 1},
            {1, 3, 1},
            {3, 2, 1}
        };
        
        Johnson johnson(4, edges);
        auto result = johnson.Run();
        
        assert(result.empty());
        std::cout << "Test 3 passed\n";
    }
    
    // Тест 4: Граф без путей
    {
        std::cout << "Test 4: Disconnected graph\n";
        std::vector<std::vector<int>> edges = {
            {0, 1, 1},
            {2, 3, 2}
        };
        
        Johnson johnson(4, edges);
        auto result = johnson.Run();
        
        assert(!result.empty());
        assert(result[0][3] == INT_MAX);  // Нет пути
        assert(result[2][3] == 2);        // Есть путь
        std::cout << "Test 4 passed\n";
    }
    
    std::cout << "All Johnson tests passed!\n";
}

int main() {
    TestJohnson();
    return 0;
}