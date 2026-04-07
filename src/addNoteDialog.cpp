#include "addNoteDialog.hpp"
#include <QDialogButtonBox>
#include <QFormLayout>

AddNoteDialog::AddNoteDialog(QWidget *parent) : QDialog(parent) {
  setWindowTitle("Add Note");

  titleEdit = new QLineEdit;
  contentEdit = new QLineEdit;

  QFormLayout *layout = new QFormLayout;
  layout->addRow("Title: ", titleEdit);
  layout->addRow("Content: ", contentEdit);

  QDialogButtonBox *button =
      new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  connect(button, &QDialogButtonBox::accepted, this, &QDialog::accept);
  connect(button, &QDialogButtonBox::rejected, this, &QDialog::reject);

  layout->addRow(button);
  setLayout(layout);
}

QString AddNoteDialog::getTitle() const { return titleEdit->text(); }
QString AddNoteDialog::getContent() const { return contentEdit->text(); }
