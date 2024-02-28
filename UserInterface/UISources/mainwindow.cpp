// mainwindow.cpp
#include "../../Server/Controller/controller.h"
#include "../../Server/ControlBlock/controlblock.h"

MainWindow* MainWindow::windowInstance = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), currentRow(0), timer(nullptr), start(nullptr),
      execute(nullptr), stop(nullptr), reset(nullptr), chooseFile(nullptr),
    progressBar(nullptr), codeGroupBox(nullptr), ramGroupBox(nullptr), scene(nullptr)

{
  QScreen *primaryScreen = QGuiApplication::primaryScreen();//Getting Screen pointer to use its properties
  QRect screenGeometry = primaryScreen->availableGeometry();//Getting screens max avaialable size
  resize(screenGeometry.size());//resize MainWindow to fill full screen
  setWindowState(Qt::WindowMaximized);//Set MainWindow state to maximized
  this->setStyleSheet("background-color: #ffffff;");

  // Initialize UI components
  initializeButtons();
  initializeLayouts();
  initializeGroupBoxes();
  initializeTextEdit();

  // Set up connections
  connectButtons();
  setup();
  // Set the central widget
  setCentralWidget(mainWidget);//Setting mainWidget as central widget of the UI
}

MainWindow* MainWindow::getWindowInstance()
{
    if(!windowInstance){
        windowInstance = new MainWindow();
    }
    return windowInstance;
}

void MainWindow::initializeButtons()
{   //Here 5 buttons on the left side of UI are created with given properties
    //For every button Parent widget is MainWindow
    start = createStyledButton("EXECUTE 1 LINE", "#4CAF50", 14,  this);//start button is actually the Execute one line button
    execute = createStyledButton("EXECUTE ALL LINES", "green", 14,  this);
    reset = createStyledButton("RESET", "yellow", 14, this);
    stop = createStyledButton("STOP", "red", 14, this);
    chooseFile = createStyledButton("Choose File", "forest", 14, this);
    progressBar = new QProgressBar(this);//Creating progress bar
    progressBar->setMinimum(0);//Setting minimum vale to be shown on progress bar
    progressBar->setValue(0);//Setting progress bar's current value
}

QPushButton *MainWindow::createStyledButton(const QString &text, const QString &color, int fontSize, QWidget *parent)
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

QString MainWindow::darkenColor(const QString &color)
{
    // Implement your own color darkening logic here
    // You can use QColor or other methods to manipulate the color
    // For simplicity, let's just make it a bit darker
    return color + "80"; // Adding "80" to the color code to make it darker
}

QString MainWindow::lightenColor(const QString &color)
{
    // Implement your own color lightening logic here
    // You can use QColor or other methods to manipulate the color
    // For simplicity, let's just make it a bit lighter
    return color + "80"; // Adding "80" to the color code to make it lighter
}

void MainWindow::initializeLayouts()
{
    mainWidget = new QWidget(this);//Creating main widget
    mainLayout = new QHBoxLayout(mainWidget);//Creating main layout to add mainWidget to it later
    buttonsLayout = new QVBoxLayout();//Creating horizontal layout to contain buttons
    leftLayout = new QVBoxLayout();//Creating layout to show the source code
    rightLayout = new QVBoxLayout();//Creating layout to show Ramsegments

    mainLayout->addLayout(buttonsLayout);//Adding buttonsLayout to mainLayout
    mainLayout->addLayout(leftLayout);//Adding leftLayout to mainLayout
    mainLayout->addLayout(rightLayout);//Adding rightLayout to mainLayout
}

void MainWindow::initializeGroupBoxes()
{   //Simple creating custom title bars for the source code on the top left side and Ram segments on the top right side of UI
    codeGroupBox = createStyledGroupBox("User Code ", "#BC804D", "#ffffff", this); // Old Value #d35400// for the source code on the top left side of UI named "User code"
    ramGroupBox = createStyledGroupBox("RAM", "green", "#ffffff", this); // Old Value #87CEEB//for the Ram segments on the top right side of UI named "Ram"
}

