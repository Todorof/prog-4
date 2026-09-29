#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Edge {
    int from, to ;
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        edges.push_back({a, b});
    }

    int start;
    cin >> start;

    vector<bool> visited(n, false);
    queue<int> q;

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int x = q.front();
        q.pop();

        cout << x << " ";

        for (int i = 0; i < m; i++) {
            int next = -1;

            if (edges[i].from == x)
                next = edges[i].to;
            else if (edges[i].to == x)
                next = edges[i].from;

            if (next != -1 && !visited[next]) {
                visited[next] = true;
                q.push(next);
            }
        }
    }

    cout << endl;

    return 0;
}
