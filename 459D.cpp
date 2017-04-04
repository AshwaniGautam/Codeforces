#include <bits/stdc++.h>

using namespace std;

int N, prefix[1000010], suffix[1000010], left_frequency[1000010], right_frequency[1000010], arr[1000010]   ;
set<int> myset  ;
unordered_map<int, int> mymap   ;
vector<int> ST[4000010] ;

inline void build(int low, int high, int pos){

    if(low == high){
        ST[pos].push_back(suffix[low]) ;
        return ;
    }
    int mid = (low + high) / 2  ;
    build(low, mid, 2*pos+1)    ;
    build(mid+1, high, 2*pos+2) ;

    merge(ST[2*pos+1].begin(), ST[2*pos+1].end(), ST[2*pos+2].begin(), ST[2*pos+2].end(), back_inserter(ST[pos]))   ;

}

inline int query(int i, int j, int low, int high, int pos, int k){

    if(j < low || i > high)
        return 0    ;
    if(i <= low && high <= j)
        return lower_bound(ST[pos].begin(), ST[pos].end(), k) - ST[pos].begin() ;
    int mid = (low + high) / 2  ;
    return query(i, j, low, mid, 2*pos+1, k) + query(i, j, mid+1, high, 2*pos+2, k)  ;
}

int main(){

    cin.sync_with_stdio(0)  ;
    cin >> N    ;

    for(int i = 0; i < N; i++){
        cin >> arr[i]  ;
        myset.insert(arr[i])    ;
    }

    int j = 0   ;
    for(auto i : myset){

        mymap[i] = j    ;
        j++ ;
    }

    for(int i = 0; i < N; i++)
        arr[i] = mymap[arr[i]]  ;

    for(int i = 0; i < N; i++){

        left_frequency[arr[i]]++    ;
        prefix[i] = left_frequency[arr[i]]    ;

    }

    for(int i = N-1; i >= 0; i--){

        right_frequency[arr[i]]++ ;
        suffix[i] = right_frequency[arr[i]]  ;
    }

    build(0, N-1, 0)    ;

    long long int ans = 0   ;

    for(int i = 0; i < N; i++)
        ans+= query(i+1, N-1, 0, N-1, 0, prefix[i])   ;
    cout << ans << "\n" ;
    return 0    ;
}
