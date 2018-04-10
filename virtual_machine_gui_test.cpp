#include <QTest>
#include <QPlainTextEdit>
#include <fstream>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>

#include "virtual_machine_gui.hpp"

#include "test_config.hpp"

using namespace std;

class VirtualMachineGUITest : public QObject {
    Q_OBJECT
    
    private slots:
    
    void initTestCase();
    void testStep();
    
private:
    
    VirtualMachineGUI widget;
    VirtualMachineGUI widget2;
};

// this section just verifies the object names and API
void VirtualMachineGUITest::initTestCase()
{
    widget.load(QString::fromStdString(TEST_FILE_DIR + "/vm/test00.asm"));
    
    auto textWidget = widget.findChild<QPlainTextEdit *>("text");
    QVERIFY2(textWidget, "Could not find QPlainText widget");
    
    auto registerViewWidget = widget.findChild<QTableView *>("registers");
    QVERIFY2(registerViewWidget, "Could not find QTableView widget for registers");
    
    auto memoryViewWidget = widget.findChild<QTableView *>("memory");
    QVERIFY2(memoryViewWidget, "Could not find QTableView widget for memory");
    
    auto statusViewWidget = widget.findChild<QLineEdit *>("status");
    QVERIFY2(statusViewWidget, "Could not find QLineEdit widget for status");
    
    auto stepButtonWidget = widget.findChild<QPushButton *>("step");
    QVERIFY2(stepButtonWidget, "Could not find QTableView widget for memory");
}

void VirtualMachineGUITest::testStep()
{
    widget2.load(QString::fromStdString(TEST_FILE_DIR + "/vm/test10.asm"));
    
    QApplication::setActiveWindow(&widget2);
    
    auto stepButtonWidget2 = widget2.findChild<QPushButton *>("step");
    
    auto statusViewWidget2 = widget2.findChild<QLineEdit *>("status");
    
    QTest::mouseClick(stepButtonWidget2, Qt::MouseButton::LeftButton);
    
    QCOMPARE(statusViewWidget2->text(), QString("Ok"));
}


QTEST_MAIN(VirtualMachineGUITest)
#include "virtual_machine_gui_test.moc"

