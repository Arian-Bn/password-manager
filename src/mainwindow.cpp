#include "mainwindow.hpp"
#include "database_manager.hpp"
#include <QGridLayout>
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

  connect(addPasswordButton, &QPushButton::clicked, this,
          &MainWindow::onAddPasswordClicked);
  connect(addNoteButton, &QPushButton::clicked, this,
          &MainWindow::onAddNoteClicked);
  connect(deleteButton, &QPushButton::clicked, this,
          &MainWindow::onDeleteClicked);

  // Arranging in a grid
  QGridLayout *layout = new QGridLayout(central);
  layout->addWidget(addPasswordButton, 0, 0);
  layout->addWidget(addNoteButton, 0, 1);
  layout->addWidget(deleteButton, 0, 2);
  layout->addWidget(entryList, 1, 0, 1, 3);
}

void MainWindow::onAddPasswordClicked() {
  QMessageBox::information(this, "Add Password",
                           "Password entry form will be here");
}

void MainWindow::onAddNoteClicked() {
  QMessageBox::information(this, "Add Note", "Note entry form will be here");
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

void MainWindow::refreshEntryList() {
  entryList->clear();

  DatabaseManager db("Vault.db");
  db.initialize();

  entryList->addItem("Loading from database...");
}
