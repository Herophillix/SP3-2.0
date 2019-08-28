#include "Screen.h"

Screen::Screen(SCREEN_AREA Area)
{
	ScreenArea = Area;
	Character = nullptr;
}

Screen::~Screen()
{

}

void Screen::Init(float m_worldWidth, float m_worldHeight)
{
	Character = new CharacterObject(CharacterObject::GO_SPRITE_TEST);
	Character->giveUp = false;
	Character->Statistics.m_experience = Math::RandFloatMinMax(1.f, 2.f);
	Character->Statistics.m_frustration = 0.f;
	Character->Statistics.m_motivation = 100.f;
	Character->Statistics.m_rest = 100.f;
	Character->setPos(Vector3(m_worldWidth / 4 - m_worldWidth / 8, m_worldHeight / 2 - 30, 5));
	Character->setScale(Vector3(30, 30, 30));
	Character->resting = false;
	Character->setActive(true);

	ItemObject* Television = new ItemObject(ItemObject::I_TELEVISION, static_cast<ItemObject::SCREEN_AREA>(ScreenArea));
	Television->setPos(Vector3(m_worldWidth * 0.8f, m_worldHeight / 2 - 30, 5));
	Television->setScale(Vector3(30, 25, 30));
	Television->setActive(true);
	m_itemList.push_back(Television);

	ItemObject* Computer = new ItemObject(ItemObject::I_COMPUTER, static_cast<ItemObject::SCREEN_AREA>(ScreenArea));
	Computer->setPos(Vector3(m_worldWidth * 0.25f, m_worldHeight / 2 - 50, 5));
	Computer->setScale(Vector3(30, 25, 30));
	Computer->setActive(true);
	m_itemList.push_back(Computer);


	ItemObject* SleepBox = new ItemObject(ItemObject::I_BOX, static_cast<ItemObject::SCREEN_AREA>(ScreenArea));
	SleepBox->setPos(Vector3(m_worldWidth * 0.4f, m_worldHeight / 2 + 35, 5));
	SleepBox->setScale(Vector3(30, 25, 30));
	SleepBox->setActive(true);
	m_itemList.push_back(SleepBox);

	UseItem = new MenuObject(MenuObject::M_USE_ITEM, Vector3(10, 10, 1));
	UseItem->setActive(true);
}

void Screen::Update(double dt, Vector3 v_mousepos, Vector3 rel_mousepos, Vector3 v_mousescale)
{
	Character->Update(dt);
	bool stop = false;
	for (int i = 0; i < (int)m_itemList.size(); ++i)
	{
		m_itemList[i]->Update(rel_mousepos, v_mousescale);
		if (!stop && Character->CheckCollision(m_itemList[i]))
		{
			stop = true;
		}
		else
		{
			switch (m_itemList[i]->getType())
			{
			case ItemObject::I_TELEVISION:
			{
				Character->resting = false;
				break;
			}
			case ItemObject::I_COMPUTER:
			{
				Character->WorkingHard = false;
				break;
			}
			case ItemObject::I_BOX:
			{
				Character->asleep = false;
				break;
			}
			default:
				Character->resting = false;
				Character->WorkingHard = false;
				Character->asleep = false;
				break;
			}
		}
	}
	UseItem->Update(v_mousepos);
	if (Character->currentItem)
	{
		if (UseItem->getChanged())
		{
			switch (Character->currentItem->getType())
			{
			case ItemObject::I_TELEVISION:
			{
				Character->resting = true;
				break;
			}
			case ItemObject::I_COMPUTER:
			{
				Character->WorkingHard = true;
				break;
			}
			case ItemObject::I_BOX:
			{
				Character->asleep = true;
				break;
			}
			default:
				break;
			}
		}
	}
}
