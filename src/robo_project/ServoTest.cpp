#include "RYSerialServo.h"

int main()
{
	int id,angle,speed,end=0;
	int return_angle,return_speed;

	Serial s1;//�I�u�W�F�N�g�̐���

	cout<<"�T�[�{ID����͂��Ă��������F";
	cin>>id;

	cout<<"�p�x����͂��Ă�������(0�`180)�F";
	cin>>angle;

	cout<<"���x����͂��Ă�������(0�`127)�F";
	cin>>speed;

	//�ЂƂ܂����[�U���w�肵���p�x��
	return_angle=s1.krs_move(id,angle,speed);
	
	cout<<"\nangle:"<<return_angle<<"\n";
	while(1);

	return 0;
}