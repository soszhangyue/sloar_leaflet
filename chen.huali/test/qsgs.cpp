// 3D_PorousMeida.cpp : Defines the entry point for the console application.

//direction of growth D3Q26

//2014/1/12 copyright by luoluobian

//#include "stdafx.h"

#include <iostream>

#include <cmath>

#include <cstdlib>

#include <iomanip>

#include <fstream>

#include <sstream>

#include <string>

#include <ctime>

using namespace std;

//D3Q19

const int Q = 19;

int e[Q][3] = { { 0, 0, 0 }, { 1, 0, 0 }, { -1, 0, 0 }, { 0, 1, 0 }, { 0, -1, 0 }, { 0, 0, 1 }, { 0, 0, -1 }, { 1, 1, 0 }, { -1, -1, 0 }, { 1, -1, 0 },
    
    { -1, 1, 0 }, { 1, 0, 1 }, { -1, 0, -1 }, { 1, 0, -1 }, { -1, 0, 1 }, { 0, 1, 1 }, { 0, -1, -1 }, { 0, 1, -1 }, { 0, -1, 1 } };

double w[Q] = { 1. / 3, 1. / 18, 1. / 18, 1. / 18, 1. / 18, 1. / 18, 1. / 18, 1. / 36, 1. / 36, 1. / 36, 1. / 36, 1. / 36, 1. / 36, 1. / 36, 1. / 36, 1. / 36, 1. / 36, 1. / 36, 1. / 36 };

//定义物理尺寸

const int NX = 200;

const int NY = 200;

const int NZ = 200;

const int M = NX*NY*NZ;

//lattice boltzmann method
/*
double *** rho=new double ** [NX + 1];
double **** u=new double *** [NX+1];
double **** u0=new double *** [NX+1];
*/
double velocity;
/*
double **** f=new double *** [NX+1];
double **** F=new double *** [NX+1];
double **** feqq=new double *** [NX+1];
double **** ftemp=new double *** [NX+1];
*/
int i, j, k, q, ip, jp, kp, n;

double c, Re, dx, dy, dz, LX, LY, LZ, dt, rho0, tau_f, niu, omega, error, temp;



int *** arrgrid=new int ** [NX + 1];
//int *** solidBoundaryNode=new int ** [NX + 1];

double rho_in = 1.0;

double rho_out = 0.5;

void initilization();

void QuartetStructureGenerationSet(int mm,int ii);

//double feq(int q, double rho, double u[3]);

//void Evolution();

//void outputdata(int m);

//void Error();

//void boundary();

//void Macroscopic();

void ini_array();

void delete_array();

void fileout(int m);



int main()

{
    srand(unsigned(time(NULL)));
    double rr[10000];
    double rr_pre=-10;
    int ind_begin=1;
    int ind_end=ind_begin+0;
    
    for(int i=ind_begin;i<=ind_end;i++)
    {
        while(abs(rr[i]-rr_pre)<2 || rr[i]<10000000 )
        {
            rr[i]=rand();
        }
        rr_pre=rr[i];
        
    }
    for(int i=ind_begin;i<=ind_end;i++)
    {
        

        
    ini_array();
    
    QuartetStructureGenerationSet(i,unsigned(rr[i]));
    
    fileout(i);

    
    delete_array();

    
    }
    return 0;
}
/*
void initilization()

{
    
    dx = 1.0;
    
    dy = 1.0;
    
    dz = 1.0;
    
    dt = dx;
    
    c = dx / dt;
    
    LX = dx*NX;
    
    LY = dy*NY;
    
    LZ = dz*NZ;
    
    tau_f = 1.35;
    
    omega = 1.0 / tau_f;
    
    rho0 = 0.5;
    
    for (k = 0; k <= NZ; k++)
        
    {
        
        for (j = 0; j <= NY; j++)
            
        {
            
            for (i = 0; i <= NX; i++)
                
            {
                
                u[i][j][k][0] = 0.0;
                
                u[i][j][k][1] = 0.0;
                
                u[i][j][k][2] = 0.0;
                
                rho[i][j][k] = rho0;
                
                for (q = 0; q < Q; q++)
                    
                {
                    
                    f[i][j][k][q] = feq(q, rho[i][j][k], u[i][j][k]);
                    
                }
                
            }
            
        }
        
    }
    
}
*/
void QuartetStructureGenerationSet(int mm,int ii)

