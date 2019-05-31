#pragma once

#include "bnComponent.h"
#include <SFML/System.hpp>

/*! \brief Removes any entity from the field for a duration of time
 * 
 * This component injects itself into the battle scene loop directly
 * Once the timer runs down, it ejects itself from the battle scene loop
 * and deletes itself
*/
class HideTimer : public Component {
private:
  sf::Time duration; /*!< How long to hide a character for */
  float elapsed; /*!< time elapsed in seconds */
  Battle::Tile* temp; /*!< The tile to return the character to */
  Character* owner; /*!< The entity as type character */
  BattleScene* scene; /*!< The battle scene referene */
public:
  /**
   * @brief Registers the owner and sets the time
   */
  HideTimer(Character* owner, double secs);

  /**
   * @brief When time is up, eject component from battle scene loop and add entity back
   * @param _elapsed in seconds
   */
  virtual void Update(float _elapsed);
  
  /**
   * @brief Remove ownership from character to the battle scene and remove entity from play
   */
  virtual void Inject(BattleScene&);
}; 
