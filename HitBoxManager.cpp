#include "DrawTexture.h"	//デバックHitBox表示用
#include "HitBoxManager.h"

using namespace GameL;

//ポインタを安全に削除をする
#define SAFE_DELETE_ARRAY(p) {if(p) {delete[] (p); (p) = nullptr;}}

//当たり判定の複数同時時判定量
#define MAX_HITS	(10)



//-------------------CHitBox-------------------
CHitBox::CHitBox()
{
	m_my_obj = nullptr;
	m_hit_data = new HIT_DATA[MAX_HITS];
	m_hit_search_data = new HIT_DATA*[MAX_HITS];
	m_hit_count = 0;
	memset(&m_hit_status, 0x00, sizeof(HIT_STATUS));
}
CHitBox::~CHitBox()
{
	SAFE_DELETE_ARRAY(m_hit_data);
	SAFE_DELETE_ARRAY(m_hit_search_data);
}
//このHitBoxを持つオブジェクトを設定する
void CHitBox::SetObj(void* obj)
{
	m_my_obj;
}
//位置情報・サイズ情報を設定する
void CHitBox::SetPos(float pos_x, float pos_y, float width,float height )
{
	m_hit_box.pos_x = pos_x;
	m_hit_box.pos_y = pos_y;
	m_hit_box.width = width;
	m_hit_box.height = height;
	
}
//位置情報を設定する
void CHitBox::SetPos(float pos_x, float pos_y)
{
	m_hit_box.pos_x = pos_x;
	m_hit_box.pos_y = pos_y;
}
//属性・名前・ポイント情報を設定する
void CHitBox::SetStatus(int element, int name, int point)
{
	m_hit_status.element = element;
	m_hit_status.name = name;
	m_hit_status.point = point;
}
//無敵フラグを設定する
void CHitBox::SetInvincible(bool invincible)
{
	m_hit_status.invincible_flag = invincible;
}
//当たっている相手の数を返す
int	CHitBox::GetHitCount()
{
	return m_hit_count;
}
//無敵状態を返す
bool CHitBox::GetInvincibility()
{
	return m_hit_status.invincible_flag;
}
//このHIT_BOXを持つオブジェクトアドレスを返す
void* CHitBox::GetMyObj()
{
	return m_my_obj;
}
//ステータスの状態を返す
HIT_STATUS*	CHitBox::GetStatus()
{
	return &m_hit_status;
}
//位置・高さ・幅の情報を返す
HIT_BOX* CHitBox::GetHitBox()
{
	return &m_hit_box;
}


//当たっている相手の中から名前情報を元に検索し、ヒットしたオブジェクト情報を1つ返す
void* CHitBox::CheckObjNameHit(int obj_name)
{
	for (int hit_count = 0; hit_count < m_hit_count; hit_count++)
		if (m_hit_data[hit_count].obj != nullptr)
			if (m_hit_data[hit_count].name == obj_name)
				return m_hit_data[hit_count].obj;
	return nullptr;
}
//当たっている相手の中から名前・ポイント情報を元に検索し、ヒットしたオブジェクト情報を1つ返す
void* CHitBox::CheckObjNameHit(int obj_name, int point)
{
	for (int hit_count = 0; hit_count < m_hit_count; hit_count++)
		if (m_hit_data[hit_count].obj != nullptr)
			if (m_hit_data[hit_count].name == obj_name)
				if(m_hit_data[hit_count].point == point)
				return m_hit_data[hit_count].obj;
	return nullptr;
}
//当たっている相手の中から属性情報を元に検索し、ヒットしたかどうかを返す
bool CHitBox::CheckElementHit(int element)
{
	for (int hit_count = 0; hit_count < m_hit_count; hit_count++)
		if (m_hit_data[hit_count].obj != nullptr)
			if (m_hit_data[hit_count].element == element)
				return true;
	return false;
}
//当たっている相手の中から属性・ポイント情報を元に検索し、ヒットしたかどうかを返す
bool CHitBox::CheckElementHit(int element, int point)
{
	for (int hit_count = 0; hit_count < m_hit_count; hit_count++)
		if (m_hit_data[hit_count].obj != nullptr)
			if (m_hit_data[hit_count].element == element)
				if(m_hit_data[hit_count].point == point)
					return true;
	return false;
}

