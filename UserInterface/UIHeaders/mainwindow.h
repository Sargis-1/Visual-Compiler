// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "ramsegment.h"

#include "../../Enums/segmentsenum.h"//Includes Enum class for Ramsegments

//Class MainWindow contains all components of UI, it the class which object is created in main function and shown when program is running
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    ~MainWindow();
    RAMSegment* getSegment(Segment segment);//Get Segment segment's pointer
private slots://Methods which are connected to buttons
    void updateSimulation(bool& b);
    void updateSimulationAllRows();

    void startClicked();//Connected to Execute 1 line button on UI
    void executeClicked();//Connected to Execute all lines button on UI
    void resetClicked();//Connected to Reset button on UI
    void stopClicked();//Connected to Stop buttonon UI
    void chooseFileClicked();//Connected to Choose file button on UI

    void updateCodeText(const QString &filePath);
private:
    QWidget *mainWidget;//Main widget where all components of UI are added later
    QHBoxLayout *mainLayout;//Layout to show mainWidget
    QTextEdit *codeTextEdit;//Is used to show the code in chosen file
    QTextEdit* ramTextEdit;
    QVBoxLayout *ramLayout;
    QVBoxLayout *leftLayout;//Layout to show code, which will be executed
    QVBoxLayout *rightLayout;//Layout to show Ram Segments
    QTimer *timer;//Timer is used to set time interval while parsing code line by line
    QPushButton *start;//Execute 1 line button
    QPushButton *execute;//Execute button
    QPushButton *stop;//Stop button
    QPushButton *reset;//Reset button
    QPushButton *chooseFile;//Choose file button
    QVBoxLayout *buttonsLayout;//Vertiacal layout for buttons
    QProgressBar *progressBar;//Progress bar shows what percent of program is executed
    QGroupBox *codeGroupBox;
    QGroupBox *ramGroupBox;
    int currentRow;//Hold the line's index which we are currently executing
    QGraphicsScene* scene;//Scene which shows all UI components

    QVector<RAMSegment*> ramSegments;//Contains all Ramsegments


    // New functions added based on refactoring
    void initializeButtons();
    void addBorederToLines();
    QPushButton *createStyledButton(const QString &text, const QString &color, int fontSize = 10, QWidget *parent = nullptr);
    void setNotebookStyle();
    void initializeLayouts();
    void initializeGroupBoxes();
    QGroupBox *createStyledGroupBox(const QString &title, const QString &borderColor, const QString &backgroundColor, QWidget *parent = nullptr);
    void initializeTextEdit();
    void connectButtons();
    QString darkenColor(const QString &color);
    QString lightenColor(const QString &color);
    void disconnectSignalsAndSlots();
    void releaseResources();
    void setupRam(QVBoxLayout* ramLayout);
    void setup();

private:
    explicit MainWindow(QWidget *parent = nullptr);//Private ctor for Singleton pattern
    static MainWindow* windowInstance;//Contains pointer to MainWindow instance
public:
    static MainWindow* getWindowInstance();//Returns Mainwindow's instance
};

#endif // MAINWINDOW_H
