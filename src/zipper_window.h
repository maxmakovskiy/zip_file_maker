#ifndef ZIP_FILE_MAKER_ZIPPER_WINDOW_H_
#define ZIP_FILE_MAKER_ZIPPER_WINDOW_H_

#include <QWidget>
#include <QString>

class QLabel;
class QTextEdit;
class QPushButton;

class ZipperWindow : public QWidget
{
    Q_OBJECT

public:
    ZipperWindow(QWidget* parent = nullptr);

private slots:
    void enableProcessingButton();
    void compressButtonClicked();
    void cleanupButtonClicked();

private:
    QLabel* inputLabel;
    QLabel* asciiLabel;
    QLabel* compressedLabel;
    QTextEdit* inputEdit;
    QTextEdit* asciiEdit;
    QTextEdit* compressedEdit;
    QPushButton* compressButton;
    QPushButton* cleanupButton;
    QPushButton* closeButton;

    const QString INPUT_LABEL = "Input text:";
    const QString ASCII_LABEL = "Non-compressed output:";
    const QString COMPRESSED_LABEL = "Compressed output:";

};

#endif
