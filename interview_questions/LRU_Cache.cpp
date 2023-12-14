// Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

// Implement the LRUCache class:

// LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
// int get(int key) Return the value of the key if the key exists, otherwise return -1.
// void put(int key, int value) Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.
// The functions get and put must each run in O(1) average time complexity.



// Example 1:

// Input
// ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
// [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
// Output
// [null, null, null, 1, null, -1, null, -1, 3, 4]

// Explanation
// LRUCache lRUCache = new LRUCache(2);
// lRUCache.put(1, 1); // cache is {1=1}
// lRUCache.put(2, 2); // cache is {1=1, 2=2}
// lRUCache.get(1);    // return 1
// lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
// lRUCache.get(2);    // returns -1 (not found)
// lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
// lRUCache.get(1);    // return -1 (not found)
// lRUCache.get(3);    // return 3
// lRUCache.get(4);    // return 4

#include <iostream>
#include <unordered_map>
#include <list>

class LRUCache {
private:
    std::unordered_map<int, std::pair<int, std::list<int>::iterator>> m_cache;
    //std::list<int>::iterator: This part of the pair is an iterator from the linked list m_cacheOrder
    //which keeps track of the order in which keys were accessed.

    std::list<int> m_cacheOrder;
    size_t m_capacity;

public:
    LRUCache(int capacity) : m_capacity(capacity) {}

    int get(int key) {
        if (m_cache.find(key) == m_cache.end()) {
            return -1;
        }

        int value = m_cache[key].first;
        m_cacheOrder.erase(m_cache[key].second);
        m_cacheOrder.push_front(key);
        m_cache[key].second = m_cacheOrder.begin();

        return value;
    }

    void put(int key, int value) {
        if (m_cache.find(key) != m_cache.end()) {
            m_cacheOrder.erase(m_cache[key].second);
        } else if (m_cache.size() >= m_capacity) {
            int keyToRemove = m_cacheOrder.back();
            m_cacheOrder.pop_back();
            m_cache.erase(keyToRemove);
        }

        m_cacheOrder.push_front(key);
        m_cache[key] = {value, m_cacheOrder.begin()};
    }
};

int main() {
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    std::cout << cache.get(1) << std::endl; // Output: 1
    cache.put(3, 3);
    std::cout << cache.get(2) << std::endl; // Output: -1
    cache.put(4, 4);
    std::cout << cache.get(1) << std::endl; // Output: -1
    std::cout << cache.get(3) << std::endl; // Output: 3
    std::cout << cache.get(4) << std::endl; // Output: 4
    return 0;
}
