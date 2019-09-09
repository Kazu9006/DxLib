#include "SceneObjManager.h"
using namespace GameL;

//ソート用 描画優先順位を比較する(降順)
int DrawOrderCompare(const shared_ptr<CObj> x, const shared_ptr<CObj> y)
{
	return x.get()->GetDrawOrder() < y.get()->GetDrawOrder();
}

list<shared_ptr<CObj>>*	SceneObjManager::m_list_data;	//ゲーム実行リスト

//----------------------------CObj----------------------------
CObj::CObj()
{
	m_draw_order = 0;
	m_name = 0;
	m_active = true;
}

//描画優先順位変更
void CObj::SetDrawOrder(unsigned int draw_order)
{
	//値を変更する
	m_draw_order = draw_order;
	//リストを並び替える
	SceneObjManager::ResetDrawOrder();
}

//設定している描画優先順位取得用
unsigned int CObj::GetDrawOrder()
{
	return m_draw_order;
}

//オブジェクト名前ID変更用
void CObj::SetName(int name)
{
	m_name = name;
}

//オブジェクト名前ID取得用
int CObj::GetName()
{
	return m_name;
}

//オブジェクトのアクティブ状態を変更
void CObj::SetActive(bool active)
{
	m_active = active;
}

//オブジェクトのアクティブ状態を取得用
bool CObj::GetActive()
{
	return m_active;
}
//-----------------------------------------------------------

//----------------------SceneObjManager----------------------
//初期化
void SceneObjManager::Init()
{
	m_list_data = new list<shared_ptr<CObj>>;
}

//削除
void SceneObjManager::Delete()
{
	m_list_data->clear();
	delete m_list_data;
}

//オブジェクトの登録
void SceneObjManager::InsertObj(CObj* obj, int name, unsigned int draw_order)
{
	if (obj == nullptr)
		return;

	//オブジェクトの初期化メソッド実行
	obj->Init();

	//オブジェクトの名前設定
	obj->SetName(name);

	//データ登録
	unique_ptr<CObj> ptr_obj(obj);
	//移動
	m_list_data->push_front(move(ptr_obj));

	//オブジェクトの描画優先順位設定
	obj->SetDrawOrder(draw_order);

	return;
}

//オブジェクトリスト削除命令
void SceneObjManager::ListDeleteSceneObj()
{
	for (auto itr = m_list_data->begin(); itr != m_list_data->end(); itr++)
	{
		m_list_data->erase(itr);
	}
}

//リストに登録している全てのオブジェクトのアクションメソッド実行
void SceneObjManager::ObjsAction()
{
	for (auto itr = m_list_data->begin(); itr != m_list_data->end(); itr++)
	{
		//アクティブ状態ならアクションメソッド実行
		if ((*itr)->GetActive() == true)
			(*itr)->Action();
	}
}

//リストに登録している全てのオブジェクトの描画メソッド実行
void SceneObjManager::ObjsDraw()
{
	for (auto itr = m_list_data->begin(); itr != m_list_data->end(); itr++)
	{
		//アクティブ状態なら描画メソッド実行
		if ((*itr)->GetActive() == true)
			(*itr)->Draw();
	}
}

//描画優先順位を変更(リストを描画優先順位の降順に並び替え)
void SceneObjManager::ResetDrawOrder()
{
	//リストに２つ以上情報があればソートをする
	if (m_list_data->size() >= 2)
	{
		m_list_data->sort(DrawOrderCompare);
	}
}

//名前情報からオブジェクト情報を１つ取得
CObj* SceneObjManager::GetObj(int name)
{
	for (auto itr = m_list_data->begin(); itr != m_list_data->end(); itr++)
	{
		//アクティブ状態なら取得できる
		if ((*itr)->GetActive() == true)
		{
			//名前が一致した最初のオブジェクト情報を渡す
			if ((*itr)->GetName() == name)
				return (*itr).get();
		}
	}

	return nullptr;
}

//名前情報からオブジェクト情報を複数取得
CObj** SceneObjManager::GetObjs(int name)
{
	CObj** objs = nullptr;

	int obj_count = 0;

	//名前が一致するオブジェクトがいくつ存在するかを数える
	for (auto itr = m_list_data->begin(); itr != m_list_data->end(); itr++)
	{
		//アクティブ状態なら
		if ((*itr)->GetActive() == true)
		{
			//名前が一致したならカウントを加算する
			if ((*itr)->GetName() == name)
				obj_count++;
		}
	}

	//いくつ同名のオブジェクトがあるか判明したのでメモリをセットする
	objs = new CObj*[obj_count];
	//オブジェクトカウントを使い回したいので初期化
	obj_count = 0;

	//後はもう一度同名のオブジェクトを検索して格納する
	for (auto itr = m_list_data->begin(); itr != m_list_data->end(); itr++)
	{
		//アクティブ状態なら
		if ((*itr)->GetActive() == true)
		{
			//名前が一致しら、格納する
			if ((*itr)->GetName() == name)
				objs[obj_count++] = (*itr).get();
		}
	}

	//全てが完了したので渡す
	return objs;
}

//-----------------------------------------------------------