QGroupBox *MainWindow::createStyledGroupBox(const QString &title, const QString &borderColor, const QString &backgroundColor, QWidget *parent)
{
    QGroupBox *groupBox = new QGroupBox(title, parent);

    // Define the base style
    QString styleSheet = "QGroupBox {"
                        "    border: 2px solid " + borderColor + ";"
                        "    border-radius: 8px;"
                        "    margin-top: 1ex;"
                        "    background-color: " + backgroundColor + ";"
                        "    height: 48px;"
                        "}";

    // Add title style
    styleSheet += " QGroupBox::title {"
                  "    subcontrol-origin: margin;"
                  "    subcontrol-position: top center;"
                  "    top: 12px;" // Adjust the title position
                  "    color: " +
                  borderColor +
                  ";"
                  "    background-color: " +
                  backgroundColor +
                  ";"
                  "    padding: 0 10px;"
                  "    border: 2px solid transparent " +
                  borderColor +
                  ";"
                  "    border-top-left-radius: 8px;"
                  "    border-top-right-radius: 8px;"
                  "    border-bottom-left-radius: 8px;"
                  "    border-bottom-right-radius: 8px;"
                  "}";

    groupBox->setStyleSheet(styleSheet);
    QFont titleFont;  // Get the current font
    titleFont.setPointSize(18);  // Set the font size
    groupBox->setFont(titleFont);// Apply the updated font

    return groupBox;
}


// In your paintEvent or another appropriate place

void MainWindow::initializeTextEdit()
{   //Creating place where source code will be shown
    codeTextEdit = new QTextEdit();
    codeTextEdit->setTextColor("black");//Setting source code text color
    codeTextEdit->setPlainText("Line 1\n");//Setting default source code
    codeTextEdit->setLineWrapColumnOrWidth(10);
    codeTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//Hiding Vertical scroll bar
    codeTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//Hiding Horizontal scroll bar

}

void MainWindow::connectButtons()
{   //Commecting each button to its method, when we press the button, connected method will be called
    connect(stop, &QPushButton::clicked, this, &MainWindow::stopClicked);
    connect(reset, &QPushButton::clicked, this, &MainWindow::resetClicked);
    connect(execute, &QPushButton::clicked, this, &MainWindow::executeClicked);
    connect(start, &QPushButton::clicked, this, &MainWindow::startClicked);
    connect(chooseFile, &QPushButton::clicked, this, &MainWindow::chooseFileClicked);
}

void MainWindow::setup()
{ //Adding every widget, button etc. to its place on UI
  buttonsLayout->addWidget(start);
  buttonsLayout->addWidget(execute);
  buttonsLayout->addWidget(reset);
  buttonsLayout->addWidget(stop);
  buttonsLayout->addWidget(chooseFile);
  leftLayout->addWidget(codeGroupBox);
  leftLayout->addWidget(codeTextEdit);
  leftLayout->addWidget(progressBar);
  rightLayout->addWidget(ramGroupBox);
  setupRam(rightLayout);
}

void MainWindow::setupRam(QVBoxLayout* ramLayout)
{
    QGraphicsScene* ramScene = new QGraphicsScene(this);//Creating separate scene for Ram Segments, which parent widget is MainWindow

    //Creating all 6 Ram Segments
    RAMSegment* stack = new RAMSegment("Stack", ramScene, this);
    RAMSegment* heap = new RAMSegment("Heap", ramScene, this);
    RAMSegment* func = new RAMSegment("Function", ramScene, this);
    RAMSegment* readOnly = new RAMSegment("Read Only", ramScene, this);
    RAMSegment* bss = new RAMSegment("BSS", ramScene, this);
    RAMSegment* data = new RAMSegment("Data", ramScene, this);

    //addinf them to vector of RamSegment* rs
    ramSegments.push_back(stack);
    ramSegments.push_back(heap);
    ramSegments.push_back(func);
    ramSegments.push_back(readOnly);
    ramSegments.push_back(bss);
    ramSegments.push_back(data);

    // Create a scroll area
    QScrollArea* ramScrollArea = new QScrollArea(this);
    ramScrollArea->setWidgetResizable(true);

    // Create a widget to contain the QGraphicsView
    QWidget* ramWidget = new QWidget(this);
    QVBoxLayout* ramWidgetLayout = new QVBoxLayout(ramWidget);

    // Add RAM segments to the layout
    ramWidgetLayout->addLayout(stack->getLayout());
    ramWidgetLayout->addLayout(heap->getLayout());
    ramWidgetLayout->addLayout(func->getLayout());
    ramWidgetLayout->addLayout(readOnly->getLayout());
    ramWidgetLayout->addLayout(bss->getLayout());
    ramWidgetLayout->addLayout(data->getLayout());
    // Set the widget as the scroll area's content
    ramScrollArea->setWidget(ramWidget);
    ramScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Add the scroll area to the ram layout
    ramLayout->addWidget(ramScrollArea);
}