//当たっている相手の中から名前情報を元に検索し、ヒットした全て(最大数)のHIT_DATA情報を返す
HIT_DATA** CHitBox::SearchObjNameHit(int obj_name)
{
	//当たっている相手の情報を距離の昇順に並び替え
	SortHitBox();
	//探索をするので情報格納用変数のメモリをセットする
	memset(&(*m_hit_search_data), 0x00, sizeof(HIT_DATA*)*MAX_HITS);
	//探索でヒットした数
	int search_count = 0;
	for (int hit_count = 0; hit_count < m_hit_count; hit_count++)
		if (m_hit_data[hit_count].obj != nullptr)
			if (m_hit_data[hit_count].name == obj_name)
				m_hit_search_data[search_count++] = &m_hit_data[hit_count];
			
	//探索ヒットしなかったらnullptrを返す
	if (search_count == 0)
		return nullptr;
	else
		return m_hit_search_data;
}
//当たっている相手の中から名前・ポイント情報を元に検索し、ヒットした全て(最大数)のHIT_DATA情報を返す
HIT_DATA** CHitBox::SearchObjNameHit(int obj_name, int point)
{
	//当たっている相手の情報を距離の昇順に並び替え
	SortHitBox();
	//探索をするので情報格納用変数のメモリをセットする
	memset(&(*m_hit_search_data), 0x00, sizeof(HIT_DATA*)*MAX_HITS);
	//探索でヒットした数
	int search_count = 0;
	for (int hit_count = 0; hit_count < m_hit_count; hit_count++)
		if (m_hit_data[hit_count].obj != nullptr)
			if (m_hit_data[hit_count].name == obj_name)
				if(m_hit_data[hit_count].point == point)
					m_hit_search_data[search_count++] = &m_hit_data[hit_count];

	//探索ヒットしなかったらnullptrを返す
	if (search_count == 0)
		return nullptr;
	else
		return m_hit_search_data;
}
//当たっている相手の中から属性情報を元に検索し、ヒットした全て(最大数)のHIT_DATA情報を返す
HIT_DATA** CHitBox::SearchElementHit(int element)
{
	//当たっている相手の情報を距離の昇順に並び替え
	SortHitBox();
	//探索をするので情報格納用変数のメモリをセットする
	memset(&(*m_hit_search_data), 0x00, sizeof(HIT_DATA*)*MAX_HITS);
	//探索でヒットした数
	int search_count = 0;
	for (int hit_count = 0; hit_count < m_hit_count; hit_count++)
		if (m_hit_data[hit_count].obj != nullptr)
			if (m_hit_data[hit_count].element == element)
				m_hit_search_data[search_count++] = &m_hit_data[hit_count];

	//探索ヒットしなかったらnullptrを返す
	if (search_count == 0)
		return nullptr;
	else
		return m_hit_search_data;
}
//当たっている相手の中から属性・ポイント情報を元に検索し、ヒットした全て(最大数)のHIT_DATA情報を返す
HIT_DATA** CHitBox::searchElementHit(int element, int point)
{
	//当たっている相手の情報を距離の昇順に並び替え
	SortHitBox();
	//探索をするので情報格納用変数のメモリをセットする
	memset(&(*m_hit_search_data), 0x00, sizeof(HIT_DATA*)*MAX_HITS);
	//探索でヒットした数
	int search_count = 0;
	for (int hit_count = 0; hit_count < m_hit_count; hit_count++)
		if (m_hit_data[hit_count].obj != nullptr)
			if (m_hit_data[hit_count].element == element)
				if(m_hit_data[hit_count].point == point)
					m_hit_search_data[search_count++] = &m_hit_data[hit_count];

	//探索ヒットしなかったらnullptrを返す
	if (search_count == 0)
		return nullptr;
	else
		return m_hit_search_data;
}

//当たっている相手の情報を距離の昇順で並び替え
void CHitBox::SortHitBox()
{
	for (int front = 0; front < m_hit_count; front++)	//前
	{
		for (int rear = front + 1; rear < m_hit_count; rear++)	//後
		{
			//前の距離を取得
			float front_distance = (m_hit_data[front].obj == nullptr) ? 9999.0f : m_hit_data[front].distance;
			//後の距離を取得
			float rear_distance =  (m_hit_data[rear].obj == nullptr)  ? 9999.0f : m_hit_data[rear].distance;

			//前の距離より後の距離が短ければ並び替えを行う
			if (front_distance > rear_distance)
			{
				HIT_DATA hit_data;
				hit_data = m_hit_data[front];
				m_hit_data[front] = m_hit_data[rear];
				m_hit_data[rear] = hit_data;
			}
		}
	}
}
//---------------------------------------------

//---------------CHitBoxManager----------------
//初期化
void CHitBoxManager::Init()
{
	m_list_hitbox = new list<shared_ptr<CHitBox>>;
}
//削除
void CHitBoxManager::Delete()
{
	DeleteAllListData();
	delete m_list_hitbox;
}
//HitBoxの作成・登録
void CHitBoxManager::SetHitBox(void* obj, float pos_x, float pos_y, float width, float height, int element, int name, int point)
{
	//データの作成
	shared_ptr<CHitBox> ptr_box(new CHitBox());
	ptr_box->SetPos(pos_x,pos_y,width,height);	//位置・幅・高さを設定する
	ptr_box->SetStatus(element,name,point);		//属性・名前・ポイントを設定する
	ptr_box->SetObj(obj);						//オブジェクト情報を設定する
	ptr_box->SetInvincible(false);				//無敵情報を設定する
	m_list_hitbox->push_front(ptr_box);			//データの登録
}
//自身のアドレスを持つHitBoxを返す
CHitBox* CHitBoxManager::GetHitBox(void* obj)
{
	for each (auto itr in *m_list_hitbox)
	{
		if (itr->GetMyObj() == obj)
			return itr.get();
	}
}
//自身のアドレスを持つHitBoxの削除
void	CHitBoxManager::DeleteHitBox(void* obj)
{
	/*for each (auto itr in *m_list_hitbox)
	{
		if (itr->GetMyObj() == obj)
		{
			m_list_hitbox->erase(itr.get());
			return;
		}
	}*/
	for (auto itr = m_list_hitbox->begin(); itr != m_list_hitbox->end(); itr++)
	{
		if ((*itr).get()->GetMyObj() == obj)
		{
			m_list_hitbox->erase(itr);	//データ削除
			return;
		}
	}

}
//衝突判定
void	CHitBoxManager::AllHitCheck()
{
	for each (auto itr_my in *m_list_hitbox)
	{

	}
}
//衝突判定リストを破棄
void	CHitBoxManager::DeleteAllListData()
{
	m_list_hitbox->clear();
}
//デバック用　当たり判定描画
void	CHitBoxManager::DrawHitBox()
{

}
//---------------------------------------------