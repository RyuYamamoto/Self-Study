#include "RYSerialServo.h"

int main()
{
	int id,angle,speed,end=0;
	int return_angle,return_speed;

	Serial s1;//オブジェクトの生成

	cout<<"サーボIDを入力してください：";
	cin>>id;

	cout<<"角度を入力してください(0～180)：";
	cin>>angle;

	cout<<"速度を入力してください(0～127)：";
	cin>>speed;

	//ひとまずユーザが指定した角度へ
	return_angle=s1.krs_move(id,angle,speed);
	
	cout<<"\nangle:"<<return_angle<<"\n";
	while(1);

	return 0;
}