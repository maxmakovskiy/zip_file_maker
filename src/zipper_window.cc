#include "zipper_window.h"

#include <iostream>
#include <sstream>
#include "coder.h"

#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

ZipperWindow::ZipperWindow(QWidget* parent)
    : QWidget(parent)
{
// --- UI blocks --------------------------------------------------
    inputLabel = new QLabel("Input text:");
    asciiLabel = new QLabel("Non-compressed output:");
    compressedLabel = new QLabel("Compressed output:");

    inputEdit = new QTextEdit;

    asciiEdit = new QTextEdit;
    asciiEdit->setReadOnly(true);

    compressedEdit = new QTextEdit;
    compressedEdit->setReadOnly(true);

    compressButton = new QPushButton("Compress");
    compressButton->setDefault(true);
    compressButton->setEnabled(false);

    cleanupButton = new QPushButton("Clean-up");
    cleanupButton->setEnabled(false);

    closeButton = new QPushButton("Close");
// ----------------------------------------------------------------

// --- SETUP SLOTS AND SIGNALS ------------------------------------
    connect(inputEdit, SIGNAL(textChanged()), this, SLOT(enableProcessingButton()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(compressButton, SIGNAL(clicked()), this, SLOT(compressButtonClicked()));
    connect(cleanupButton, SIGNAL(clicked()), this, SLOT(cleanupButtonClicked()));

// ----------------------------------------------------------------

// --- SETUP LAYOUTS ----------------------------------------------
    QVBoxLayout* inputLayout = new QVBoxLayout;
    inputLayout->addWidget(inputLabel);
    inputLayout->addWidget(inputEdit);

    QVBoxLayout* asciiLayout = new QVBoxLayout;
    asciiLayout->addWidget(asciiLabel);
    asciiLayout->addWidget(asciiEdit);

    QVBoxLayout* compressedLayout = new QVBoxLayout;
    compressedLayout->addWidget(compressedLabel);
    compressedLayout->addWidget(compressedEdit);

    QHBoxLayout* outputLayout = new QHBoxLayout;
    outputLayout->addLayout(asciiLayout);
    outputLayout->addLayout(compressedLayout);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(compressButton);
    buttonLayout->addWidget(cleanupButton);
    buttonLayout->addWidget(closeButton);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(outputLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
// ----------------------------------------------------------------

    setWindowTitle("Compress It!");
    setFixedHeight(sizeHint().height());

}

void ZipperWindow::enableProcessingButton()
{
    compressButton->setEnabled(true);
    cleanupButton->setEnabled(true);
}

void ZipperWindow::compressButtonClicked()
{
    QString content = inputEdit->toPlainText();
    std::string strForLib = content.toStdString();

    std::istringstream iss;
    iss.str(strForLib);
    std::ostringstream oss;
    zip_maker::Coder coder(iss);
    coder.Encode(oss);

    compressedEdit->setPlainText(QString::fromStdString(oss.str()));
    asciiEdit->setPlainText(QString::fromStdString(
                                zip_maker::textToBinary(strForLib)));
}

void ZipperWindow::cleanupButtonClicked()
{
    inputEdit->clear();
    asciiEdit->clear();
    compressedEdit->clear();

    compressButton->setEnabled(false);
    cleanupButton->setEnabled(false);
}


