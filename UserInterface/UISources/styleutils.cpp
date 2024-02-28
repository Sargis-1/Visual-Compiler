#include "../UIHeaders/styleutils.h"

QGroupBox *StyleUtils::createSmallStyledGroupBox(const QString &title, const QString &borderColor, const QString &backgroundColor, QWidget *parent)
{
  {
      QGroupBox *groupBox = new QGroupBox(title, parent);

      // Define the base style
      QString styleSheet = "QGroupBox {"
                          "    border: 2px solid " + borderColor + ";"
                          "    border-radius: 3px;"
                          "    margin-top: 1ex;"
                          "    background-color: " + backgroundColor + ";"
                          "    height: 40px;"
                          "}";

      // Add title style
      styleSheet += " QGroupBox::title {"
                    "    subcontrol-origin: margin;"
                    "    subcontrol-position: top center;"
                    "    top: 10px;" // Adjust the title position(change RamSegments title positions)
                    "    border: 0px solid transparent;"
                    "    color: " +
                    borderColor +
                    ";"
                    "    background-color: " +
                    backgroundColor +
                    ";"
                    "    padding: 0 10px;"
                    "    border: 0px solid transparent " +
                    borderColor +
                    ";"
                    "    border-top-left-radius: 8px;"
                    "    border-top-right-radius: 8px;"
                    "    border-bottom-left-radius: 8px;"
                    "    border-bottom-right-radius: 8px;"
                    "}";

      groupBox->setStyleSheet(styleSheet);
      QFont titleFont;  // Get the current font
      titleFont.setPointSize(19);  // Set the font size

      groupBox->setFont(titleFont);// Apply the updated font

      return groupBox;
  }
}

QPushButton *StyleUtils::createStyledButton(const QString &text, const QString &color, int fontSize, QWidget *parent)
{

  QPushButton *button = new QPushButton(text, parent);

  // Define the base style
  QString styleSheet = "QPushButton {"
                      "    background-color: " + color + ";"
                      "    color: white;"
                      "    padding: 8px 16px;"
                      "    border: 2px solid " + darkenColor(color) + ";" // Darken the border color
                      "    border-radius: 4px;"
                      "    font-size: " + QString::number(fontSize) + "px;"
                      "}";

  // Hover state
  styleSheet += "QPushButton:hover {"
                "    background-color: " + lightenColor(color) + ";" // Lighten the background on hover
                "}";

  // Pressed state
  styleSheet += "QPushButton:pressed {"
                "    background-color: " + darkenColor(color) + ";" // Darken the background on press
                "}";

  button->setStyleSheet(styleSheet);
  return button;
}
QString StyleUtils::darkenColor(const QString &color)
{
    // Implement your own color darkening logic here
    // You can use QColor or other methods to manipulate the color
    // For simplicity, let's just make it a bit darker
    return color + "80"; // Adding "80" to the color code to make it darker
}

QString StyleUtils::lightenColor(const QString &color)
{
    // Implement your own color lightening logic here
    // You can use QColor or other methods to manipulate the color
    // For simplicity, let's just make it a bit lighter
    return color + "80"; // Adding "80" to the color code to make it lighter
}

StyleUtils::StyleUtils()
{

}
