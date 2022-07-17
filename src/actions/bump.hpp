#pragma once
#include <fmt/core.h>

#include "../fov.hpp"
#include "../types/position.hpp"
#include "base.hpp"
namespace action {
class Bump : public Action {
 public:
  Bump() = default;
  Bump(Position dir) : dir_{dir} {}
  virtual void perform(World& world, Actor& actor) override {
    const Position dest = actor.pos + dir_;
    Map& map = world.active_map();
    if (!map.tiles.in_bounds(dest)) {
      world.log.append("That way is blocked!");
      return;
    }
    if (map.tiles.at(dest) != Tiles::floor) {
      world.log.append("That way is blocked!");
      return;
    }
    for (const auto& [other_id, other] : world.actors) {
      if (other.pos == dest) {
        world.log.append(fmt::format("The {} laughs at your puny efforts to attack him!", other.name));
        return;
      }
    }
    actor.pos = dest;
    if (&actor == &world.active_player()) update_fov(map, actor.pos);
  };

 private:
  Position dir_{0, 0};
};

}  // namespace action
