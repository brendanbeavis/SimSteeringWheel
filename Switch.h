/*
Switch
Copyright (C) 2012  Albert van Dalen http://www.avdweb.nl
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License at http://www.gnu.org/licenses .
*/

#ifndef SWITCH_H
#define SWITCH_H

class Switch
{
public:
  Switch(bool polarity=HIGH, int debounceDelay=150);
  bool update(bool newlevel); // Returns 1 if switched
  bool switched(); // will be refreshed by update()
  bool on();
  bool pushed(); // will be refreshed by update()
  bool released(); // will be refreshed by update()

  unsigned long _switchedTime, pushedTime;
protected:
  const int debounceDelay;
  const bool polarity;
  bool level, _switched;

};

#endif
