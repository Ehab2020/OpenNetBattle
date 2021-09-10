#pragma once
#include "bnBattleSceneBase.h"
#include "States/bnCharacterTransformBattleState.h" // defines TrackedFormData struct

class Player;
class Mob;

/*
    \brief Lots of properties packed into a clean struct
*/
struct MobBattleProperties {
  BattleSceneBaseProps base;
  enum class RewardBehavior : int {
    take = 0,    //!< One reward at the end of all mobs
    takeForEach, //!< Each mobs rewards the player
    none         //!< No rewards given
  } reward{ };
  std::vector<Mob*> mobs;
  sf::Sprite mug; // speaker mugshot
  Animation anim; // mugshot animation
  std::shared_ptr<sf::Texture> emotion; // emotion atlas image
};

/*
    \brief Battle scene configuration for a regular PVE battle
*/
class MobBattleScene final : public BattleSceneBase {
  MobBattleProperties props;
  std::vector<std::shared_ptr<Player>> players;
  std::vector<std::shared_ptr<TrackedFormData>> trackedForms;
  bool playerDecross{ false };
  int playerHitCount{};

  public:
  MobBattleScene(swoosh::ActivityController& controller, const MobBattleProperties& props, BattleResultsFunc onEnd=nullptr);
  ~MobBattleScene();

  void OnHit(Entity& victim, const Hit::Properties& props) override final;
  void onStart() override final;
  void onExit() override;
  void onEnter() override;
  void onResume() override;
  void onLeave() override;
};