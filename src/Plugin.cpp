/**
 * @file Plugin.cpp
 * @brief The main file of the plugin
 */

#include <DynamicCommandAPI.h>
#include <EventAPI.h>
#include <LoggerAPI.h>
#include <ScheduleAPI.h>

#include <MC/CommandOrigin.hpp>
#include <MC/CommandOutput.hpp>
#include <MC/Objective.hpp>
#include <MC/Player.hpp>
#include <MC/Scoreboard.hpp>
#include <MC/Types.hpp>
#include <map>
#include <string>
#include <unordered_map>

/**
 * @brief The entrypoint of the plugin. DO NOT remove or rename this function.
 *
 */
void PluginInit() {
  // Operations related to the game can only be performed after the server
  // starts.
  Event::ServerStartedEvent::subscribe([](const Event::ServerStartedEvent& event) {
    // Create a scoreboard objective
    auto* objective = Scoreboard::newObjective("lldeathcounter", "Death Count");
    // Display the objective at the player list
    objective->setDisplay(/*slotName=*/"list",
                          /*sort=*/ObjectiveSortOrder::Descending);
    // Always return true, for this event cannot be suppressed
    return true;
  });

  // Add death count when a player dies
  Event::PlayerDieEvent::subscribe([](const Event::PlayerDieEvent& event) {
    // Add the score
    Scoreboard::addScore("lldeathcounter", event.mPlayer, 1);
    // Always return true, for this event cannot be suppressed
    return true;
  });

  // WRONG! Calling game-related interfaces here will result in SEH error.
  // auto* objective = Scoreboard::newObjective("lldeathcounter", "Death Count");
  // objective->setDisplay(/*slotName=*/"list",
  //                       /*sort=*/ObjectiveSortOrder::Descending);
}
