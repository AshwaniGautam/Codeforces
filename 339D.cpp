#include <bits/stdc++.h>

using namespace std;

struct node{

    int flag, ans ;

}   ;

int N, Q;
int arr[1<<17]  ;
node ST[1 << 19]    ;

inline void combine(int pos){

    if(ST[2*pos+1].flag == -1){
        ST[pos].ans = ST[2*pos+1].ans | ST[2*pos+2].ans ;
        ST[pos].flag = 1    ;
    }
    else{
        ST[pos].ans = ST[2*pos+1].ans ^ ST[2*pos+2].ans ;
        ST[pos].flag = -1   ;

    }
}

inline void build(int low, int high, int pos){

    if(low == high){

        ST[pos].ans = arr[low]  ;
        ST[pos].flag = -1   ;
        return ;
    }

    int mid = (low + high) / 2  ;
    build(low, mid, 2*pos+1)    ;
    build(mid+1, high, 2*pos+2) ;
    combine(pos)    ;
}

inline void update(int idx, int low, int high, int pos, int value){

    if(idx < low || idx > high)
        return ;
    if(low == high){
        ST[pos].ans = value ;
        return ;
    }

    int mid = (low + high) / 2  ;
    update(idx, low, mid, 2*pos+1, value)   ;
    update(idx, mid+1, high, 2*pos+2, value)    ;
    combine(pos)    ;
}

inline void wow(){

    for(int i = 0; i < 8; i++)
        cout << ST[i].ans << " "    ;
    cout << endl;
}

int main(){

    cin.sync_with_stdio(0)  ;
    cin >> N >> Q   ;
    for(int i = 0; i < 1 << N; i++)
        cin >> arr[i]   ;

    build(0, (1 << N)-1, 0)    ;
    for(int i = 0; i < Q; i++){
        int u, v    ;
        cin >> u >> v    ;
        u--;
        update(u, 0, (1 << N)-1, 0, v) ;
        cout << ST[0].ans << "\n"   ;
    }
    return 0    ;
}
