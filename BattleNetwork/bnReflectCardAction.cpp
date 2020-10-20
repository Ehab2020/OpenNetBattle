#include "bnReflectCardAction.h"
#include "bnCardAction.h"
#include "bnSpriteProxyNode.h"
#include "bnTextureResourceManager.h"
#include "bnAudioResourceManager.h"
#include "bnReflectShield.h"

#define FRAME1 { 1, 1.3f }

#define FRAMES FRAME1


ReflectCardAction::ReflectCardAction(Character * owner, int damage) : CardAction(owner, "PLAYER_IDLE", nullptr, "Buster") {
  ReflectCardAction::damage = damage;

  // add override anims
  OverrideAnimationFrames({ FRAMES });
}

ReflectCardAction::~ReflectCardAction()
{
}

void ReflectCardAction::Execute() {
  auto user = GetOwner();

  // Create a new reflect shield component. This handles the logic for shields.
  ReflectShield* reflect = new ReflectShield(user, damage);

  // Add the component to the player
  user->RegisterComponent(reflect);

  // Play the appear sound
  AUDIO.Play(AudioType::APPEAR);

  // Add shield artifact on the same layer as player
  Battle::Tile* tile = user->GetTile();

  if (tile) {
    user->GetField()->AddEntity(*reflect, tile->GetX(), tile->GetY());
  }
}

void ReflectCardAction::OnUpdate(float _elapsed)
{
  CardAction::OnUpdate(_elapsed);
}

void ReflectCardAction::OnAnimationEnd()
{
}

void ReflectCardAction::EndAction()
{
  Eject();
}
