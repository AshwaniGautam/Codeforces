#include <bits/stdc++.h>

using namespace std;

struct node{
    int left, right, idx, k ;
}   ;

int N, Q, BLOCK_SIZE, pos    ;
int color[100001], starting[100001], ending[100010], tour[100010], cnt[100010], above[100010], answers[100010]   ;
vector<int>adj[100001]  ;
node queries[100010]    ;

inline void add(int x){

    above[cnt[x]]++ ;
    cnt[x]++    ;
}

inline void remove(int x){

    cnt[x]--    ;
    above[cnt[x]]-- ;

}

inline bool cmp(node x, node y){

    int x_block = x.left / BLOCK_SIZE    ;
    int y_block = y.left / BLOCK_SIZE    ;
    if(x_block != y_block)
        return x_block < y_block    ;
    return x.right < y.right    ;
}

inline void ETT(int v, int pv){

    tour[pos] = v   ;
    starting[v] = pos++ ;

    for(auto i : adj[v])
        if(i != pv)
            ETT(i, v)   ;
    ending[v] = pos-1   ;
}

int main(){

    cin.sync_with_stdio(0)  ;
    cin >> N >> Q   ;
    BLOCK_SIZE = static_cast<int>(sqrt(N))  ;

    for(int i = 1; i <= N; i++)
        cin >> color[i] ;

    for(int i = 0; i < N-1; i++){

        int u, v    ;
        cin >> u >> v   ;
        adj[u].push_back(v) ;
        adj[v].push_back(u) ;
    }

    ETT(1, 0)   ;
    for(int i = 0; i < Q; i++){

        int u, x    ;
        cin >> u >> x   ;
        queries[i].left = starting[u]    ;
        queries[i].right = ending[u]    ;
        queries[i].k = x    ;
        queries[i].idx = i  ;
    }
    sort(queries, queries+Q, cmp)   ;

    int m_left = queries[0].left    ;
    int m_right = m_left - 1    ;

    for(int i = 0; i < Q; i++){

        int l = queries[i].left  ;
        int r = queries[i].right ;

        while(m_right < r){
            m_right++   ;
            add(color[tour[m_right]]) ;
        }
        while(m_right > r){
            remove(color[tour[m_right]])    ;
            m_right--   ;
        }
        while(m_left < l){
            remove(color[tour[m_left]]) ;
            m_left++    ;
        }
        while(m_left > l){
            m_left--    ;
            add(color[tour[m_left]])   ;
        }
        answers[queries[i].idx] = above[queries[i].k - 1]  ;
    }
    for(int i = 0; i < Q; i++)
        cout << answers[i] << "\n"  ;
    return 0    ;
}
