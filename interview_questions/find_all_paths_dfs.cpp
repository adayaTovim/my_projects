// You get a list where each member specifies a node and the node connected to it.
// You must return all possible routes from head to tail.
// For example:
// input:[[a,b], [a,c], [b,d], [b,e], [d,f]]
// output should be: [[ac], [abe], [abdf]]

#include <vector>
#include <string>
#include <map>
#include <set>
#include <iostream>
#include <stack>

void fillGraph(const std::vector<std::pair<char,char>>& a_vec, std::map<char,std::set<char>>& a_graph)
{
    for(auto pair : a_vec) {
        char currNode = pair.first;
        char nextNode = pair.second;
        a_graph[currNode].insert(nextNode);
    }
    // for(auto i : a_graph) {
    //     std::cout<<i.first<<" - ";
    //     for(auto j : i.second) {
    //         std::cout<<j<<" ";
    //     }
    //     std::cout<<"\n";
    // }
    // std::cout<<"\n";
}

void findHeads(const std::map<char,std::set<char>>& a_graph, std::set<char>& a_heads)
{
    for(auto i : a_graph) {
        a_heads.insert(i.first);
    }

    for(auto i : a_graph) {
        for(auto j : i.second) {
            if(a_heads.find(j) != a_heads.end())
                a_heads.erase(j);
        }
    }
    // for(auto i : a_heads) {
    //     std::cout<<i<<" ";
    // }
    // std::cout<<"\n";

}

std::vector<std::string> findAllPaths(const std::vector<std::pair<char,char>>& a_vec)
{
    std::map<char,std::set<char>> graph;
    fillGraph(a_vec, graph);

    std::set<char> heads;
    findHeads(graph, heads);

    std::stack<char> stack;
    for(auto i: heads) {
        stack.push(i);
    }

    std::vector<std::string> paths;
    std::string currPath = "";
    std::set<char> visitedNode;

    while(!stack.empty()) {
        char curNode = stack.top();
        if(visitedNode.find(curNode) == visitedNode.end()) {
            visitedNode.insert(curNode);
            currPath += curNode;
            if(graph.find(curNode) == graph.end()) {
                paths.push_back(currPath);
                currPath.pop_back();
                stack.pop();
            } else {
                for(auto i : graph[curNode]) {
                    stack.push(i);
                }
            }
        } else {
            stack.pop();
            currPath.pop_back();
        }
    }
    return paths;
}

int main()
{
    std::vector<std::pair<char, char>> v = {std::make_pair('a', 'b'), std::make_pair('a', 'c'),
                                            std::make_pair('b', 'd'), std::make_pair('b', 'e'),
                                            std::make_pair('d', 'f')};

    std::vector<std::string> result = findAllPaths(v);

    for(auto i : result) {
        std::cout<<i<<"\n";
    }
    return 0;
}
