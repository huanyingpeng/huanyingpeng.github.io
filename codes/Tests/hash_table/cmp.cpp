#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#define y1 y3647
#define INF 1000000000
#define LL long long
#define pii pair<int,int>
using namespace std;
template<typename T>
inline int read(T &x){
	x=0;int f=1;char ch=getchar();
	while(ch!=45&&(ch<'0'||ch>'9'))ch=getchar();
	if(ch==45){f=-1,ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*=f;
}
template<typename T1,typename T2>void cmin(T1 &a,const T2 &b){if(a>b)a=b;}
template<typename T1,typename T2>void cmax(T1 &a,const T2 &b){if(a<b)a=b;}
const int N=1e6+10,M=1e7+10;
LL a[M*4],b[M*4];
int n,m,i;
mt19937 mt_rand(time(NULL));
template<typename H>
class Hash_Table_Test{
	public:
	H mp;
	string name;
	int im,fm,cr;
	LL ans=0;
	Hash_Table_Test(string _name,int insert_method=0,int find_method=0,int cross=0){
		name=_name;
		im=insert_method,fm=find_method,cr=cross;
	}
	void insert(){
		if(im==0){
			for(int i=1;i<=n;i++)mp.insert(make_pair(a[i],i));
		}
		else{
			for(int i=1;i<=n;i++)mp[i]=i;
		}
	}
	void find(){
		if(fm==0){
			for(int i=1;i<=m;i++){
				auto it=mp.find(b[i]);
				if(it==mp.end())continue;
				ans+=it->second;
			}
		}
		else{
			for(int i=1;i<=m;i++)ans+=mp[b[i]];
		}
	}
	void clear(){mp.clear();ans=0;}
	void operator ()(){
		insert();
		find();
		printf("%lld\n",ans);
	}
};
LL Rand(LL l,LL r){
	return 1ull*mt_rand()*mt_rand()%(r-l+1)+l;
}
template<typename Fun>
void Test_Speed(Fun &functor){	
	auto start_time=clock();
	functor();
	cout<<functor.name<<" Time consume(ms):"<<clock()-start_time<<'\n';
}
void gen_data(int nn=1e6,int mm=1e7,int hit=5,int le=1){
	n=nn,m=mm;
	assert(hit>=1);
	for(i=1;i<=n;i++)a[i]=Rand(1,1e12);
	for(i=1;i<=m;i++){
		if(Rand(1,hit)<=le)b[i]=a[Rand(1,n)];
		else b[i]=Rand(1,1e12);
	}
}
signed main()
{
// 	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	freopen(".in","w",stdout);

	Hash_Table_Test<__gnu_pbds::gp_hash_table<LL,LL>> gp("gp_hash_table"s);
	Hash_Table_Test<unordered_map<LL,LL>> um("unordered_map"s);
//	gen_data();
//	Test_Speed(gp);
//	Test_Speed(um);
//	gen_data(1e7,2e7);
//	gp.clear();um.clear();
//	Test_Speed(gp);
//	Test_Speed(um);
	gen_data(1e6,4e7,8,7);
	gp.clear();um.clear();
	Test_Speed(gp);
	Test_Speed(um);
	gen_data(1e6,4e7,8);
	gp.clear();um.clear();
	Test_Speed(gp);
	Test_Speed(um);
	return 0;
}


