#define _GA_PROGRAM

//コンストラクタ
ga::ga(int a)
{
	city_number = a;		//都市の設定

	//都市
	city << 0,0,0,1,0,
			0,1,0,0,0,
			0,0,1,0,0,
			1,0,0,0,0,
			0,0,1,0,0;
}

//デストラクタ
ga::~ga()
{
	cout<<"メモリ解放\n";
}

//初期集団生成
void ga::initialize(int b)
{
	int num = 0;
	indivisual = b;		//個体数

	srand(unsigned(time(NULL)));
	for(int i=0;i<indivisual;i++){
		for(int j=0;j<city_number;j++){
		}
	}
}

//評価
void ga::evaluate()
{

}

//選択
void ga::selection()
{

}

//交叉
void ga::cross_over()
{

}

//突然変異
void ga::mutation()
{

}

//距離計算
double calc_distance(int x,int y)
{

}