{
    
    srand(ii);
    
    double d1_6 = 0.02;
    
    double d7_18 = d1_6 / 2.;
    
    double d19_26 = d1_6 / 8.;
    
    double n = 0.65;
    
    double cdd = 0.001;
    
    double numtotal_need = (1 - n)*NX*NY*NZ;
    
    int numsoild = 0;
    
    int Tnumsoild;
    
    int **soild=new int *[M + 1];
    for(int l=0;l<M+1;l++)
    {
        soild[l]=new int [3];
        for(int n=0;n<3;n++)
            soild[l][n]=0;
    }
    
    
    srand((unsigned)time(NULL));
    
    //第一步，遍历所有网格，生成固相内核

    for (i = 0; i <= NX; i++)
        
    {
        
        for (j = 0; j <= NY; j++)
            
        {
            
            for (k = 0; k <= NZ; k++)
                
            {
                
                arrgrid[i][j][k] = 0;
                
                soild[numsoild][0] = 0;
                
                soild[numsoild][1] = 0;
                
                soild[numsoild][2] = 0;
                
                if (((rand() % 1000) / 1000.0) < cdd)
                    
                {
                    
                    arrgrid[i][j][k] = 1;
                    
                    soild[numsoild][0] = i;
                    
                    soild[numsoild][1] = j;
                    
                    soild[numsoild][2] = k;
                    
                    numsoild = numsoild + 1;
                    
                }
                
            }
            
        }
        
    }
    
    Tnumsoild = numsoild;
    
    //第二步，从固相核向周围26个方向生长
    
    while (Tnumsoild < numtotal_need)
        
    {

        for (int index_soild = 0; index_soild < Tnumsoild; index_soild++)
            
        {
            
            int index_i = soild[index_soild][0];
            
            int index_j = soild[index_soild][1];
            
            int index_k = soild[index_soild][2];
            
            //1向右方向生长
            
            if (index_j < NY - 1)
                
            {
                
                i = index_i;
                
                j = index_j + 1;
                
                k = index_k;
                
                if (arrgrid[i][j][k] == 0 && ((rand() % 1000) / 1000.0) < d1_6)
                    
                {
                    
                    numsoild = numsoild + 1;
                    
                    arrgrid[i][j][k] = 1;
                    
                    soild[numsoild][0] = i;
                    
                    soild[numsoild][1] = j;
                    
                    soild[numsoild][2] = k;
                    
                }
                
            }
            
            //2向后方向生长
            
            if (index_i > 0)
                
            {
                
                i = index_i - 1;
                
                j = index_j;
                
                k = index_k;
                
                if (arrgrid[i][j][k] == 0 && ((rand() % 1000) / 1000.0) < d1_6)
                    
                {
                    
                    numsoild = numsoild + 1;
                    
                    arrgrid[i][j][k] = 1;
                    
                    soild[numsoild][0] = i;
                    
                    soild[numsoild][1] = j;
                    
                    soild[numsoild][2] = k;
                    
                }
                
            }
            
            //3向左方向生长
            
            if (index_j > 0)
                
            {
                
                i = index_i;
                
                j = index_j - 1;
                
                k = index_k;
                
                if (arrgrid[i][j][k] == 0 && ((rand() % 1000) / 1000.0) < d1_6)
                    
                {
                    
                    numsoild = numsoild + 1;
                    
                    arrgrid[i][j][k] = 1;
                    
                    soild[numsoild][0] = i;
                    
                    soild[numsoild][1] = j;
                    
                    soild[numsoild][2] = k;
                    
                }
                
            }
            
            //4向前方向生长
            
            if (index_i < NX - 1)
                
            {
                
                i = index_i + 1;
                
                j = index_j;
                
                k = index_k;
                
                if (arrgrid[i][j][k] == 0 && ((rand() % 1000) / 1000.0) < d1_6)
                    
                {
                    
                    numsoild = numsoild + 1;
                    
                    arrgrid[i][j][k] = 1;
                    
                    soild[numsoild][0] = i;
                    
                    soild[numsoild][1] = j;
                    
                    soild[numsoild][2] = k;
                    
                }
                
            }
            
            //5向上方向生长
            
            if (index_k < NZ - 1)
                
            {
                
                i = index_i;
                
                j = index_j;
                
                k = index_k + 1;
                
                if (arrgrid[i][j][k] == 0 && ((rand() % 1000) / 1000.0) < d1_6)
                    
                {
                    
                    numsoild = numsoild + 1;
                    
                    arrgrid[i][j][k] = 1;
                    
                    soild[numsoild][0] = i;
                    
                    soild[numsoild][1] = j;
                    
                    soild[numsoild][2] = k;
                    
                }
                
            }
            
            //6向下方向生长
            
            if (index_k > 0)
                
            {
                
                i = index_i;
                
                j = index_j;
                
                k = index_k - 1;
                
                if (arrgrid[i][j][k] == 0 && ((rand() % 1000) / 1000.0) < d1_6)
                    
                {
                    
                    numsoild = numsoild + 1;
                    
                    arrgrid[i][j][k] = 1;
                    
                    soild[numsoild][0] = i;
                    
                    soild[numsoild][1] = j;
                    
                    soild[numsoild][2] = k;
                    
                }
                
            }
            
            //7向水平方向右前生长
            
            if (index_i < NX - 1 && index_j < NY - 1)
                
            {
                
                i = index_i + 1;
                
                j = index_j + 1;
                
                k = index_k;
                
                if (arrgrid[i][j][k] == 0 && ((rand() % 1000) / 1000.0) < d7_18)
                    
                {
                    
                    numsoild = numsoild + 1;
                    
                    arrgrid[i][j][k] = 1;
                    
                    soild[numsoild][0] = i;
                    
                    soild[numsoild][1] = j;
                    
                    soild[numsoild][2] = k;
                    
                }
                
            }
            
            //8向水平方向左前生长
            
            if (index_i < NX - 1 && index_j > 0)
                
            {
                
                i = index_i + 1;
                
                j = index_j - 1;
                
                k = index_k;
                
                if (arrgrid[i][j][k] == 0 && ((rand() % 1000) / 1000.0) < d7_18)
                    
                {
                    
                    numsoild = numsoild + 1;
                    
                    arrgrid[i][j][k] = 1;
                    
                    soild[numsoild][0] = i;
                    
                    soild[numsoild][1] = j;
                    
                    soild[numsoild][2] = k;
                    
                }
                
            }
            
            //9向水平方向右后生长
            
            if (index_i > 0 && index_j < NY - 1)
                
            {
                
                i = index_i - 1;
                
                j = index_j + 1;
                
                k = index_k;
                
                if (arrgrid[i][j][k] == 0 && ((rand() % 1000) / 1000.0) < d7_18)
                    
                {
                    
                    numsoild = numsoild + 1;
                    
                    arrgrid[i][j][k] = 1;
                    
                    soild[numsoild][0] = i;
                    
                    soild[numsoild][1] = j;
                    
                    soild[numsoild][2] = k;
                    
                }
                
            }
            
            //10向水平方向左后生长
            
            if (index_i > 0 && index_j > 0)
                
            {
                
                i = index_i - 1;
                
                j = index_j - 1;
                
                k = index_k;
                
                if (arrgrid[i][j][k] == 0 && ((rand() % 1000) / 1000.0) < d7_18)
                    
                {
                    
                    numsoild = numsoild + 1;
                    
                    arrgrid[i][j][k] = 1;
                    
                    soild[numsoild][0] = i;
                    
                    soild[numsoild][1] = j;
                    
                    soild[numsoild][2] = k;
                    
                }
                
            }
            
            //11向右上方向生长
            
            if (index_j < NY - 1 && index_k < NZ - 1)
                
            {
                
                i = index_i;
                
                j = index_j + 1;
                
                k = index_k + 1;
                
                if (arrgrid[i][j][k] == 0 && ((rand() % 1000) / 1000.0) < d7_18)
                    
                {
                    
                    numsoild = numsoild + 1;
                    
                    arrgrid[i][j][k] = 1;
                    
                    soild[numsoild][0] = i;
                    
                    soild[numsoild][1] = j;
                    
                    soild[numsoild][2] = k;
                    
                }
                
            }
            
            //12向右下方向生长
            
            if (index_j <NY - 1 && index_k >0)
                
            {
                
                i = index_i;
                
                j = index_j + 1;
                
                k = index_k - 1;
                
                if (arrgrid[i][j][k] == 0 && ((rand() % 1000) / 1000.0) < d7_18)
                    
                {
                    
                    numsoild = numsoild + 1;
                    
                    arrgrid[i][j][k] = 1;
                    
                    soild[numsoild][0] = i;
                    
                    soild[numsoild][1] = j;
                    
                    soild[numsoild][2] = k;
                    
                }
                
            }
            
            //13向左上方向生长
            
            if (index_j > 0 && index_k < NZ - 1)
                
            {
                
                i = index_i;
                
                j = index_j - 1;
                
                k = index_k + 1;
                
                if (arrgrid[i][j][k] == 0 && ((rand() % 1000) / 1000.0) < d7_18)
                    
                {
                    
                    numsoild = numsoild + 1;
                    
                    arrgrid[i][j][k] = 1;
                    
                    soild[numsoild][0] = i;
                    
                    soild[numsoild][1] = j;
                    
                    soild[numsoild][2] = k;
                    
                }
                
            }
            
            //14向左下方向生长
            
            if (index_j > 0 && index_k > 0)
                
            {
                
                i = index_i;
                
                j = index_j - 1;
                
                k = index_k - 1;
                
                if (arrgrid[i][j][k] == 0 && ((rand() % 1000) / 1000.0) < d7_18)
                    
                {
                    
                    numsoild = numsoild + 1;
                    
                    arrgrid[i][j][k] = 1;
                    
                    soild[numsoild][0] = i;
                    
                    soild[numsoild][1] = j;
                    
                    soild[numsoild][2] = k;
                    
                }
                
            }
            
            //15向前上方向生长
            
            if (index_i < NX - 1 && index_k < NZ - 1)
                
            {
                
                i = index_i + 1;
                
                j = index_j;
                
                k = index_k + 1;
                
                if (arrgrid[i][j][k] == 0 && ((rand() % 1000) / 1000.0) < d7_18)
                    
                {
                    
                    numsoild = numsoild + 1;
                    
                    arrgrid[i][j][k] = 1;
                    
                    soild[numsoild][0] = i;
                    
                    soild[numsoild][1] = j;
                    
                    soild[numsoild][2] = k;
                    
                }
                
            }
            
            //16向前下方向生长
            
            if (index_i <NX - 1 && index_k >0)
                
            {
                
                i = index_i + 1;
                
                j = index_j;
                
                k = index_k - 1;
                
                if (arrgrid[i][j][k] == 0 && ((rand() % 1000) / 1000.0) < d7_18)
                    
                {
                    
                    numsoild = numsoild + 1;
                    
                    arrgrid[i][j][k] = 1;
                    
                    soild[numsoild][0] = i;
                    
                    soild[numsoild][1] = j;
                    
                    soild[numsoild][2] = k;
                    
                }
                
            }
            
            //17向后上方向生长
            
            if (index_i > 0 && index_k < NZ - 1)
                
            {
                
                i = index_i - 1;
                
                j = index_j;
                
                k = index_k + 1;
                
                if (arrgrid[i][j][k] == 0 && ((rand() % 1000) / 1000.0) < d7_18)
                    
                {
                    
                    numsoild = numsoild + 1;
                    
                    arrgrid[i][j][k] = 1;
                    
                    soild[numsoild][0] = i;
                    
                    soild[numsoild][1] = j;
                    
                    soild[numsoild][2] = k;
                    
                }
                
            }
            
            //18向后下方向生长
            
            if (index_i > 0 && index_k > 0)
                
            {
                
                i = index_i - 1;
                
                j = index_j;
                
                k = index_k - 1;
                
                if (arrgrid[i][j][k] == 0 && ((rand() % 1000) / 1000.0) < d7_18)
                    
                {
                    
                    numsoild = numsoild + 1;
                    
                    arrgrid[i][j][k] = 1;
                    
                    soild[numsoild][0] = i;
                    
                    soild[numsoild][1] = j;
                    
                    soild[numsoild][2] = k;
                    
                }
                
            }
            
            //19向右前上对角线方向生长
            
            if (index_i < NX - 1 && index_j < NY - 1 && index_k < NZ - 1)
                
            {
                
                i = index_i + 1;
                
                j = index_j + 1;
                
                k = index_k + 1;
                
                if (arrgrid[i][j][k] == 0 && ((rand() % 1000) / 1000.0) < d19_26)
                    
                {
                    
                    numsoild = numsoild + 1;
                    
                    arrgrid[i][j][k] = 1;
                    
                    soild[numsoild][0] = i;
                    
                    soild[numsoild][1] = j;
                    
                    soild[numsoild][2] = k;
                    
                }
                
            }
            
            //20向右后上对角线方向生长
            
            if (index_i > 0 && index_j < NY - 1 && index_k < NZ - 1)
                
            {
                
                i = index_i - 1;
                
                j = index_j + 1;
                
                k = index_k + 1;
                
                if (arrgrid[i][j][k] == 0 && ((rand() % 1000) / 1000.0) < d19_26)
                    
                {
                    
                    numsoild = numsoild + 1;
                    
                    arrgrid[i][j][k] = 1;
                    
                    soild[numsoild][0] = i;
                    
                    soild[numsoild][1] = j;
                    
                    soild[numsoild][2] = k;
                    
                }
                
            }
            
            //21向左后上对角线方向生长
            
            if (index_i > 0 && index_j > 0 && index_k < NZ - 1)
                
            {
                
                i = index_i - 1;
                
                j = index_j - 1;
                
                k = index_k + 1;
                
                if (arrgrid[i][j][k] == 0 && ((rand() % 1000) / 1000.0) < d19_26)
                    
                {
                    
                    numsoild = numsoild + 1;
                    
                    arrgrid[i][j][k] = 1;
                    
                    soild[numsoild][0] = i;
                    
                    soild[numsoild][1] = j;
                    
                    soild[numsoild][2] = k;
                    
                }
                
            }
            
            //22向左前上对角线方向生长
            
            if (index_i<NX - 1 && index_j>0 && index_k < NZ - 1)
                
            {
                
                i = index_i + 1;
                
                j = index_j - 1;
                
                k = index_k + 1;
                
                if (arrgrid[i][j][k] == 0 && ((rand() % 1000) / 1000.0) <
                    
                    d19_26)
                    
                {
                    
                    numsoild = numsoild + 1;
                    
                    arrgrid[i][j][k] = 1;
                    
                    soild[numsoild][0] = i;
                    
                    soild[numsoild][1] = j;
                    
                    soild[numsoild][2] = k;
                    
                }
                
            }
            
            //23向右前下对角线方向生长
            
            if (index_i < NX - 1 && index_j<NY - 1 && index_k>0)
                
            {
                
                i = index_i + 1;
                
                j = index_j + 1;
                
                k = index_k - 1;
                
                if (arrgrid[i][j][k] == 0 && ((rand() % 1000) / 1000.0) < d19_26)
                    
                {
                    
                    numsoild = numsoild + 1;
                    
                    arrgrid[i][j][k] = 1;
                    
                    soild[numsoild][0] = i;
                    
                    soild[numsoild][1] = j;
                    
                    soild[numsoild][2] = k;
                    
                }
                
            }
            
            //24向右后下对角线方向生长
            
            if (index_i > 0 && index_j<NY - 1 && index_k>0)
                
            {
                
                i = index_i - 1;
                
                j = index_j + 1;
                
                k = index_k - 1;
                
                if (arrgrid[i][j][k] == 0 && ((rand() % 1000) / 1000.0) < d19_26)
                    
                {
                    
                    numsoild = numsoild + 1;
                    
                    arrgrid[i][j][k] = 1;
                    
                    soild[numsoild][0] = i;
                    
                    soild[numsoild][1] = j;
                    
                    soild[numsoild][2] = k;
                    
                }
                
            }
            
            //25向左后下对角线方向生长
            
            if (index_i > 0 && index_j > 0 && index_k > 0)
                
            {
                
                i = index_i - 1;
                
                j = index_j - 1;
                
                k = index_k - 1;
                
                if (arrgrid[i][j][k] == 0 && ((rand() % 1000) / 1000.0) < d19_26)
                    
                {
                    
                    numsoild = numsoild + 1;
                    
                    arrgrid[i][j][k] = 1;
                    
                    soild[numsoild][0] = i;
                    
                    soild[numsoild][1] = j;
                    
                    soild[numsoild][2] = k;
                    
                }
                
            }
            
            //26向左前下对角线方向生长
            
            if (index_i<NX - 1 && index_j>0 && index_k > 0)
                
            {
                
                i = index_i + 1;
                
                j = index_j - 1;
                
                k = index_k - 1;
                
                if (arrgrid[i][j][k] == 0 && ((rand() % 1000) / 1000.0) < d19_26)
                    
                {
                    
                    numsoild = numsoild + 1;
                    
                    arrgrid[i][j][k] = 1;
                    
                    soild[numsoild][0] = i;
                    
                    soild[numsoild][1] = j;
                    
                    soild[numsoild][2] = k;
                    
                }
                
            }
            
        }
        
        Tnumsoild = numsoild;
        
    }
    
    for(int l=0;l<M+1;l++)
    {
        delete[] soild[l];
    }
    
    
    cout<<mm<<": media generated!!  "<<ii<<"\n";
    
}

