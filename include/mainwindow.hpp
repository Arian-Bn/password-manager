#pragma once
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <qtmetamacros.h>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);

  void updateEntryList(
      const std::vector<std::tuple<int, std::string, std::string>> &entries);

private slots:
  void onAddNoteClicked();
  void onDeleteClicked();
  void onExitClicked();
  void onEditEntry(QListWidgetItem *item);
  void onSearchTextChanged(const QString &text);

private:
  QPushButton *addNoteButton;
  QPushButton *deleteButton;
  QPushButton *exitButton;
  QListWidget *entryList;
  QLineEdit *lineEdit;

  void refreshEntryList();
};
