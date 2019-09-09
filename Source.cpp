#include "DxLib.h"
#include <list>
#include <iterator>
#include <iostream>
#include <time.h>

#include "Input.h"
#include "DrawTexture.h"
#include "SceneObjManager.h"
#include "HitBoxManager.h"

#include "GameHead.h"

using namespace std;
using namespace GameL;


//関数参考サイト
//http://dxlib.o.oo7.jp/dxfunc.html

//マップの作製
void MapCreate(int map[][MAP_SIZE_X]);
//Map情報を描画
void DrawMap(int map[][MAP_SIZE_X]);
//移動処理関数
void Move(int &playerX, int &playerY,int &ballX,int &ballY, int map[][MAP_SIZE_X]);
//関数ランダム
//引数１	int min	:最小数
//引数２	int max	:最大数
//戻り値	最小数から最大数の間でランダムに値を渡す
int GetRandom(int min, int max);
//ゲーム終了判定
bool EndOfGameDetermination(int ballX, int ballY, int map[][MAP_SIZE_X]);

//プロブラムはWinMainから始まる
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);	//Windowモード(ウィンドウモード)

	if (DxLib_Init() == -1)	//DXライブラリ初期化処理
		return -1;			//エラーがおきたら終了

	//画像データの読み込み
	Draw::LoadDevImage	("Image/Player.png"	, ImageID::PLAYER,10,3,4,40,40);
	//Draw::LoadImage		("Image/Player.png", ImageID::PLAYER);
	Draw::LoadImage		("Image/Block.png"	, ImageID::BLOCK);
	Draw::LoadImage		("Image/Net.png"	, ImageID::NET);
	Draw::LoadDevImage	("Image/Enemy.png"	, ImageID::ENEMY,3,3,1,40,40);

	//描画先をバックバッファに設定
	SetDrawScreen(DX_SCREEN_BACK);
	
	//インプット初期化
	Input::Init();
	//オブジェクトマネージャー初期化「
	SceneObjManager::Init();
	//当たり判定初期化
	CHitBoxManager::Init();

	//マップオブジェクト生成
	CObjBlock* block = new CObjBlock();
	Objs::InsertObj(block,ObjName::BLOCK,5);

	//ゲームループ
	while (ProcessMessage() != -1)
	{
		//キーの状態を更新する
		Input::UpDataPushInfo();

		//テキストを表示
		DrawString(0, 0, "Text", 0xffff);

		//(仮)　全ての登録済みオブジェクトのアクションを実行
		SceneObjManager::ObjsAction();


		//ゲームが終了したかどうか判定を行う
		if (false)
		{
			DrawString(255, 255, "ゲームクリア！！！！！！！", 0xfffff);
			DrawString(260, 300, "Escを押すとゲーム終了する。", 0xffff);
		}

		//(仮)全ての登録済みのオブジェクトの描画を実行
		SceneObjManager::ObjsDraw();

		//エスケープキー入力で終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		ScreenFlip();//画面のフリップ
		//バックバッファを消去する
		ClearDrawScreen();
		
	}

	//オブジェクトマネージャーを破棄
	SceneObjManager::Delete();
	//描画用オブジェクトを破棄
	Draw::DeleteDrawTexture();
	//当たり判定を破棄
	CHitBoxManager::Delete();

	DxLib_End();	//DXライブラリ使用の終了処理

	return 0;	//ソフトの終了

}
//指定されたIDの位置情報をpos_x・pos_yに格納する
//＊複数ある場合は、最初に見つけた場所を格納する
void GetTheSpecifiedIDPos(int id,int map[][MAP_SIZE_X],int &pos_x,int &pos_y)
{
	for (int map_y = 0; map_y < MAP_SIZE_Y; map_y++)
	{
		for (int map_x = 0; map_x < MAP_SIZE_X; map_x++)
		{
			if (map[map_y][map_x] == id)
			{
				pos_x = map_x; pos_y = map_y;
				return;
			}
		}
	}
	pos_x = -1; pos_y = -1;
	return;
}
//指定された場所のID情報を取得
int GetTheSpecifiedPos(int pos_x, int pos_y, int map[][MAP_SIZE_X])
{
	return map[pos_y][pos_x];
}
//移動処理関数
void Move(int &playerX,int &playerY, int &ballX, int &ballY,int map[][MAP_SIZE_X])
{
	//移動ベクトル
	int playerVX=0, playerVY=0;

	//キーボード入力
	if (Input::GetKeyDown(KEY_INPUT_LEFT)) playerVX--;
	if (Input::GetKeyDown(KEY_INPUT_RIGHT)) playerVX++;
	if (Input::GetKeyDown(KEY_INPUT_UP)) playerVY--;
	if (Input::GetKeyDown(KEY_INPUT_DOWN)) playerVY++;

	//移動したい場所が移動可能場所なら
	if (GetTheSpecifiedPos(playerX + playerVX, playerY + playerVY, map) == 0)
	{
		//Playerの移動先に玉が存在していたら
		if (playerX + playerVX == ballX && playerY + playerVY == ballY)
		{
			//玉が移動したい場所が移動可能な場所ならPlayerとBallを移動をする
			if (GetTheSpecifiedPos(ballX + playerVX, ballY + playerVY, map) == 0 ||
				GetTheSpecifiedPos(ballX + playerVX, ballY + playerVY, map) == 3)
			{
				playerX += playerVX;
				playerY += playerVY;
				ballX	+= playerVX;
				ballY	+= playerVY;
			}
		}
		//Playerの移動先に玉がなければ移動をする
		else
		{
			playerX += playerVX;
			playerY += playerVY;
		}

	}
}
//関数ランダム
//引数１	int min	:最小数
//引数２	int max	:最大数
//戻り値	最小数から最大数の間でランダムに値を渡す
int GetRandom(int min, int max)
{
	static char s = 0;
	if (s == 0)
	{
		srand((unsigned)time(NULL));
		s = 1;
	}
	return min + (int)(rand()*(max - min + 1.0) / (1.0 + RAND_MAX));
}
//ゲーム終了判定
bool EndOfGameDetermination(int ballX, int ballY, int map[][MAP_SIZE_X])
{
	//ボールの位置に穴があればゲーム終了
	if (GetTheSpecifiedPos(ballX, ballY, map) == 3)
	{
		return true;
	}

	return false;
}