#include<bits/stdc++.h>
using namespace std;
struct Vertex {
    int left, right;
    long long sum = 0;
    Vertex *left_child = nullptr, *right_child = nullptr;

    Vertex(int lb, int rb) {
        left = lb;
        right = rb;
    }

    void extend() {
        if (!left_child && left  < right) {
            int t = (left + right) / 2;
            left_child = new Vertex(left, t);
            right_child = new Vertex(t+1, right);
        }
    }

    void add(int k, int x) {
        extend();
        if(left==right)
            sum=x;
        else if (left_child) {
            if (k <= left_child->right)
                left_child->add(k, x);
            else
                right_child->add(k, x);

            sum=left_child->sum+right_child->sum;
        }
    }

    long long get_sum(int lq, int rq) {
        if (lq <= left && right <= rq)
            return sum;
        if (left>rq||right<lq)
            return 0;
        extend();
        return left_child->get_sum(lq, rq) + right_child->get_sum(lq, rq);
    }
};
int main(){

    int n,q;
    cin>>n>>q;
    Vertex *node= new Vertex(0,n-1);
    int val;
    for(int i=0;i<n;i++){
        cin>>val;
        node->add(i,val);
    }

    int type,a,b;
    while(q--){
        cin>>type>>a>>b;
        if(type==1)
            node->add(a,b);
        else
            cout<<node->get_sum(a,b-1)<<endl;


    }
    return 0;

}
