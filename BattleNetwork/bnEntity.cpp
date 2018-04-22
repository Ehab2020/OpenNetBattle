#include "bnEntity.h"

Entity::Entity(void)
  : tile(nullptr),
  previous(nullptr),
  field(nullptr),
  team(Team::UNKNOWN),
  deleted(false) {
}

Entity::~Entity(void) {
}

void Entity::Update(float _elapsed) {
}

bool Entity::Move(Direction _direction) {
  assert(false && "Move shouldn't be called directly from Entity");
  return false;
}

vector<Drawable*> Entity::GetMiscComponents() {
  assert(false && "GetMiscComponents shouldn't be called directly from Entity");
  return vector<Drawable*>();
}

int Entity::GetStateFromString(string _string) {
  assert(false && "GetStateFromString shouldn't be called directly from Entity");
  return 0;
}

void Entity::AddAnimation(int _state, FrameAnimation _animation, float _duration) {
  assert(false && "AddAnimation shouldn't be called directly from Entity");
}

void Entity::SetAnimation(int _state) {
  assert(false && "SetAnimation shouldn't be called directly from Entity");
}

int Entity::GetHealth() {
  // assert(false && "GetHealth shouldn't be called directly from Entity");
  return health;
}

TextureType Entity::GetTextureType() {
  assert(false && "GetGetTextureType shouldn't be called directly from Entity");
  return (TextureType)0;
}

bool Entity::Teammate(Team _team) {
  return team == _team;
}

void Entity::SetTile(Tile* _tile) {
  tile = _tile;
}

Tile* Entity::GetTile() const {
  return tile;
}

void Entity::SetField(Field* _field) {
  field = _field;
}

Field* Entity::GetField() const {
  return field;
}

Team Entity::GetTeam() const {
  return team;
}
void Entity::SetTeam(Team _team) {
  team = _team;
}

int* Entity::GetAnimOffset() {
  return nullptr;
}

void Entity::SetHealth(const int _health) {
  health = _health;
}

bool Entity::IsDeleted() const {
  return deleted;
}

void Entity::TryDelete()
{
  deleted = (health <= 0);
  return;
}
