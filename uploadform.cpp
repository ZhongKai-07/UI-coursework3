#include "uploadform.h"

#include <qboxlayout.h>
#include <qcalendarwidget.h>
#include <qlabel.h>
#include <qmessagebox.h>
#include <qnamespace.h>
#include <qpushbutton.h>


#include <iostream>

using namespace std;

UploadForm::UploadForm(QWidget *parent) : QWidget(parent){
    this->setGeometry(400, 400, 400, 400);
    setWindowTitle("Add New Video");
    openButton = new QPushButton("Open", this);
    connect(openButton, SIGNAL(clicked()), this, SLOT(openFile()));

    pathField = new QLineEdit(this);
    pathField->setReadOnly(true);
    dateField = new QCalendarWidget(this);
    memoField = new QTextEdit(this);

    QBoxLayout *pathLayout = new QHBoxLayout();
    pathLayout->addWidget(pathField);
    pathLayout->addWidget(openButton);
    pathLayout->setMargin(0);

    okButton = new QPushButton("OK", this);
    okButton->setDisabled(true);
    connect(okButton, SIGNAL(clicked()), this, SLOT(submit()));

    cancelButton = new QPushButton("Cancel", this);
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));

    QBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    QFormLayout *form = new QFormLayout();
    form->addRow("Video path:", pathLayout);
    form->addRow("Filmed at:", dateField);
    form->addRow("Memory:", memoField);

    form->addRow(buttonLayout);
    form->setHorizontalSpacing(10);
    form->setVerticalSpacing(10);
    form->setLabelAlignment(Qt::AlignCenter);

    setLayout(form);
}

void UploadForm::openFile(){
    files = QFileDialog::getOpenFileNames(this, tr("Select Video"), ".",
                                          "Video Files (*.mp4 *.mov *.wmv *.avi *.mp3)");
    if (files.isEmpty()) {
        return;
    }

    QString filesDisp;
    QTextStream fileDispStream(&filesDisp);
    for (int i = 0; i < files.size(); i++) {
        fileDispStream << QFileInfo(files[i]).fileName() << "; ";
    }
    pathField->setText(filesDisp);

    QFileInfo info(files[0]);
    okButton->setDisabled(false);
}

void UploadForm::reset(){
    files.clear();
    dateField->showToday();
    pathField->clear();
    memoField->clear();
    okButton->setDisabled(true);
}

void UploadForm::cancel(){
    reset();
    hide();
}

void UploadForm::submit(){

}
