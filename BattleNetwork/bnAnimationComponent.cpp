#include <SFML/Graphics.hpp>
using sf::Sprite;
using sf::IntRect;

#include "bnAnimationComponent.h"
#include "bnFileUtil.h"
#include "bnLogger.h"
#include "bnEntity.h"
#include "bnCharacter.h"

AnimationComponent::AnimationComponent(Entity* _entity) : Component(_entity) {
  speed = 1.0;
}

AnimationComponent::~AnimationComponent() {
}

void AnimationComponent::OnUpdate(float _elapsed)
{
  auto character = this->GetOwnerAs<Character>();

  if (character && character->IsStunned()) {
    return;
  }

  animation.Update(_elapsed, *GetOwner(), speed);
}

void AnimationComponent::Setup(string _path)
{
  path = _path;
}

void AnimationComponent::Load() {
  this->Reload();
}

void AnimationComponent::Reload() {
  animation = Animation(path);
  animation.Reload();
}

const std::string AnimationComponent::GetAnimationString() const
{
  return animation.GetAnimationString();
}

const std::string& AnimationComponent::GetFilePath() const
{
  return path;
}

void AnimationComponent::SetPlaybackSpeed(const double playbackSpeed)
{
  speed = playbackSpeed;
}

const double AnimationComponent::GetPlaybackSpeed()
{
  return speed;
}

void AnimationComponent::SetAnimation(string state, std::function<void()> onFinish)
{
  animation.SetAnimation(state);
  animation << onFinish;

  // TODO: why does this cancel callbacks?
  //animation.Refresh(*GetOwner());
}

void AnimationComponent::SetAnimation(string state, char playbackMode, std::function<void()> onFinish)
{
  animation.SetAnimation(state);
  animation << playbackMode << onFinish;

  // TODO: why does this cancel callbacks?
  //animation.Refresh(*GetOwner());
}

void AnimationComponent::SetPlaybackMode(char playbackMode)
{
	animation << playbackMode;
}

void AnimationComponent::AddCallback(int frame, std::function<void()> onFrame, std::function<void()> outFrame, bool doOnce) {
  animation << Animator::On(frame, onFrame, doOnce) << Animator::On(frame+1, outFrame, doOnce);
}

void AnimationComponent::CancelCallbacks()
{
  // We just want to cancel callbacks
  // Preserve some other state info
  auto mode = animation.GetMode();
  animation.RemoveCallbacks();
  animation << mode;
}

sf::Vector2f AnimationComponent::GetPoint(const std::string & pointName)
{
  return animation.GetPoint(pointName);
}

void AnimationComponent::OverrideAnimationFrames(const std::string& animation, std::list<OverrideFrame>&& data, std::string & uuid)
{
  this->animation.OverrideAnimationFrames(animation, std::move(data), uuid);
}

void AnimationComponent::SyncAnimation(Animation & other)
{
  animation.SyncAnimation(other);
}

void AnimationComponent::SyncAnimation(AnimationComponent * other)
{
  animation.SyncAnimation(other->animation);
}

void AnimationComponent::SetFrame(const int index)
{
  animation.SetFrame(index, *GetOwner());
}
