#include <iostream>
#include <math.h>

using namespace std;


int findMaxelem(double **a, int column, int n)
{
    double maxelem = a[0][column];
    int maxindex = 0;

    for (int i = 1; i <= n; ++i){
        if (a[i][column] > maxelem){
            maxelem = a[i][column];
            maxindex = i;
        }
    }
    return maxindex;
}

void exchangeRows(double **a,double *f,int index1,int m,int n)
{
    double temp = 0;
    for (int i = 0; i <= n; ++i){
        temp = a[index1][i];
        a[index1][i] = a[m][i];
        a[m][i] = temp;
    }
    temp = f[index1];
    f[index1] = f[m];
    f[m] = temp;
}

void methodGaussian(double **a,double *f,int k,int n)
{

    double d;
    int j, i;

        for (j = k-1; j >= 0; j--){
            d = a[j][n-k] / a[k][n-k];
            for (i = n-k; i <= n; ++i){
                a[j][i] = a[j][i] - d * a[k][i];
            }
            f[j] = f[j] - d * f[k];
        }
}

void removeX(double **b,int n,int index)
{
    double **t = new double *[n-1];
    for( i = 0; i < n-1; ++i)
        t[i] = new double[n-1];

}

int main()
{
    int i, j;
    int  s1=2, s2=10, s3=20;
    float ro12=0, ro13=0, ro23=-0.6;
    double *mx = new double [3];
    mx[0]=10;
    mx[1]=20;
    mx[2]=50;

    /*cin >> m[0];
    cin >> m[1];
    cin >> m[2];
    cin >> s1;
    cin >> s2;
    cin >> s3;
    cin >> ro12;
    cin >> ro13;
    cin >> ro23;*/

    double **s = new double *[3];
    for( i = 0; i < 3; ++i)
        s[i] = new double[3];

    s[0][0] = s1 * s1;
    s[0][1] = s[1][0] = s1 * s2 * ro12;
    s[0][2] = s[2][0] = s1 * s3 * ro13;
    s[1][1] = s2 * s2;
    s[1][2] = s[2][1] = s2 *s3 * ro23;
    s[2][2] = s3 * s3;

//----------------------------------------------------------------
    int n=4;
    double **a = new double *[n];
    for( i = 0; i < n; ++i)
        a[i] = new double[n];
    for ( i = 0; i < n-1; ++i){
        for ( j = 0; j < n-1; ++j){
            a[i][j] = 2 * s[i][j];
        }
    }
    for ( i = 0; i < n-1; ++i){
            a[i][3] = 1;
            a[3][i] = 1;
    }
    a[3][3] = 0;

    double *f = new double[n];
    f[0] = f[1] = f[2] = 0;
    f[3] = 1;

//--------------------------------------------------------------------
    int m= 5;
    double **b = new double *[m];
    for( i = 0; i < m; ++i)
        b[i] = new double[m];

    for ( i = 0; i < n; ++i){
        for ( j = 0; j < n; ++j){
            b[i][j] = a[i][j];
        }
    }

    b[0][4] = b[4][0] = mx[0];
    b[1][4] = b[4][1] = mx[1];
    b[2][4] = b[4][2] = mx[2];
    b[3][4] = b[4][3] = 0;
    b[4][4] = 0;

    double *g = new double[m];
    g[0] = g[1] = g[2] = 0;
    g[3] = 1;
    g[4] = 30;

//------------------------------------------------------------------
    int k = n-1, maxindex=0;
    for (int column = 0; column <= n-1; ++column){
        maxindex = findMaxelem (a, column, k);
        if (maxindex != k)
            exchangeRows (a, f, maxindex, k, n-1);
        methodGaussian (a, f, k, n-1);
        k--;
    }

    double *x = new double [n];
    x[3]=f[0]/a[0][3];
    x[2]=(f[1]-a[1][3]*x[3])/a[1][2];
    x[1]=(f[2]-a[2][3]*x[3]-a[2][2]*x[2])/a[2][1];
    x[0]=(f[3]-a[3][3]*x[3]-a[3][2]*x[2]-a[3][1]*x[1])/a[3][0];

    cout << "Results for the task of preserving capital: " << endl;
    for( i = 0; i < n-1; ++i)
        cout << "x[" << i+1 << "]=" << x[i] << " " << endl;

    double *x_copy = new double [n];
    for(i = 0; i < n; ++i)
        x_copy[i] = x[i];

//----------------------------------------------------------------------
    for(i=0; i < n-1; ++i)
        if(x[i] < 0)
            x[i] = 0;

    double mP1 = 0, sP1 = 0;
    for(i = 0; i < n-1; ++i){
        if(x[i] > 0){
            mP1 += x[i] * mx[i];
        }
    }
    cout << " Expected rate of return mP= " << mP1 << endl;
    sP1 = sqrt(x[0]*x[0]*s1*s1+x[1]*x[1]*s2*s2+x[2]*x[2]*s3*s3+2*x[0]*x[1]*s[0][1]+2*x[0]*x[2]*s[0][2]+2*x[1]*x[2]*s[1][2]);
    cout << "The magnitude of the risk sigmaP= " << sP1 << endl;

//----------------------------------------------------------

   int vidyemna_x_index = 0 ,flag = 0;
   for(i = 0; i < n-1; ++i){
        if(x_copy[i] < 0){
            vidyemna_x_index = i;
            removeX(b,m-flag,vidyemna_x_index);
            flag++;
        }
    }
    m -= flag;

    k = m-1, maxindex = 0;
    for (int column = 0; column < m; ++column){
        maxindex = findMaxelem (b, column, k);
        if (maxindex != k)
            exchangeRows (b, g, maxindex, k, m-1);
        methodGaussian (b, g, k, m-1);
        k--;
    }


    double *xx = new double [m];
    xx[m - 1] = g[0]/b[0][4];
    int l = 1;
    for (i = m-2; i >= 0; i--)
    {
        xx[i] = g[l];
        for (j = i+1; j < m; ++j)
            xx[i] -= b[l][j] * xx[j];
        xx[i] /= b[l][m-1-l];
        l++;
    }

    cout << endl;
    cout << "Results for increase in capital growth: " << endl;
    for( i = 0; i < l-2; ++i)
        cout << "x[" << i+1 << "]=" << xx[i] << " " << endl;
//-------------------------------------------------------------------------------------------------
    for(i = 0; i < n-1; ++i)
        if(xx[i] < 0)
            xx[i] = 0;


    double mP2 = 0, sP2 = 0;
    for( i = 0; i < l-2; ++i){
        if(xx[i] > 0){
                mP2 += xx[i] * mx[i];
        }
    }
    cout << "Expected rate of return mP= " << mP2 << endl;
    sP2=sqrt(xx[0]*xx[0]*s1*s1+xx[1]*xx[1]*s2*s2+xx[2]*xx[2]*s3*s3+2*xx[0]*xx[1]*s[0][1]+2*xx[0]*xx[2]*s[0][2]+2*xx[1]*xx[2]*s[1][2]);
    cout << "The magnitude of the risk sigmaP= " << sP2 << endl;




    delete[]f;
    delete[]a;
    delete[]x;
    delete[]b;
    delete[]g;
    delete[]xx;
    delete[]x_copy;
    return 0;
}

