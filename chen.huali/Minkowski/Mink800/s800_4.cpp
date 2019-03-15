//
//  main.cpp
//  2DPoreStructure
//
//  Created by HarryChan on 16/11/30.
//  Copyright © 2016年 HarryChan. All rights reserved.
//

#include <stdio.h>

#include <stdlib.h>

#include <math.h>

#include <time.h>

#include <string>

//#include<windows.h>

using namespace std;

#define M 800

#define N 800

#define M1 (M + 1)

#define N1 (N + 1)

#define Q 9

#define cs (0.001)

#define poro (0.65)  //porosity

#define ep (1.0e-6)

#define Hr (60 * 60)

#define Min 60

//=========================================================================================================================================

int flag[M1][N1], e[Q][2];

double sumn = 1.0 * M1 * N1, Ds[Q];

double porosity();

//=========================================================================================================================================

double porosity()
{
    
    double por, sumf = 0.0;
    
    int j, i;
    
    
    
    for(j = 0; j < M1; j++)
        for(i = 0; i < N1; i++)
        {
            
            sumf += 1.0 * flag[j][i];
            
        }
    
    por = sumf / sumn;
    
    return por;
    
}

int main()
{
    int ii=151;
    int EnsembleNum=ii+49;
    time_t Time;
    int sec,h,m;

    
    
    
    int j, i, k, jp, ip, Mb = 4, Me = 796, Nb = 4, Ne = 796;
    
    double pore = 1.0, pc;
    
    FILE *fp;
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    
    e[0][0] = 0;  e[0][1] = 0;
    
    e[1][0] = 1;  e[1][1] = 0;
    
    e[2][0] = 0;  e[2][1] = 1;
    
    e[3][0] = -1; e[3][1] = 0;
    
    e[4][0] = 0;  e[4][1] = -1;
    
    e[5][0] = 1;  e[5][1] = 1;
    
    e[6][0] = -1; e[6][1] = 1;
    
    e[7][0] = -1; e[7][1] = -1;
    
    e[8][0] = 1;  e[8][1] = -1;
    
    Ds[0] = 0.0; Ds[1] = Ds[2] = Ds[3] = Ds[4] = 0.004;  Ds[5] = Ds[6] = Ds[7] = Ds[8] = 0.004;
    
    

    
    //	srand(1);
    time_t StartTime=time(NULL);

    
//    unsigned ll=unsigned(time(NULL));
//    printf("%d\n",unsigned(tick1));
    
    

    srand(unsigned(time(NULL)));
    
    while(ii<=EnsembleNum)
    {
        
//    ll=unsigned(time(NULL))*100;
//        printf("%d\n",ll+ii);

        
//        printf("%d\n",unsigned(ll+tick2-tick1));
        
        
        pore=1;

        string filename1="flag200_";
        string filename2=to_string(ii);
        string filename3=".dat";
        string filename=filename1+filename2+filename3;
        
        
        for(j = 0; j < M1; j++)
            for(i = 0; i < N1; i++)
            {
                
                flag[j][i] = 1;
                
                if((i >= Nb) & (i <= Ne) & (j <= Me) & (j >= Mb))
                {
                    
                    pc = 1.0 * rand() / (RAND_MAX + 1.0);
                    
                    if(pc <= cs) flag[j][i] = 0;
                    
                }
                
                
            }
        
        //--------------------------------------------------------------------------------------------------------------------------------------------
        
        while(pore >= (poro + ep))
        {
            
            for(j = 0; j < M1; j++)
                for(i = 0; i < N1; i++)
                {
                    
                    if(flag[j][i] == 0)
                    {
                        
                        for(k = 1; k < Q; k++)
                        {
                            
                            jp = j + e[k][1]; ip = i + e[k][0];
                            
                            if((jp >= Mb) & (jp <= Me) & (ip >= Nb) & (ip <= Ne))
                            {
                                
                                if(flag[jp][ip] == 1)
                                {
                                    
                                    pc = 1.0 * rand() / (RAND_MAX + 1.0);
                                    
                                    if(pc <= Ds[k])
                                    {
                                        
                                        flag[jp][ip] = 0;
                                        
                                        pore = porosity();
                                        
                                        if(pore < (poro+ep)) break;
                                        
                                    }
                                }
                                
                            }
                            
                        }
                        
                    }
                    
                }
        }
        
        if(ii % 100 ==0)
            printf("n= %d , pore = %f , ", ii,pore);
        
        if((fp=fopen(filename.c_str(),"w"))==NULL) {printf("File Open Error\n");exit(1);}
        
        for(j = 0; j < M1; j++)
        {
            
            for(i = 0; i < N1; i++)
                
                fprintf(fp, "%d ", flag[j][i]);
            
            fprintf(fp, "\n");
            
        }
        
        fclose(fp);
        
        time_t EndTime = time(NULL);
        Time = EndTime - StartTime;
        h = Time / Hr;
        Time = Time % Hr;
        m = Time / Min;
        Time = Time % Min;
        sec = Time;
        
        
        if(ii % 1 ==0)
            printf(" %02d:%02d:%02d \n", h, m, sec);

        
        
        ii=ii+1;
    }
    
    return 0;
    
}

