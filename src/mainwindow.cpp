#include "mainwindow.hpp"
#include <QGridLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  setWindowTitle("SecureVault");
  resize(800, 600);

  // Create a central wodget
  QWidget *central = new QWidget(this);
  setCentralWidget(central);

  // Create buttons
  addPasswordButton = new QPushButton("Add Password");
  addNoteButton = new QPushButton("Add Notes");
  deleteButton = new QPushButton("Delete");
  entryList = new QListWidget();

  // Arranging in a grid
  QGridLayout *layout = new QGridLayout(central);
  layout->addWidget(addPasswordButton, 0, 0);
  layout->addWidget(addNoteButton, 0, 1);
  layout->addWidget(deleteButton, 0, 2);
  layout->addWidget(entryList, 1, 0, 1, 3);
}
