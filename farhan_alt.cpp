#include <bits/stdc++.h>
#define MOD 1000000007
#define MAXN 100000
#define LOGN 18
#define LOGMX 62

using namespace std;
typedef long long ll;


int n,q;
ll k;
ll ara[MAXN+5];
vector<int>grf[MAXN+5];
int immpar[MAXN+5];
int par[MAXN+5][LOGN];
int ht[MAXN+5];
pair<int,int> rng[MAXN+5];
int id;

void dfs(int node,int prv,int h) {
    ht[node]=h;
    rng[node].first=id;
    id++;

    for(int i=0;i<grf[node].size();i++) {
        int now=grf[node][i];
        if(now==prv) {
            continue;
        }
        immpar[now]=node;
        dfs(now,node,h+1);
    }

    rng[node].second=id-1;
}

 
void buildSparseforLCA(){
    for(int i=1;i<=n;i++) par[i][0]=immpar[i];
    for(int j=1;j<LOGN;j++){
        for(int i=1;i<=n; i++) {
            par[i][j]=par[par[i][j-1]][j-1];
        } 
    }
}
 
int LCA(int u,int v) {
    if(ht[u]>ht[v]) {
        swap(u,v);
    }

    int d=ht[v]-ht[u];

    for(int i=0;i<LOGN;i++) {
        if(d&(1<<i)) {
            v=par[v][i];
        }
    }

    if(u==v) {
        return u;
    }


    for(int i=LOGN-1;i>=0;i--) {
        if(par[u][i]!=par[v][i]) {
            u=par[u][i];
            v=par[v][i];
        }
    }

    return par[u][0];
}



ll bit[MAXN+5];

void update(int x,ll val)
{
    for(int i=x;i<=n;i+=(i&-i)) {
        bit[i]+=val;
        bit[i]%=MOD;
    }
}
ll query(int x)
{
    ll ret=0;
    for(int i=x;i>0;i-=(i&-i)) {
        ret+=bit[i];
        ret%=MOD;
    }
    return ret;
}
void buildBIT() {
    for(int i=1;i<=n;i++) {
        int l=rng[i].first;
        int r=rng[i].second;
        update(l,ara[i]);
        update(r+1,-ara[i]);
    }
}


ll dist(int u,int v) {
    int lca=LCA(u,v);
    ll du=query(rng[u].first);
    ll dv=query(rng[v].first);
    ll dlca=query(rng[lca].first);
    ll val=du+dv;val%=MOD;
    val-=2*dlca;val%=MOD;
    val+=ara[lca];val%=MOD;
    val=val+MOD;val%=MOD;
    return val;
}





struct Matrix{
    int len; 
    vector<vector<ll> >mat;
    Matrix()
    {
        len=3;
        for(int i=0;i<len;i++)    {
            vector<ll>tmp;
            for(int j=0;j<len;j++)    tmp.push_back(0);
            mat.push_back(tmp);
        }
    }
    Matrix(int l)
    {
        len=l;
        for(int i=0;i<len;i++)    {
            vector<ll>tmp;
            for(int j=0;j<len;j++)    tmp.push_back(0);
            mat.push_back(tmp);
        }
    }
    void setToUnitMatrix()
    {
        for(int i=0;i<len;i++)    {
            mat[i][i]=1;
        }
    }
    void setToRecurrence() {
        mat[0][0]=k;
        mat[0][2]=k-2;
        mat[1][0]=1;
        mat[2][1]=1;
    }
};

void MatMult(Matrix& A, Matrix& B)
{
    int dim=A.len;
    Matrix tmp(dim);
   
 
    for(int i=0;i<dim;i++)    {
        for(int j=0;j<dim;j++)    {
            for(int k=0;k<dim;k++)    {
                tmp.mat[i][j]+=A.mat[i][k]*B.mat[k][j];
                tmp.mat[i][j]%=MOD;
            }
        }
    }
 
    for(int i=0;i<dim;i++)    {
        for(int j=0;j<dim;j++)    {
            A.mat[i][j]=tmp.mat[i][j];
        }
    }
}

Matrix mtmp[LOGMX+2];

void prepMatExp() {
    
    Matrix X=Matrix(3);
    X.setToRecurrence();

    for(int i=0;i<LOGMX;i++) {
        mtmp[i]=X;
        MatMult(X,X);
    }
}

ll calcX(ll x) {
    if(x==1) {
        return 1;
    } else if(x==2) {
        return 2;
    } else if(x==3) {
        return 5;
    } else {

        x-=3;
        ll f1,f2,f3;
        f3=5;f2=2;f1=1;

        for(int i=0;i<LOGMX;i++) {
            if(x&(1LL<<i)) {
                Matrix now=mtmp[i];
                ll nf3=(((f3*now.mat[0][0])%MOD+(f2*now.mat[0][1])%MOD)%MOD+(f1*now.mat[0][2])%MOD)%MOD;
                ll nf2=(((f3*now.mat[1][0])%MOD+(f2*now.mat[1][1])%MOD)%MOD+(f1*now.mat[1][2])%MOD)%MOD;
                ll nf1=(((f3*now.mat[2][0])%MOD+(f2*now.mat[2][1])%MOD)%MOD+(f1*now.mat[2][2])%MOD)%MOD;
                f3=nf3;f2=nf2;f1=nf1;
            }
        }

        return f3;
    }
    
}





int main() {

    //freopen("testcases.txt","r",stdin);

    scanf("%d %d %lld",&n,&q,&k);
    prepMatExp();


    for(int i=1;i<=n;i++) {
        scanf("%lld",&ara[i]);
        ara[i]=calcX(ara[i]);
    }


    for(int i=0;i<n-1;i++) {
        int u,v;
        scanf("%d %d",&u,&v);
        grf[u].push_back(v);
        grf[v].push_back(u);
    }

    id=1;
    dfs(1,0,0);
    buildSparseforLCA();
    buildBIT();
    

    while(q--) {

        int cmd;
        scanf("%d",&cmd);

        if(cmd==1) {
            int u,v;
            scanf("%d %d",&u,&v);
            printf("%lld\n",dist(u,v));
        } else {
            int u;
            ll x;
            scanf("%d %lld",&u,&x);
            x=calcX(x);
            int l=rng[u].first;
            int r=rng[u].second;
            ll def=x-ara[u];
            ara[u]=x;
            def%=MOD;
            update(l,def);
            update(r+1,-def);
        }

    }

    return 0;

}