#ifndef STYLEUTILS_H
#define STYLEUTILS_H

class StyleUtils
{
public:
  static QGroupBox* createSmallStyledGroupBox(const QString &title, const QString &borderColor, const QString &backgroundColor, QWidget *parent);
  static QGroupBox* createMediumStyledGroupBox(const QString &title, const QString &borderColor, const QString &backgroundColor, QWidget *parent);
  static QPushButton* createStyledButton(const QString &text, const QString &color, int fontSize, QWidget *parent);
private:
  StyleUtils();
  static QString darkenColor(const QString &color);
  static QString lightenColor(const QString &color);
};

#endif // STYLEUTILS_H
