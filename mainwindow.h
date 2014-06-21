#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QLabel>
#include <QScrollArea>

#include "imagewidget.h"



namespace Ui {
class MainWindow;
}



class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openFileSlot();
    void saveFileClicked();
    void keyPressEvent( QKeyEvent *e );

private:
    Ui::MainWindow *ui;

    QImage image;
    ImageWidget *imageWidget;
    QScrollArea *imageArea;

    QPushButton *openFileBtn;
    QLineEdit *fileNameLE;
    QPushButton *saveFileBtn;
    int counter;

    QVBoxLayout *mainLayout;
    QHBoxLayout *bottomLayout;

    QString picFileName;
    QString previousOpenedFolder;

    void updateFileNameLE();
};

#endif // MAINWINDOW_H
