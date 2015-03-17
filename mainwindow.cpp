#include "mainwindow.h"
#include "boximage.h"
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QSplitter>
#include <QListView>
#include <QGridLayout>
#include <QBoxLayout>
#include <QPushButton>
#include <QAction>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent){
    splitter = new QSplitter();
    box = new BoxImage(splitter);
    Init();
}

MainWindow::~MainWindow()
{

}

void MainWindow::Init()
{
     QMenu *fileMenu;
     fileMenu = menuBar()->addMenu(tr("&File"));
     fileMenu->addAction("New", this, SLOT(InvalidItem()), 0);
     fileMenu->addAction("Open", this, SLOT(InvalidItem()), 0);
     fileMenu->addSeparator();
     fileMenu->addAction("Save", this, SLOT(InvalidItem()), 0);
     fileMenu->addAction("Save as", this, SLOT(InvalidItem()), 0);
     fileMenu->addSeparator();
     fileMenu->addAction("Quit", this, SLOT(quit()), 0);

     QMenu *editMenu;
     editMenu = menuBar()->addMenu(tr("&Edit"));
     editMenu->addAction("Undo", this, SLOT(InvalidItem()), 0);
     editMenu->addAction("Redo", this, SLOT(InvalidItem()), 0);
     editMenu->addSeparator();
     QAction *actionAddCollection = editMenu->addAction("Add Collection");
     QAction *actionAddImage =  editMenu->addAction("Add Image");
     QAction *actionDeleteAllImages = editMenu->addAction("Remove All Images");

     QPushButton *AddCollection = new QPushButton("Add Collection", 0);
     QPushButton *AddImage = new QPushButton("Add Image", 0);
     QPushButton *DeleteAllImages = new QPushButton("Delete All Images", 0);
     connect(actionAddImage, SIGNAL(triggered()), box, SLOT(slotAddImage()));
     connect(AddImage, SIGNAL(clicked()), box, SLOT(slotAddImage()));
     connect(actionAddCollection, SIGNAL(triggered()), box, SLOT(slotAddCollection()));
     connect(AddCollection, SIGNAL(clicked()), box, SLOT(slotAddCollection()));
     connect(actionDeleteAllImages, SIGNAL(triggered()), box, SLOT(slotDeleteAllImages()));
     connect(DeleteAllImages, SIGNAL(clicked()), box, SLOT(slotDeleteAllImages()));

     QWidget *leftWidget = new QWidget(0);
     QBoxLayout *leftLayout = new QBoxLayout(QBoxLayout::TopToBottom, 0);
     AddCollection->setMinimumHeight(75);
     AddImage->setMinimumHeight(75);
     DeleteAllImages->setMinimumHeight(75);
     leftLayout->addWidget(AddCollection, 1, 0);
     leftLayout->addWidget(AddImage, 1, 0);
     leftLayout->addWidget(DeleteAllImages, 1, 0);
     leftLayout->addWidget(new QWidget());
     leftLayout->setSpacing(4);
     leftWidget->setLayout(leftLayout);
     leftWidget->resize(150, 500);
     splitter->addWidget(leftWidget);
     QScrollArea *right = new QScrollArea();
     right->setWidget(box);
     right->setWidgetResizable(true);
     right->setMaximumWidth(780);
     right->resize(780, 500);
     splitter->addWidget(right);
     setCentralWidget(splitter);
     this->resize(950, 500);
}


void MainWindow::InvalidItem()
{
    QMessageBox *msgBox = new QMessageBox;
    msgBox->setText("Not implemented yet");
    msgBox->exec();
}
void MainWindow::quit()
{
    exit(0);
}
