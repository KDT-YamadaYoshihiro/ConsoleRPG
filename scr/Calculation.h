#pragma once
#include "Define.h"

class Calculation {

public:
	
	// ダメージ計算
	static int DamageCalc(int attackerAtk, int defenderDef) {
		int damage = attackerAtk - defenderDef;
		if (damage < MINIMUM_DAMAGE) {
			damage = MINIMUM_DAMAGE; // 最低ダメージを1に設定
		}
		return damage;
	}


};