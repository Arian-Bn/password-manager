#include "addPasswordDialog.hpp"
#include <QDialogButtonBox>
#include <QFormLayout>

AddPasswordDialog::AddPasswordDialog(QWidget *parent) : QDialog(parent) {
  setWindowTitle("Add Password");

  titleEdit = new QLineEdit;
  websiteEdit = new QLineEdit;
  usernameEdit = new QLineEdit;
  passwordEdit = new QLineEdit;
  passwordEdit->setEchoMode(QLineEdit::Password);

  QFormLayout *layout = new QFormLayout;
  layout->addRow("Title: ", titleEdit);
  layout->addRow("Website: ", websiteEdit);
  layout->addRow("Username: ", usernameEdit);
  layout->addRow("Password: ", passwordEdit);

  QDialogButtonBox *button =
      new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  connect(button, &QDialogButtonBox::accepted, this, &QDialog::accept);
  connect(button, &QDialogButtonBox::rejected, this, &QDialog::reject);

  layout->addRow(button);
  setLayout(layout);
}

QString AddPasswordDialog::getTitle() const { return titleEdit->text(); }
QString AddPasswordDialog::getWebsite() const { return websiteEdit->text(); }
QString AddPasswordDialog::getUsername() const { return usernameEdit->text(); }
QString AddPasswordDialog::getPassword() const { return passwordEdit->text(); }
