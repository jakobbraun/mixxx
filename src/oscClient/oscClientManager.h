#ifndef OscClientManager_H
#define OscClientManager_H

#include <QDateTime>
#include <QObject>
#include <QString>

#include "configobject.h"
#include "controlobject.h"
#include "controlobjectthread.h"
//#include "oscClient/defs_oscClient.h"
#include <QTimer>
#include <QList>
#include <QTime>


class EngineMaster;

class OscClientManager : public QObject
{
    Q_OBJECT
  public:
    OscClientManager(ConfigObject<ConfigValue>* pConfig, EngineMaster* pEngine);
    virtual ~OscClientManager();
public slots:
    void sendState();
    void maybeSendState();
    void connectServer();
private:
    QTimer timer;
};

#endif // OscClientManager_H
