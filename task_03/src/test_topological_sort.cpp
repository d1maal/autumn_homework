#include "topological_sort.h"

#include <iostream>
#include <vector>
#include <cassert>


void TestTopologicalSort() {
    // Тест 1: Простой граф без циклов
    {
        std::cout << "Test 1: Simple acyclic graph\n";
        int n = 4;
        std::vector<std::pair<int, int>> edges = {
            {1, 2},
            {1, 3},
            {2, 4},
            {3, 4}
        };
        
        std::vector<int> result;
        bool has_order = TopologicalSorter::Sort(n, edges, result);
        
        assert(has_order);
        assert(result.size() == n);
        
        // Проверяем корректность топологического порядка
        std::vector<int> position(n + 1);
        for (size_t i = 0; i < result.size(); ++i) {
            position[result[i]] = i;
        }
        
        for (const auto& edge : edges) {
            assert(position[edge.first] < position[edge.second]);
        }
        
        std::cout << "Test 1 passed. Topological order found.\n";
    }
    
    // Тест 2: Граф с циклом
    {
        std::cout << "Test 2: Graph with cycle\n";
        int n = 3;
        std::vector<std::pair<int, int>> edges = {
            {1, 2},
            {2, 3},
            {3, 1}  // Создает цикл 1->2->3->1
        };
        
        std::vector<int> result;
        bool has_order = TopologicalSorter::Sort(n, edges, result);
        
        assert(!has_order);
        assert(result.size() < n);
        std::cout << "Test 2 passed. Cycle detected.\n";
    }
    
    // Тест 3: Граф с несколькими компонентами связности (без циклов)
    {
        std::cout << "Test 3: Graph with multiple connected components\n";
        int n = 6;
        std::vector<std::pair<int, int>> edges = {
            {1, 2},
            {2, 3},
            {4, 5},
            {5, 6}
            // Компоненты: {1,2,3} и {4,5,6}
        };
        
        std::vector<int> result;
        bool has_order = TopologicalSorter::Sort(n, edges, result);
        
        assert(has_order);
        assert(result.size() == n);
        
        std::vector<int> position(n + 1);
        for (size_t i = 0; i < result.size(); ++i) {
            position[result[i]] = i;
        }
        
        for (const auto& edge : edges) {
            assert(position[edge.first] < position[edge.second]);
        }
        
        std::cout << "Test 3 passed. Topological order found for disconnected graph.\n";
    }
    
    // Тест 4: Одна вершина без ребер
    {
        std::cout << "Test 4: Single vertex with no edges\n";
        int n = 1;
        std::vector<std::pair<int, int>> edges;
        
        std::vector<int> result;
        bool has_order = TopologicalSorter::Sort(n, edges, result);
        
        assert(has_order);
        assert(result.size() == 1);
        assert(result[0] == 1);
        std::cout << "Test 4 passed. Single vertex.\n";
    }
    
    // Тест 5: Несколько вершин без ребер
    {
        std::cout << "Test 5: Multiple vertices with no edges\n";
        int n = 5;
        std::vector<std::pair<int, int>> edges;
        
        std::vector<int> result;
        bool has_order = TopologicalSorter::Sort(n, edges, result);
        
        assert(has_order);
        assert(result.size() == n);
        
        // Проверяем, что все вершины присутствуют
        std::vector<bool> visited(n + 1, false);
        for (int v : result) {
            assert(v >= 1 && v <= n);
            visited[v] = true;
        }
        for (int i = 1; i <= n; ++i) {
            assert(visited[i]);
        }
        
        std::cout << "Test 5 passed. All vertices present.\n";
    }
    
    // Тест 6: Граф с несколькими возможными топологическими сортировками
    {
        std::cout << "Test 6: Graph with multiple possible topological orders\n";
        int n = 5;
        std::vector<std::pair<int, int>> edges = {
            {1, 3},
            {1, 4},
            {2, 3},
            {2, 4},
            {3, 5},
            {4, 5}
        };
        
        std::vector<int> result;
        bool has_order = TopologicalSorter::Sort(n, edges, result);
        
        assert(has_order);
        assert(result.size() == n);
        
        std::vector<int> position(n + 1);
        for (size_t i = 0; i < result.size(); ++i) {
            position[result[i]] = i;
        }
        
        for (const auto& edge : edges) {
            assert(position[edge.first] < position[edge.second]);
        }
        
        std::cout << "Test 6 passed. Valid topological order found.\n";
    }
    
    // Тест 7: Цепочка из n вершин
    {
        std::cout << "Test 7: Chain of n vertices\n";
        int n = 10;
        std::vector<std::pair<int, int>> edges;
        for (int i = 1; i < n; ++i) {
            edges.push_back({i, i + 1});
        }
        
        std::vector<int> result;
        bool has_order = TopologicalSorter::Sort(n, edges, result);
        
        assert(has_order);
        assert(result.size() == n);
        
        // В цепочке должен быть ровно один правильный порядок: 1, 2, 3, ..., n
        for (int i = 0; i < n; ++i) {
            assert(result[i] == i + 1);
        }
        
        std::cout << "Test 7 passed. Chain correctly ordered.\n";
    }
    
    // Тест 8: Большой случайный граф без циклов
    {
        std::cout << "Test 8: Large random acyclic graph\n";
        int n = 100;
        std::vector<std::pair<int, int>> edges;
        
        // Создаем граф без циклов: ребра только от меньших вершин к большим
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rand() % 3 == 0) {  // Случайно добавляем ребра
                    edges.push_back({i, j});
                }
            }
        }
        
        std::vector<int> result;
        bool has_order = TopologicalSorter::Sort(n, edges, result);
        
        assert(has_order);
        assert(result.size() == n);
        
        std::vector<int> position(n + 1);
        for (size_t i = 0; i < result.size(); ++i) {
            position[result[i]] = i;
        }
        
        for (const auto& edge : edges) {
            assert(position[edge.first] < position[edge.second]);
        }
        
        std::cout << "Test 8 passed. Large graph processed correctly.\n";
    }
    
    // Тест 9: Граф с изолированными вершинами и компонентами
    {
        std::cout << "Test 9: Graph with isolated vertices\n";
        int n = 7;
        std::vector<std::pair<int, int>> edges = {
            {1, 2},
            {2, 3},
            {4, 5},
            // Вершины 6 и 7 изолированы
        };
        
        std::vector<int> result;
        bool has_order = TopologicalSorter::Sort(n, edges, result);
        
        assert(has_order);
        assert(result.size() == n);
        
        std::vector<int> position(n + 1);
        for (size_t i = 0; i < result.size(); ++i) {
            position[result[i]] = i;
        }
        
        for (const auto& edge : edges) {
            assert(position[edge.first] < position[edge.second]);
        }
        
        std::cout << "Test 9 passed. Graph with isolated vertices.\n";
    }
    
    // Тест 10: Граф со всеми возможными ребрами (транзитивное замыкание)
    {
        std::cout << "Test 10: Complete DAG\n";
        int n = 5;
        std::vector<std::pair<int, int>> edges;
        
        // Все ребра от меньших вершин к большим
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                edges.push_back({i, j});
            }
        }
        
        std::vector<int> result;
        bool has_order = TopologicalSorter::Sort(n, edges, result);
        
        assert(has_order);
        assert(result.size() == n);
        
        std::vector<int> position(n + 1);
        for (size_t i = 0; i < result.size(); ++i) {
            position[result[i]] = i;
        }
        
        // Проверяем, что порядок возрастающий (единственный возможный для полного DAG)
        for (int i = 0; i < n - 1; ++i) {
            assert(result[i] < result[i + 1]);
        }
        
        std::cout << "Test 10 passed. Complete DAG.\n";
    }
    
    // Тест 11: Граф с петлей (ребро из вершины в себя)
    {
        std::cout << "Test 11: Graph with self-loop (should be treated as cycle)\n";
        int n = 3;
        std::vector<std::pair<int, int>> edges = {
            {1, 2},
            {2, 2},  // Петля
            {2, 3}
        };
        
        std::vector<int> result;
        bool has_order = TopologicalSorter::Sort(n, edges, result);
        
        // Петля создает цикл, поэтому топологической сортировки не должно существовать
        assert(!has_order);
        std::cout << "Test 11 passed. Self-loop detected as cycle.\n";
    }
    
    // Тест 12: Граф с дублирующими ребрами
    {
        std::cout << "Test 12: Graph with duplicate edges\n";
        int n = 4;
        std::vector<std::pair<int, int>> edges = {
            {1, 2},
            {1, 2},  // Дубликат
            {2, 3},
            {1, 3},
            {3, 4},
            {2, 4}
        };
        
        std::vector<int> result;
        bool has_order = TopologicalSorter::Sort(n, edges, result);
        
        assert(has_order);
        assert(result.size() == n);
        
        std::vector<int> position(n + 1);
        for (size_t i = 0; i < result.size(); ++i) {
            position[result[i]] = i;
        }
        
        for (const auto& edge : edges) {
            assert(position[edge.first] < position[edge.second]);
        }
        
        std::cout << "Test 12 passed. Graph with duplicate edges.\n";
    }
    
    std::cout << "\nAll topological sort tests passed!\n";
}

int main() {
    TestTopologicalSort();
    return 0;
}