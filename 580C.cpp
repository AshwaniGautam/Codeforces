#include <bits/stdc++.h>

using namespace std;

int N, M, cats[200001], answer    ;
vector <int> adj[200001]    ;

inline void dfs(int v, int pv, int consecutive){

    if (cats[v])
        consecutive++   ;
    else
        consecutive = 0 ;

    if(consecutive > M)
        return ;

    for(auto i : adj[v])
        if(i != pv)
            dfs(i, v, consecutive) ;

    if(adj[v].size() == 1 and consecutive <= M and v > 1)
        answer++    ;
}


int main(){

    cin.sync_with_stdio(0)  ;
    cin >> N >> M   ;
    for(int i = 1; i <= N; i++)
        cin >> cats[i]  ;
    for(int i = 0; i < N-1; i++){
        int u, v    ;
        cin >> u >> v  ;
        adj[u].push_back(v) ;
        adj[v].push_back(u) ;
    }
    dfs(1, 0, 0)   ;
    cout << answer << "\n"  ;
    return 0    ;
}
