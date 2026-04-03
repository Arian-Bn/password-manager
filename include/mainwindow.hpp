#pragma once
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow {

public:
  MainWindow(QWidget *parent = nullptr);

private:
  QPushButton *addPasswordButton;
  QPushButton *addNoteButton;
  QPushButton *deleteButton;
  QListWidget *entryList;
};
