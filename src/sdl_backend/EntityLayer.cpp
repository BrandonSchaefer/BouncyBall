// -*- Mode: C++; indent-tabs-mode: nil; tab-width: 2 -*-
/*
 * Copyright (C) 2014 Brandon Schaefer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Brandon Schaefer <brandontschaefer@gmail.com>
 */

#include "EntityLayer.h"

namespace sdl_backend
{

EntityLayer::EntityLayer()
  : paused_(false)
  , visible_(true)
{
}

void EntityLayer::AddEntity(Entity::Ptr const& entity)
{
  hash_table_.add(entity);
}

void EntityLayer::RemoveEntity(unsigned id)
{
  hash_table_.remove(id);
}

Entity::Ptr EntityLayer::GetEntity(unsigned id)
{
  return hash_table_.get(id);
}

void EntityLayer::Pause()
{
  for (auto& e : hash_table_.raw_table())
    e.second->Pause();

  paused_ = true;
}

void EntityLayer::UnPause()
{
  for (auto& e : hash_table_.raw_table())
    e.second->UnPause();

  paused_ = false;
}

void EntityLayer::Show()
{
  visible_ = true;
}

void EntityLayer::Hide()
{
  visible_ = false;
}

bool EntityLayer::Paused() const
{
  return paused_;
}

bool EntityLayer::Visible() const
{
  return visible_;
}

std::unordered_map<unsigned, Entity::Ptr> const& EntityLayer::hash_table() const
{
  return hash_table_.raw_table();
}

} // namespace sdl_backend
