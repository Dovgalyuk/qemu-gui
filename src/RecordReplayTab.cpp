#include "RecordReplayTab.h"

RecordReplayTab::RecordReplayTab(QWidget *parent)
    : QWidget(parent)
{
    if (RecordReplayTab::objectName().isEmpty())
        RecordReplayTab::setObjectName(QStringLiteral("RecordReplayTab"));
    resize(400, 300);
    
    execution_list = new QListWidget();
    rec_btn = new QPushButton("Start record");
    rpl_btn = new QPushButton("Start replay");

    rename_act = new QAction("Rename", execution_list);
    delete_act = new QAction("Delete", execution_list);
    rename_act->setDisabled(true);
    delete_act->setDisabled(true);

    execution_list->setEditTriggers(QAbstractItemView::AnyKeyPressed | 
        QAbstractItemView::SelectedClicked | QAbstractItemView::DoubleClicked);
 
    execution_list->addItem("First");
    execution_list->addItem("Second");
    execution_list->addItem("Third");

    execution_list->addAction(rename_act);
    execution_list->addAction(delete_act);
    execution_list->setContextMenuPolicy(Qt::ActionsContextMenu);

    widget_placement();
    connect_signals();
}

RecordReplayTab::~RecordReplayTab()
{

}

void RecordReplayTab::connect_signals()
{
    connect(rec_btn, SIGNAL(clicked()), this, SLOT(record_execution()));
    connect(rpl_btn, SIGNAL(clicked()), this, SLOT(replay_execution()));

    connect(execution_list, SIGNAL(itemSelectionChanged()), this, SLOT(execution_listItemSelectionChanged()));

    connect(rename_act, SIGNAL(triggered()), this, SLOT(rename_ctxmenu()));
    connect(delete_act, SIGNAL(triggered()), this, SLOT(delete_ctxmenu()));
}

void RecordReplayTab::widget_placement()
{
    QVBoxLayout *main_lay = new QVBoxLayout(this);

    QHBoxLayout *lay_btn = new QHBoxLayout(this);
    lay_btn->addWidget(rec_btn);
    lay_btn->addWidget(rpl_btn);

    main_lay->addWidget(new QLabel("List of existing executions"));
    main_lay->addWidget(execution_list);
    main_lay->addLayout(lay_btn);
}

void RecordReplayTab::record_execution()
{
    QMessageBox::about(this, "", "record");
}

void RecordReplayTab::replay_execution()
{
    QMessageBox::about(this, "", "replay");
}

void RecordReplayTab::execution_listItemSelectionChanged()
{
    rename_act->setDisabled(false);
    delete_act->setDisabled(false);
}

void RecordReplayTab::rename_ctxmenu()
{
    if (execution_list->currentItem())
    {
        execution_list->currentItem()->setFlags(execution_list->currentItem()->flags() | Qt::ItemIsEditable);
    }
}

void RecordReplayTab::delete_ctxmenu()
{    
    if (execution_list->currentItem())
    {
        delete execution_list->currentItem();
        execution_list->clearSelection();
        rename_act->setDisabled(true);
        delete_act->setDisabled(true);
    }
}
