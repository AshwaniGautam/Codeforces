#include<bits/stdc++.h>
#define MAXN 3000000
using namespace std;

int N, arr[3000010], ST[3000010*4]   ;
long long int le[3000010], gr[3000010]  ;

set<int> myset  ;
unordered_map<int, int>mymap    ;

inline void update(int idx, int low, int high, int pos){

    if(idx < low || idx > high)
        return ;

    if(low == high){
        ST[pos] = 1;
        return ;
    }
    int mid = (low + high) / 2  ;
    update(idx, low, mid, 2*pos+1)  ;
    update(idx, mid+1, high, 2*pos+2);
    ST[pos] = ST[2*pos+1] + ST[2*pos+2] ;
}

inline int query(int i, int j, int low, int high, int pos){

    if(j < low || i > high)
        return 0    ;
    if(i <= low && high <= j)
        return ST[pos]  ;

    int mid = (low + high) / 2  ;
    return (query(i, j, low, mid, 2*pos+1)+query(i, j, mid+1, high, 2*pos+2))   ;
}

int main(){

    cin.sync_with_stdio(0)  ;
    cin >> N    ;
    for(int i = 0; i < N; i++){
        cin >> arr[i]   ;
        myset.insert(arr[i]);
    }
    int j = 0   ;
    for(auto i: myset){

        mymap[i] = j    ;
        j++ ;
    }
    for(int i = 0; i < N; i++)
        arr[i] = mymap[arr[i]]   ;

    for(int i = 0; i < N; i++){

        gr[i] = query(arr[i]+1, MAXN, 0, MAXN, 0)   ;
        update(arr[i], 0, MAXN, 0)  ;

    }
    memset(ST, 0, sizeof(ST))   ;
    for(int i = N-1; i >= 0; i--){

        le[i] = query(0, arr[i]-1, 0, MAXN, 0)  ;
        update(arr[i], 0, MAXN, 0)  ;

    }
    long long int ans = 0   ;
    for(int i = 0; i < N; i++)
        ans += le[i] * gr[i]    ;
    cout << ans << "\n" ;



    return 0    ;
}