MainWindow::~MainWindow()
{
    disconnectSignalsAndSlots();
    releaseResources();
}

RAMSegment* MainWindow::getSegment(Segment segment)
{
    int index = static_cast<int>(segment);
    return ramSegments[index];
}

void MainWindow::disconnectSignalsAndSlots()
{   //Disconnecting all signals and slot which were connected earlier
    disconnect(stop, &QPushButton::clicked, this, &MainWindow::stopClicked);
    disconnect(reset, &QPushButton::clicked, this, &MainWindow::resetClicked);
    disconnect(execute, &QPushButton::clicked, this, &MainWindow::executeClicked);
    disconnect(start, &QPushButton::clicked, this, &MainWindow::startClicked);
    disconnect(chooseFile, &QPushButton::clicked, this, &MainWindow::chooseFileClicked);

    if (timer) {
        disconnect(timer, &QTimer::timeout, this, nullptr);
    }
}

void MainWindow::releaseResources()
{
//    delete ui; // Release the UI resources

    // Release dynamically allocated buttons
    if (start) delete start;
    if (execute) delete execute;
    if (stop) delete stop;
    if (reset) delete reset;
    if (chooseFile) delete chooseFile;

    // Release dynamically allocated layouts
    if (mainLayout) delete mainLayout;
    if (buttonsLayout) delete buttonsLayout;
    if (leftLayout) delete leftLayout;
    if (rightLayout) delete rightLayout;

    // Release dynamically allocated progress bar
    if (progressBar) delete progressBar;

    // Release dynamically allocated group boxes
    if (codeGroupBox) delete codeGroupBox;
    if (ramGroupBox) delete ramGroupBox;

    // Release dynamically allocated text edits
    if (codeTextEdit) delete codeTextEdit;

    // Release the timer resource, if applicable
    if (timer) {
        timer->stop();
        delete timer;
    }
    if(scene) delete scene;
    for (auto& slot : ramSegments) {
        if(slot) delete slot;
        slot = nullptr;
    }

    ramSegments.clear();

    // Set member variables to nullptr after deletion
    timer = nullptr;
    start = nullptr;
    execute = nullptr;
    stop = nullptr;
    reset = nullptr;
    chooseFile = nullptr;
    progressBar = nullptr;
    mainLayout = nullptr;
    buttonsLayout = nullptr;
    leftLayout = nullptr;
    rightLayout = nullptr;
    codeGroupBox = nullptr;
    ramGroupBox = nullptr;
    codeTextEdit = nullptr;
}

void MainWindow::startClicked()
{
    QPushButton* startButton = qobject_cast<QPushButton*>(sender());//qobject_cast is type of dynamic cast in Qt, used to cast
    //the object pointer which triggered the call to this private slot to cast it into  QPushButton*
    startButton->setDisabled(true);//Disable button while according method is being executed

    bool success = false;

    timer = new QTimer(this);//Creating new timer
    connect(timer, &QTimer::timeout, this, [this, startButton, &success]() {//lambda function which is connected to timer
        updateSimulation(success);
        startButton->setEnabled(true);  // Re-enable the button after the timer completes
        timer->stop();  // Stop the timer
        timer->deleteLater();  // Delete the timer object
    });

    timer->start(1000);  // Start the timer

    // Note: Avoid deleting the timer here as it will not allow the timer to complete its work.
    // delete timer;
}


void MainWindow::executeClicked()
{
    QPushButton *executeButton = qobject_cast<QPushButton*>(sender());
    executeButton->setDisabled(true);
    QStringList codeLines = codeTextEdit->toPlainText().split('\n');
    int initialInterval = (codeLines.isEmpty() || codeLines.first().trimmed().isEmpty()) ? 0 : 50;//Line parsing speed

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateSimulationAllRows);

    timer->start(initialInterval);
}

