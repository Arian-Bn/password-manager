#pragma once
#include <QComboBox>
#include <QLabel>
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);

private slots:
  void onAddNoteClicked();
  void onDeleteClicked();
  void onExitClicked();
  void onEditEntry(QListWidgetItem *item);
  void onSearchTextChanged(const QString &text);
  void onNoteSelected(QListWidgetItem *item);

private:
  QPushButton *addNoteButton;
  QPushButton *deleteButton;
  QPushButton *exitButton;
  QListWidget *entryList;
  QLineEdit *lineEdit;
  QComboBox *categoryFilter;
  QLabel *categoryDisplay;
  QTextEdit *noteContentDisplay;

  void refreshEntryList();
  void refreshCategoryFilter();
  void updateEntryList(
      const std::vector<std::tuple<int, std::string, std::string>> &entries);
};
