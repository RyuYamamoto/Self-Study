/**
 * @file   ga.h
 * @brief  Function list of Generaric Algorithm Program
 * @author Ryu Yamamoto
 * @date   2014/12/18
 */

//#ifdef  _GA_PROGRAM
//#define _GA_PROGRAM

#include <iostream>
#include <cstdlib>
#include <Eigen/Dense>
#define DISTANCE 1

using namespace std;
using namespace Eigen;

MatrixXd city = MatrixXd::Zero(5,5);	//都市の範囲

class ga{
	int individual;			//!個体数
	int generation_number;	//!世代数
	int city_number;		//!都市の数
public:
	ga(int a);				//!コンストラクタ
	~ga();					//!デストラクタ
	void initialize(int b);	//初期集団生成
	void evaluate();		//!評価
	void selection();		//!選択
	void cross_over();		//!交叉
	void mutation();		//!突然変異
	double calc_distance(int x,int y);	//!距離計算
};

//#endif
