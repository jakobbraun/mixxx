#ifndef DLGPREFOSC_H
#define DLGPREFOSC_H

#include <QRadioButton>
#include <QWidget>

#include "ui_dlgprefoscdlg.h"
#include "configobject.h"
#include "preferences/dlgpreferencepage.h"

class ControlObject;
class ControlObjectThread;

class DlgPrefOsc : public DlgPreferencePage, public Ui::DlgPrefOscDlg  {
    Q_OBJECT
  public:
    DlgPrefOsc(QWidget *parent, ConfigObject<ConfigValue> *_config);
    virtual ~DlgPrefOsc();

  public slots:
    // Apply changes to widget
    void slotApply();
    void slotUpdate();
    void slotResetToDefaults();



  signals:
    void apply(const QString &);

  private:
    // Pointer to config object
    ConfigObject<ConfigValue>* m_pConfig;
};

#endif
