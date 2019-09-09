#pragma once


//オブジェクトネーム------------------------------

//------------------------------------------------


//当たり判定属性----------------------------------

//------------------------------------------------


//セーブ＆ロードとシーン間のやり取りするデータ----

//------------------------------------------------


//ゲーム内で使用されるグローバル変数・定数・列挙--


//読み込み画像のID-------------------------
namespace ImageID
{
	constexpr int NOT	{ 0 };
	constexpr int PLAYER{ 1 };
	constexpr int BLOCK	{ 2 };
	constexpr int NET	{ 3 };
	constexpr int ENEMY	{ 4 };
};
//画像のサイズ
namespace ImageSize
{
	constexpr int ALL	{38};
}

//マップの番号
namespace MapNumber
{
	constexpr int NOT	{0};
	constexpr int BLOCK	{1};
	constexpr int PLAYER{2};
	constexpr int NET	{3};
	constexpr int ENEMY	{4};
}

//オブジェクトネームID
namespace ObjName
{
	constexpr int PLAYER{0};
	constexpr int ENEMY	{1};
	constexpr int BLOCK	{2};
}

//当たり判定属性
namespace HitElement
{
	constexpr int NOT{0};//属性無し(全ての属性と当たり判定を行う)
	//以下　同属性同士は当たり判定を行わない
	//属性は追加可能だが、デバック時の色が初期設定分のみ(追加可能)
	constexpr int PLAYER{1};
	constexpr int ENEMY	{2};
	constexpr int ITEM	{3};
	constexpr int MAGIC	{4};
	constexpr int FIELD	{5};
	constexpr int RED	{6};
	constexpr int GREEN	{7};
	constexpr int BLUE	{8};
	constexpr int BLACK	{9};
	constexpr int WHiTE	{10};
}

//マクロ---------------------------
#define MAP_SIZE_X	(17)
#define MAP_SIZE_Y	(12)
//------------------------------------------------


//ゲーム内で使用するクラスヘッダ------------------

//------------------------------------------------


//ゲームシーンオブジェクトヘッダ------------------
#include "CObjPlayer.h"
#include "CObjEnemy.h"
#include "CObjBlock.h"

//------------------------------------------------


//シーンスタートクラス---------------------------

//------------------------------------------------