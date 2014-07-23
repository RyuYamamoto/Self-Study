//インクルード
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <windows.h>
#using <System.dll>

//名前空間の指定
using namespace std;
using namespace System;
using namespace System::IO::Ports;

//グローバル変数
bool flag=true; //読み取れているかどうかの判定用変数(0:成功/1:失敗)
static int servo_id[]={0,1,2,3,4,5,6,7};//サーボID格納配列

//Serialクラス
class Serial{
public:
	//Serial(); //コンストラクタ関数
	~Serial(); //デストラクタ関数
	void off_set_load();//off_set.txtをロードしてサーボに初期値として代入する関数
	int krs_move(int id,int angle,int speed); //サーボ移動関数
	int krs_read(int id);//サーボ角度読み取り関数
	int krs_speed(int id,int speed);//サーボ速度変更関数
};

//コンストラクタ関数
/*Serial::Serial()
{
	SerialPort^ port=gcnew SerialPort("COM5",115200,Parity::Even,8,StopBits::One);//COMの設定とボーレートの設定
	port->Open();//ポート接続
}*/

//デストラクタ関数(バッファを破棄)
Serial::~Serial()
{
	SerialPort^ port;
	port->DiscardInBuffer();   //受信バッファ破棄
	port->DiscardOutBuffer();  //送信バッファ破棄
}

//サーボ移動関数
//Serial::set_pos(サーボID,移動角度(0<=anglevalue<=180),速度(0<=speed<=127(0は脱力状態)))
int Serial::krs_move(int id,int angle,int speed)
{
	SerialPort^ port=gcnew SerialPort("COM3",115200,Parity::Even,8,StopBits::One);//シリアルの設定
	port->Open();//ポート接続
	//SerialPort^ port;
	int anglevalue; //角度をコマンド値に変換
	int dat;//サーボの現在位置を格納する変数
	array<Byte>^tx = {0,0,0};//送信用バッファ
	array<Byte>^rx = {0,0,0,0,0,0};//受信用バッファ

	port->DiscardInBuffer();   // 受信バッファ破棄
    port->DiscardOutBuffer();  //送信バッファ破棄

	//角度変換
	anglevalue = angle * 27.777777777777777777777777777778 + 5000.0;

	tx[0]=(Byte)(0xC0 | id);//CMD(0x110xxxxx と idの論理和)→スピード変更CMD
	tx[1]=(Byte)(0x02);//サブコマンド(2がスピード可変モード)
	tx[2]=(Byte)(speed);//(速度)

	port->Write(tx,0,3);//3バイト送信

	port->DiscardInBuffer();   // 受信バッファ破棄
    port->DiscardOutBuffer();  //送信バッファ破棄

	//コマンド
	tx[0] = (Byte)(0x80 | id); //CMD(0x10000000 と idの論理和)
    tx[1] = (Byte)((anglevalue>>7) & 0x7F); //POS_H(上位7ビット)
    tx[2] = (Byte)(anglevalue & 0x7F); //POS_L(下位7ビット)

	//データ送信
	port->Write(tx,0,3);
	
	//6回読み取り
	for (int i = 0; i < 3; i++){
		try{
			rx[i] = (Byte)port->ReadByte(); //データ受信
		}
		catch(...)
		{
			flag = false;//例外が発生
			break;
		}
		if(flag=false)
			return -1;//例外が発生した場合は-1を返す
	}
	port->Close();//ポートを閉じる

	dat=(int)rx[1];
	dat=(dat<<7)+(int)rx[2];

	return dat;
}

//速度変更用関数(移動関数のほうの引数でスピードも可変できるので需要ないかも。一応サーボからの速度返却します)
int Serial::krs_speed(int id,int speed)
{
	SerialPort^ port=gcnew SerialPort("COM3",115200,Parity::Even,8,StopBits::One);//シリアルの設定
	port->Open();//ポート接続

	int dat;
	array<Byte>^tx = {0,0,0};
	array<Byte>^rx = {0,0,0,0,0,0};

	tx[0]=(Byte)(0xC0 | id);//CMD(0x110xxxxx と idの論理和)
	tx[1]=(Byte)(0x02);//サブコマンド(2がスピード可変モード)
	tx[2]=(Byte)(speed);//(速度)

	port->Write(tx,0,3);

	for(int i=0;i<6;i++){
		try{
			rx[i] = (Byte)port->ReadByte(); //データ受信
		}
		catch(...)
		{
			flag = false;//例外が発生
			break;
		}
		if(flag=false)
			return -1;//例外が発生した場合は-1を返す
	}
	port->Close();

	dat=(int)rx[5];//スピードが返却
	return dat;
}
