#pragma once
#include "bnSpell.h"

class ProgBomb : public Spell {
private:
  int random;
  sf::Vector2f start;
  double arcDuration;
  double arcProgress;
public:
  ProgBomb(Team _team,sf::Vector2f startPos, float _duration);
  ~ProgBomb();

  void OnUpdate(double _elapsed) override;
  void Attack(Character* _entity) override;
  void OnDelete() override;
};