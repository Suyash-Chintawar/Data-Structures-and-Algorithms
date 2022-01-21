#include<bits/stdc++.h>
using namespace std;
#define pi acos(-1)
#define mod 1000000007
typedef complex<double> cd;

int pow(int a,int b)
{
    int res=1;
    while(b>0)
    {
        if(b%2==1) res=(res*a)%mod;
        a=(a*a)%mod;
        b/=2;
    }
    return res;
}

int reverse(int num, int logn)
{
    int res = 0;
    for(int i=0;i<logn;i++) 
    {
        if(num&pow(2,i)) res|=pow(2,logn-i-1);
    }
    return res;
}

void fft(vector<cd> &coef, bool inverse) 
{
    int n = coef.size();
    int logn = log2(n);

    for(int i=0;i<n;i++) 
    {
        if(i<reverse(i,logn)) 
    	{
    		int idx = reverse(i,logn);
    		cd temp = coef[idx];
    		coef[idx]=coef[i];
    		coef[i]=temp;
    	}
    }

    for(int l=2;l<=n;l*=2)
    {
        double angle = 2*pi/l;
    	if(inverse==false) angle*=-1;
        cd wl(cos(angle),sin(angle));
        for(int i=0;i<n;i+=l)
        {
            cd w(1);
            for(int j=0;j<l/2;j++) 
            {
                cd u = coef[i+j];
                cd v = coef[i+j+l/2]*w;
                coef[i+j]=u+v;
                coef[i+j+l/2]=u-v;
                w*=wl;
            }
        }
    }

    if(inverse==true) 
    {
        for(auto x:coef) x /= n;
    }
}

int main()
{
	int n;
	cout<<"Enter size of array:";
	cin>>n;
	vector<int> v(n);
	cout<<"Enter the "<<n<<" elements (space separated integers): \n";
	for(int i=0;i<n;i++)
	{
		cin>>v[i];
	}
	vector<cd> coef(v.begin(),v.end());
    fft(coef,false);
    cout<<"\nDFT of the input array is:\n";
    for (int i=0;i<n;i++) 
	{
		if(coef[i].imag()>=0) cout<<coef[i].real()<<"+"<<coef[i].imag()<<"i"<<endl;
		else cout<<coef[i].real()<<coef[i].imag()<<"i"<<endl;
	}
}