#pragma once
#include "DxLib.h" 
#include "DrawTexture.h"
#include "GameHead.h"
#include "Input.h"
#include "SceneObjManager.h"

using namespace GameL;


//向きの情報
namespace PlayerDirection
{
	constexpr int FRONT	{0};	//正面
	constexpr int UP	{1};		//上
	constexpr int DOWN	{2};	//下
	constexpr int LEFT	{3};	//左
	constexpr int RIGHT	{4};//右
}
//プレイヤー
class CObjPlayer : public CObj{
	public:
		CObjPlayer(float pos_x, float pos_y);//コンストラクタ
		void Init();	//初期化
		void Action();//処理
		void Draw();//描画
		float GetX() { return m_pos_x; }
		float GetY() { return m_pos_y; }
	private:
		float m_pos_x, m_pos_y;	//プレイヤーの位置情報
		float m_vec_x, m_vec_y;	//プレイヤーの移動ベクトル
		float m_move_speed;		//プレイヤーの移動速度
		float m_posture;			//プレイヤーの向き情報: PlayerPosture参照
};
