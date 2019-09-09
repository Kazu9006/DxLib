#pragma once
#include "DxLib.h"

#define KEY_MAX		(256)
#define MOUSE_BUTON_MAX	(3)

//2バイト(ビット演算用)
typedef unsigned short  BYTE2;

namespace GameL
{
	class Input
	{
		enum PushInfo
		{
			DownPressing = 0x0001,	//キーを押している(連射状態)
			DownMoment = 0x0010,	//キーを押していない状態から押した時
			UpMoment = 0x0100,	//キーを押している状態から離した時
		};

	public://関数用
	//初期化関数
		static void Init();

		//キーボード・マウスの状態を更新する
		static void UpDataPushInfo();

		//キーを押している間は常に(連射状態)
		static bool GetKey(int key);
		//キーを押していない状態から押した時
		static bool GetKeyDown(int key);
		//キーを押している状態から離した時
		static bool GetKeyUp(int key);

		//マウスを押している間は常に(連射状態)
		//引数 int botton:0=左ボタン 1=右ボタン 2=中央ボタン
		static bool GetMouseButton(int button);

		//マウスをおしていない状態から押した時
		//引数 int botton:0=左ボタン 1=右ボタン 2=中央ボタン
		static bool GetMouseButtonDown(int button);

		//マウスを押している状態から離した時
		//引数 int botton:0=左ボタン 1=右ボタン 2=中央ボタン
		static bool GetMouseButtonUp(int button);
	public://変数用
		static int m_mouse_x, m_mouse_y;//マウスの座標
	private://変数用
		static BYTE2 m_KeyBoard[KEY_MAX];//キーボード配列
		static BYTE2 m_MouseButon[MOUSE_BUTON_MAX];	//マウスのボタン

	};
}
