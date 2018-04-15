#ifndef VIRTUAL_MACHINE_GUI_HPP
#define VIRTUAL_MACHINE_GUI_HPP

#include <QString>
#include <QWidget>
#include <QHeaderView>
#include <QGroupBox>
#include <QLayout>
#include <QLabel>
#include <QStandardItemModel>
#include <QPlainTextEdit>
#include <QTextStream>
#include <QTableView>
#include <QStringList>
#include <QLineEdit>
#include <fstream>
#include <QPushButton>

#include "lexer.hpp"
#include "module.hpp"
#include "test_config.hpp"

using namespace std;

class VirtualMachineGUI: public QWidget, public VirtualMachine
{
    Q_OBJECT
public:
    VirtualMachineGUI();
    void initializeGUI();
    void populateRegMemTables();
    void load (QString the_filename);
    
    public slots:
    void executeProtocol();
    
protected:
    void createTables();
    void createStatus();
    void createExecuteButton();
    
private:
    bool gui_parse;
    
    QGroupBox* my_controls = new QGroupBox;
    QGroupBox* my_status = new QGroupBox;
    QGroupBox* my_tables = new QGroupBox;
    
    QPlainTextEdit* the_text = new QPlainTextEdit;
    QTableView* the_gui_registers= new QTableView;
    QTableView* the_gui_memory= new QTableView;
    QPushButton* execute_button = new QPushButton(tr("Step"));
    QPushButton* run_button = new QPushButton(tr("Run"));
    QPushButton* break_button = new QPushButton(tr("Break"));
    QLineEdit* the_status = new QLineEdit;
    
    QGridLayout *tablelayout = new QGridLayout;
    
    QStandardItemModel the_register_model;
    QStandardItemModel the_memory_model;
    
    QStringList regmodel_header;
    QStringList memorymodel_header;
    
    QLabel* status_label;
    
    QVBoxLayout *mainview = new QVBoxLayout;
    QGridLayout *statuslayout = new QGridLayout;
    QGridLayout *controllayout = new QGridLayout;
    
    QStandardItem* ritem00;
    QStandardItem* ritem10;
    QStandardItem* ritem20;
    QStandardItem* ritem30;
    QStandardItem* ritem40;
    QStandardItem* ritem50;
    QStandardItem* ritem60;
    QStandardItem* ritem70;
    QStandardItem* ritem80;
    QStandardItem* ritem90;
    QStandardItem* ritem100;
    QStandardItem* ritem110;
    QStandardItem* ritem120;
    QStandardItem* ritem130;
    QStandardItem* ritem140;
    QStandardItem* ritem150;
    QStandardItem* ritem160;
    QStandardItem* ritem170;
    QStandardItem* ritem180;
    QStandardItem* ritem190;
    QStandardItem* ritem200;
    QStandardItem* ritem210;
    QStandardItem* ritem220;
    QStandardItem* ritem230;
    QStandardItem* ritem240;
    QStandardItem* ritem250;
    QStandardItem* ritem260;
    QStandardItem* ritem270;
    QStandardItem* ritem280;
    QStandardItem* ritem290;
    QStandardItem* ritem300;
    QStandardItem* ritem310;
    QStandardItem* ritem320;
    QStandardItem* ritem330;
    QStandardItem* ritem340;
    
    QStandardItem* ritem01;
    QStandardItem* ritem11;
    QStandardItem* ritem21;
    QStandardItem* ritem31;
    QStandardItem* ritem41;
    QStandardItem* ritem51;
    QStandardItem* ritem61;
    QStandardItem* ritem71;
    QStandardItem* ritem81;
    QStandardItem* ritem91;
    QStandardItem* ritem101;
    QStandardItem* ritem111;
    QStandardItem* ritem121;
    QStandardItem* ritem131;
    QStandardItem* ritem141;
    QStandardItem* ritem151;
    QStandardItem* ritem161;
    QStandardItem* ritem171;
    QStandardItem* ritem181;
    QStandardItem* ritem191;
    QStandardItem* ritem201;
    QStandardItem* ritem211;
    QStandardItem* ritem221;
    QStandardItem* ritem231;
    QStandardItem* ritem241;
    QStandardItem* ritem251;
    QStandardItem* ritem261;
    QStandardItem* ritem271;
    QStandardItem* ritem281;
    QStandardItem* ritem291;
    QStandardItem* ritem301;
    QStandardItem* ritem311;
    QStandardItem* ritem321;
    QStandardItem* ritem331;
    QStandardItem* ritem341;
    
