#include "adventure_control.h"
#include "DataDefs.h"

#include "df/viewscreen.h"

#include "modules/Gui.h"

#include <queue>

using namespace AdventureControl;
using namespace df::enums;
using namespace DFHack;
using namespace Gui;

std::queue<interface_key::interface_key> keyQueue;

void KeyUpdate()
{
	if (!keyQueue.empty())
	{
		getCurViewscreen()->feed_key(keyQueue.front());
		keyQueue.pop();
	}
}

command_result MoveCommand(DFHack::color_ostream &stream, const MoveCommandParams *in)
{
	auto viewScreen = getCurViewscreen();
	if (!in->has_direction())
		return CR_WRONG_USAGE;
	auto dir = in->direction();
	switch (dir.x())
	{
	case -1:
		switch (dir.y())
		{
		case -1:
			switch (dir.z())
			{
			case -1:
				viewScreen->feed_key(interface_key::A_MOVE_NW_DOWN);
				break;
			case 0:
				viewScreen->feed_key(interface_key::A_MOVE_NW);
				break;
			case 1:
				viewScreen->feed_key(interface_key::A_MOVE_NW_UP);
				break;
			}
			break;
		case 0:
			switch (dir.z())
			{
			case -1:
				viewScreen->feed_key(interface_key::A_MOVE_W_DOWN);
				break;
			case 0:
				viewScreen->feed_key(interface_key::A_MOVE_W);
				break;
			case 1:
				viewScreen->feed_key(interface_key::A_MOVE_W_UP);
				break;
			}
			break;
		case 1:
			switch (dir.z())
			{
			case -1:
				viewScreen->feed_key(interface_key::A_MOVE_SW_DOWN);
				break;
			case 0:
				viewScreen->feed_key(interface_key::A_MOVE_SW);
				break;
			case 1:
				viewScreen->feed_key(interface_key::A_MOVE_SW_UP);
				break;
			}	
			break;
		}
		break;
	case 0:
		switch (dir.y())
		{
		case -1:
			switch (dir.z())
			{
			case -1:
				viewScreen->feed_key(interface_key::A_MOVE_N_DOWN);
				break;
			case 0:
				viewScreen->feed_key(interface_key::A_MOVE_N);
				break;
			case 1:
				viewScreen->feed_key(interface_key::A_MOVE_N_UP);
				break;
			}
			break;
		case 0:
			switch (dir.z())
			{
			case -1:
				viewScreen->feed_key(interface_key::A_MOVE_DOWN);
				break;
			case 1:
				viewScreen->feed_key(interface_key::A_MOVE_UP);
				break;
			}
			break;
		case 1:
			switch (dir.z())
			{
			case -1:
				viewScreen->feed_key(interface_key::A_MOVE_S_DOWN);
				break;
			case 0:
				viewScreen->feed_key(interface_key::A_MOVE_S);
				break;
			case 1:
				viewScreen->feed_key(interface_key::A_MOVE_S_UP);
				break;
			}
			break;
		}
		break;
	case 1:
		switch (dir.y())
		{
		case -1:
			switch (dir.z())
			{
			case -1:
				viewScreen->feed_key(interface_key::A_MOVE_NE_DOWN);
				break;
			case 0:
				viewScreen->feed_key(interface_key::A_MOVE_NE);
				break;
			case 1:
				viewScreen->feed_key(interface_key::A_MOVE_NE_UP);
				break;
			}
			break;
		case 0:
			switch (dir.z())
			{
			case -1:
				viewScreen->feed_key(interface_key::A_MOVE_E_DOWN);
				break;
			case 0:
				viewScreen->feed_key(interface_key::A_MOVE_E);
				break;
			case 1:
				viewScreen->feed_key(interface_key::A_MOVE_E_UP);
				break;
			}
			break;
		case 1:
			switch (dir.z())
			{
			case -1:
				viewScreen->feed_key(interface_key::A_MOVE_SE_DOWN);
				break;
			case 0:
				viewScreen->feed_key(interface_key::A_MOVE_SE);
				break;
			case 1:
				viewScreen->feed_key(interface_key::A_MOVE_SE_UP);
				break;
			}
			break;
		}
		break;
	}
	return CR_OK;
}
command_result JumpCommand(DFHack::color_ostream &stream, const MoveCommandParams *in)
{
	if (!in->has_direction())
		return CR_WRONG_USAGE;
	auto dir = in->direction();
	keyQueue.push(interface_key::A_JUMP);
	int x = dir.x();
	int y = dir.y();
	if (x > 0)
	{
		for (int i = 0; i < x; i++)
		{
			keyQueue.push(interface_key::CURSOR_RIGHT);
		}
	}
	if (x < 0)
	{
		for (int i = 0; i > x; i--)
		{
			keyQueue.push(interface_key::CURSOR_LEFT);
		}
	}
	if (y > 0)
	{
		for (int i = 0; i < y; i++)
		{
			keyQueue.push(interface_key::CURSOR_DOWN);
		}
	}
	if (y < 0)
	{
		for (int i = 0; i > y; i--)
		{
			keyQueue.push(interface_key::CURSOR_UP);
		}
	}
	keyQueue.push(interface_key::SELECT);
	return CR_OK;
}