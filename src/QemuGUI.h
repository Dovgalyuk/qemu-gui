#ifndef QEMUGUI_H
#define QEMUGUI_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets>

#include "VMSettingsForm.h"
#include "CreateVMForm.h"
#include "RecordReplayTab.h"
#include "VMConfig.h"
#include "GlobalConfig.h"
#include "QemuLauncher.h"
#include "QMPInteraction.h"
#include "TerminalSettingsForm.h"
#include "TerminalTab.h"
#include "ConnectionSettingsForm.h"

enum VMState {None, Running, Stopped};

class QemuGUI : public QMainWindow
{
    Q_OBJECT

public:
    QemuGUI(QWidget *parent = 0);
    ~QemuGUI();

protected:
    bool eventFilter(QObject *target, QEvent *event);

private:
    GlobalConfig *global_config;
    QemuLauncher *launch_qemu;

    VMState vm_state;
    QTcpSocket monitor_socket;
    
    QDialog *qemu_install_dir_settings;
    QListWidget *qemu_install_dir_list;
    
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    QAction *qemu_play;
    QAction *qemu_pause;
    QAction *qemu_stop;
    
    QComboBox *qemu_install_dir_combo;

    QListWidget *listVM;
    QAction *delete_act;
    QAction *exclude_act;

    QGroupBox *propBox;
    QLabel *info_lbl;
    QPushButton *edit_btn;
    QTabWidget *tab;
    QWidget *tab_info;
    QMPInteraction *qmp;

    CreateVMForm *createVMWindow;
    RecordReplayTab *rec_replay_tab;
    TerminalTab *terminal_tab;


    QString qmp_port = "";
    QString monitor_port = "";


private:
    QIcon set_button_icon_for_state(const QString &normal_icon, const QString &disable_icon);
    void create_qemu_install_dir_dialog();
    void connect_signals();
    void widget_placement();
    void fill_listVM_from_config();
    void fill_qemu_install_dir_from_config();

public slots:
    void stop_qemu_btn_state();
    void resume_qemu_btn_state();
    void set_connection_settings(const QString &qmp, const QString &monitor);

private slots:

    void set_qemu_install_dir();
    void add_qemu_install_dir_btn();
    void del_qemu_install_dir_btn();
    void refresh();
    QString delete_exclude_vm(bool delete_vm);
    void delete_vm_ctxmenu();
    void exclude_vm_ctxmenu();
    void play_machine();
    void finish_qemu();
    void pause_machine();
    void stop_machine();
    void create_machine();
    void add_machine();
    void edit_settings();
    void listVM_item_selection_changed();
    void listVM_current_item_changed(QListWidgetItem *current, QListWidgetItem *previous);
    void qemu_install_dir_combo_activated(int index);
    void qemu_install_dir_combo_index_changed(int index);
    void set_terminal_settings();
    void launch_settings();


signals:
    void qmp_resume_qemu();
    void qmp_stop_qemu();
    void monitor_connect(int);

};

#endif // QEMUGUI_H

