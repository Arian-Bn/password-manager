#pragma once
#include "qtmetamacros.h"
#include <QDialog>
#include <QLineEdit>

class AddPasswordDialog : public QDialog {
  Q_OBJECT

public:
  AddPasswordDialog(QWidget *parent = nullptr);

  QString getTitle() const;
  QString getWebsite() const;
  QString getUsername() const;
  QString getPassword() const;

private:
  QLineEdit *titleEdit;
  QLineEdit *websiteEdit;
  QLineEdit *usernameEdit;
  QLineEdit *passwordEdit;
};
