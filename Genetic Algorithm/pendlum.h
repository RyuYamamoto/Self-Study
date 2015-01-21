#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "parameter.h"
using namespace std;

//加速度取得
double get_x2_func(double f)
{
		return(f/M+dtheta*dtheta*sin(theta)-dtheta2*cos(theta));
}

//角加速度取得
double get_theta2_fun(double f)
{
		return(G*sin(theta)-cos(theta)*(f/M+L*(dtheta)*sin(theta)));
}

//集団初期化
void initialize()
{
		int i,j;
		//初期集団生成
		//1,-1を乱数にて代入
		for(i=0;i<MAX_POPULATION;i++){
				for(j=0;j<MAX_GENE;j++){
						population[i].control[j] = gene[rand()%2];
				}
		}
}

//評価
void calculation_cost()
{
		int i;
}
