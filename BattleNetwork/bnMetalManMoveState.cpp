#include "bnMetalMan.h"
#include "bnHitbox.h"
#include "bnTile.h"
#include "bnField.h"
#include "bnMetalManIdleState.h"
#include "bnMetalManMoveState.h"
#include "bnMetalManPunchState.h"
#include "bnMetalManThrowState.h"
#include "bnMetalManMissileState.h"

MetalManMoveState::MetalManMoveState() : isMoving(false), AIState<MetalMan>() { ; }
MetalManMoveState::~MetalManMoveState() { ; }

void MetalManMoveState::OnEnter(MetalMan& metal) {
  isMoving = false;
}

void MetalManMoveState::OnUpdate(double _elapsed, MetalMan& metal) {
  if (isMoving || !metal.GetTarget() || !metal.GetTarget()->GetTile()) return; // We're already moving (animations take time)

  nextDirection = Direction::none;

  Battle::Tile* nextTile = nullptr;

  auto tiles = metal.GetField()->FindTiles([metalPtr = &metal](Battle::Tile* t) {
    return t->GetTeam() == metalPtr->GetTeam();
  });

  if (tiles.empty()) metal.GoToNextState();

  nextTile = tiles[rand() % tiles.size()];

  // Find a new spot that is on our team
  if (metal.Teleport(nextTile)) {
    auto onFinish = [this, m = &metal]() {
        m->GoToNextState();
    };

    metal.GetFirstComponent<AnimationComponent>()->SetAnimation("MOVING", onFinish);
    isMoving = true;
  }
  else {
  metal.GoToNextState();
  }
}

void MetalManMoveState::OnLeave(MetalMan& metal) {
  metal.GetFirstComponent<AnimationComponent>()->SetAnimation("IDLE", Animator::Mode::Loop);
}

