#include "DrawTexture.h"

using namespace GameL;

TextureHandorList Draw::list;

//外部グラフィックファイルを読み込む
void DrawTexture::LoadImage(char* name, int id)
{
	for each (TextureData texure_data in list)
		//過去に登録したテクスチャデータの中で同じIDが存在していたら終了する
		if (texure_data.image_id == id)
			return;
	
	//テクスチャデータ
	TextureData texture;
	//IDを設定
	texture.image_id = id;
	//ハンドルを設定
	texture.texture_handor = new int[1];
	texture.texture_handor[0] = LoadGraph(name);

	//リストに追加する
	list.push_back(texture);
}
//外部グラフィックファイルの分割読み込み
/*
引数1 char* name	:ファイル名
引数2 int	id		:登録ID
引数3 int	all_num	:画像の分割総数
引数4 int	x_num	:画像の横向きに対する分割数
引数5 int	y_num	:画像の縦向きに対する分割数
引数6 int	x_size	:分割された1つの大きさ(X)
引数7 int	y_size	:分割された1つの大きさ(Y)
＊分割をした場合、表示するために必要な分割IDは以下のように割り振られる
	XNum = 4 ; YNum = 4 ; AllNum = 14 ;
	0	1	2	3
	4	5	6	7
	8	9	10	11
	12	13
*/
void DrawTexture::LoadDevImage(char* name, int id, int all_num, int x_num, int y_num, int x_size, int y_size)
{
	for each (TextureData texure_data in list)
		//過去に登録したテクスチャデータの中で同じIDが存在していたら終了する
		if (texure_data.image_id == id)
			return;

	//テクスチャデータ
	TextureData texture;
	//IDを設定する
	texture.image_id = id;
	//ハンドルを設定する
	texture.texture_handor = new int[all_num];
	LoadDivGraph(name, all_num, x_num, y_num, x_size, y_size, texture.texture_handor);

	//リストに追加
	list.push_back(texture);
}

//登録したテクスチャを表示
//引数 int div_id	:分割読み込みした時の番号　※分割読み込みしていないなら設定しないでよい
void DrawTexture::Draw(int x,int y,int id, bool trans_flag, int div_id)
{
	for each (TextureData texture_data in list)
	{
		//指定されたIDが一致したら
		if (texture_data.image_id == id)
		{
			//テクスチャが存在していたら表示
			if (texture_data.texture_handor[div_id] != NULL)
			{
				DrawGraph(x, y, texture_data.texture_handor[div_id], trans_flag);
				return;
			}
		}
	}
}
//登録したテクスチャをサイズ指定で表示
void DrawTexture::Draw(int x, int y, int x_size, int y_size, int id, bool trans_flag, int div_id)
{
	for each (TextureData texture_data in list)
	{
		//指定されたIDが一致したら
		if (texture_data.image_id == id)
		{
			//テクスチャが存在していたら表示
			if (texture_data.texture_handor[div_id] != NULL)
			{
				DrawExtendGraph(x, y, x + x_size, y + y_size, texture_data.texture_handor[div_id], trans_flag);
			}
		}
	}
}
//登録したテクスチャをLR反転かつサイズ指定で表示
void DrawTexture::DrawLRTurn(int x, int y, int x_size, int y_size , int id, bool trans_flag, int div_id)
{
	for each (TextureData texture_data in list)
	{
		//指定されたIDが一致したら
		if (texture_data.image_id == id)
		{
			//テクスチャが存在していたら表示
			if (texture_data.texture_handor[div_id] != NULL)
			{
				DrawExtendGraph(x + x_size, y, x, y+y_size, texture_data.texture_handor[div_id], trans_flag);
			}
		}
	}
}

//描画用オブジェクト破棄
void DrawTexture::DeleteDrawTexture()
{
	//読みこんだグラフィックデータをすべて削除する
	InitGraph();
	//リストを初期化する
	list.clear();
}


