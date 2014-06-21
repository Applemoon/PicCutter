#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>



MainWindow :: MainWindow(QWidget *parent) :
    QWidget(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    counter = 1;
    previousOpenedFolder = "C:\\Users\\Public\\Pictures\\Sample Pictures";

    imageWidget = new ImageWidget;
    imageWidget->setPixmap( QPixmap::fromImage( image ) );

    imageArea = new QScrollArea;
    imageArea->setWidget( imageWidget );
    imageArea->setBackgroundRole( QPalette::Dark );

    openFileBtn = new QPushButton( tr( "Открыть" ) );
    fileNameLE = new QLineEdit;
    saveFileBtn = new QPushButton( tr( "Сохранить" ) );
    saveFileBtn->setDefault( true );

    bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget( openFileBtn );
    bottomLayout->addWidget( fileNameLE );
    bottomLayout->addWidget( saveFileBtn );

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget( imageArea );
    mainLayout->addLayout( bottomLayout );
    setLayout( mainLayout );

    connect( openFileBtn, SIGNAL( clicked() ), SLOT( openFileSlot() ) );
    connect( saveFileBtn, SIGNAL( clicked() ), SLOT( saveFileClicked() ) );

    updateFileNameLE();
}



MainWindow :: ~MainWindow()
{
    delete ui;
}



void MainWindow :: openFileSlot()
{
    const QString prevPicFileName = picFileName;
    picFileName = "";
    picFileName = QFileDialog::getOpenFileName( this, tr( "Открытие изображения" ),
                  previousOpenedFolder, tr( "Изображения (*.png *.jpg *.bmp);;Все файлы (*)" ) );

    if ( !picFileName.isEmpty() )
    {
        image.load( picFileName );
        imageWidget->setImage( image );

        updateFileNameLE();

        previousOpenedFolder = picFileName.section( "/", 1, -2 );
    }
    else
    {
        picFileName = prevPicFileName;
    }
}



void MainWindow :: saveFileClicked()
{
    const QString newFileName = fileNameLE->text();
    if ( QFile::exists( newFileName ) )
    {
        QMessageBox msg;
        msg.setIcon( QMessageBox::Warning );
        msg.setText( tr( "Файл с этим именем уже существует." ) );
        msg.setInformativeText( tr( "Заменить?" ) );
        msg.addButton( tr( "Да" ), QMessageBox::AcceptRole );
        QPushButton *noBtn = msg.addButton( tr( "Нет" ), QMessageBox::RejectRole );
        msg.exec();

        if ( msg.clickedButton() == noBtn )
        {
            return;
        }
    }

    QImage savedImage = imageWidget->getFramedImage();
    savedImage.save( newFileName, "", 100 );

    ++counter;
    updateFileNameLE();
}



void MainWindow :: keyPressEvent( QKeyEvent *e )
{
    if ( e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return )
    {
        saveFileClicked();
    }

    if ( e->key() == Qt::Key_Escape )
    {
        exit( 0 );
    }
}



void MainWindow :: updateFileNameLE()
{
    if ( !picFileName.isEmpty() )
    {
        QString leText = picFileName;
        const QString format = picFileName.section( ".", -1 );
        leText.remove( leText.section( "/", -1 ) );
        leText += QString::number( counter );
        fileNameLE->setText( leText + "." + format );
    }
    else
    {
        fileNameLE->setText( "" );
    }
}
