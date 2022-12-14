@@ -0,0 +1,64 @@
#include <bits/stdc++.h>

using namespace std;

//for sorting complex values of nth roots
//of unity we use complex<double>
typedef complex<double> cd;

//recursive function of FFT
vector<cd> fft(vector<cd>& a)
{
    int n=a.size();

    //if input contains just one element
    if(n==1)
        return vector<cd>(1,a[0]);

    //
    vector<cd> w(n);
    for(int i=0;i<n;i++)
    {
        double alpha=2*M_PI*i/n;
        w[i]=cd(cos(alpha),sin(alpha));
    }

    vector<cd> A0(n/2),A1(n/2);
    for(int i=0;i<n/2;i++)
    {
        //even indexed coefficients
        A0[i]=a[i*2];
        //odd indexed coefficients
        A1[i]=a[i*2+1];
    }

    //recursive call
    vector<cd> y0=fft(A0);
    vector<cd> y1=fft(A1);

    //for storing values of y0,y1,...yn-1
    vector<cd> y(n);

    for(int k=0;k<n/2;k++)
    {
        y[k]=y0[k]+w[k]*y1[k];
        y[k+n/2]=y0[k]-w[k]*y1[k];
    }

    return y;
}

//driver code
int main()
{
    vector<cd> a(1000);
    for(int i=0;i<1000;i++)
        a[i]=i+1;
    vector<cd> b=fft(a);
    for(int i=0;i<1000;i++)
    {
        cout<<b[i]<<endl;
    }

    return 0;
}
