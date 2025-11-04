#pragma once

enum ACTION {
	SELECT,
	ATTACK,
	HEAL,
	END,
	NONE
};

enum GAME_END {
	RETURY = 1,
	EXIT = 2,
};

enum CONTINUECHOICE {
	NEXT_PHASE = 1,
	TO_RESULT = 2,
};
