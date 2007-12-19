/****************************************************************
 *  Vidalia is distributed under the following license:
 *
 *  Copyright (C) 2006,  Matt Edman, Justin Hipple
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
 * \file configpagestack.cpp
 * \version $Id$
 * \brief A collection of configuration pages
 */

#include <QAction>
#include "configpagestack.h"

/** Default constructor. */
ConfigPageStack::ConfigPageStack(QWidget *parent)
: QStackedWidget(parent)
{
}

/** Adds a page to the stack. */
void
ConfigPageStack::add(ConfigPage *page, QAction *action)
{
  _pages.insert(action, page);
  insertWidget(count(), page);
}

/** Sets the current config page and checks its action. */
void
ConfigPageStack::setCurrentPage(ConfigPage *page)
{
  foreach (QAction *action, _pages.keys(page)) {
    action->setChecked(true);
  }
  setCurrentWidget(page);
}

/** Sets the current config page index and checks its action. */
void
ConfigPageStack::setCurrentIndex(int index)
{
  setCurrentPage((ConfigPage *)widget(index));
}

/** Shows the config page associated with the activated action. */
void
ConfigPageStack::showPage(QAction *pageAction)
{
  setCurrentWidget(_pages.value(pageAction));
}
