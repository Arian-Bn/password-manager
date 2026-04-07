#include "mainwindow.hpp"
#include "addNoteDialog.hpp"
#include "addPasswordDialog.hpp"
#include "database_manager.hpp"
#include <QGridLayout>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  setWindowTitle("SecureVault");
  resize(800, 600);

  // Create a central widget
  QWidget *central = new QWidget(this);
  setCentralWidget(central);

  // Create buttons
  addPasswordButton = new QPushButton("Add Password");
  addNoteButton = new QPushButton("Add Notes");
  deleteButton = new QPushButton("Delete");
  entryList = new QListWidget();

  // Load entries from database into list
  refreshEntryList();

  connect(addPasswordButton, &QPushButton::clicked, this,
          &MainWindow::onAddPasswordClicked);
  connect(addNoteButton, &QPushButton::clicked, this,
          &MainWindow::onAddNoteClicked);
  connect(deleteButton, &QPushButton::clicked, this,
          &MainWindow::onDeleteClicked);
  connect(entryList, &QListWidget::itemClicked, this,
          &MainWindow::onEntryClicked);

  // Arranging in a grid
  QGridLayout *layout = new QGridLayout(central);
  layout->addWidget(addPasswordButton, 0, 0);
  layout->addWidget(addNoteButton, 0, 1);
  layout->addWidget(deleteButton, 0, 2);
  layout->addWidget(entryList, 1, 0, 1, 3);
}

void MainWindow::onAddPasswordClicked() {
  AddPasswordDialog dialog(this);
  if (dialog.exec() == QDialog::Accepted) {
    // TODO: Save in DB
    QMessageBox::information(this, "Success", "Password saved (coming soon)");
    refreshEntryList();
  }
}

void MainWindow::onAddNoteClicked() {
  AddNoteDialog dialog(this);
  if (dialog.exec() == QDialog::Accepted) {
    // TODO: SAve in DB
    QMessageBox::information(this, "Success", "Note saved (coming soon)");
    refreshEntryList();
  }
}

void MainWindow::onDeleteClicked() {
  QMessageBox::StandardButtons reply;
  reply = QMessageBox::question(
      this, "Delete", "Are you sure you want to delete the selected entry?",
      QMessageBox::Yes | QMessageBox::No);

  if (reply == QMessageBox::Yes) {
    QMessageBox::information(this, "Delete", "Entry deleted (placeholder)");
  }
}

void MainWindow::onEntryClicked(QListWidgetItem *item) {
  int id = item->data(Qt::UserRole).toInt();
  QMessageBox::information(this, "Selected",
                           "Record ID " + QString::number(id));
}

void MainWindow::refreshEntryList() {
  entryList->clear();

  DatabaseManager db("Vault.db");
  db.initialize();

  auto entries = db.getAllEntries();

  for (const auto &entry : entries) {
    int id = std::get<0>(entry);
    std::string title = std::get<1>(entry);
    std::string type = std::get<2>(entry);

    QString displayText = QString::fromStdString(title);
    if (type == "password") {
      displayText = "🔒 " + displayText;
    } else {
      displayText = "📝 " + displayText;
    }

    QListWidgetItem *item = new QListWidgetItem(displayText);
    item->setData(Qt::UserRole, id);
    entryList->addItem(item);
  }
}
