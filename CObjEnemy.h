#pragma once
#include "DxLib.h" 
#include "DrawTexture.h"
#include "GameHead.h"

#include "SceneObjManager.h"

using namespace GameL;

//敵
class CObjEnemy : public CObj{
public:
	CObjEnemy(float x, float y);//コンストラクタ
	void Init();	//初期化
	void Action();//処理
	void Draw();//描画
	float GetX() { return m_pos_x; }
	float GetY() { return m_pos_y; }
private:
	float m_pos_x, m_pos_y;	//箱の位置情報
};
