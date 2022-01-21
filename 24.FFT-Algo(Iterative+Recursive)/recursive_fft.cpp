#include<bits/stdc++.h>
using namespace std;
#define pi acos(-1)
typedef complex<double> cd;

void fft(vector<cd> &coef, bool inverse) {
    int n = coef.size();
    if (n == 1) return;

    vector<cd> left(n/2),right(n/2);

    for(int i=0;2*i<n;i++)
    {
    	left[i]=coef[2*i];
    	right[i]=coef[2*i+1];
    }

    
    fft(left, inverse);
    fft(right, inverse);

    double angle = 2*pi/n;
    if(inverse==false) angle*=-1;

    cd w(1), wn(cos(angle),sin(angle));

    for(int i=0;2*i<n;i++)
    {
    	coef[i]=left[i]+w*right[i];
    	coef[i+n/2]=left[i]-w*right[i];
    	if (inverse == true) 
    	{
            coef[i]/=2;
            coef[i+n/2]/=2;
        }
        w*=wn;
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