void MainWindow::updateSimulationAllRows()
{
      //Controller controller;  //will be changed

      ControlBlock* cb = ControlBlock::getControlBlock();//Getting Control Block pointer
      // Check if we reached the end of the code
      QStringList codeLines = codeTextEdit->toPlainText().split('\n');


      if (currentRow >= codeLines.size()) {
          cb->removeLastScope();
          //delete cb;
          //cb = nullptr;
          timer->stop();
          execute->setDisabled(false);
          return;
      }

      bool visited = 0;
      progressBar->setMaximum(codeLines.size());
      // Update the left part (code)
      QTextCursor cursor(codeTextEdit->document());
      cursor.movePosition(QTextCursor::Start);

      for (int i = 0; i < currentRow; ++i) {
          QTextBlockFormat blockFormat;
              blockFormat.setBackground(QColor("#ffffff")); // Set the background color to #222222
              cursor.setBlockFormat(blockFormat);
              cursor.movePosition(QTextCursor::NextBlock);
      }
      QTextBlockFormat blockFormat;
      if (!cursor.block().text().trimmed().isEmpty()) {
          blockFormat.setBackground(QBrush(Qt::green));
          cursor.mergeBlockFormat(blockFormat);
          visited = 1;
          // Non-empty line, set regular timer interval
          timer->setInterval(300);
          //ramSegments[0]->addSlot("0x455", "Garbage", "number", "X bytes");


          //controller.processInput(); // will be changed
          std::string str = codeLines[currentRow].toStdString();
          //str = "int x(int arg)";
          //qDebug() << "this is line " << codeLines[currentRow] << " = " << currentRow << "\n";
          cb->processString(str, currentRow);
      } else {
          // Empty line, set a shorter timer interval or no interval at all
          timer->setInterval(0); // Set to 0 or adjust as needed
      }

      currentRow++;
      progressBar->setValue(currentRow);
      // Update the right part (RAM simulation)


      codeTextEdit->setTextCursor(cursor);
      codeTextEdit->ensureCursorVisible();
}

void MainWindow::updateSimulation(bool& success)
{
    // Check if we reached the end of the code
    QStringList codeLines = codeTextEdit->toPlainText().split('\n');
    if (currentRow >= codeLines.size()) {
        timer->stop();
        return;
    }

    // Update the left part (code)
    progressBar->setMaximum(codeLines.size());

    QTextCursor cursor(codeTextEdit->document());
    cursor.movePosition(QTextCursor::Start);
    for (int i = 0; i < currentRow; ++i) {
        cursor.movePosition(QTextCursor::NextBlock);
    }
    QTextBlockFormat blockFormat;
    blockFormat.setBackground(QBrush(Qt::green));
    cursor.mergeBlockFormat(blockFormat);
    currentRow++;
    progressBar->setValue(currentRow);

    success = true;
}

void MainWindow::resetClicked()
{

    // Reset the currentRow counter
    currentRow = 0;

    // Remove the green background from all lines
    QTextCursor cursor(codeTextEdit->document());
    cursor.movePosition(QTextCursor::Start);
    codeTextEdit->setTextCursor(cursor);
    QTextBlockFormat BlockFormat;  // Default block format (no background color)
    do {
        //qDebug() << "do";
        BlockFormat.setBackground(QBrush("#ffffff"));  // Set the background to the default color
        cursor.mergeBlockFormat(BlockFormat);
    } while (cursor.movePosition(QTextCursor::NextBlock));
    for(auto& segment : ramSegments){
        segment->setDefaultValues();
    }
    codeTextEdit->setTextColor("black");
    progressBar->setValue(0);
}

void MainWindow::stopClicked()
{
  if(timer && timer->isActive())
    {
      timer->stop();
    }
  // Enable the "Execute" button and "Reset" button
        execute->setEnabled(true);
        reset->setEnabled(true);
}

void MainWindow::chooseFileClicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Choose File", QString(), "Text Files (*.cpp);;All Files (*)");
    if(!filePath.isEmpty()){
        updateCodeText(filePath);
    }
}

void MainWindow::updateCodeText(const QString &filePath) {
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        codeTextEdit->setPlainText(in.readAll());
        file.close();
    }
}
