#include <map>
#include <vector>
#include <cstring>
#include <iostream>
#include <cstring>
#include<sstream>

using namespace std;

// Change this file as you want or add more files
vector<int> ids;        //是否可以放在函数内部？

class Vocabulary
{
private:
    // Choose a proper container from STL.
    map<string,int> mymap;
    int size_num=0;
public:
    vector<int> insertSentReturnIds(string sentence){
        ids.clear();
        int flag=-1;
        for(int i=0;i<=sentence.length();++i){
            if(i==sentence.length()||sentence.at(i)==32){
                char tmp[50];
                memset(tmp,0,sizeof(tmp));
                sentence.copy(tmp,i-flag-1,flag+1);
                if(mymap.find(tmp)==mymap.end()){
                    mymap[tmp]=++size_num;
                    ids.push_back(size_num);
                }
                else{
                    ids.push_back(mymap.find(tmp)->second);
                }
                flag=i;
            }
        }
        return ids;
        //Enter your code here.
        //This function should build vocabulary and at the same time return a sentence encoding.
    }
};


class DataLoader{
private:
    vector<int> _rand_order;
    int batch_size=0;
    //Enter your code here
    vector<int> total_data[1001];
    vector<int> ordered[1001];
    vector<vector<int>> batch[500];
    int total_num=0;
    int batch_num=0;
public:
    friend struct Iterator;
    void setBatchSize(int N){
        this->batch_size = N; // can also change
        batch_num=0;
        for(int i=0;i<500;++i)  batch[i].clear();
        for(int i=0;i<total_num;i+=N){
            int max_size=0;
            for(int j=i;j<i+N&&j<total_num;++j){
                if(ordered[j].size()>max_size)  max_size=ordered[j].size();
            }
            for(int j=i;j<i+N&&j<total_num;++j){
                for(int k=ordered[j].size();k<max_size;++k){
                    ordered[j].push_back(0);
                }
            }
            for(int j=i;j<i+N&&j<total_num;++j){
                batch[batch_num].push_back(ordered[j]);
            }
            batch_num++;
        }
    }

    void setOrder(vector<int>& x){
        _rand_order = x; // can also change
        int j=0;
        for(int i=0;i<1001;++i) ordered[i].clear();
        for(auto i:x){
            ordered[j++].assign(total_data[i].begin(),total_data[i].end());
        }
    }

    void addData(vector<int> sent_encoding){
        total_data[total_num++].assign(sent_encoding.begin(),sent_encoding.end());
        //Enter you code here;
    }

    struct Iterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        // Add more using statement here
        // hint: using value_type = ?
        //       using reference = ?
        using value_type=vector<vector<int>>;
        using reference=vector<vector<int>>&;
        using pointer=vector<vector<int>>*;
        //Define your constructor and functions that are needed for a Iterator.
        Iterator(vector<vector<int>> *_p):p(_p){};

        vector<vector<int>> operator*(){
            return *p;
        }
        
        bool operator!=(Iterator m){
            if(this->p==m.p)  return false;
            else return true;
        };
        
        Iterator operator++(){
            return Iterator(++this->p);
        };
        private:
        // Add what where variable you want here to make the Iterator functional.
        vector<vector<int>> *p;
    };
    
    Iterator begin() {
        return Iterator(batch);
        //Enter your code here.
    }
    Iterator end() {
        return Iterator(batch+batch_num);
        //Enter your code here.
    }
};






