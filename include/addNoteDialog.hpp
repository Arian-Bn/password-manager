#pragma once
#include "qtmetamacros.h"
#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>

class AddNoteDialog : public QDialog {
  Q_OBJECT

public:
  AddNoteDialog(QWidget *parent = nullptr);

  QString getTitle() const;
  QString getContent() const;

private:
  QLineEdit *titleEdit;
  QLineEdit *contentEdit;
};
