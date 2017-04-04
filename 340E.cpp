#include <bits/stdc++.h>

using namespace std;

struct node{
    long long int left, right, idx    ;
};

long long int N, Q, K, curr_answer, BLOCK_SIZE ;
long long int pref[100000]    ;
node queries[100001]    ;
long long int answers[100001] ;
long long int arr[100002] ;
long long int check[100000]   ;

inline bool cmp(node x, node y){

    int x_block = x.left / BLOCK_SIZE;
    int y_block = y.left / BLOCK_SIZE;

    if(x_block != y_block)
        return x_block < y_block   ;
    return x.right < y.right    ;
}

inline void add(long long int x){

    long long int req = x ^ K ;
    curr_answer += check[req]   ;
    //cout << req << " searchong " <<check[req]<< endl ;
    check[x]++  ;

}

inline void remove(long long int x){


    long long int req = x ^ K ;
    curr_answer -= check[req]   ;
    //cout << req << " searchong " <<check[req]<< endl ;
    check[x]--  ;

}

inline void wow(){

    for(int i = 0; i < 4; i++)
        cout << check[i] << " "     ;
    cout << endl;
}

int main(){

    cin.sync_with_stdio(false)  ;
    cin >> N >> Q >> K  ;
    BLOCK_SIZE = static_cast<int>(sqrt(N))  ;
    for(int i = 1; i <= N; i++){
        cin >> arr[i]   ;
        pref[i] = pref[i-1]^arr[i]   ;
    }

    for(int i = 0; i < Q; i++){
        int u, v    ;
        cin >> u >> v   ;
        u--;
        queries[i].left = u ;
        queries[i].right = v    ;
        queries[i].idx = i  ;
    }

    //cout << BLOCK_SIZE << "hahah" << endl;
    sort(queries, queries + Q, cmp)  ;


    int m_left = queries[0].left;
    int m_right = m_left - 1    ;

    for(int i = 0; i < Q; i++){

        int left = queries[i].left;
        int right = queries[i].right    ;
        //cout << left << right << endl;

      //  wow()   ;

        while(m_right < right){
            m_right++ ;
            add(pref[m_right])   ;
        }
        while(m_right > right){
            remove(pref[m_right])    ;
            m_right--   ;
        }
        while(m_left > left){
            m_left--    ;
            add(pref[m_left])    ;
        }
        while(m_left < left){
            remove(pref[m_left]) ;
            m_left++    ;
        }
      //  cout << curr_answer ;
        answers[queries[i].idx] = curr_answer   ;
    }
    for(int i = 0; i < Q; i++)
        cout << answers[i] << "\n"  ;
    return  0;
}
