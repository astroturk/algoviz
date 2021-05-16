#include <bits/stdc++.h>
#include <iostream>
using namespace std;

string code;
string var;

class V{
    private:
    vector<int> v;
    int sz=0;

    public:
    V(){
        code+="var v = jsav.ds.array([]);";
        var+="\"v\",";
    }
    V(int n,int val){
        code+="var v = jsav.ds.array([]);";
        var+="\"v\",";
        sz = n;
        v.assign(n,val);
         for(int i = 0;i<sz;i++){
            code+="v.value("+to_string(i)+","+to_string(val)+");";
        }
    }
    void push_back(int val){
        v.push_back(val);
        code+="v.value("+to_string(sz)+","+to_string(val)+");";
        sz++;
    }
    void pop_back(){
        v.pop_back();
        code+="v.value("+to_string(sz-1)+","+"''"+");";
        sz--;
    }
    int size(){
        sz = v.size();
        return sz;
    }
    int get(int ind){
        return v[ind];
    }
    void set(int ind,int val){
        v[ind] = val;
        code+="v.value("+to_string(ind)+","+to_string(val)+");";
    }
    void sort_V(int l,int r){
        sort(v.begin()+l,v.begin()+r);
        for(int i = 0;i<r;i++){
            code+="v.value("+to_string(i)+","+to_string(v[i])+");";
        }
    }
    void assign(int n,int val){
        sz = n;
        v.assign(n,val);
         for(int i = 0;i<sz;i++){
            code+="v.value("+to_string(i)+","+to_string(val)+");";
        }
    }
    void swap_V(int i,int j){
        swap(v[i],v[j]);
        code+="v.swap("+to_string(i)+","+to_string(j)+");";
    }
    
};

void start(){
}
void end(){
	var.pop_back();
    cout<<"{\"code\":\"";
    cout<<code;
    cout<<"\",\"var\":[";
    cout<<var;
    cout<<"]}";
}
void viz(){
    code+="jsav.step();";
}

int main(){
    start();
    V a;
    a.push_back(3);
    a.push_back(8);
    a.push_back(4);
    a.push_back(6);
    a.push_back(5);
    a.push_back(7);
    viz();
    a.sort_V(0,a.size());
    viz();
    int sz = a.size();
    a.set(0,1);
    for(int i=0;i<=(sz-1)/2;i++){
        a.swap_V(i,sz-i-1);
        viz();
    }
    end();
}