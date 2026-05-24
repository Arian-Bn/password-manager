#include "addNoteDialog.hpp"
#include <QDialogButtonBox>
#include <QFormLayout>

AddNoteDialog::AddNoteDialog(QWidget *parent) : QDialog(parent) {
  setWindowTitle("Add Note");
  setFixedSize(400, 150);

  titleEdit = new QLineEdit;
  contentEdit = new QLineEdit;
  categoryEdit = new QLineEdit;

  QFormLayout *layout = new QFormLayout;
  layout->addRow("Category: ", categoryEdit);
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
QString AddNoteDialog::getCategory() const { return categoryEdit->text(); }

void AddNoteDialog::accept() {
  // Prevent saving empty title
  if (titleEdit->text().isEmpty()) {
    // Visual feedback for user
    titleEdit->setStyleSheet(
        "QLineEdit { border: 2px solid red; background: #ffeeee; }");
    titleEdit->setPlaceholderText("Title connot be empty!");
    return; // Keep dialog open
  }

  QDialog::accept();
}