double feq(int q, double rho, double u[3])

{
    
    double eu, uvw, feq;
    
    eu = e[q][0] * u[0] + e[q][1] * u[1] + e[q][2] * u[2];
    
    uvw = u[0] * u[0] + u[1] * u[1] + u[2] * u[2];
    
    feq = w[q] * rho* (1.0 + 3.0*eu + 4.5*eu*eu - 1.5*uvw);
    
    return feq;
    
}
/*
void Evolution()

{
    
    //Collision step
    
    for (k = 0; k <= NZ; k++)
        
    {
        
        for (j = 0; j <= NY; j++)
            
        {
            
            for (i = 0; i <= NX; i++)
                
            {
                
                for (q = 0; q < Q; q++)
                    
                {
                    
                    if (arrgrid[i][j][k] == 0)
                        
                    {
                        
                        f[i][j][k][q] = f[i][j][k][q] + omega*(feq(q, rho[i][j][k], u[i][j][k]) - f[i][j][k][q]);
                        
                    }
                    
                }
                
            }
            
        }
        
    }
    
    //streaming
    
    for (k = 0; k <= NZ; k++)
        
    {
        
        for (j = 0; j <= NY; j++)
            
        {
            
            for (i = 0; i <= NX; i++)
                
            {
                
                for (q = 0; q < Q; q++)
                    
                {
                    
                    ip = i + e[q][0];
                    
                    jp = j + e[q][1];
                    
                    kp = k + e[q][2];
                    
                    if (ip >= 0 && jp >= 0 && kp >= 0 && ip <= NX && jp <= NY && kp <= NZ)
                        
                    {
                        
                        ftemp[ip][jp][kp][q] = f[i][j][k][q];
                        
                    }
                    
                }
                
            }
            
        }
        
    }
    
    for (k = 0; k <= NZ; k++)
        
    {
        
        for (j = 0; j <= NY; j++)
            
        {
            
            for (i = 0; i <= NX; i++)
                
            {
                
                for (q = 0; q < Q; q++)
                    
                {
                    
                    f[i][j][k][q]
                    
                    = ftemp[i][j][k][q];
                    
                }
                
            }
            
        }
        
    }
    
}

void Macroscopic()

{
    
    //macroscopic
    
    for (k = 0; k <= NZ; k++)
        
    {
        
        for (j = 0; j <= NY; j++)
            
        {
            
            for (i = 0; i <= NX; i++)
                
            {
                
                u0[i][j][k][0] = u[i][j][k][0];
                
                u0[i][j][k][1] = u[i][j][k][1];
                
                u0[i][j][k][2] = u[i][j][k][2];
                
                rho[i][j][k] = 0.0;
                
                u[i][j][k][0] = 0.0;
                
                u[i][j][k][1] = 0.0;
                
                u[i][j][k][2] = 0.0;
                
                if (arrgrid[i][j][k] == 0)
                    
                {
                    
                    for (q = 0; q < Q; q++)
                        
                    {
                        
                        rho[i][j][k] += f[i][j][k][q];
                        
                        u[i][j][k][0] += e[q][0] * f[i][j][k][q];
                        
                        u[i][j][k][1] += e[q][1] * f[i][j][k][q];
                        
                        u[i][j][k][2] += e[q][2] * f[i][j][k][q];
                        
                    }
                    
                    u[i][j][k][0] = u[i][j][k][0] / rho[i][j][k];
                    
                    u[i][j][k][1] = u[i][j][k][1] / rho[i][j][k];
                    
                    u[i][j][k][2] = u[i][j][k][2] / rho[i][j][k];
                    
                }
                
            }
            
        }
        
    }
    
}

void boundary()

{
    
    // bounce back
    
    for (k = 0; k <= NZ; k++)
        
    {
        
        for (j = 0; j <= NY; j++)
            
        {
            
            for (i = 0; i <= NX; i++)
                
            {
                
                if (arrgrid[i][j][k] == 1)
                    
                {
                    
                    temp = f[i][j][k][1];
                    
                    f[i][j][k][1] = f[i][j][k][2];
                    
                    f[i][j][k][2] = temp;
                    
                    temp = f[i][j][k][3];
                    
                    f[i][j][k][3] = f[i][j][k][4];
                    
                    f[i][j][k][4] = temp;
                    
                    temp = f[i][j][k][5];
                    
                    f[i][j][k][5] = f[i][j][k][6];
                    
                    f[i][j][k][6] = temp;
                    
                    temp = f[i][j][k][7];
                    
                    f[i][j][k][7] = f[i][j][k][8];
                    
                    f[i][j][k][8] = temp;
                    
                    temp = f[i][j][k][9];
                    
                    f[i][j][k][9] = f[i][j][k][10];
                    
                    f[i][j][k][10] = temp;
                    
                    temp = f[i][j][k][11];
                    
                    f[i][j][k][11] = f[i][j][k][12];
                    
                    f[i][j][k][12] = temp;
                    
                    temp = f[i][j][k][13];
                    
                    f[i][j][k][13] = f[i][j][k][14];
                    
                    f[i][j][k][14] = temp;
                    
                    temp = f[i][j][k][15];
                    
                    f[i][j][k][15] = f[i][j][k][16];
                    
                    f[i][j][k][16] = temp;
                    
                    temp = f[i][j][k][17];
                    
                    f[i][j][k][17] = f[i][j][k][18];
                    
                    f[i][j][k][18] = temp;
                    
                }
                
            }
            
        }
        
    }
    
    //left and right boundary
    
    for (k = 1; k < NZ; k++)
        
    {
        
        for (j = 1; j < NY; j++)
            
        {
            
            for (q = 0; q < Q; q++)
                
            {
                
                rho[0][j][k] = rho_in;
                
                u[0][j][k][0] = u[1][j][k][0];
                
                u[0][j][k][1] = u[1][j][k][1];
                
                u[0][j][k][2] = u[1][j][k][2];
                
                f[0][j][k][q] = feq(q, rho[0][j][k], u[0][j][k]) + f[1][j][k][q] - feq(q, rho[1][j][k], u[1][j][k]);
                
                rho[NX][j][k] = rho_out;
                
                u[NX][j][k][0] = u[NX - 1][j][k][0];
                
                u[NX][j][k][1] = u[NX - 1][j][k][1];
                
                u[NX][j][k][2] = u[NX - 1][j][k][2];
                
                f[NX][j][k][q] = feq(q, rho[NX][j][k], u[NX][j][k]) + f[NX - 1][j][k][q] - feq(q, rho[NX - 1][j][k], u[NX - 1][j][k]);
                
            }
            
        }
        
    }
    
    //top and bottom boundary
    
    for (j = 0; j <= NY; j++)
        
    {
        
        for (i = 0; i <= NX; i++)
            
        {
            
            for (q = 0; q < Q; q++)
                
            {
                
                rho[i][j][0] = rho[i][j][1];
                
                u[i][j][0][0] = 0;
                
                u[i][j][0][1] = 0;
                
                u[i][j][0][2] = 0;
                
                f[i][j][0][q] = feq(q, rho[i][j][0], u[i][j][0]) + f[i][j][1][q] - feq(q, rho[i][j][1], u[i][j][1]);
                
                rho[i][j][NZ] = rho[i][j][NZ - 1];
                
                u[i][j][NZ][
                            
                            0] = 0;
                
                u[i][j][NZ][1] = 0;
                
                u[i][j][NZ][2] = 0;
                
                f[i][j][NZ][q] = feq(q, rho[i][j][NZ], u[i][j][NZ]) + f[i][j][NZ - 1][q] - feq(q, rho[i][j][NZ - 1], u[i][j][NZ - 1]);
                
            }
            
        }
        
    }
    
    //former and behind boundary
    
    for (k = 0; k <= NZ; k++)
        
    {
        
        for (i = 0; i <= NX; i++)
            
        {
            
            for (q = 0; q < Q; q++)
                
            {
                
                rho[i][0][k] = rho[i][1][k];
                
                u[i][0][k][0] = 0;
                
                u[i][0][k][1] = 0;
                
                u[i][0][k][2] = 0;
                
                f[i][0][k][q] = feq(q, rho[i][0][k], u[i][0][k]) + f[i][1][k][q] - feq(q, rho[i][1][k], u[i][1][k]);
                
                rho[i][NY][k] = rho[i][NY - 1][k];
                
                u[i][NY][k][0] = 0;
                
                u[i][NY][k][1] = 0;
                
                u[i][NY][k][2] = 0;
                
                f[i][NY][k][q] = feq(q, rho[i][NY][k], u[i][NY][k]) + f[i][NY - 1][k][q] - feq(q, rho[i][NY - 1][k], u[i][NY - 1][k]);
                
            }
            
        }
        
    }
    
}

void Error()

{
    
    double temp1, temp2;
    
    temp1 = 0;
    
    temp2 = 0;
    
    for (k = 0; k <= NZ; k++)
        
    {
        
        for (j = 0; j <= NY; j++)
            
        {
            
            for (i = 0; i <= NX; i++)
                
            {
                
                temp1 += ((u[i][j][k][0] - u0[i][j][k][0])*(u[i][j][k][0] - u0[i][j][k][0]) +
                          
                          (u[i][j][k][1] - u0[i][j][k][1])*(u[i][j][k][1] - u0[i][j][k][1]) +
                          
                          (u[i][j][k][2] - u0[i][j][k][2])*(u[i][j][k][2] - u0[i][j][k][2]));
                
                temp2 += (u[i][j][k][0] * u[i][j][k][0] + u[i][j][k][1] * u[i][j][k][1] + u[i][j][k][2] * u[i][j][k][2]);
                
            }
            
        }
        
    }
    
    temp1 = sqrt(temp1);
    
    temp2 = sqrt(temp2);
    
    error = temp1 / (temp2 + 1e-30);
    
}

void outputdata(int m)

{
    
    ostringstream name;
    
    name << "LBM_heat_transfer_through_porous_media_" << m << ".dat";
    
    ofstream out(name.str().c_str());
    
    out << "Titel=\"porous media\"\n"
    
    << "VARIABLES=\"X\",\"Y\",\"Z\",\"U\",\"V\",\"W\",\"rho\",\"arr\",\"vel\"\n" << "ZONE T=\"BOX\",I="
    
    << NX + 1 << ",J=" << NY + 1 << ",K=" << NZ + 1 << ",F=POINT" << endl;
    
    for (k = 0; k <= NZ; k++)
        
    {
        
        for (j = 0; j <= NY; j++)
            
        {
            
            for (i = 0; i <= NX; i++)
                
            {
                
                out << double(i)*dx << " " << double(j)*dy << " " << double(k)*dy
                
                << " " << u[i][j][k][0] << " " << u[i][j][k][1] << " " << u[i][j][k][2] << " "
                
                << rho[i][j][k] << " " << arrgrid[i][j][k] << " "
                
                << pow(u[i][j][k][0] * u[i][j][k][0] + u[i][j][k][1] * u[i][j][k][1] + u[i][j][k][2] * u[i][j][k][2], 0.5) << endl;
                
            }
            
        }
        
    }
    
}
*/

