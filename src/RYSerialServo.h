//�C���N���[�h
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <windows.h>
#using <System.dll>

//���O��Ԃ̎w��
using namespace std;
using namespace System;
using namespace System::IO::Ports;

//�O���[�o���ϐ�
bool flag=true; //�ǂݎ��Ă��邩�ǂ����̔���p�ϐ�(0:����/1:���s)
static int servo_id[]={0,1,2,3,4,5,6,7};//�T�[�{ID�i�[�z��

//Serial�N���X
class Serial{
public:
	//Serial(); //�R���X�g���N�^�֐�
	~Serial(); //�f�X�g���N�^�֐�
	void off_set_load();//off_set.txt�����[�h���ăT�[�{�ɏ����l�Ƃ��đ������֐�
	int krs_move(int id,int angle,int speed); //�T�[�{�ړ��֐�
	int krs_read(int id);//�T�[�{�p�x�ǂݎ��֐�
	int krs_speed(int id,int speed);//�T�[�{���x�ύX�֐�
};

//�R���X�g���N�^�֐�
/*Serial::Serial()
{
	SerialPort^ port=gcnew SerialPort("COM5",115200,Parity::Even,8,StopBits::One);//COM�̐ݒ�ƃ{�[���[�g�̐ݒ�
	port->Open();//�|�[�g�ڑ�
}*/

//�f�X�g���N�^�֐�(�o�b�t�@��j��)
Serial::~Serial()
{
	SerialPort^ port;
	port->DiscardInBuffer();   //��M�o�b�t�@�j��
	port->DiscardOutBuffer();  //���M�o�b�t�@�j��
}

//�T�[�{�ړ��֐�
//Serial::set_pos(�T�[�{ID,�ړ��p�x(0<=anglevalue<=180),���x(0<=speed<=127(0�͒E�͏��)))
int Serial::krs_move(int id,int angle,int speed)
{
	SerialPort^ port=gcnew SerialPort("COM3",115200,Parity::Even,8,StopBits::One);//�V���A���̐ݒ�
	port->Open();//�|�[�g�ڑ�
	//SerialPort^ port;
	int anglevalue; //�p�x���R�}���h�l�ɕϊ�
	int dat;//�T�[�{�̌��݈ʒu���i�[����ϐ�
	array<Byte>^tx = {0,0,0};//���M�p�o�b�t�@
	array<Byte>^rx = {0,0,0,0,0,0};//��M�p�o�b�t�@

	port->DiscardInBuffer();   // ��M�o�b�t�@�j��
    port->DiscardOutBuffer();  //���M�o�b�t�@�j��

	//�p�x�ϊ�
	anglevalue = angle * 27.777777777777777777777777777778 + 5000.0;

	tx[0]=(Byte)(0xC0 | id);//CMD(0x110xxxxx �� id�̘_���a)���X�s�[�h�ύXCMD
	tx[1]=(Byte)(0x02);//�T�u�R�}���h(2���X�s�[�h�σ��[�h)
	tx[2]=(Byte)(speed);//(���x)

	port->Write(tx,0,3);//3�o�C�g���M

	port->DiscardInBuffer();   // ��M�o�b�t�@�j��
    port->DiscardOutBuffer();  //���M�o�b�t�@�j��

	//�R�}���h
	tx[0] = (Byte)(0x80 | id); //CMD(0x10000000 �� id�̘_���a)
    tx[1] = (Byte)((anglevalue>>7) & 0x7F); //POS_H(���7�r�b�g)
    tx[2] = (Byte)(anglevalue & 0x7F); //POS_L(����7�r�b�g)

	//�f�[�^���M
	port->Write(tx,0,3);
	
	//6��ǂݎ��
	for (int i = 0; i < 3; i++){
		try{
			rx[i] = (Byte)port->ReadByte(); //�f�[�^��M
		}
		catch(...)
		{
			flag = false;//��O������
			break;
		}
		if(flag=false)
			return -1;//��O�����������ꍇ��-1��Ԃ�
	}
	port->Close();//�|�[�g�����

	dat=(int)rx[1];
	dat=(dat<<7)+(int)rx[2];

	return dat;
}

//���x�ύX�p�֐�(�ړ��֐��̂ق��̈����ŃX�s�[�h���ςł���̂Ŏ��v�Ȃ������B�ꉞ�T�[�{����̑��x�ԋp���܂�)
int Serial::krs_speed(int id,int speed)
{
	SerialPort^ port=gcnew SerialPort("COM3",115200,Parity::Even,8,StopBits::One);//�V���A���̐ݒ�
	port->Open();//�|�[�g�ڑ�

	int dat;
	array<Byte>^tx = {0,0,0};
	array<Byte>^rx = {0,0,0,0,0,0};

	tx[0]=(Byte)(0xC0 | id);//CMD(0x110xxxxx �� id�̘_���a)
	tx[1]=(Byte)(0x02);//�T�u�R�}���h(2���X�s�[�h�σ��[�h)
	tx[2]=(Byte)(speed);//(���x)

	port->Write(tx,0,3);

	for(int i=0;i<6;i++){
		try{
			rx[i] = (Byte)port->ReadByte(); //�f�[�^��M
		}
		catch(...)
		{
			flag = false;//��O������
			break;
		}
		if(flag=false)
			return -1;//��O�����������ꍇ��-1��Ԃ�
	}
	port->Close();

	dat=(int)rx[5];//�X�s�[�h���ԋp
	return dat;
}
