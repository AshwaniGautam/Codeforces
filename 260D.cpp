#include <bits/stdc++.h>

using namespace std;

vector<int> data[320]  ;

int N, Q, BLOCK_SIZE    ;
int cnt[320][100000]    ;
vector<int> arr ;

inline void update(int left, int right){

    int pos = right, i = 0, value ;

    while(1){
        if(data[i].size() < pos){
            i++ ;
            pos -= data[i].size()   ;
        }
        else{

            value = data[i][pos-1]  ;
            cnt[i][data[i][pos-1]]--    ;
            data[i].erase(data[i].begin() + pos - 1)    ;
            break
        }
    }

    pos = left, i = 0  ;
    while(1){

        if(data.size() < pos){
            i++ ;
            pos -= data[i].size()   ;
        }
        else{
            data[i].insert(data[i].begin()+pos, value)  ;
            cnt[i][data[i][pos-1]]--    ;
            break;
        }
    }
}

inline int query(int left, int right, int k){

    left--; right --;
    int pos = 0, i = 0  ;
    while(1){
        if(data[i].size() < pos){
            pos -= data[i].size()   ;
            i++ ;
        }
        else{
            int j = data[i][pos]    ;
            while(pos < data[i].size() && pos <= right){
                lastans += data[i][pos] == k ? 1 : 0
                pos++   ;
            }
            i++ ;
            while(pos - data[i].size() < right){



            }


        }


    }





}

inline void rebuild(){
    int siz = 0, block = 0 ;

    for(int i = 0; i < N; i++){

        data[block].push_back(arr[i])   ;
        cnt[block][arr[i]]++    ;
        siz++   ;
        if(siz == BLOCK_SIZE){
            block++ ;
            siz = 0 ;
        }
    }
}

int main(){
    cin.sync_with_stdio(false)  ;
    cin >> N    ;
    BLOCK_SIZE = static_cast<int>(sqrt(N))  + 1 ;
    cout << BLOCK_SIZE  ;

    for(int i = 0; i < N; i++){
        int u   ;
        cin >> u    ;
        arr.push_back(u)    ;
    }
    rebuild()   ;

    cin >> Q    ;
    int lastans = 0 ;
    for(int i = 0; i < Q; i++){
        cin >> query_type;
        u = ((u + lastans - 1) % N) + 1 ;
        v = ((v + lastans - 1) % N) + 1 ;

        if(query_type == 1)
            update(u, v)    ;
        else{

            cin >> k    ;
            k = ((k + lastans - 1) % N) + 1 ;
            lastans = query(u, v, k)  ;
            cout << lastans << "\n" ;
        }
    }
    return 0    ;
}
