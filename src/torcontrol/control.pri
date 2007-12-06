#################################################################
#  $Id$
#
#  Vidalia is distributed under the following license:
#
#  Copyright (C) 2006,  Matt Edman, Justin Hipple
#
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; either version 2
#  of the License, or (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  
#  02110-1301, USA.
#################################################################

INCLUDEPATH += $$PWD

HEADERS += $$PWD/torcontrol.h \
           $$PWD/torprocess.h \
           $$PWD/controlconnection.h \
           $$PWD/controlsocket.h \
           $$PWD/controlcommand.h \
           $$PWD/controlreply.h \
           $$PWD/replyline.h \
           $$PWD/torevents.h \
           $$PWD/eventtype.h \
           $$PWD/addressmapevent.h \
           $$PWD/bandwidthevent.h \
           $$PWD/circuitevent.h \
           $$PWD/streamevent.h \
           $$PWD/logevent.h \
           $$PWD/orconnevent.h \
           $$PWD/torsignal.h \
           $$PWD/newdescriptorevent.h \
           $$PWD/routerdescriptor.h \
           $$PWD/circuit.h \
           $$PWD/stream.h \
           $$PWD/addressmap.h \
           $$PWD/protocolinfo.h \
           $$PWD/statusevent.h \
           $$PWD/generalstatusevent.h \
           $$PWD/clientstatusevent.h \
           $$PWD/serverstatusevent.h \
           $$PWD/circuitestablishedevent.h \
           $$PWD/unrecognizedclientstatusevent.h \
           $$PWD/unrecognizedserverstatusevent.h \
           $$PWD/unrecognizedgeneralstatusevent.h \
           $$PWD/dangerousversionevent.h

SOURCES += $$PWD/torcontrol.cpp \
           $$PWD/torprocess.cpp \
           $$PWD/controlconnection.cpp \
           $$PWD/controlsocket.cpp \
           $$PWD/controlcommand.cpp \
           $$PWD/controlreply.cpp \
           $$PWD/replyline.cpp \
           $$PWD/torevents.cpp \
           $$PWD/logevent.cpp \
           $$PWD/orconnevent.cpp \
           $$PWD/torsignal.cpp \
           $$PWD/routerdescriptor.cpp \
           $$PWD/circuit.cpp \
           $$PWD/stream.cpp \
           $$PWD/addressmap.cpp \
           $$PWD/protocolinfo.cpp \
           $$PWD/statusevent.cpp \
           $$PWD/generalstatusevent.cpp \
           $$PWD/clientstatusevent.cpp \
           $$PWD/serverstatusevent.cpp \
           $$PWD/dangerousversionevent.cpp

win32 {
  HEADERS += $$PWD/torservice.h
  SOURCES += $$PWD/torservice.cpp
}
