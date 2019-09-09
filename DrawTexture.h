#pragma once
#include "DxLib.h"
#include <list>

using namespace std;

namespace GameL
{
	//テクスチャデータ
	class TextureData
	{
	public:
		int image_id;		//読み込む際に設定したID情報(同じIDは存在しない)
		int* texture_handor;	//テクスチャのハンドル
	};

	//テクスチャハンドルリスト用テンプレート
	typedef list<TextureData> TextureHandorList;

	typedef class DrawTexture
	{
		public:
			//外部グラフィックファイルを読み込む
			static void LoadImage(char* name, int id);
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
			static void LoadDevImage(char* name, int id, int all_num, int x_num, int y_num, int x_size, int y_size);

			//登録したテクスチャを表示
			//引数2 int div_id	:分割読み込みした時の番号＊分割読み込みしていないなら設定しないでよい
			static void Draw(int x, int y, int id,bool trans_flag, int div_id=0);
			//登録したテクスチャをサイズ指定で表示
			static void Draw(int x, int y, int x_size, int y_size, int id, bool trans_flag, int div_id = 0);
			//登録したテクスチャをLR反転かつサイズ指定で表示
			static void DrawLRTurn(int x, int y, int x_size, int y_size, int id, bool trans_flag, int div_id = 0);
			//描画用オブジェクト破棄
			static void DeleteDrawTexture();
		private:
			//読み込んだTexture保存用List
			static TextureHandorList list;
	}Draw;
}