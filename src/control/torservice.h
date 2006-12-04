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
 * \file torservice.h
 * \version $Id$
 * \brief Starts, stops, installs, and uninstalls a Tor service (Win32).
 */

#ifndef _TORSERVICE_H
#define _TORSERVICE_H

#include <QObject>
#include <QProcess>

#include <windows.h>
#define TOR_SERVICE_NAME "tor"
#define TOR_SERVICE_DISP "Tor Win32 Service"
#define TOR_SERVICE_DESC \
  TEXT("Provides an anonymous Internet communication system.")
#define TOR_SERVICE_ACCESS SERVICE_ALL_ACCESS
#define SERVICE_ERROR 8

/* NT service function prototypes. This code is adapted from Tor's
 * nt_service_load_library() in main.c. See LICENSE for details on
 * Tor's license. */
typedef BOOL (WINAPI *ChangeServiceConfig2A_fn)(
                             SC_HANDLE hService,
                             DWORD dwInfoLevel,
                             LPVOID lpInfo);
typedef BOOL (WINAPI *CloseServiceHandle_fn)(
                             SC_HANDLE hSCObject);
typedef BOOL (WINAPI *ControlService_fn)(
                             SC_HANDLE hService,
                             DWORD dwControl,
                             LPSERVICE_STATUS lpServiceStatus);
typedef SC_HANDLE (WINAPI *CreateServiceA_fn)(
                             SC_HANDLE hSCManager,
                             LPCTSTR lpServiceName,
                             LPCTSTR lpDisplayName,
                             DWORD dwDesiredAccess,
                             DWORD dwServiceType,
                             DWORD dwStartType,
                             DWORD dwErrorControl,
                             LPCTSTR lpBinaryPathName,
                             LPCTSTR lpLoadOrderGroup,
                             LPDWORD lpdwTagId,
                             LPCTSTR lpDependencies,
                             LPCTSTR lpServiceStartName,
                             LPCTSTR lpPassword);
typedef BOOL (WINAPI *DeleteService_fn)(
                             SC_HANDLE hService);
typedef SC_HANDLE (WINAPI *OpenSCManagerA_fn)(
                             LPCTSTR lpMachineName,
                             LPCTSTR lpDatabaseName,
                             DWORD dwDesiredAccess);
typedef SC_HANDLE (WINAPI *OpenServiceA_fn)(
                             SC_HANDLE hSCManager,
                             LPCTSTR lpServiceName,
                             DWORD dwDesiredAccess);
typedef BOOL (WINAPI *QueryServiceStatus_fn)(
                             SC_HANDLE hService,
                             LPSERVICE_STATUS lpServiceStatus);
typedef BOOL (WINAPI *SetServiceStatus_fn)(SERVICE_STATUS_HANDLE,
                             LPSERVICE_STATUS);
typedef BOOL (WINAPI *StartServiceA_fn)(
                             SC_HANDLE hService,
                             DWORD dwNumServiceArgs,
                             LPCTSTR* lpServiceArgVectors);

/** Table of NT service related functions. */
typedef struct ServiceFunctions {
  bool loaded;
  ChangeServiceConfig2A_fn ChangeServiceConfig2A;
  CloseServiceHandle_fn    CloseServiceHandle;
  ControlService_fn        ControlService;
  CreateServiceA_fn        CreateServiceA;
  DeleteService_fn         DeleteService;
  OpenSCManagerA_fn        OpenSCManagerA;
  OpenServiceA_fn          OpenServiceA;
  QueryServiceStatus_fn    QueryServiceStatus;
  SetServiceStatus_fn      SetServiceStatus;
  StartServiceA_fn         StartServiceA;
};


class TorService : public QObject
{
  Q_OBJECT

public:
  /** Returns if services are supported. */
  static bool isSupported();
  /** Dynamically loads NT service related functions from advapi32.dll. */
  static bool loadServiceFunctions();

  /** Default ctor. */
  TorService(QObject* parent = 0);
  /** Default dtor. */
  ~TorService();

  /** Returns true if the Tor service is installed. */
  bool isInstalled();
  /** Returns true if the Tor service is running. */
  bool isRunning();
  /** Starts the Tor service. Emits started on success. */
  void start();
  /** Stops the Tor service. Emits finished on success. */
  void stop();
  /** Returns the exit code of the last Tor service that finished. */
  int exitCode();
  /** Returns the exit status of the last Tor service that finished. */
  QProcess::ExitStatus exitStatus();
  /** Installs the Tor service. */
  bool install(const QString &torPath, const QString &torrc,
               quint16 controlPort);
  /** Removes the Tor service. */
  bool remove();

signals:
  /** Called when the service gets started. */
  void started();
  /** Called when the service gets stopped. */
  void finished(int exitCode, QProcess::ExitStatus);
  /** Called when there is an error in starting the service. */
  void startFailed(QString error);

private:
  /** Initializes the service and the service manager. */
  bool initialize();
  /** Closes the service and the service manager. */
  void close();
  /** Gets the status of the Tor service. */
  DWORD status(); 
  
  SC_HANDLE _manager; /** Handle to a service manager object. */
  SC_HANDLE _service; /** Handle to the Tor service object. */

  /** List of dynamically loaded NT service functions. */
  static ServiceFunctions _service_fns;
};

#endif

