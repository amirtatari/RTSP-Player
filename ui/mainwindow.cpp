#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QApplication>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
    , ui{new Ui::MainWindow}
    , m_videoWidget{0, 0, 0, 0, "video1"}
    , m_urlInput{new QLineEdit{"", this}}
    , m_stateMachine{this, this}
{
    ui->setupUi(this);

    // init ui main page
    setupMainPageUi();
}

MainWindow::~MainWindow()
{

    delete ui;
}

QString MainWindow::getUrl() const
{
    return m_urlInput->text();
}

void MainWindow::setupMainPageUi()
{
    // set the main window title
    setWindowTitle("GStreamer Player");

    // create a vertical layout as the central widget;
    QWidget *mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    QVBoxLayout *v_layout = new QVBoxLayout();
    mainWidget->setLayout(v_layout);

    // add elemetns to main layout
    v_layout->addWidget(&m_videoWidget);

    // add a horizontal line
    v_layout->addWidget(drawHorizontalLine());

    // initialize the text box ui
    setupTextInputUi(v_layout);

    // initialize buttons ui
    setupButtonsUi(v_layout);
}

void MainWindow::setupTextInputUi(QVBoxLayout *vLayout)
{
    QLabel *urlLabel = new QLabel("Enter RTSP URL:", this);
    QHBoxLayout *h_layout = new QHBoxLayout();
    h_layout->addWidget(urlLabel);
    h_layout->addWidget(m_urlInput);
    vLayout->addLayout(h_layout);
}

QFrame *MainWindow::drawHorizontalLine()
{
    QFrame *line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    return line;
}

void MainWindow::setupButtonsUi(QVBoxLayout *vLayout)
{
    // create buttons
    QPushButton *start_btn = new QPushButton("Play Stream", this);
    QPushButton *stop_btn = new QPushButton("Stop Stream", this);
    QPushButton *quit_btn = new QPushButton("Quit", this);
    start_btn->setFixedSize(QSize(120, 30));
    stop_btn->setFixedSize(QSize(120, 30));
    quit_btn->setFixedSize(QSize(60, 30));

    // add the buttons to horizontal layout
    QHBoxLayout *h_layout = new QHBoxLayout{};
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
    m_stateMachine.changeState(Event::STOP);
}

void MainWindow::slotStartStream()
{
    m_stateMachine.changeState(Event::PLAY);
}
