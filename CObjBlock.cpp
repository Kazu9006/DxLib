#include "CObjBlock.h"

CObjBlock::CObjBlock()
{
	int map[MAP_SIZE_Y][MAP_SIZE_X] = { { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
										{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
										{ 1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1 },
										{ 1,1,1,0,1,0,1,0,1,1,1,4,1,0,1,0,1 },
										{ 1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1 },
										{ 1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1 },
										{ 1,0,0,0,0,0,0,0,1,0,0,3,0,0,0,0,1 },
										{ 1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1 },
										{ 1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1 },
										{ 1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1 },
										{ 1,0,0,0,0,0,0,2,1,0,0,0,0,0,0,0,1 },
										{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	memcpy(m_map, map, sizeof(int) * (MAP_SIZE_X * MAP_SIZE_Y));
}

void CObjBlock::Init()
{

}

void CObjBlock::Action()
{

}

void CObjBlock::Draw()
{
	//マップの表示 (最初の１回はPlayerやEnemyを作成)
	for (int map_y = 0; map_y < MAP_SIZE_Y; map_y++)
	{
		for (int map_x = 0; map_x < MAP_SIZE_X; map_x++)
		{
			//画像のID情報格納用
			int image_id = -1;
			switch (m_map[map_y][map_x])
			{
					//ブロック
				case MapNumber::BLOCK:
					image_id = ImageID::BLOCK;
					break;
					//プレイヤー
				case MapNumber::PLAYER:
				{
					//image_id = ImageID::PLAYER;
					CObjPlayer* player = new CObjPlayer((float)(ImageSize::ALL * map_x), (float)(ImageSize::ALL * map_y));
					Objs::InsertObj(player, ObjName::PLAYER, 10);
					m_map[map_y][map_x] = 0;
					break;
				}
				//蜘蛛の巣
				case MapNumber::NET:
					image_id = ImageID::NET;
					break;
					//敵
				case MapNumber::ENEMY:
				{
					//image_id = ImageID::ENEMY;
					CObjEnemy* enemy = new CObjEnemy(ImageSize::ALL * map_x, ImageSize::ALL * map_y);
					Objs::InsertObj(enemy, ObjName::ENEMY, 4);
					m_map[map_y][map_x] = 0;
					break;
				}
			}
			//image_idが-1でなければ画像を表示する
			if (image_id != -1)
				Draw::Draw(map_x * ImageSize::ALL, map_y * ImageSize::ALL, ImageSize::ALL, ImageSize::ALL, image_id, true);
		}
	}
}

//BlockHit関数
//引数１	float *x		:判定を行うobjectのX位置
//引数２	float *y		:判定を行うobjectのY位置
//引数３	bool scroll_on	:判定を行うobjectはスクリーンの影響を与えるかどうか(true=与える　false=与えない)
//引数４	bool *up		:上下左右判定の上部分に当たっているかどうかを返す
//引数５	bool *down		:上下左右判定の下部分に当たっているかどうかを返す
//引数６	bool *left		:上下左右判定の左部分に当たっているかどうかを返す
//引数７	bool *right		:上下左右判定の右部分に当たっているかどうかを返す
//引数８	float *rvx		:左右判定時の反発による移動方向・力の値を変えて返す
//引数９	const float *speed_power	:スピードのパワー

//判定を行うobjectとブロック40*40限定で、当たり判定と上下左右判定を行う。
//その結果は引数４～１０に返す
void CObjBlock::BlockHit(
	float *x, float *y, bool scroll_on,
	bool *up, bool *down, bool *left, bool *right,
	float *vx, float *vy, const float *speed_power
)
{
	//衝撃状態確認用フラグの初期化
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//主人公情報をもってくる
	CObjPlayer * player = (CObjPlayer*)Objs::GetObj(ObjName::PLAYER);

	//持ってきたオブジェクト座標が主人公のものかどうか確認用
	bool hero_is_confirmation = false;//true:主人公のものと断定  false:主人公のもので無いと断定

	//主人公オブジェクトが存在していたら
	if (player != nullptr)
	{
		//X位置を検索
		if (*x == player->GetX())
		{
			//Y位置を検索
			if (*y == player->GetY())
			{
				//持ってきたオブジェクトの座標が主人公の座標と一致
				hero_is_confirmation = true;
			}
		}
	}

	//m_maoの全要素にアクセス
	for (int map_y = 0; map_y < MAP_SIZE_Y; map_y++)
	{
		for (int map_x = 0; map_x < MAP_SIZE_X; map_x++)
		{
			//調べようとしていいる場所にブロックがあったら
			if (m_map[map_y][map_x] == 1)
			{
				//要素番号を座標に変更
				float bx = (float)map_x * ImageSize::ALL;
				float by = (float)map_y * ImageSize::ALL;

				//スクロールの影響
				float scroll = scroll_on ? 0.0f : 0.0f;

				//オブジェクトとブロックのあたり判定
				if ((*x + (-scroll) + ImageSize::ALL > bx) && (*x + (-scroll) < bx + ImageSize::ALL) && (*y + ImageSize::ALL > by) && (*y < by + ImageSize::ALL))
				{
					//上下左右判定

					//vectorの作成
					float rvx = (*x + (-scroll)) - bx;
					float rvy = *y - by;

					//長さを求める
					float len = sqrt(rvx * rvx + rvy * rvy);

					//角度を求める
					float r = atan2(rvy, rvx);
					r = r * 180.0f / 3.14f;

					if (r <= 0.0f)
						r = abs(r);
					else
						r = 360.0f - abs(r);

					if (len < 88.0)
					{
						//角度で上下左右を判定
						//右
						if ((r < 45 && r >= 0) || r > 315)
						{
							if (!(*vx > 0))//右に移動していたら判定しない
							{
								*right = true;//オブジェクトの左の部分が衝突している
								*x = bx + ImageSize::ALL + (scroll);//ブロックの位置　+　オブジェクトの幅

																//真右(真横)より上
								if ((r < 45 && 0 < r))
								{
									//主人公オブジェクトだったら規定のボタンを押した場合だけ処理。
									//主人公オブジェクトではなかったらそのまま処理
									if (hero_is_confirmation == false || (hero_is_confirmation == true && (Input::GetKey(KEY_INPUT_LEFT) == true)))
									{
										//上の上
										if (r <= 45 && r >= 44)
										{
											//今のYの位置の上の位置に移動
											*y = ((float)map_y - 1) * ImageSize::ALL;
											*x += -1.0f;
										}
										else
										{
											*vy = -*speed_power;
										}
									}
								}
								//真右(真横)より下 && 下にブロックが無かったら
								else if (r > 315)
								{
									//主人公オブジェクトだったら規定のボタンを押した場合だけ処理。
									//主人公オブジェクトではなかったらそのまま処理
									if (hero_is_confirmation == false || (hero_is_confirmation == true && (Input::GetKey(KEY_INPUT_LEFT) == true)))
									{
										//下の下
										if (r >= 315 && r <= 316)
										{
											//今のYの位置の下の位置に移動
											*y = ((float)map_y + 1) * ImageSize::ALL;
											*x += -1.0f;
										}
										else
										{
											*vy = *speed_power;
										}
									}
								}
								//下にも上にもブロックがあったら
								else if (m_map[map_y + 1][map_x] != 0 && m_map[map_y - 1][map_x] != 0)
								{
									*vx = -(*vx) * 0.1f;//-VX*反発係数
								}
							}
						}
						//上
						if (r > 45 && r < 135)
						{
							if (!(*vy < 0))//上に移動していたら判定しない
							{
								*down = true;//オブジェクトの下の部分が衝突している
								*y = by - ImageSize::ALL;//ブロックの位置　-　主人公の幅
								*vy = 0.0f;
								//真上より右
								if (r > 45 && r < 90)
								{
									//右の右
									if (r > 45 && r < 46)
									{
										*x = (map_x + 1) * ImageSize::ALL + scroll;
										*y += 1.0f;
									}
									else
									{
										*vx = *speed_power;
									}
										
								}
								//真上より左
								else if (r < 135 && r > 90)
								{
									//左の左
									if (r < 135 && r > 134)
									{
										*x = (map_x - 1) * ImageSize::ALL + scroll;
										*y += 1.0f;
									}
									else
									{
										*vx = -*speed_power;
									}
								}
							}
						}
						//左
						if (r > 135 && r < 225)
						{
							if (!(*vx < 0))//左に移動していたら判定しない
							{
								*left = true;//オブジェクトの右の部分が衝突している
								*x = bx - ImageSize::ALL + (scroll);//ブロックの位置　-　オブジェクト幅

																//真左より上
								if ((r > 135 && r < 180))
								{
									//主人公オブジェクトだったら規定のボタンを押した場合だけ処理。
									//主人公オブジェクトではなかったらそのまま処理
									if (hero_is_confirmation == false || (hero_is_confirmation == true && (Input::GetKey(KEY_INPUT_RIGHT) == true)))
									{
										//左の左
										if (r > 135 && r < 136)
										{
											*y = ((float)map_y - 1) * ImageSize::ALL;
											*x += 1.0f;
										}
										else
										{
											*vy = -*speed_power;
										}
											
									}
								}
								//真左より下
								else if ((r < 225 || r > 180))
								{
									//主人公オブジェクトだったら規定のボタンを押した場合だけ処理。
									//主人公オブジェクトではなかったらそのまま処理
									if (hero_is_confirmation == false || (hero_is_confirmation == true && (Input::GetKey(KEY_INPUT_RIGHT) == true)))
									{
										//右の右
										if (r < 225 && r > 224)
										{
											*y = ((float)map_y + 1) * ImageSize::ALL;
											*x += 1.0f;
										}
										else
										{
											*vy = *speed_power;
										}
									}
								}
								//上下にブロックがあったら
								else if (m_map[map_y + 1][map_x] != 0 && m_map[map_y + 1][map_x] != 0)
								{
									*vx = -(*vx) * 0.1f;//-VX*反発係数
								}
							}

						}
						//下
						if (r > 225 && r < 315)
						{
							if (!(*vy > 0))//下に移動していたら判定しない
							{
								*up = true;//主人公から見て上の部分が衝突している
								*y = by + ImageSize::ALL;//ブロックの位置　+　主人公の幅
								*vy = 0.0f;
								//真下より左
								if (r > 225 && r < 275)
								{
									//左の左
									if (r > 225 && r < 226)
									{
										*x = (map_x - 1) * ImageSize::ALL + scroll;
										*y -= 1.0f;
									}
									else
									{
										*vx = -*speed_power;
									}
								}
								//真下より右
								else if (r < 315 && r > 275)
								{
									//右の右
									if (r < 315 && r > 314)
									{
										*x = (map_x + 1) * ImageSize::ALL + scroll;
										*y -= 1.0f;
									}
									else
									{
										*vx = *speed_power;
									}
										
								}
							}
						}
					}
				}
			}
		}
	}
}
