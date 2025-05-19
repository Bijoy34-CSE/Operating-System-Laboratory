#include <iostream>
#include <vector>
using namespace std;

bool dfs(int node, vector<vector<int>> &graph, vector<bool> &visited, vector<bool> &recStack, vector<int> &path) {
    visited[node] = true;
    recStack[node] = true;
    path.push_back(node);

    for (int i = 0; i < graph.size(); ++i) {
        if (graph[node][i]) {
            if (!visited[i]) {
                if (dfs(i, graph, visited, recStack, path))
                    return true;
            } else if (recStack[i]) {
                path.push_back(i); // cycle start
                return true;
            }
        }
    }

    recStack[node] = false;
    path.pop_back();
    return false;
}

bool detectDeadlock(vector<vector<int>> &graph) {
    int n = graph.size();
    vector<bool> visited(n, false), recStack(n, false);
    vector<int> path;

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            if (dfs(i, graph, visited, recStack, path)) {
                cout << "Deadlock detected! Cycle: ";
                for (int j = 0; j < path.size(); ++j) {
                    cout << "P" << path[j];
                    if (j < path.size() - 1) cout << " -> ";
                }
                cout << endl;
                return true;
            }
        }
    }
    return false;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<vector<int>> waitGraph(n, vector<int>(n));
    cout << "Enter Wait-For Graph Matrix (1 if Pi waits for Pj, else 0):\n";
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
            cin >> waitGraph[i][j];
    }

    if (!detectDeadlock(waitGraph))
        cout << "No deadlock detected.\n";

    return 0;
}
