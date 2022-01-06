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
    void on_compressButton_clicked();
    void on_cleanupButton_clicked();

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


};

#endif
