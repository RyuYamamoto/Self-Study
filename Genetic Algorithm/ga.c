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

	srand(unsigned(time(NULL)));
	for(int i=0;i<indivisual;i++){
		for(int j=0;j<city_number;j++){
			num = rand()%