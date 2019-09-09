#pragma once
#include "DxLib.h" 
#include "DrawTexture.h"
#include "GameHead.h"

#include "SceneObjManager.h"

using namespace GameL;

//マップ
class CObjBlock : public CObj {
public:
	CObjBlock();//コンストラクタ
	void Init();	//初期化
	void Action();//処理
	void Draw();//描画
	//BlockHit関数
	void BlockHit(
		float *x, float *y, bool scroll_on,
		bool *up, bool *down, bool *left, bool *right,
		float *vx, float *vy, const float *speed_power
	);
private:
	int m_map[MAP_SIZE_Y][MAP_SIZE_X]; //マップ情報
};
