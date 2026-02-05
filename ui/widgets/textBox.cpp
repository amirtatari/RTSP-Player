#include "textBox.hpp"
#include <QDateTime>

TextBoxWidget::TextBoxWidget(QWidget* parent) 
  : QTextEdit{parent} 
{
  setReadOnly(true);
  setPlaceholderText("System logs and status will appear here...");
  setFixedHeight(150);
}

void TextBoxWidget::appendMessage(const QString& message)
{
  const QString timestamp {QDateTime::currentDateTime().toString("hh:mm:ss")};
  append(QString("[%1] %2").arg(timestamp, message));
}
