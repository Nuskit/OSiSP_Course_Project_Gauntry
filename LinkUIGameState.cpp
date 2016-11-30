#include "stdafx.h"
#include "LinkUIGameState.h"
#include "UILoopState.h"
#include "GameLoopState.h"
#include <map>

using namespace std;

typedef map<UILoopState*, GameLoopState*> MapUiGameStates;

GameLoopState* GetLinkUiToGameStates(UILoopState* uiState)
{
	static MapUiGameStates links =
	{
		{reinterpret_cast<UILoopState*>(&UILoopState::uiStateInitialize),reinterpret_cast<GameLoopState*>(&GameLoopState::gameStateInitialize)},
		{reinterpret_cast<UILoopState*>(&UILoopState::uiStateMainMenu),reinterpret_cast<GameLoopState*>(&GameLoopState::gameStateMainMenu)},
		{reinterpret_cast<UILoopState*>(&UILoopState::uiStateNewGame),reinterpret_cast<GameLoopState*>(&GameLoopState::gameStateNewGame)}
	};

	MapUiGameStates::const_iterator gameStateIt = links.find(uiState);
	return (gameStateIt != links.end()) ? gameStateIt->second : nullptr;
}