void fileout(int m)
{
    ostringstream name;
    
    name << "flag";
    if(m<10000)
    {
        name<<0;
        if(m<1000)
        {
            name<<0;
            if(m<100)
            {
                name<<0;
                if(m<10)
                    name<<0;
                
            }
            
        }
    }
    
    
    name << m << ".dat";
    
    
    
    
    ofstream out(name.str().c_str());
    for (i = 0; i <= NX; i++)
        
    {
        
        for (j = 0; j <= NY; j++)
            
        {
            
            for (k = 0; k <= NZ; k++)
                
            {
                
                out<<arrgrid[i][j][k]<<" ";
                
            }
            out<<endl;
            
        }
        
    }
    
    
    
}





void ini_array()
{
    
    for(int i=0;i<NX+1;i++)
    {
//        rho[i]=new double * [NY+1];
        arrgrid[i]=new int *[NY+1];
//        solidBoundaryNode[i]=new int *[NY+1];
        for(int j=0;j<NY+1;j++)
        {
//            rho[i][j]=new double[NZ+1];
            arrgrid[i][j]=new int[NZ+1];
//            solidBoundaryNode[i][j]=new int[NZ+1];
            for(int k=-0;k<NZ+1;k++)
            {
//                rho[i][j][k]=0;
                arrgrid[i][j][k]=0;
//                solidBoundaryNode[i][j][k]=0;
            }
        }
        
    }
/*
    for(int i=0;i<NX+1;i++)
    {
        u[i]=new double ** [NY+1];
        u0[i]=new double **[NY+1];
        f[i]=new double ** [NY+1];
        F[i]=new double **[NY+1];
        feqq[i]=new double ** [NY+1];
        ftemp[i]=new double **[NY+1];
        
        for(int j=0;j<NY+1;j++)
        {
            u[i][j]=new double * [NZ+1];
            u0[i][j]=new double * [NZ+1];
            f[i][j]=new double * [NZ+1];
            F[i][j]=new double *[NZ+1];
            feqq[i][j]=new double * [NZ+1];
            ftemp[i][j]=new double *[NZ+1];
            
            for(int k=-0;k<NZ+1;k++)
            {
                u[i][j][k]=new double [3];
                u0[i][j][k]=new double [3];
                f[i][j][k]=new double [Q];
                F[i][j][k]=new double [Q];
                feqq[i][j][k]=new double [Q];
                ftemp[i][j][k]=new double [Q];
                
                for(int m=0;m<3;m++)
                {
                    u[i][j][k][m]=0;
                    u0[i][j][k][m]=0;
                }
                
                for(int l=0;l<3;l++)
                {
                    f[i][j][k][l]=0;
                    F[i][j][k][l]=0;
                    feqq[i][j][k][l]=0;
                    ftemp[i][j][k][l]=0;
                }
                
                
                
            }
        }
        
    }
    
*/
    
}


void delete_array()
{
    
    for(int i=0;i<NX+1;i++)
    {

        for(int j=0;j<NY+1;j++)
        {
//            delete[] rho[i][j];
            delete[] arrgrid[i][j];
//            delete[] solidBoundaryNode[i][j];

        }
//        delete[] rho[i];
        delete[] arrgrid[i];
//        delete[] solidBoundaryNode[i];
    }
/*
    for(int i=0;i<NX+1;i++)
    {

        
        for(int j=0;j<NY+1;j++)
        {

            
            for(int k=-0;k<NZ+1;k++)
            {
                delete[] u[i][j][k];
                delete[] u0[i][j][k];
                delete[] f[i][j][k];
                delete[] F[i][j][k];
                delete[] feqq[i][j][k];
                delete[] ftemp[i][j][k];
                
                
            }
            delete[] u[i][j];
            delete[] u0[i][j];
            delete[] f[i][j];
            delete[] F[i][j];
            delete[] feqq[i][j];
            delete[] ftemp[i][j];
        }
        delete[] u[i];
        delete[] u0[i];
        delete[] f[i];
        delete[] F[i];
        delete[] feqq[i];
        delete[] ftemp[i];
    }
    
    
*/
    
}




