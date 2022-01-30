#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
using namespace std;
typedef long long ll;
ll mx,test[8]={2,3,5,7,11,13,82,373},re[105];
/*
ll mul(ll a,ll b,ll mod){
	ll sum=0;
	while(b){
		if(b&1ll) sum=(sum+a)%mod;
		a=(a<<1)%mod,b>>=1;
	}
	return sum;
}
*/
ll mul(ll a,ll b,ll mod){
	return (__int128)a*b%mod;
}
ll qpow(ll a,ll b,ll mod){
	ll sum=1;
	while(b){
		if(b&1ll) sum=mul(sum,a,mod);
		a=mul(a,a,mod),b>>=1;
	}
	return sum;
}
inline bool Miller_Rabin(ll n){
	if(n==2|n==3||n==5) return 1;
	if(n<2) return 0;
	if(n%6!=1&&n%6!=5) return 0;
	int tm=0;
	ll u=n-1;
	while((u&1)==0) tm++,u>>=1;
	for(int T=0;T<8;T++){
		ll a=test[T]%(n-2)+2;
		re[0]=qpow(a,u,n);
		for(int i=1;i<=tm;i++){
			re[i]=mul(re[i-1],re[i-1],n);
			if(re[i]==1&&re[i-1]!=1&&re[i-1]!=n-1) return 0;
		}
		if(re[tm]!=1) return 0;
	}
	return 1;
}
ll gcd(ll a,ll b){
	if(!b) return a;
	return gcd(b,a%b);
}
inline ll Abs(ll x){return x>=0?x:-x;}
ll pollard_rho(ll n){
	if(n%2==0) return 2;
	if(n%3==0) return 3;
	ll x=0,y=0,g=1,lc=1,c=(rand()%99+3);
	for(int k=2;;k<<=1,y=x,lc=1){
		for(int i=1;i<=k;i++){
			x=mul(x,x,n)+c,x-=(x>=n?n:0);
			lc=mul(lc,Abs(y-x),n);
			if((i&127)==0){
				g=gcd(lc,n);
				if(g>1) return g;
			}
		}
		if(g>1||(g=gcd(lc,n))>1) return g;
	}
	return g;
}
void find(ll x){
//	if(x==1) return;
	if(x<=mx) return;
	if(Miller_Rabin(x)){
		mx=max(mx,x);
		return;
	}
	ll y=x;
	while(y==x) y=pollard_rho(x);
	while(x%y==0) x/=y;
	find(y);find(x);
}
int main(){
	srand(time(0));
	int T;
//	clock_t start,end;
	scanf("%d",&T);
//	start=clock();
	while(T--){
		ll n;
		mx=0;
		scanf("%lld",&n);
		find(n);
		if(mx==n) puts("Prime");
		else printf("%lld\n",mx);
	}
//	end=clock();
//	cout<<end-start;
	return 0;
}
