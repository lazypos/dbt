#include "ResourceManager.h"
#include <array>
#include <sstream>

CResourceManager::CResourceManager()
{
}


CResourceManager::~CResourceManager()
{
}

void CResourceManager::loadResource()
{
	loadCardResource();
	loadLoginResource();
	loadDeskResource();
}

void CResourceManager::loadCardResource()
{
	ostringstream	os;

	//load card flower
#define flower_weight 44
#define flower_height 42
	SpriteFrame *flowerframe = nullptr;
	flowerframe = SpriteFrame::create("poker_flower.png", Rect(0 * flower_weight, 0, flower_weight, flower_height));
	SpriteFrameCache::getInstance()->addSpriteFrame(flowerframe, "flower2");
	flowerframe = SpriteFrame::create("poker_flower.png", Rect(1 * flower_weight, 0, flower_weight, flower_height));
	SpriteFrameCache::getInstance()->addSpriteFrame(flowerframe, "flower0");
	flowerframe = SpriteFrame::create("poker_flower.png", Rect(2 * flower_weight, 0, flower_weight, flower_height));
	SpriteFrameCache::getInstance()->addSpriteFrame(flowerframe, "flower3");
	flowerframe = SpriteFrame::create("poker_flower.png", Rect(3 * flower_weight, 0, flower_weight, flower_height));
	SpriteFrameCache::getInstance()->addSpriteFrame(flowerframe, "flower1");

	//load card number
#define number_size	39
	SpriteFrame* numframe = nullptr;
	for (int i = 0; i < 13; i++) {
		os.str("");
		os << "r_num" << i;
		numframe = SpriteFrame::create("poker_num.png", Rect(i * number_size, number_size, number_size, number_size));
		SpriteFrameCache::getInstance()->addSpriteFrame(numframe, os.str());
		os.str("");
		os << "b_num" << i;
		numframe = SpriteFrame::create("poker_num.png", Rect(i*number_size, 0, number_size, number_size));
		SpriteFrameCache::getInstance()->addSpriteFrame(numframe, os.str());
	}

	//load surface
#define card_weight	98
#define card_height	138
	SpriteFrame* puke = nullptr;
	puke = SpriteFrame::create("poker_surface.png", Rect(0 * card_weight, 0, card_weight, card_height));
	SpriteFrameCache::getInstance()->addSpriteFrame(puke, "front");
	puke = SpriteFrame::create("poker_surface.png", Rect(1 + 1 * card_weight, 0, card_weight, card_height));
	SpriteFrameCache::getInstance()->addSpriteFrame(puke, "r_joker");
	puke = SpriteFrame::create("poker_surface.png", Rect(1 + 2 * card_weight, 0, card_weight, card_height));
	SpriteFrameCache::getInstance()->addSpriteFrame(puke, "b_joker");
	puke = SpriteFrame::create("poker_surface.png", Rect(1 + 3 * card_weight, 0, card_weight, card_height));
	SpriteFrameCache::getInstance()->addSpriteFrame(puke, "back");
}

void CResourceManager::loadLoginResource()
{
	//login
#define login_weight	350
#define login_height	60
	SpriteFrame* login = nullptr;
	login = SpriteFrame::create("login.png", Rect(0, 0, login_weight, login_height));
	SpriteFrameCache::getInstance()->addSpriteFrame(login, "login");
	login = SpriteFrame::create("nick.png", Rect(0, 0, login_weight, login_height));
	SpriteFrameCache::getInstance()->addSpriteFrame(login, "nick");
	login = SpriteFrame::create("pass.png", Rect(0, 0, login_weight, login_height));
	SpriteFrameCache::getInstance()->addSpriteFrame(login, "pass");
	login = SpriteFrame::create("rpass.png", Rect(0, 0, login_weight, login_height));
	SpriteFrameCache::getInstance()->addSpriteFrame(login, "rpass");
	login = SpriteFrame::create("sep.png", Rect(0, 0, 10, 768));
	SpriteFrameCache::getInstance()->addSpriteFrame(login, "sep");

	//hall
	login = SpriteFrame::create("add_desk_bg.png", Rect(0, 0, 323, 60));
	SpriteFrameCache::getInstance()->addSpriteFrame(login, "add_desk_bg");	
}

void CResourceManager::loadDeskResource()
{
	//¼ÓÔØ³öÅÆ°´Å¥
#define button_weight 152
#define button_height 61
	SpriteFrame* button = nullptr;
	button = SpriteFrame::create("poker_play_card.png", Rect(0, 0, button_weight, button_height));
	SpriteFrameCache::getInstance()->addSpriteFrame(button, "noputbtn");
	button = SpriteFrame::create("poker_play_card.png", Rect(button_weight, 0, button_weight, button_height));
	SpriteFrameCache::getInstance()->addSpriteFrame(button, "putbtn");

}