    QStandardItem* ritem02;
    QStandardItem* ritem12;
    QStandardItem* ritem22;
    QStandardItem* ritem32;
    QStandardItem* ritem42;
    QStandardItem* ritem52;
    QStandardItem* ritem62;
    QStandardItem* ritem72;
    QStandardItem* ritem82;
    QStandardItem* ritem92;
    QStandardItem* ritem102;
    QStandardItem* ritem112;
    QStandardItem* ritem122;
    QStandardItem* ritem132;
    QStandardItem* ritem142;
    QStandardItem* ritem152;
    QStandardItem* ritem162;
    QStandardItem* ritem172;
    QStandardItem* ritem182;
    QStandardItem* ritem192;
    QStandardItem* ritem202;
    QStandardItem* ritem212;
    QStandardItem* ritem222;
    QStandardItem* ritem232;
    QStandardItem* ritem242;
    QStandardItem* ritem252;
    QStandardItem* ritem262;
    QStandardItem* ritem272;
    QStandardItem* ritem282;
    QStandardItem* ritem292;
    QStandardItem* ritem302;
    QStandardItem* ritem312;
    QStandardItem* ritem322;
    QStandardItem* ritem332;
    QStandardItem* ritem342;
    
    QStandardItem* mitem00;
    QStandardItem* mitem10;
    QStandardItem* mitem20;
    QStandardItem* mitem30;
    QStandardItem* mitem40;
    QStandardItem* mitem50;
    QStandardItem* mitem60;
    QStandardItem* mitem70;
    QStandardItem* mitem80;
    QStandardItem* mitem90;
    QStandardItem* mitem100;
    QStandardItem* mitem110;
    QStandardItem* mitem120;
    QStandardItem* mitem130;
    QStandardItem* mitem140;
    QStandardItem* mitem150;
    QStandardItem* mitem160;
    QStandardItem* mitem170;
    QStandardItem* mitem180;
    QStandardItem* mitem190;
    QStandardItem* mitem200;
    QStandardItem* mitem210;
    QStandardItem* mitem220;
    QStandardItem* mitem230;
    QStandardItem* mitem240;
    QStandardItem* mitem250;
    QStandardItem* mitem260;
    QStandardItem* mitem270;
    QStandardItem* mitem280;
    QStandardItem* mitem290;
    QStandardItem* mitem300;
    QStandardItem* mitem310;
    QStandardItem* mitem320;
    QStandardItem* mitem330;
    QStandardItem* mitem340;
    
    QStandardItem* mitem01;
    QStandardItem* mitem11;
    QStandardItem* mitem21;
    QStandardItem* mitem31;
    QStandardItem* mitem41;
    QStandardItem* mitem51;
    QStandardItem* mitem61;
    QStandardItem* mitem71;
    QStandardItem* mitem81;
    QStandardItem* mitem91;
    QStandardItem* mitem101;
    QStandardItem* mitem111;
    QStandardItem* mitem121;
    QStandardItem* mitem131;
    QStandardItem* mitem141;
    QStandardItem* mitem151;
    QStandardItem* mitem161;
    QStandardItem* mitem171;
    QStandardItem* mitem181;
    QStandardItem* mitem191;
    QStandardItem* mitem201;
    QStandardItem* mitem211;
    QStandardItem* mitem221;
    QStandardItem* mitem231;
    QStandardItem* mitem241;
    QStandardItem* mitem251;
    QStandardItem* mitem261;
    QStandardItem* mitem271;
    QStandardItem* mitem281;
    QStandardItem* mitem291;
    QStandardItem* mitem301;
    QStandardItem* mitem311;
    QStandardItem* mitem321;
    QStandardItem* mitem331;
    QStandardItem* mitem341;
    
    QStandardItem* mitem02;
    QStandardItem* mitem12;
    QStandardItem* mitem22;
    QStandardItem* mitem32;
    QStandardItem* mitem42;
    QStandardItem* mitem52;
    QStandardItem* mitem62;
    QStandardItem* mitem72;
    QStandardItem* mitem82;
    QStandardItem* mitem92;
    QStandardItem* mitem102;
    QStandardItem* mitem112;
    QStandardItem* mitem122;
    QStandardItem* mitem132;
    QStandardItem* mitem142;
    QStandardItem* mitem152;
    QStandardItem* mitem162;
    QStandardItem* mitem172;
    QStandardItem* mitem182;
    QStandardItem* mitem192;
    QStandardItem* mitem202;
    QStandardItem* mitem212;
    QStandardItem* mitem222;
    QStandardItem* mitem232;
    QStandardItem* mitem242;
    QStandardItem* mitem252;
    QStandardItem* mitem262;
    QStandardItem* mitem272;
    QStandardItem* mitem282;
    QStandardItem* mitem292;
    QStandardItem* mitem302;
    QStandardItem* mitem312;
    QStandardItem* mitem322;
    QStandardItem* mitem332;
    QStandardItem* mitem342;
};


#endif

