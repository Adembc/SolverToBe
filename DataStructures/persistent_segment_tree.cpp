#include <bits/stdc++.h>
using namespace std;
#define FAST ios::sync_with_stdio(0), cin.tie(0),cout.tie(0)
#define MP make_pair
#define PB push_back
#define all(x) x.begin(),x.end()
#define rep(i,n) for(ll i=0;i<n;i++)
#define repinv(i,n) for(ll i=n-1;i>-1;i--)
#define MOD 1000000007
#define endl '\n'
typedef long long ll;
struct Vertex {
    ll left, right;
    Vertex *left_child = nullptr, *right_child = nullptr;
    ll sum=0;
    Vertex(ll lb, ll rb, Vertex* left_child, Vertex *right_child ) {
        left = lb;
        right = rb;
        this->left_child=left_child;
        this->right_child=right_child;

    }

    void extend() {
        if (!left_child && left  < right) {
            ll t = (left + right) / 2;
            left_child = new Vertex(left, t);
            right_child = new Vertex(t+1, right);
        }
    }


    void add(ll k, ll x) {
        extend();
        if(left==right){
            sum=x;
            return;
        }
        else if (left_child) {
            if (k <= left_child->right)
                left_child->add(k, x);
            else
                right_child->add(k, x);

            sum=right_child->sum+left_child->sum;
        }
    }
    Vertex* update(Vertex* v, int tl, int tr,int pos,int new_val) {
        if (tl == tr)
            return new Vertex(new_val);
        int tm = (tl + tr) / 2;
        if (new_val<= tm)
            return new Vertex(tl, tr, update(v->l, tl, tm, pos, new_val), v->r);
        else
            return new Vertex(tl, tr, v->l,update(v->r, tm+1, tr, pos, new_val));
    }
    long long get(int i,int j) {
        if(left>=i&&right<=j)
            return sum;
        else if(right<i||left>j)
            return 0;
        else{
            extend();
            return left_child->get(i,j)+right_child->get(i,j);
        }




    }
};
int main(){

    ll n,q;
    cin>>n;
    Vertex *node= new Vertex(0,n-1);
    Vertex nodes[41];
    ll val;
    int t[100005];
    for(ll i=0;i<n;i++){
        cin>>t[i];
        node->add(t[i]-1,0);
    }
    nodes[0]=node;
    rep(i,n){
        nodes[i+1]=update(nodes[i],0, n-1,t[i-1],1);
    }
    return 0;

}
