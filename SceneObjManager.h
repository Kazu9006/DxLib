#pragma once
#include <memory>
#include <list>
#include <algorithm>

using namespace std;

namespace GameL
{
	//継承抽象用　オブジェクトクラス
	class CObj
	{
		public:
			CObj();
			virtual ~CObj() {};
			virtual void Init() = 0;	//初期化関数
			virtual void Action() = 0;	//処理関数
			virtual void Draw() = 0;	//描画関数
			void		 SetDrawOrder(unsigned int draw_order);//描画優先順位を設定する
			unsigned int GetDrawOrder();					   //設定している描画優先順位取得用
			void		 SetName(int name);					   //オブジェクト名前ID変更用
			int			 GetName();							   //オブジェクト名前ID取得用
			void		 SetActive(bool active);			   //オブジェクトのアクティブ状態を変更
			bool		 GetActive();						   //オブジェクトのアクティブ状態を取得用

		private:
			unsigned int	m_draw_order;	//描画優先順番
			int				m_name;			//オブジェクトの名前ID
			bool			m_active;		//オブジェクトのアクティブ状態(Action・Drawを実行するかどうか)
	};

	//オブジェクトマネージャー
	typedef class SceneObjManager
	{
		public:
			static void Init();					//初期化関数
			static void Delete();				//削除関数
			static void InsertObj(CObj* obj,int name,unsigned int draw_order);	//オブジェクトの登録
			static void ListDeleteSceneObj();	//オブジェクトリスト削除命令
			static void ObjsAction();			//リストに登録している全てのオブジェクトのアクションメソッド実行
			static void ObjsDraw();				//リストに登録している全てのオブジェクトの描画メソッド実行
			static void ResetDrawOrder();		//描画優先順位を変更(リストを描画優先順位の降順に並び替え)

			static CObj* GetObj(int name);		//名前情報からオブジェクト情報を１つ取得
			static CObj** GetObjs(int name);	//名前情報からオブジェクト情報を複数取得
		private:
			static list<shared_ptr<CObj>>* m_list_data;	//ゲーム実行リスト
	}Objs;

}