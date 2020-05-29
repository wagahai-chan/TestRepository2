#pragma once
#include <memory>
#include <tuple> 
#include <_debug/_DebugConOut.h>
#include <common\Vector2.h>
#include <Scene\BaseScene.h>
#include <Scene/TitleScene.h>
#include <common\ImageMng.h>
#include "LAYER_ID.h"
#include <vector>
#include <map>

enum class DRAW_QUE // enum‚ÍŒ^‚ªB–† class‚ğ‚Â‚¯‚é‚Æclass–¼–¼‘O‹óŠÔ‚¾‚©‚çX‚Æ‚¢‚¤–¼‘O‚ª“¯‚¶‚Å‚àˆá‚¤‚à‚Ì‚É‚È‚é 
{
	IMAGE,
	X,
	Y,
	RATE,
	RAD,
	ZORDER,		// Ú²Ô°“à‚Ì•`‰æ‡(”’l“à‚Ì’á‚¢‚Ù‚¤‚ª‰œ)
	LAYER,		// ID‚Ì¬‚³‚¢‚Ù‚¤‚ª‰œ‚É•`‰æ
	DRAW_MODE,	// •`‰æƒ‚[ƒh
	DRAW_NUM	// •`‰æƒ‚[ƒh‚É“n‚·’l
};

#define lpSceneMng SceneMng::GetInstance()

using DrawQueT = std::tuple<int, double, double,double, double,LAYER,bool>;
						//  id    x        y    Šg‘å—¦   rad   ”½–Ê

class SceneMng
{
public:
	static SceneMng &GetInstance(void)
	{
		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new SceneMng();
		}
	}

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr; // ÃŞØ°Ä‚µ‚Ä‚àºŞĞ‚ª‚Ì‚±‚é‚©‚çnull‚ğ‚¢‚ê‚é
	}

	void Run(void);
	bool AddDrawQue(DrawQueT dQue);
	bool AddActQue(ActQueT aQue);
	bool AddMakeQue(MakeQueT mQue);
	bool AddDeleteQue(DeleteQueT dQue);

	const Vector2 ScreenSize;
	const Vector2 ScreenCenter;			// ½¸Ø°İ‚Ì’†S

	double PX;		// ÌßÚ²Ô°‚Æ‰æ–Ê’†‰›‚Æ‚Ì·•ª
	double Pos[3];
	bool check[static_cast<int>(UNIT_ID::MAX)][4];		// ‚Ç‚ê‚©ˆê‚Â‚Å‚à‚ ‚½‚Á‚Ä‚¢‚ê‚Îtrue‚É‚µ‚Ä“®‚«‚ğ~‚ß‚é
	
	bool makeFlag = false;	// true:MakeScene  false:GameScene

	std::vector<sharedObj> _saveList;

private:
	static SceneMng* sInstance;

	unique_Base _activeScene;

	void Draw(void);

	std::vector<DrawQueT> _drawList;
	std::vector<ActQueT>  _actList;
	std::vector<MakeQueT> _makeList;
	std::vector<DeleteQueT> _deleteList;

	~SceneMng();
	SceneMng();
	bool SysInit(void);
};
