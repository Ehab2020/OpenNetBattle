#include "bnProtoman.h"

#include "bnExplodeState.h"
#include "bnField.h"
#include "bnTextureResourceManager.h"
#include "bnAudioResourceManager.h"
#include "bnEngine.h"
#include "bnLogger.h"
#include "bnBusterCardAction.h"
#include "bnReflectCardAction.h"
#include "bnWideSwordCardAction.h"
#include <Swoosh/Ease.h>

const float COPY_DROP_COOLDOWN = 0.15f; // in seconds

const std::string RESOURCE_PATH = "resources/navis/protoman/protoman.animation";

CardAction* Protoman::OnExecuteBusterAction()
{
  return new BusterCardAction(this, false, 1*GetAtkLevel());
}

CardAction* Protoman::OnExecuteChargedBusterAction()
{
  return new WideSwordCardAction(this, 20*GetAtkLevel());
}

CardAction* Protoman::OnExecuteSpecialAction() {
  auto* action = new ReflectCardAction(this, 20, ReflectShield::Type::red);
  action->SetLockout(ActionLockoutProperties{
    ActionLockoutType::async,
    frames(40).asSeconds()
  });
  action->SetDuration(frames(21));

  return action;
}

Protoman::Protoman() : Player()
{
  chargeEffect.setPosition(0, -20.0f);
  SetName("Protoman");
  SetLayer(0);
  team = Team::red;
  SetElement(Element::none);

  animationComponent->SetPath(RESOURCE_PATH);
  animationComponent->Reload();

  setTexture(TEXTURES.LoadTextureFromFile("resources/navis/protoman/navi_proto_atlas.png"));

  SetHealth(1000);

  chargeEffect.SetFullyChargedColor(sf::Color::White);
}

Protoman::~Protoman()
{
}

const float Protoman::GetHeight() const
{
  return 100.0f;
}

void Protoman::OnUpdate(float _elapsed)
{
  // Continue with the parent class routine
  Player::OnUpdate(_elapsed);
}

void Protoman::OnDelete()
{
  Player::OnDelete();
}