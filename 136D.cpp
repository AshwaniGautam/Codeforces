#include <bits/stdc++.h>

using namespace std;

struct node{
    int left, right, idx ;
};

int N, Q, BLOCK_SIZE, curr_answer    ;
int arr[100000] ;
node queries[100000]    ;
int answers[100000] ;
int frequency[100000]   ;

inline void add(int x){

    if(x > N)
        return;

    if (frequency[x] == x)
        curr_answer--   ;
    frequency[x]++  ;
    if(frequency[x] == x)
        curr_answer++   ;
}

inline void remove(int x){

    if(x > N)
        return ;

    if (frequency[x] == x)
        curr_answer--   ;
    frequency[x]--  ;
    if(frequency[x] == x)
        curr_answer++   ;

}

inline bool cmp(node x, node y){

    int x_block = x.left / BLOCK_SIZE   ;
    int y_block = y.left / BLOCK_SIZE   ;

    if(x_block != y_block)
        return x_block < y_block    ;
    return x.right < y.right    ;
}

int main(){
    cin.sync_with_stdio(false)  ;
    cin >> N >> Q   ;
    BLOCK_SIZE = static_cast<int>(sqrt(N))  ;

    for(int i = 0; i < N; i++)
        cin >> arr[i]   ;


    for(int i = 0; i < Q; i++){
        int u, v    ;
        cin >> u >> v   ;
        u--; v--;
        queries[i].left = u     ;
        queries[i].right = v    ;
        queries[i].idx = i  ;
    }
    sort(queries, queries + Q, cmp) ;

    int m_left = queries[0].left    ;
    int m_right = m_left -1 ;

    for(int i = 0; i < Q; i++){

        int left =  queries[i].left ;
        int right = queries[i].right    ;

        while(m_right < right){
            m_right++   ;
            add(arr[m_right])   ;
        }
        while(m_right > right){
            remove(arr[m_right])    ;
            m_right--   ;
        }
        while(m_left < left){
            remove(arr[m_left]) ;
            m_left++    ;
        }
        while(m_left > left){
            m_left--    ;
            add(arr[m_left])    ;
        }
        answers[queries[i].idx] =  curr_answer ;
    }
    for(int i = 0; i < Q; i++)
        cout << answers[i] << "\n"  ;
    return 0    ;
}
