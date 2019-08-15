
#include "GameObject.h"

GameObject::GameObject()
	: type(0),
	scale(1, 1, 1),
	active(false)
{
}

GameObject::~GameObject()
{
}
//bool GameObject::getDirection()
//{
//	return m_dLeftRight;
//}
//
//void GameObject::setDirection(bool leftTrue)
//{
//	m_dLeftRight = leftTrue;
//}
//
//bool GameObject::getState()
//{
//	return isMoving;
//}
//
//void GameObject::setState(bool move)
//{
//	isMoving = move;
//}
