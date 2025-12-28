#include "graph.h"

#include <iostream>
#include <vector>
#include <cassert>

void TestMSTWithDegreeLimit() {
    // Тест 1: Простой граф, MST существует с ограничением d=2
    {
        std::cout << "Test 1: Simple graph with d=2\n";
        int n = 4, m = 5, d = 2;
        std::vector<Edge> edges = {
            Edge(1, 2, 1),
            Edge(1, 3, 3),
            Edge(1, 4, 4),
            Edge(2, 3, 2),
            Edge(3, 4, 5)
        };
        
        long long result = FindMinimumSpanningTreeWithDegreeLimit(n, d, edges);
        assert(result == 7);
        std::cout << "Test 1 passed. MST weight: " << result << "\n";
    }
    
    // Тест 2: Ограничение слишком строгое (невозможно построить)
    {
        std::cout << "Test 2: Too strict degree limit (d=1)\n";
        int n = 3, m = 3, d = 1;
        std::vector<Edge> edges = {
            Edge(1, 2, 1),
            Edge(2, 3, 2),
            Edge(1, 3, 3)
        };
        
        long long result = FindMinimumSpanningTreeWithDegreeLimit(n, d, edges);
        assert(result == -1);
        std::cout << "Test 2 passed. Result: " << (result == -1 ? "Impossible" : std::to_string(result)) << "\n";
    }
    
    // Тест 3: Граф с равными весами
    {
        std::cout << "Test 3: Graph with equal weights, d=2\n";
        int n = 5, m = 7, d = 2;
        std::vector<Edge> edges = {
            Edge(1, 2, 1),
            Edge(2, 3, 1),
            Edge(3, 4, 1),
            Edge(4, 5, 1),
            Edge(1, 5, 1),
            Edge(1, 3, 2),
            Edge(2, 4, 2)
        };
        
        long long result = FindMinimumSpanningTreeWithDegreeLimit(n, d, edges);
        assert(result == 4);
        std::cout << "Test 3 passed. MST weight: " << result << "\n";
    }
    
    // Тест 4: Звезда с центром в вершине 1 (d=3 - невозможно, d=4 - возможно)
    {
        std::cout << "Test 4: Star graph\n";
        int n = 5, m = 4, d = 3;
        std::vector<Edge> edges = {
            Edge(1, 2, 1),
            Edge(1, 3, 1),
            Edge(1, 4, 1),
            Edge(1, 5, 1)
        };
        
        long long result = FindMinimumSpanningTreeWithDegreeLimit(n, d, edges);
        assert(result == -1);
        std::cout << "Test 4 (d=3) passed: impossible\n";
        
        d = 4;
        result = FindMinimumSpanningTreeWithDegreeLimit(n, d, edges);
        assert(result == 4);
        std::cout << "Test 4 (d=4) passed. MST weight: " << result << "\n";
    }
    
    // Тест 5: Большой граф с разными весами
    {
        std::cout << "Test 5: Larger graph with various weights, d=3\n";
        int n = 6, m = 9, d = 3;
        std::vector<Edge> edges = {
            Edge(1, 2, 4),
            Edge(1, 3, 2),
            Edge(2, 3, 1),
            Edge(2, 4, 5),
            Edge(3, 4, 8),
            Edge(3, 5, 9),
            Edge(4, 5, 1),
            Edge(4, 6, 3),
            Edge(5, 6, 7)
        };
        
        long long result = FindMinimumSpanningTreeWithDegreeLimit(n, d, edges);
        assert(result == 12);
        std::cout << "Test 5 passed. MST weight: " << result << "\n";
    }
    
    // Тест 6: Граф с кратными ребрами
    {
        std::cout << "Test 6: Graph with multiple edges, d=2\n";
        int n = 4, m = 6, d = 2;
        std::vector<Edge> edges = {
            Edge(1, 2, 1),
            Edge(1, 2, 4),
            Edge(2, 3, 2),
            Edge(2, 3, 5),
            Edge(3, 4, 3),
            Edge(1, 4, 6)
        };
        
        long long result = FindMinimumSpanningTreeWithDegreeLimit(n, d, edges);
        assert(result == 6);
        std::cout << "Test 6 passed. MST weight: " << result << "\n";
    }
    
    // Тест 7: Граф с петлями (должны игнорироваться)
    {
        std::cout << "Test 7: Graph with self-loops, d=2\n";
        int n = 3, m = 4, d = 2;
        std::vector<Edge> edges = {
            Edge(1, 1, 5),
            Edge(1, 2, 1),
            Edge(2, 3, 2),
            Edge(1, 3, 4)
        };
        
        long long result = FindMinimumSpanningTreeWithDegreeLimit(n, d, edges);
        assert(result == 3);
        std::cout << "Test 7 passed. MST weight: " << result << "\n";
    }
    
    // Тест 8: Невозможно построить из-за недостатка ребер
    {
        std::cout << "Test 8: Not enough edges to form spanning tree\n";
        int n = 4, m = 2, d = 3;
        std::vector<Edge> edges = {
            Edge(1, 2, 1),
            Edge(3, 4, 2)
        };
        
        long long result = FindMinimumSpanningTreeWithDegreeLimit(n, d, edges);
        assert(result == -1);
        std::cout << "Test 8 passed. Result: Impossible\n";
    }
    
    // Тест 9: Граф с одним ребром (тривиальный случай)
    {
        std::cout << "Test 9: Single edge graph\n";
        int n = 2, m = 1, d = 1;
        std::vector<Edge> edges = {
            Edge(1, 2, 5)
        };
        
        long long result = FindMinimumSpanningTreeWithDegreeLimit(n, d, edges);
        assert(result == 5);
        std::cout << "Test 9 passed. MST weight: " << result << "\n";
    }
    
    // Тест 10: Сложный случай с ограничением на степень
    {
        std::cout << "Test 10: Complex case with degree constraint\n";
        int n = 5, m = 10, d = 2;
        std::vector<Edge> edges = {
            Edge(1, 2, 1),
            Edge(1, 3, 2),
            Edge(1, 4, 3),
            Edge(1, 5, 4),
            Edge(2, 3, 5),
            Edge(2, 4, 6),
            Edge(2, 5, 7),
            Edge(3, 4, 8),
            Edge(3, 5, 9),
            Edge(4, 5, 10)
        };
        
        long long result = FindMinimumSpanningTreeWithDegreeLimit(n, d, edges);
        assert(result == 18);
        std::cout << "Test 10 passed. MST weight: " << result << "\n";
    }
    
    // Тест 11: Граф где оптимальное MST невозможно из-за ограничения степени
    {
        std::cout << "Test 11: Graph where optimal MST is impossible due to degree limit\n";
        int n = 4, m = 6, d = 2;
        std::vector<Edge> edges = {
            Edge(1, 2, 1),
            Edge(1, 3, 1),
            Edge(1, 4, 100),
            Edge(2, 3, 100),
            Edge(2, 4, 1),
            Edge(3, 4, 1)
        };
        
        long long result = FindMinimumSpanningTreeWithDegreeLimit(n, d, edges);
        
        assert(result == 3);
        std::cout << "Test 11 passed. MST weight: " << result << "\n";
    }
    
    // Тест 12: Полный граф K4
    {
        std::cout << "Test 12: Complete graph K4\n";
        int n = 4, m = 6, d = 2;
        std::vector<Edge> edges = {
            Edge(1, 2, 1),
            Edge(1, 3, 2),
            Edge(1, 4, 3),
            Edge(2, 3, 4),
            Edge(2, 4, 5),
            Edge(3, 4, 6)
        };
        
        long long result = FindMinimumSpanningTreeWithDegreeLimit(n, d, edges);
        assert(result == 8);
        std::cout << "Test 12 passed. MST weight: " << result << "\n";
    }
    
    // Тест 13: Граф, где алгоритм может пропустить лучшее решение
    {
        std::cout << "Test 13: Graph where greedy might not find optimal solution\n";
        int n = 4, m = 5, d = 2;
        std::vector<Edge> edges = {
            Edge(1, 2, 1),
            Edge(2, 3, 1),
            Edge(3, 4, 1),
            Edge(1, 4, 2),
            Edge(1, 3, 3)
        };
        
        long long result = FindMinimumSpanningTreeWithDegreeLimit(n, d, edges);
        
        assert(result == 3);
        std::cout << "Test 13 passed. MST weight: " << result << "\n";
    }
    
    // Тест 14: Граф с 1 вершиной (тривиальный случай)
    {
        std::cout << "Test 14: Single vertex graph\n";
        int n = 1, m = 0, d = 0;
        std::vector<Edge> edges;
        
        long long result = FindMinimumSpanningTreeWithDegreeLimit(n, d, edges);
        // MST из 1 вершины имеет вес 0
        assert(result == 0);
        std::cout << "Test 14 passed. MST weight: " << result << "\n";
    }
    
    std::cout << "\nAll MST tests passed!\n";
}

int main() {
    TestMSTWithDegreeLimit();
    return 0;
}