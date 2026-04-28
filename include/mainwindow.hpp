#pragma once
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <qtmetamacros.h>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);

private slots:
  void onAddNoteClicked();
  void onDeleteClicked();
  void onEditEntry(QListWidgetItem *item);

private:
  QPushButton *addNoteButton;
  QPushButton *deleteButton;
  QListWidget *entryList;

  void refreshEntryList();
};
