#ifndef  _CARDSPRITE_H_
#define  _CARDSPRITE_H_

#include <memory>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class CardSprite;
typedef shared_ptr<CardSprite>	cardSpritePtr;

class CardSprite
	: public Sprite
{
public:
	CardSprite();
	~CardSprite();
	
	void	setSeq(int seq) { _cardSeq = seq; };
	int		getSeq() { return _cardSeq; };
	void	setSelect(bool state) { _bSelected = state; };
	int		getSelect() { return _bSelected; };

	static	CardSprite* createCardSprite(int seq);

	CREATE_FUNC(CardSprite);
private:
	int		_cardSeq = -1;
	bool	_bSelected = false;
};

#endif