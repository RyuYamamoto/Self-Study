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

MatrixXd city = MatrixXd::Zero(5,5);	//�s�s�͈̔�

class ga{
	int individual;			//!�̐�
	int generation_number;	//!���㐔
	int city_number;		//!�s�s�̐�
public:
	ga(int a);				//!�R���X�g���N�^
	~ga();					//!�f�X�g���N�^
	void initialize(int b);	//�����W�c����
	void evaluate();		//!�]��
	void selection();		//!�I��
	void cross_over();		//!����
	void mutation();		//!�ˑR�ψ�
	double calc_distance(int x,int y);	//!�����v�Z
};

//#endif
