#ifndef CONNECTIONSETTINGSFORM_H
#define CONNECTIONSETTINGSFORM_H

#include <QtWidgets>
#include "GlobalConfig.h"

class ConnectionSettingsForm : public QWidget
{
    Q_OBJECT

public:
    ConnectionSettingsForm(QWidget *parent = 0);
    ~ConnectionSettingsForm();

private:
    QLineEdit *qmp_line;
    QLineEdit *monitor_line;
    
private slots:
    void save_connection_settings();

signals:
    void done_connection_settings(QString, QString);

};

#endif //CONNECTIONSETTINGSFORM_H
