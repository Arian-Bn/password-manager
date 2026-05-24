#include "editNoteDialog.hpp"
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <qdialog.h>
#include <qdialogbuttonbox.h>

EditNoteDialog::EditNoteDialog(int id, const QString &title,
                               const QString &content, const QString &category,
                               QWidget *parent)
    : QDialog(parent), noteId(id) {
  setWindowTitle("Edit Note");

  titleEdit = new QLineEdit(title);
  contentEdit = new QTextEdit;
  contentEdit->setPlainText(content);
  categoryEdit = new QLineEdit(category);

  QFormLayout *layout = new QFormLayout;
  layout->addRow("Category: ", categoryEdit);
  layout->addRow("Title: ", titleEdit);
  layout->addRow("Content: ", contentEdit);

  QDialogButtonBox *buttonBox =
      new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
  connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
  layout->addRow(buttonBox);

  setLayout(layout);
}

int EditNoteDialog::getId() const { return noteId; }
QString EditNoteDialog::getTitle() const { return titleEdit->text(); }
QString EditNoteDialog::getCategory() const { return categoryEdit->text(); }
QString EditNoteDialog::getContent() const {
  return contentEdit->toPlainText();
}
