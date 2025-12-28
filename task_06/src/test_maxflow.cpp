#include "maxflow.h"
#include <iostream>
#include <vector>
#include <cassert>

void TestMaxFlow() {
    // Тест 1: Простая сеть
    {
        std::cout << "Test 1: Simple network\n";
        std::vector<std::vector<int>> edges = {
            {0, 1, 3},
            {0, 2, 2},
            {1, 2, 5},
            {1, 3, 2},
            {2, 3, 3}
        };
        
        MaxFlow mf(4, edges);
        int flow = mf.Calculate(0, 3);
        
        assert(flow == 5);
        std::cout << "Test 1 passed\n";
    }
    
    // Тест 2: Сеть с несколькими путями
    {
        std::cout << "Test 2: Network with multiple paths\n";
        std::vector<std::vector<int>> edges = {
            {0, 1, 10},
            {0, 2, 10},
            {1, 2, 2},
            {1, 3, 4},
            {1, 4, 8},
            {2, 4, 9},
            {3, 5, 10},
            {4, 3, 6},
            {4, 5, 10}
        };
        
        MaxFlow mf(6, edges);
        int flow = mf.Calculate(0, 5);
        
        assert(flow == 19);
        std::cout << "Test 2 passed\n";
    }
    
    // Тест 3: Сеть с обратными ребрами
    {
        std::cout << "Test 3: Network with reverse edges\n";
        std::vector<std::vector<int>> edges = {
            {0, 1, 16},
            {0, 2, 13},
            {1, 2, 10},
            {2, 1, 4},
            {1, 3, 12},
            {3, 2, 9},
            {2, 4, 14},
            {4, 3, 7},
            {3, 5, 20},
            {4, 5, 4}
        };
        
        MaxFlow mf(6, edges);
        int flow = mf.Calculate(0, 5);
        
        assert(flow == 23);
        std::cout << "Test 3 passed\n";
    }
    
    // Тест 4: Источник = сток
    {
        std::cout << "Test 4: Source equals sink\n";
        std::vector<std::vector<int>> edges = {
            {0, 1, 5},
            {1, 2, 3}
        };
        
        MaxFlow mf(3, edges);
        int flow = mf.Calculate(0, 0);
        
        assert(flow == 0);
        std::cout << "Test 4 passed\n";
    }
    
    std::cout << "All MaxFlow tests passed!\n";
}

int main() {
    TestMaxFlow();
    return 0;
}