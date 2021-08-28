#pragma once
#ifdef BN_MOD_SUPPORT

#include <sol/sol.hpp>
#include "dynamic_object.h"
#include "../bnSpell.h"
#include "../bnAnimationComponent.h"

using sf::Texture;

/**
 * @class ScriptedSpell
*/
class ScriptedSpell final : public Spell, public dynamic_object {
public:
  ScriptedSpell(Team _team);
  ~ScriptedSpell();
  
  void OnUpdate(double _elapsed) override;
  void OnDelete() override;
  void OnCollision(const Character* other) override;
  bool CanMoveTo(Battle::Tile * next) override;
  void Attack(Character* e) override;
  void OnSpawn(Battle::Tile& spawn) override;
  const float GetHeight() const;
  void SetHeight(const float height);
  void ShowShadow(const bool shadow);

  void SetAnimation(const std::string& path);
  Animation& GetAnimationObject();
  // duration in seconds
  void ShakeCamera(double power, float duration);
  void NeverFlip(bool enabled);

  std::function<void(ScriptedSpell&, Battle::Tile&)> spawnCallback;
  std::function<void(ScriptedSpell&, Character&)> attackCallback;
  std::function<void(ScriptedSpell&, Character&)> collisionCallback;
  std::function<bool(Battle::Tile&)> canMoveToCallback;
  std::function<void(ScriptedSpell&)> deleteCallback;
  std::function<void(ScriptedSpell&, double)> updateCallback;
private:
  bool flip{true};
  float height{};
  sf::Vector2f scriptedOffset{};
  SpriteProxyNode* shadow{ nullptr };
  AnimationComponent* animComponent{ nullptr };
};
#endif