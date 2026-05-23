#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>

class AddNoteDialog : public QDialog {
public:
  AddNoteDialog(QWidget *parent = nullptr);

  QString getTitle() const;
  QString getContent() const;
  QString getCategory() const;

private:
  QLineEdit *titleEdit;
  QLineEdit *contentEdit;
  QLineEdit *categoryEdit;
};
