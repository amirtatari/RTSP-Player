#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QApplication>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow{parent}, 
    ui{new Ui::MainWindow},
    m_sWidget{new PlayerWidget{0, 0, 1080, 720, "streamWidget1", this}},
    m_urlInput{new QLineEdit{"", this}}
{
    ui->setupUi(this);
    
    // init ui main page
    setupMainPageUi();

    // init gsteamer
    if (!gst_init_check(nullptr, nullptr, nullptr))
    {
        throw std::runtime_error("MainWindow::CTOR: gstreamer init failed!");
    }
}

MainWindow::~MainWindow()
{
    gst_deinit();
    delete ui;
}


void MainWindow::setupMainPageUi()
{
    // set the main window title
    setWindowTitle("GStreamer Player");

    // create a vertical layout as the central widget;
    QWidget* mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    QVBoxLayout* v_layout = new QVBoxLayout();
    mainWidget->setLayout(v_layout);

    // add elemetns to main layout
    v_layout->addWidget(m_sWidget);

    // add a horizontal line
    v_layout->addWidget(drawHorizontalLine());

    // initialize the text box ui
    setupTextInputUi(v_layout);

    // initialize buttons ui
    setupButtonsUi(v_layout);
}

void MainWindow::setupTextInputUi(QVBoxLayout* vLayout)
{
    QLabel* urlLabel = new QLabel("Enter RTSP URL:", this);
    QHBoxLayout* h_layout = new QHBoxLayout();
    h_layout->addWidget(urlLabel);
    h_layout->addWidget(m_urlInput);
    vLayout->addLayout(h_layout);
}

QFrame* MainWindow::drawHorizontalLine()
{
    QFrame *line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    return line;
}

void MainWindow::setupButtonsUi(QVBoxLayout* vLayout)
{
    // create buttons
    QPushButton* start_btn = new QPushButton("Play Stream", this);
    QPushButton* stop_btn = new QPushButton("Stop Stream", this);
    QPushButton* quit_btn = new QPushButton("Quit", this);
    start_btn->setFixedSize(QSize(120, 30));
    stop_btn->setFixedSize(QSize(120, 30));
    quit_btn->setFixedSize(QSize(60, 30));

    // add the buttons to horizontal layout
    QHBoxLayout* h_layout = new QHBoxLayout{};
    h_layout->addWidget(start_btn);
    h_layout->addWidget(stop_btn);
    h_layout->addWidget(quit_btn);
    vLayout->addLayout(h_layout);

    // connect released events of buttons to corresponding slots
    connect(start_btn, &QPushButton::released, this, &MainWindow::slotStartStream);
    connect(stop_btn, &QPushButton::released, this, &MainWindow::slotStopStream);
    connect(quit_btn, &QPushButton::clicked, &QApplication::quit);
}


void MainWindow::slotStopStream()
{
    m_sWidget->stop();
    std::cout << "MainWindow::slotStopStream: stopped!\n";
}


void MainWindow::slotStartStream()
{
    try
    {
        // cconstruct description components
        if(m_urlInput->text().isEmpty())
        {
            throw std::invalid_argument("MainWindow::slotStartStream: URL input is empty!");
        }
        const QString rtspsrc = "rtspsrc location=" + m_urlInput->text();
        const QString latency = " latency=100 !";
        const QString mimeType = " application/x-rtp, media=video, clock-rate=90000, payload=96 !";
        const QString rtpJitter = " rtpjitterbuffer name=jitterbuffer !";
        const QString depay = " rtph264depay ! h264parse !";
        const QString decode = " avdec_h264 !";
        const QString videoScale = " videoconvert ! videoscale ! video/x-raw,width=800,height=600 !";
        const QString sink = " ximagesink name=video_sink sync=false";
        const QString description = rtspsrc + latency + mimeType + rtpJitter + depay + decode + videoScale + sink;

        // play the stream
        m_sWidget->play(description);
    
    }
    catch(const std::exception& e)
    {
        std::cerr << "MainWindow::slotStartStream: "<< e.what() << '\n';
    }
}

