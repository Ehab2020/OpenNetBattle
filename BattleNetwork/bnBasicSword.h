#pragma once
#include "bnSpell.h"

/**
 * @class BasicSword
 * @author mav
 * @date 13/05/19
 * @brief A single-tile hit box that is used for sword cards. 
 * 
 * @warnig We already have a Hitbox class now and makes this code obsolete
 */
class BasicSword : public Spell {
public:
  BasicSword(Team _team,int damage);
  virtual ~BasicSword();

  virtual void OnUpdate(double _elapsed) override;
  virtual void Attack(Character* _entity) override;
  virtual void OnDelete() override;
private:
  int damage;
  double cooldown;
  float hitHeight;
  bool hit;
};
