#include "mainwindow.hpp"
#include "addNoteDialog.hpp"
#include "database_manager.hpp"
#include "vault.hpp"
#include <QGridLayout>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  setWindowTitle("NotesVault");
  resize(800, 600);

  // Create a central widget
  QWidget *central = new QWidget(this);
  setCentralWidget(central);

  // Create buttons
  addNoteButton = new QPushButton("Add Note");
  deleteButton = new QPushButton("Delete");
  entryList = new QListWidget();

  // Load entries from database into list
  refreshEntryList();

  connect(addNoteButton, &QPushButton::clicked, this,
          &MainWindow::onAddNoteClicked);
  connect(deleteButton, &QPushButton::clicked, this,
          &MainWindow::onDeleteClicked);

  // Arranging in a grid
  QGridLayout *layout = new QGridLayout(central);
  layout->addWidget(addNoteButton, 0, 0);
  layout->addWidget(deleteButton, 0, 1);
  layout->addWidget(entryList, 1, 0, 1, 2);

  connect(entryList, &QListWidget::itemDoubleClicked, this,
          &MainWindow::onEditEntry);
}

void MainWindow::onAddNoteClicked() {
  AddNoteDialog dialog(this);
  if (dialog.exec() == QDialog::Accepted) {
    Vault vault;
    vault.addNoteEntry(dialog.getTitle().toStdString(),
                       dialog.getContent().toStdString());
    refreshEntryList();
  }
}

void MainWindow::onDeleteClicked() {
  QListWidgetItem *current = entryList->currentItem();
  if (!current) {
    QMessageBox::warning(this, "Warning", "No entry selected");
    return;
  }

  int id = current->data(Qt::UserRole).toInt();

  QMessageBox::StandardButtons reply;
  reply = QMessageBox::question(
      this, "Delete", "Are you sure you want to delete the selected entry?",
      QMessageBox::Yes | QMessageBox::No);

  if (reply == QMessageBox::Yes) {
    Vault vault;
    vault.deleteEntry(id);
    refreshEntryList();
  }
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
    if (type == "note") {
      displayText = "📝 " + displayText;
    }

    QListWidgetItem *item = new QListWidgetItem(displayText);
    item->setData(Qt::UserRole, id);
    entryList->addItem(item);
  }
}

void MainWindow::onEditEntry(QListWidgetItem *item) {
  if (!item)
    return;

  int id = item->data(Qt::UserRole).toInt();
  QMessageBox::information(this, "Edit",
                           "Edit entry ID: " + QString::number(id));
}
