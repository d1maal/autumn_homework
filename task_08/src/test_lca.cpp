#include "lca.h"
#include <iostream>
#include <vector>
#include <cassert>

void TestLCA() {
    // Тест 1: Простое дерево
    {
        std::cout << "Test 1: Simple tree\n";
        int n = 7;
        std::vector<std::vector<int>> graph(n);
        
        // Дерево: 0-1-2-3-4 цепочка и 1-5, 5-6
        graph[0] = {1};
        graph[1] = {0, 2, 5};
        graph[2] = {1, 3};
        graph[3] = {2, 4};
        graph[4] = {3};
        graph[5] = {1, 6};
        graph[6] = {5};
        
        LCA lca(n, graph);
        lca.Preprocess(0);
        
        assert(lca.Query(0, 4) == 0);
        assert(lca.Query(2, 4) == 2);
        assert(lca.Query(3, 6) == 1);
        assert(lca.Query(4, 6) == 1);
        assert(lca.Query(5, 6) == 5);
        std::cout << "Test 1 passed\n";
    }
    
    // Тест 2: Полное двоичное дерево
    {
        std::cout << "Test 2: Complete binary tree\n";
        int n = 7;
        std::vector<std::vector<int>> graph(n);
        
        // Дерево: 0-1, 0-2, 1-3, 1-4, 2-5, 2-6
        graph[0] = {1, 2};
        graph[1] = {0, 3, 4};
        graph[2] = {0, 5, 6};
        graph[3] = {1};
        graph[4] = {1};
        graph[5] = {2};
        graph[6] = {2};
        
        LCA lca(n, graph);
        lca.Preprocess(0);
        
        assert(lca.Query(3, 4) == 1);
        assert(lca.Query(3, 5) == 0);
        assert(lca.Query(5, 6) == 2);
        assert(lca.Query(4, 6) == 0);
        assert(lca.Query(1, 4) == 1);
        std::cout << "Test 2 passed\n";
    }
    
    // Тест 3: Звезда (одна вершина в центре)
    {
        std::cout << "Test 3: Star tree\n";
        int n = 5;
        std::vector<std::vector<int>> graph(n);
        
        // Дерево: 0-1, 0-2, 0-3, 0-4
        graph[0] = {1, 2, 3, 4};
        graph[1] = {0};
        graph[2] = {0};
        graph[3] = {0};
        graph[4] = {0};
        
        LCA lca(n, graph);
        lca.Preprocess(0);
        
        assert(lca.Query(1, 2) == 0);
        assert(lca.Query(3, 4) == 0);
        assert(lca.Query(1, 3) == 0);
        assert(lca.Query(2, 4) == 0);
        assert(lca.Query(1, 1) == 1);
        std::cout << "Test 3 passed\n";
    }
    
    // Тест 4: Цепочка
    {
        std::cout << "Test 4: Chain tree\n";
        int n = 5;
        std::vector<std::vector<int>> graph(n);
        
        // Дерево: 0-1-2-3-4
        graph[0] = {1};
        graph[1] = {0, 2};
        graph[2] = {1, 3};
        graph[3] = {2, 4};
        graph[4] = {3};
        
        LCA lca(n, graph);
        lca.Preprocess(0);
        
        assert(lca.Query(0, 4) == 0);
        assert(lca.Query(2, 4) == 2);
        assert(lca.Query(1, 3) == 1);
        assert(lca.Query(3, 4) == 3);
        assert(lca.Query(0, 2) == 0);
        std::cout << "Test 4 passed\n";
    }
    
    // Тест 5: Дерево с разными корнями
    {
        std::cout << "Test 5: Tree with different root\n";
        int n = 6;
        std::vector<std::vector<int>> graph(n);
        
        // Дерево: 0-1, 1-2, 1-3, 3-4, 3-5
        graph[0] = {1};
        graph[1] = {0, 2, 3};
        graph[2] = {1};
        graph[3] = {1, 4, 5};
        graph[4] = {3};
        graph[5] = {3};
        
        LCA lca(n, graph);
        lca.Preprocess(1);  // Корень = 1, а не 0
        
        assert(lca.Query(0, 2) == 1);
        assert(lca.Query(4, 5) == 3);
        assert(lca.Query(0, 4) == 1);
        assert(lca.Query(2, 5) == 1);
        assert(lca.Query(4, 4) == 4);
        std::cout << "Test 5 passed\n";
    }
    
    // Тест 6: Сложное дерево с несколькими уровнями
    {
        std::cout << "Test 6: Complex tree with multiple levels\n";
        int n = 10;
        std::vector<std::vector<int>> graph(n);
        
        
        graph[0] = {1, 2};
        graph[1] = {0, 3, 4};
        graph[2] = {0, 5};
        graph[3] = {1, 6};
        graph[4] = {1, 7, 8};
        graph[5] = {2};
        graph[6] = {3};
        graph[7] = {4};
        graph[8] = {4, 9};
        graph[9] = {8};
        
        LCA lca(n, graph);
        lca.Preprocess(0);
        
        assert(lca.Query(6, 7) == 1);   
        assert(lca.Query(6, 9) == 1);   
        assert(lca.Query(5, 9) == 0);   
        assert(lca.Query(7, 8) == 4);   
        assert(lca.Query(6, 3) == 3);   
        std::cout << "Test 6 passed\n";
    }
    
    std::cout << "All LCA tests passed!\n";
}

int main() {
    TestLCA();
    return 0;
}