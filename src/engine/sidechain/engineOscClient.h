/***************************************************************************
                          EngineOscClient.h  -  description
                             -------------------
    copyright            : (C) 2007 by John Sully
    email                :
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef EngineOscClient_H
#define EngineOscClient_H


#include "configobject.h"
#include "engine/sidechain/sidechainworker.h"
#include "trackinfoobject.h"
#include "controlobjectthread.h"
#include <QTime>
#include <QList>
#include "lo/lo.h"
#include "configobject.h"
#include "controlobject.h"
#include "controlobjectthread.h"

class ConfigKey;
class ControlObjectSlave;
class Encoder;

class EngineOscClient : public QObject, public SideChainWorker {
    Q_OBJECT
  public:
    EngineOscClient(ConfigObject<ConfigValue>* _config);
    virtual ~EngineOscClient();

public slots:
    void sendState();
    void maybeSendState();
    void connectServer();


    //interface SideChainWorker
    void process(const CSAMPLE* pBuffer, const int iBufferSize);
    void shutdown() {}


  private:
    QTime time;
    lo_address serverAdress;
    ConfigObject<ConfigValue>* m_pConfig;
    QList<ControlObjectThread*> connectedControls;
    ControlObjectThread prefUpdate;

};

#endif
