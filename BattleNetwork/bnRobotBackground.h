#pragma once
#include <SFML/Graphics.hpp>
using sf::Texture;
using sf::Sprite;
using sf::IntRect;
using sf::Drawable;
#include <vector>
using std::vector;

#include "bnAnimation.h"
#include "bnBackground.h"

/**
 * @class RobotBackground
 * @author mav
 * @date 09/21/19
 * @brief robot animates and scrolls upward
 */
class RobotBackground final : public Background
{
public:
  RobotBackground();
  ~RobotBackground();

  void Update(double _elapsed) override;

private:
  float x, y;
  Animation animation;
  sf::Sprite dummy;
};
