#pragma once
#include "bnCardAction.h"
#include "bnAnimation.h"
#include <SFML/Graphics.hpp>

class SpriteProxyNode;
class Character;
class BombCardAction : public CardAction {
private:
  SpriteProxyNode* attachment;
  Animation attachmentAnim;
  int damage;
public:
  BombCardAction(Character& user, int damage);
  ~BombCardAction();
  void Update(double _elapsed) override;
  void OnAnimationEnd() override;
  void OnEndAction() override;
  void OnExecute() override;
};
