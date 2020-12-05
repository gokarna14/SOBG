#include <iostream>
#include "data_structures.hpp"
#include <math.h>

using namespace std;

int Graph::selectMinVertex(vector<float>& value, vector<bool>& processed, int V)
{
    int minimum = INT_MAX;
    float vertex;
    for (int i = 0; i < V; ++i)
    {
        if (processed[i] == false && value[i] < minimum)
        {
            vertex = i;
            minimum = value[i];
        }
    }
    return vertex;
}

void Graph::display()

{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            cout << adj_mat[i][j] << "\t";
        }
        cout << "\n\n";
    }
}