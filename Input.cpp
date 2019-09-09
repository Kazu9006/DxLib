#include "Input.h"

using namespace GameL;

BYTE2 Input::m_KeyBoard[KEY_MAX];
BYTE2 Input::m_MouseButon[MOUSE_BUTON_MAX];

int Input::m_mouse_x;
int Input::m_mouse_y;

//初期化関数
void Input::Init()
{
	//キーボードの初期化
	memset(m_KeyBoard, 0x00, sizeof(m_KeyBoard));
	//マウスの初期化
	memset(m_MouseButon, 0x00, sizeof(m_MouseButon));
	m_mouse_x = m_mouse_y = 0;
}

//キーボード・マウスの状態を更新する
void Input::UpDataPushInfo()
{
	//キーボードの状態を更新する
	for (int key = 0; key < KEY_MAX; key++)
	{
		//キーが押されていたら
		if (CheckHitKey(key))
		{
			//押し続けていた状態だったら
			if ((m_KeyBoard[key] & DownPressing) == DownPressing)
				//キーを押していない状態から押した時でないのでフラグをOFFにする
				m_KeyBoard[key] &= ~DownMoment;
			//押し続けている状態でなかったら
			else//キーを押していない状態からおしたときなのでフラグをONにする
				m_KeyBoard[key] |= DownMoment;
			

			//キーを押しているのでフラグをONにする
			m_KeyBoard[key] |= DownPressing;
		}
		//キーが押されていなかったら
		else
		{
			//押し続けていた状態だったら
			if ((m_KeyBoard[key] & DownPressing) == DownPressing)
				//キーを押し続けていた状態から離した時なのでフラグをONにする
				m_KeyBoard[key] |= UpMoment;
			else//押し続けていない状態だったら
				//キーを押し続けていない状態から離したわけでないのでフラグをOFFにする
				m_KeyBoard[key] &= ~UpMoment;

			//キーを押していないのでフラグをOFFにする
			m_KeyBoard[key] &= ~DownPressing;
		}
	}

	//マウスの状態を更新する
	GetMousePoint(&m_mouse_x, &m_mouse_y);
	for (int mouse = 0; mouse < MOUSE_BUTON_MAX; mouse++)
	{
		//GetMouseInputの戻り値調べる用
		int reference_mouse;
		switch (mouse)
		{
			//左ボタン
		case 0:
			reference_mouse = MOUSE_INPUT_LEFT;
			break;
			//右ボタン
		case 1:
			reference_mouse = MOUSE_INPUT_RIGHT;
			break;
			//中央ボタン
		case 2:
			reference_mouse = MOUSE_INPUT_MIDDLE;
			break;
		}

		//マウスのボタンが押されたら
		if (GetMouseInput() == reference_mouse)
		{
			//マウスを押し続けている状態なら
			if ((m_MouseButon[mouse] & DownPressing) == DownPressing)
				//マウスを押していない状態から押したわけではないのでフラグをOFFにする
				m_MouseButon[mouse] &= ~DownMoment;
			//マウスを押していない状態なら
			else//マウスを押していない状態から押したのでフラグをONにする
				m_MouseButon[mouse] |= DownMoment;

			//マウスを押したのでフラグをONにする
			m_MouseButon[mouse] |= DownPressing;
		}
		else
		{
			//マウスを押し続けていた状態なら
			if ((m_MouseButon[mouse] & DownPressing) == DownPressing)
				//マウスを押している状態から離したのでフラグをONにする
				m_MouseButon[mouse] |= UpMoment;
			//マウスを離している状態なら
			else//マウスを押している状態から離したわけでないのでフラグをOFFにする
				m_MouseButon[mouse] &= ~UpMoment;
			
			//マウスを離したのでフラグをOFFにする
			m_MouseButon[mouse] &= ~DownPressing;
		}
	}
}

//キーを押している間は常に(連射状態)
bool Input::GetKey(int key)
{
	if ((m_KeyBoard[key] & DownPressing) == DownPressing)
		return true;
	else
		return false;
}

//キーを押していない状態から押した時
bool Input::GetKeyDown(int key)
{
	if ((m_KeyBoard[key] & DownMoment) == DownMoment)
		return true;
	else
		return false;
}

//キーを押している状態から離した時
bool Input::GetKeyUp(int key)
{
	if ((m_KeyBoard[key] & UpMoment) == UpMoment)
		return true;
	else
		return false;
}

//マウスが押している間は常に(連射状態)
//引数 int botton:0=左ボタン 1=右ボタン 2=中央ボタン
bool Input::GetMouseButton(int button)
{
	if ((m_MouseButon[button] & DownPressing) == DownPressing)
		return true;
	else
		return false;
}

//マウスをおしていない状態から押した時
//引数 int botton:0=左ボタン 1=右ボタン 2=中央ボタン
bool Input::GetMouseButtonDown(int button)
{
	if ((m_MouseButon[button] & DownMoment) == DownMoment)
		return true;
	else
		return false;
}

//マウスを押している状態から離した時
//引数 int botton:0=左ボタン 1=右ボタン 2=中央ボタン
bool Input::GetMouseButtonUp(int button)
{
	if ((m_MouseButon[button] & UpMoment) == UpMoment)
		return true;
	else
		return false;
}


