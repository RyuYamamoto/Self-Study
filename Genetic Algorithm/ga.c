#define _GA_PROGRAM

//�R���X�g���N�^
ga::ga(int a)
{
	city_number = a;		//�s�s�̐ݒ�

	//�s�s
	city << 0,0,0,1,0,
			0,1,0,0,0,
			0,0,1,0,0,
			1,0,0,0,0,
			0,0,1,0,0;
}

//�f�X�g���N�^
ga::~ga()
{
	cout<<"���������\n";
}

//�����W�c����
void ga::initialize(int b)
{
	int num = 0;
	indivisual = b;		//�̐�

	srand(unsigned(time(NULL)));
	for(int i=0;i<indivisual;i++){
		for(int j=0;j<city_number;j++){
		}
	}
}

//�]��
void ga::evaluate()
{

}

//�I��
void ga::selection()
{

}

//����
void ga::cross_over()
{

}

//�ˑR�ψ�
void ga::mutation()
{

}

//�����v�Z
double calc_distance(int x,int y)
{

}

