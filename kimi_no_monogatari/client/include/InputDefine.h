#ifndef _INPUT_DEFINE_H_
#define _INPUT_DEFINE_H_

namespace tree
{

class MouseEvent
{
public:
	enum ButtonType
	{
		BT_LEFT,
		BT_RIGHT,
		BT_MIDDLE,
	};

	enum ACTION
	{
		ACT_PRESS,
		ACT_RELEASE,
		ACT_DOUBLE_CLICK,
		ACT_MOVE,
	};

	MouseEvent(s32 x_, s32 y_, ButtonType buttonType_, ACTION action_)
		:x(x_),
		y(y_),
		buttonType(buttonType_),
		action(action_)
		{
		}

	u16 x, y;
	ButtonType buttonType;
	ACTION action;
};

class KeyEvent
{
public:
	enum ACTION
	{
		ACT_PRESS,
		ACT_RELEASE,
	};

	KeyEvent(u32 keyCode_, ACTION action_)
		:keyCode(keyCode_),
		action(action_)
		{
		}

	u32 keyCode;
	ACTION action;
};

}

#endif /* _INPUT_DEFINE_H_ */
