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
  exitButton = new QPushButton("Exit");
  entryList = new QListWidget(this);
  lineEdit = new QLineEdit(this);
  lineEdit->setPlaceholderText("Search by title...");

  // Load entries from database into list
  refreshEntryList();

  connect(addNoteButton, &QPushButton::clicked, this,
          &MainWindow::onAddNoteClicked);
  connect(deleteButton, &QPushButton::clicked, this,
          &MainWindow::onDeleteClicked);
  connect(exitButton, &QPushButton::clicked, this, &MainWindow::onExitClicked);
  connect(entryList, &QListWidget::itemDoubleClicked, this,
          &MainWindow::onEditEntry);
  connect(lineEdit, &QLineEdit::textChanged, this,
          &MainWindow::onSearchTextChanged);

  // Arranging in a grid
  QGridLayout *layout = new QGridLayout(central);
  layout->addWidget(addNoteButton, 0, 0);
  layout->addWidget(deleteButton, 0, 1);
  layout->addWidget(exitButton, 0, 3);
  layout->addWidget(lineEdit, 1, 0, 1, 3);
  layout->addWidget(entryList, 2, 0, 1, 3);
}

void MainWindow::updateEntryList(
    const std::vector<std::tuple<int, std::string, std::string>> &entries) {
  entryList->clear();

  for (const auto &entry : entries) {
    int id = std::get<0>(entry);
    std::string title = std::get<1>(entry);
    std::string type = std::get<2>(entry);

    QString displayText = "📝 " + QString::fromStdString(title);

    QListWidgetItem *item = new QListWidgetItem(displayText);
    item->setData(Qt::UserRole, id);
    entryList->addItem(item);
  }
}

void MainWindow::onAddNoteClicked() {
  AddNoteDialog dialog(this);
  if (dialog.exec() == QDialog::Accepted) {
    Vault vault;
    vault.addNoteEntry(dialog.getTitle().toStdString(),
                       dialog.getContent().toStdString(),
                       dialog.getCategory().toStdString());
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

void MainWindow::onExitClicked() { close(); }

void MainWindow::refreshEntryList() {
  entryList->clear();

  DatabaseManager db("Vault.db");
  db.initialize();

  auto entries = db.getAllEntries();

  for (const auto &entry : entries) {
    int id = std::get<0>(entry);
    std::string title = std::get<1>(entry);
    std::string type = std::get<2>(entry);

    QString displayText = "📝 " + QString::fromStdString(title);

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

void MainWindow::onSearchTextChanged(const QString &text) {
  DatabaseManager db("Vault.db");

  if (text.isEmpty()) {
    auto entries = db.getAllEntries();
    MainWindow::updateEntryList(entries);
  } else {
    auto entries = db.getEntriesFiltered(text.toStdString());
    MainWindow::updateEntryList(entries);
  }
}
