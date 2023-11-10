#include <iostream>
#include <regex>
#include <vector>
#include "AdjacencyList.h"
using namespace std;

int main(){
    string no_of_lines, power_iterations;
    AdjacencyList graph;
    string from, to;
    cin >> no_of_lines;
    cin >> power_iterations;
    for(int i = 0;i < stoi(no_of_lines); i++)
    {
        cin >> from;
        cin >> to;
        graph.AddLink(from, to);
    }
    //Create a graph object
    graph.PageRank(stoi(power_iterations));

    return 0;
}