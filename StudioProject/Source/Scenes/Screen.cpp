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
	Character->pos.Set(m_worldWidth / 4 - m_worldWidth / 8, m_worldHeight / 2 - 30, 5);
	Character->scale = Vector3(30, 30, 30);
	Character->resting = false;
	Character->active = true;

	ItemObject* Television = new ItemObject(ItemObject::I_TELEVISION, static_cast<ItemObject::SCREEN_AREA>(ScreenArea));
	Television->pos.Set(m_worldWidth * 0.8, m_worldHeight / 2 - 30, 5);
	Television->scale = Vector3(30, 25, 30);
	Television->active = true;
	m_itemList.push_back(Television);

	ItemObject* Computer = new ItemObject(ItemObject::I_COMPUTER, static_cast<ItemObject::SCREEN_AREA>(ScreenArea));
	Computer->pos.Set(m_worldWidth * 0.25, m_worldHeight / 2 - 50, 5);
	Computer->scale = Vector3(30, 25, 30);
	Computer->active = true;
	m_itemList.push_back(Computer);


	ItemObject* SleepBox = new ItemObject(ItemObject::I_BOX, static_cast<ItemObject::SCREEN_AREA>(ScreenArea));
	SleepBox->pos.Set(m_worldWidth * 0.4, m_worldHeight / 2 + 35, 5);
	SleepBox->scale = Vector3(30, 25, 30);
	SleepBox->active = true;
	m_itemList.push_back(SleepBox);

	UseItem = new MenuObject(MenuObject::M_USE_ITEM, Vector3(10, 10, 1));
	UseItem->active = true;
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
			switch (m_itemList[i]->type)
			{
			case ItemObject::I_TELEVISION:
			{
				Character->resting = false;
				break;
			}
			case ItemObject::I_COMPUTER:
			{
				Character->WorkingHard = true;
			}

			default:
				break;
			}
		}
	}
	UseItem->Update(v_mousepos);
	if (Character->currentItem)
	{
		if (UseItem->getChanged())
		{
			switch (Character->currentItem->type)
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

			}
			default:
				break;
			}
		}
	}
}