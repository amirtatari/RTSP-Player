#pragma once

#include <QTextEdit>

class TextBoxWidget : public QTextEdit
{
  Q_OBJECT
public:
  explicit TextBoxWidget(QWidget* parent = nullptr);
  void appendMessage(const QString& message);
};