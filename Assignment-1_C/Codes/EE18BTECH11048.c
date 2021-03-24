#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <string.h>

void fft(double complex* x, int n){
    if (n == 1)
        return;

    double complex* odd = malloc(n/2 * sizeof(double complex));
    double complex* even = malloc(n/2 * sizeof(double complex));
    for (int i = 0; 2 * i < n; i++) {
        even[i] = x[2 * i];
        odd[i] = x[2 * i + 1];
    }

    fft(even, n/2);
    fft(odd, n/2);


    double complex w; 
    for (int i = 0; 2 * i < n; i++) {
        w = CMPLX(cos(2*M_PI*i/n), sin(2*M_PI*i/n));
        x[i] = even[i] + w * odd[i];
        x[i + n/2] = even[i] - w * odd[i];
    }
    free(even);
    free(odd);
}

void ifft(double complex* x, int n){
    if (n == 1)
        return;

    double complex* odd = malloc(n/2 * sizeof(double complex));
    double complex* even = malloc(n/2 * sizeof(double complex));
    for (int i = 0; 2 * i < n; i++) {
        even[i] = x[2 * i];
        odd[i] = x[2 * i + 1];
    }

    ifft(even, n/2);
    ifft(odd, n/2);

    double complex w;
    for (int i = 0; 2 * i < n; i++) {
        w = CMPLX(cos(-2*M_PI*i/n), sin(-2*M_PI*i/n));
        x[i] = even[i] + w * odd[i];
        x[i + n/2] = even[i] - w * odd[i];
    }
    free(even);
    free(odd);
}




int main()
{
    int n= (1<<20);
    double* x = (double*)malloc(n * sizeof(double));
    double* h = (double*)malloc(n * sizeof(double));
    
    double complex* X = (double complex*)malloc(n * sizeof(double complex));
    double complex* H = (double complex*)malloc(n * sizeof(double complex));
    double complex* Y = (double complex*)malloc(n * sizeof(double complex));
    double complex* ifft_Y = (double complex*)malloc(n * sizeof(double complex));
    
    FILE *fin1,*fout1,*fout2,*fout3;

    fin1 = fopen("x.dat","r");
    int count=0;
    while (!feof(fin1) && count < n) 
    {
        fscanf(fin1, "%lf", &(x[count]));
        X[count] = CMPLX(x[count],0);
        count++;
    }
   
    fft(X,n);
    fout1 = fopen("X_FFT.dat","w");
    for(int i=0;i<n;i++)
    {
        fprintf(fout1,"%lf+%lfi \n",creal(X[i]),cimag(X[i]));
    }

    double a[] = {1,-2.52,2.56,-1.206,0.22013};
    double b[] = {0.00345,0.0138,0.020725,0.0138,0.00345};

    h[0] = (b[0]/a[0]);
    h[1] = (1/a[0])*(b[1] - a[1]*h[0]);
    h[2] = (1/a[0])*(b[2]- a[1]*h[1]-a[2]*h[0]);
    h[3] = (1/a[0])*(b[3] - a[1]*h[2]-a[2]*h[1]-a[3]*h[0]);
    h[4] = (1/a[0])*(b[4] - a[1]*h[3]-a[2]*h[2]-a[3]*h[1]-a[4]*h[0]);
    for(int i=0; i<5;i++)
        H[i] = CMPLX(h[i],0);
    for(int i=5;i<n;i++){
        h[i] = (1/a[0])*(0 - a[1]*h[i-1]-a[2]*h[i-2]-a[3]*h[i-3]-a[4]*h[i-4]);
        H[i] = CMPLX(h[i],0);
    }


    fft(H,n);
    fout2 = fopen("H_FFT.dat","w");
    for(int i=0;i<n;i++)
    {
        fprintf(fout2,"%lf+%lfi \n",creal(H[i]),cimag(H[i]));
    }

    for(int i=0;i<n;i++)
    {
        Y[i] = H[i]*X[i];
        ifft_Y[i] = Y[i];
    }

    ifft(ifft_Y,n);
    fout3 = fopen("Y_IFFT.dat","w");
    for(int i=0;i<n;i++)
    {
        fprintf(fout3,"%lf \n",creal(ifft_Y[i]/n));
    }

    fclose(fin1);
    fclose(fout1);
    fclose(fout2);
    fclose(fout3);
    return 0;
    
}