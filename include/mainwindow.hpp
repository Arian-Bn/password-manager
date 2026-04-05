#pragma once
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);

private:
  QPushButton *addPasswordButton;
  QPushButton *addNoteButton;
  QPushButton *deleteButton;
  QListWidget *entryList;

private:
  void onAddPasswordClicked();
  void onAddNoteClicked();
  void onDeleteClicked();
};
