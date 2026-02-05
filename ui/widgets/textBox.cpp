#include "textBox.hpp"
#include <QCoreApplication>

TextBoxWidget::TextBoxWidget(QWidget* parent) 
  : QTextEdit{parent} 
{
  setReadOnly(true);
  setPlaceholderText("System logs and status will appear here...");
  setFixedHeight(150);
}

void TextBoxWidget::appendMessage(const QString& message)
{
  append(QString("%1").arg(message));
  QCoreApplication::processEvents();
}
