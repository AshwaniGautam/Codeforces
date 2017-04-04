#include <bits/stdc++.h>

using namespace std;

int N, M, start[500001], ending[500001], tim    ;
vector<int> parent[500001], h[5000001], ans[500001]  ;
char arr[500001]  ;

inline void dfs(int node, int height){

    start[node] = ++tim;
    h[height].push_back(start[node]) ;
    ans[height].push_back(1 << (arr[node] - 'a') )    ;

    for(auto i : parent[node])
        dfs(i, height+1)    ;
    ending[node] = ++tim;
}

int main(){

    cin.sync_with_stdio(0)  ;
    cin >> N >> M   ;
    for(int i = 2; i <= N; i++){
        int temp    ;
        cin >> temp     ;
        parent[temp].push_back(i)   ;
    }

    for(int i = 1; i <= N; i++)
        cin >> arr[i]   ;
    dfs(1, 1);

    for(int i = 1; i < 500000; i++)
        for(int j = 1; j < ans[i].size(); j++)
            ans[i][j] ^= ans[i][j-1]    ;

    for(int i = 0; i < M; i++){
        int u, v    ;
        cin >> u >> v   ;
        auto lower = lower_bound(h[v].begin(), h[v].end(), start[u]) - h[v].begin()  ;
        auto upper = lower_bound(h[v].begin(), h[v].end(), ending[u]) - h[v].begin()  ;

        int decide  ;

        if(upper == 0)
            decide = 0  ;
        else if(lower == 0)
            decide = ans[v][upper-1]    ;
        else
            decide = ans[v][upper-1]^ans[v][lower-1]    ;
        if(__builtin_popcount(decide) <= 1)
            cout << "Yes\n"   ;
        else
            cout << "No\n"    ;
    }
    return  0;
}
