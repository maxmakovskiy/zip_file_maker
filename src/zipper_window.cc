#include "zipper_window.h"

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
    if (inputEdit->toPlainText().isEmpty()) return;

    compressButton->setEnabled(true);
    cleanupButton->setEnabled(true);

}

void ZipperWindow::on_compressButton_clicked()
{


}

void ZipperWindow::on_cleanupButton_clicked()
{
    inputEdit->clear();
    asciiEdit->clear();
    compressedEdit->clear();
}


