#pragma once

#include <QMainWindow>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QFrame> 

#include "widgets/videoWidget/videoWidget.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Ui::MainWindow *ui;
    PlayerWidget* m_sWidget;
    QLineEdit* m_urlInput;

    // setup Ui components for main ui page
    void setupMainPageUi();

    // setup the vertical layout ui for the text input
    void setupTextInputUi(QVBoxLayout* vLayout);

    // setup the buttons ui
    void setupButtonsUi(QVBoxLayout* vLayout);

    // draw a horizontal line
    QFrame* drawHorizontalLine();

private slots:
    // connecting start button released signal & play the stream in the widget
    void slotStartStream();

    // connecting stop button released signal & stop the stream from playing
    void slotStopStream();
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(); 

};
