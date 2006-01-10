/****************************************************************
 *  $Id$
 * 
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

#include "traymenu.h"

/*
  Creates a QMenu object that has is to be used as the system tray
  context menu.
*/
TrayMenu::TrayMenu(QWidget* parent) 
: QMenu(parent)
{
  toolsMenu = new QMenu(QString(tr("Tools")), trayMenu);
  signalMenu = new QMenu(QString(tr("Send Signal")), toolsMenu);

  /* Signals menu */
  signalMenu->addAction(QString(tr("Reload Config")));
  signalMenu->addAction(QString(tr("Dump Stats")));
  signalMenu->addAction(QString(tr("Debug Mode")));
  signalMenu->addAction(QString(tr("Shutdown")));
  signalMenu->addAction(QString(tr("Kill")));
  
  /* Tools menu */
  toolsMenu->addAction(QString(tr("Bandwidth Graph")));
  toolsMenu->addAction(QString(tr("Message History")));
  toolsMenu->addSeparator();
  toolsMenu->addMenu(signalMenu);

  /* Systray context menu */
  this.addAction(QString(tr("Start Tor")));
  this.addAction(QString(tr("Stop Tor")));
  this.addMenu(toolsMenu);
  this.addSeparator();
  this.addAction(QString(tr("Configure")));
  this.addAction(QString(tr("About")));
  this.addSeparator();
  this.addAction(QString(tr("Exit")));
}

TrayMenu::~TrayMenu()
{
}
