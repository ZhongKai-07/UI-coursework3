#include "menu_bar.h"

#include <QFileDialog>

MenuBar::MenuBar(QWidget* parent) : QWidget(parent)
{
    //this->icons = icons;

    setFixedHeight(64);

    layout = new QHBoxLayout();
    layout->setContentsMargins(128, 0, 128, 0);
    setLayout(layout);

    addItems();

    addConnect();
}

MenuBar::~MenuBar()
{

}

void MenuBar::setButton(QPushButton *button, QString name)
{
    //button->setIcon(icons->find(name).value());
    button->setIconSize(QSize(80, 40));
    button->setFixedSize(button->iconSize());
    //button->setFlat(true);
    layout->addWidget(button);
}

void MenuBar::addItems()
{
    uploadButton = new QPushButton();
    setButton(uploadButton, "upload");
    uploadButton->setText("Upload");

    layout->addStretch();

    toPlayButton = new QPushButton();
    setButton(toPlayButton, "toplay");
    toPlayButton->setText("Play");
}



void MenuBar::addConnect()
{
    connect(uploadButton, SIGNAL(clicked()), this, SLOT(uploadButtonClicked()));
    connect(toPlayButton, SIGNAL(clicked()), this, SLOT(toPlayButtonClicked()));
}



void MenuBar::uploadButtonClicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this, "Open Videos", "./", "*.wmv");
    if(files.length() > 0)
    {
        emit upload(files);
    }
}

void MenuBar::toPlayButtonClicked()
{
    emit toPlay();
}
