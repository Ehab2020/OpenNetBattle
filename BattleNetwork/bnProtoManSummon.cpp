#include <random>
#include <time.h>
#include <algorithm>

#include "bnProtoManSummon.h"
#include "bnTile.h"
#include "bnField.h"
#include "bnTextureResourceManager.h"
#include "bnAudioResourceManager.h"
#include "bnBasicSword.h"
#include "bnSwordEffect.h"

#include "bnCardSummonHandler.h"

#define RESOURCE_PATH "resources/spells/protoman_summon.animation"

ProtoManSummon::ProtoManSummon(CardSummonHandler* _summons) : Spell(_summons->GetCaller()->GetField(), _summons->GetCaller()->GetTeam())
{
  summons = _summons;
  SetPassthrough(true);
  random = rand() % 20 - 20;

  int lr = (team == Team::red) ? 1 : -1;
  setScale(2.0f*lr, 2.0f);

  Battle::Tile* _tile = summons->GetCaller()->GetTile();

  field->AddEntity(*this, *_tile);

  AUDIO.Play(AudioType::APPEAR);

  setTexture(TEXTURES.LoadTextureFromFile("resources/spells/protoman_summon.png"), true);

  animationComponent = CreateComponent<AnimationComponent>(this);
  animationComponent->SetPath(RESOURCE_PATH);
  animationComponent->Load();

  Battle::Tile* next = nullptr;

  auto allTiles = field->FindTiles([](Battle::Tile* tile) { return true; });
  auto iter = allTiles.begin();

  while (iter != allTiles.end()) {
    next = (*iter);

    if (next->ContainsEntityType<Character>() && !next->ContainsEntityType<Obstacle>() && next->GetTeam() != GetTeam()) {
      int step = -1;

      if (GetTeam() == Team::blue) {
        step = 1;
      }
      
      Battle::Tile* prev = field->GetAt(next->GetX() + step, next->GetY());

      auto characters = prev->FindEntities([_summons](Entity* in) {
        return _summons->GetCaller() != in && (dynamic_cast<Character*>(in)  && in->GetTeam() != Team::unknown);
      });

      bool blocked = (characters.size() > 0) || !prev->IsWalkable();

      if(!blocked) {
        targets.push_back(next);
      }
    }

    iter++;
  }

  // TODO: noodely callbacks desgin might be best abstracted by ActionLists
  animationComponent->SetAnimation("APPEAR", [this] {
  auto handleAttack = [this] () {
      DoAttackStep();
    };
    animationComponent->SetAnimation("MOVE", handleAttack);
  });

  auto props = GetHitboxProperties();
  props.damage = 120;
  props.flags |= Hit::flinch;
  props.aggressor = _summons->GetCaller();
  SetHitboxProperties(props);
}

ProtoManSummon::~ProtoManSummon() {
}

void ProtoManSummon::DoAttackStep() {
  if (targets.size() > 0) {
    int step = -1;

    if (GetTeam() == Team::blue) {
      step = 1;
    }

    Battle::Tile* prev = field->GetAt(targets[0]->GetX() + step, targets[0]->GetY());
    GetTile()->RemoveEntityByID(GetID());
    prev->AddEntity(*this);

    animationComponent->SetAnimation("ATTACK", [this, prev] {
      animationComponent->SetAnimation("MOVE", [this, prev] {
      DoAttackStep();
      });
    });

    animationComponent->AddCallback(4,  [this]() {
      for (auto entity : targets[0]->FindEntities([](Entity* e) { return dynamic_cast<Character*>(e); })) {
        entity->GetTile()->AffectEntities(this);
      }

      targets.erase(targets.begin());
    }, true);
  }
  else {
    animationComponent->SetAnimation("MOVE", [this] {
      Delete();
      summons->GetCaller()->Reveal();
    });
  }
}

void ProtoManSummon::OnDelete()
{
  Remove();
}

void ProtoManSummon::OnUpdate(float _elapsed) {
  if (tile != nullptr) {
    setPosition(tile->getPosition());
  }
}

bool ProtoManSummon::Move(Direction _direction) {
  return false;
}

void ProtoManSummon::Attack(Character* _entity) {
  auto field = GetField();

  auto tile = _entity->GetTile();

  SwordEffect* e = new SwordEffect(field);
  e->SetAnimation("WIDE");
  field->AddEntity(*e, tile->GetX() + 1, tile->GetY());

  BasicSword* b = new BasicSword(field, GetTeam(), 0);
  auto props = this->GetHitboxProperties();
  props.aggressor = summons->GetCaller();
  b->SetHitboxProperties(props);

  AUDIO.Play(AudioType::SWORD_SWING);
  field->AddEntity(*b, tile->GetX() + 1,tile->GetY());

  b = new BasicSword(field, GetTeam(), 0);
  props = this->GetHitboxProperties();
  props.aggressor = summons->GetCaller();
  b->SetHitboxProperties(props);
  field->AddEntity(*b,tile->GetX() + 1, tile->GetY() + 1);

  b = new BasicSword(field, GetTeam(), 0);
  props = this->GetHitboxProperties();
  props.aggressor = summons->GetCaller();
  field->AddEntity(*b, tile->GetX() + 1, tile->GetY() - 1);

  AUDIO.Play(AudioType::SWORD_SWING);
}
