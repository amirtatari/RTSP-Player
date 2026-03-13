#pragma once

#include <QMainWindow>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QFrame> 

#include "widgets/videoWidget.hpp"
#include "widgets/textBox.hpp"
#include "../backend/stateMachine/stateMachine.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
    Ui::MainWindow *ui;
    QLineEdit* m_urlInput;

    VideoWidget m_videoWidget; 
    TextBoxWidget m_textBox;

    // setup Ui components for main ui page
    void setupMainPageUi();

    // setup the vertical layout ui for the text input
    void setupTextInputUi(QVBoxLayout* vLayout);

    // setup the buttons ui
    void setupButtonsUi(QVBoxLayout* vLayout);

    // draw a horizontal line
    QFrame* drawHorizontalLine();
private slots:
    void slotStartStream();
    void slotStopStream();

public slots:
    // handle gstreamer signals
    void handleMessage(const QString& message);
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(); 

    VideoWidget& getVideoWidget() { return m_videoWidget; }
    QString getUrl() const;

signals:
    void sendEvent(Event event);
};
