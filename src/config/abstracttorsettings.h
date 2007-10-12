/****************************************************************
 *  Vidalia is distributed under the following license:
 *
 *  Copyright (C) 2006-2007,  Matt Edman, Justin Hipple
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, 
 *  Boston, MA  02110-1301, USA.
 ****************************************************************/

/** 
 * \file abstracttorsettings.h
 * \version $Id$
 * \brief Manages settings that need to be SETCONF'ed to Tor
 */

#ifndef _ABSTRACTTORSETTINGS_H
#define _ABSTRACTTORSETTINGS_H

#include <torcontrol.h>
#include "vsettings.h"


class AbstractTorSettings : public VSettings
{
public:
  /** Constructor. All settings will be under the heading <b>group</b> and
   * <b>torControl</b> will be used to <i>getconf</i> values from Tor. */
  AbstractTorSettings(const QString &group, TorControl *torControl);
  
  /** Sets a value indicating that the server settings have changed since
   * apply() was last called. */
  void setChanged(bool changed);
  /** Returns true if any settings have changed since the last time apply()
   * was called. */
  virtual bool changedSinceLastApply();
  /** Reverts all settings to their values at the last time apply() was
   * called. */
  virtual void revert();
  /** Subclasses must implement this to <i>setconf</i> values to apply them
   * to a running Tor instance. */
  virtual bool apply(QString *errmsg) = 0;

protected:
  /** If Vidalia is connected to Tor, this returns the value associated with
   * <b>key</b> by calling torValue(). Otherwise, this calls localValue()
   * to get the locally saved value associated with <b>key</b>. */
  virtual QVariant value(const QString &key);
  /** Returns the value associated with <b>key</b> saved in the local
   * configuration file. */
  virtual QVariant localValue(const QString &key);
  /** Returns the value associated with <b>key</b> by querying TOr via 
   * <i>getconf key</i>. */
  virtual QVariant torValue(const QString &key);
  /** Saves the value <b>val</b> for the setting <b>key</b> to the local
   * settings file. */
  virtual void setValue(const QString &key, const QVariant &value);
  
  /** Returns true if the given QVariant contains an empty value, depending on
   * the data type. For example, 0 is considered an empty integer and "" is
   * an empty string. */
  bool isEmptyValue(const QVariant &value);

  TorControl* _torControl;

private:
  QMap<QString, QVariant> _backupSettings;
};

#endif
