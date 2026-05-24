#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>

class EditNoteDialog : public QDialog {
public:
  EditNoteDialog(int id, const QString &title, const QString &content,
                 const QString &category, QWidget *parent = nullptr);

  int getId() const;
  QString getTitle() const;
  QString getContent() const;
  QString getCategory() const;

private:
  int noteId;
  QLineEdit *titleEdit;
  QTextEdit *contentEdit;
  QLineEdit *categoryEdit;
};
