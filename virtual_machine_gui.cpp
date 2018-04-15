#include "virtual_machine_gui.hpp"

VirtualMachineGUI::VirtualMachineGUI()
{
    regmodel_header.append("Number");
    regmodel_header.append("Alias");
    regmodel_header.append("Value (Hex)");
    
    memorymodel_header.append("Address (Hex)");
    memorymodel_header.append("Value (Hex)");
    memorymodel_header.append("");
    
    break_button->setEnabled(false);
    
    initializeGUI();
    
    connect(execute_button, SIGNAL(clicked()), this, SLOT(executeProtocol()));
}

void VirtualMachineGUI::initializeGUI()
{
    createTables();
    createStatus();
    createExecuteButton();
    
    mainview->addWidget(my_tables);
    mainview->addWidget(my_status);
    mainview->addWidget(my_controls);
    
    setLayout(mainview);
    setWindowTitle("Pleiades MIPS Simulator");
}

void VirtualMachineGUI::createTables()
{
    populateRegMemTables();
    
    the_gui_registers->setObjectName("registers");
    the_gui_memory->setObjectName("memory");
    
    the_text->setReadOnly(my_tables);
    the_text->moveCursor(QTextCursor::Start);
    
    the_gui_registers->setModel(&the_register_model);
    the_gui_memory->setModel(&the_memory_model);
    
    the_gui_registers->setColumnWidth(0, 93);
    the_gui_registers->setColumnWidth(1, 93);
    the_gui_registers->setColumnWidth(2, 93);
    
    the_gui_memory->setColumnWidth(0, 93);
    the_gui_memory->setColumnWidth(1, 93);
    the_gui_memory->setColumnWidth(2, 98);
    
    
    tablelayout->addWidget(the_gui_registers, 0, 1);
    tablelayout->addWidget(the_gui_memory, 0, 2);
    
    tablelayout->setColumnMinimumWidth(0, 400);
    tablelayout->setColumnMinimumWidth(1, 290);
    tablelayout->setColumnMinimumWidth(2, 290);
    
    my_tables->setLayout(tablelayout);
}


void VirtualMachineGUI::createStatus()
{
    status_label = new QLabel(tr("Status: "));
    
    the_status->setText(QString("Ok"));
    the_status->setReadOnly(my_status);
    
    the_status->setObjectName("status");
    
    statuslayout->addWidget(status_label, 0, 0);
    statuslayout->addWidget(the_status, 0, 1);
    
    my_status->setLayout(statuslayout);
}

void VirtualMachineGUI::createExecuteButton()
{
    controllayout->addWidget(execute_button, 0, 0);
    controllayout->addWidget(run_button, 0, 1);
    controllayout->addWidget(break_button, 0, 2);
    
    execute_button->setObjectName("step");
    run_button->setObjectName("run");
    break_button->setObjectName("break");
    
    my_controls->setLayout(controllayout);
}

void VirtualMachineGUI::populateRegMemTables()
{
    the_register_model.index(1, 1, the_register_model.index(0, 0));
    the_register_model.setHorizontalHeaderLabels(regmodel_header);
    the_gui_registers->verticalHeader()->setVisible(false);
    
    the_memory_model.index(1, 1, the_memory_model.index(0, 0));
    the_memory_model.setHorizontalHeaderLabels(memorymodel_header);
    the_gui_memory->verticalHeader()->setVisible(false);
    
    ritem00 = new QStandardItem(QString(""));
    ritem10 = new QStandardItem(QString(""));
    ritem20 = new QStandardItem(QString(""));
    ritem30 = new QStandardItem(QString("$0"));
    ritem40 = new QStandardItem(QString("$1"));
    ritem50 = new QStandardItem(QString("$2"));
    ritem60 = new QStandardItem(QString("$3"));
    ritem70 = new QStandardItem(QString("$4"));
    ritem80 = new QStandardItem(QString("$5"));
    ritem90 = new QStandardItem(QString("$6"));
    ritem100 = new QStandardItem(QString("$7"));
    ritem110 = new QStandardItem(QString("$8"));
    ritem120 = new QStandardItem(QString("$9"));
    ritem130 = new QStandardItem(QString("$10"));
    ritem140 = new QStandardItem(QString("$11"));
    ritem150 = new QStandardItem(QString("$12"));
    ritem160 = new QStandardItem(QString("$13"));
    ritem170 = new QStandardItem(QString("$14"));
    ritem180 = new QStandardItem(QString("$15"));
    ritem190 = new QStandardItem(QString("$16"));
    ritem200 = new QStandardItem(QString("$17"));
    ritem210 = new QStandardItem(QString("$18"));
    ritem220 = new QStandardItem(QString("$19"));
    ritem230 = new QStandardItem(QString("$20"));
    ritem240 = new QStandardItem(QString("$21"));
    ritem250 = new QStandardItem(QString("$22"));
    ritem260 = new QStandardItem(QString("$23"));
    ritem270 = new QStandardItem(QString("$24"));
    ritem280 = new QStandardItem(QString("$25"));
    ritem290 = new QStandardItem(QString("$26"));
    ritem300 = new QStandardItem(QString("$27"));
    ritem310 = new QStandardItem(QString("$28"));
    ritem320 = new QStandardItem(QString("$29"));
    ritem330 = new QStandardItem(QString("$30"));
    ritem340 = new QStandardItem(QString("$31"));
    
    the_register_model.setItem(0, 0, ritem00);
    the_register_model.setItem(1, 0, ritem10);
    the_register_model.setItem(2, 0, ritem20);
    the_register_model.setItem(3, 0, ritem30);
    the_register_model.setItem(4, 0, ritem40);
    the_register_model.setItem(5, 0, ritem50);
    the_register_model.setItem(6, 0, ritem60);
    the_register_model.setItem(7, 0, ritem70);
    the_register_model.setItem(8, 0, ritem80);
    the_register_model.setItem(9, 0, ritem90);
    the_register_model.setItem(10, 0, ritem100);
    the_register_model.setItem(11, 0, ritem110);
    the_register_model.setItem(12, 0, ritem120);
    the_register_model.setItem(13, 0, ritem130);
    the_register_model.setItem(14, 0, ritem140);
    the_register_model.setItem(15, 0, ritem150);
    the_register_model.setItem(16, 0, ritem160);
    the_register_model.setItem(17, 0, ritem170);
    the_register_model.setItem(18, 0, ritem180);
    the_register_model.setItem(19, 0, ritem190);
    the_register_model.setItem(20, 0, ritem200);
    the_register_model.setItem(21, 0, ritem210);
    the_register_model.setItem(22, 0, ritem220);
    the_register_model.setItem(23, 0, ritem230);
    the_register_model.setItem(24, 0, ritem240);
    the_register_model.setItem(25, 0, ritem250);
    the_register_model.setItem(26, 0, ritem260);
    the_register_model.setItem(27, 0, ritem270);
    the_register_model.setItem(28, 0, ritem280);
    the_register_model.setItem(29, 0, ritem290);
    the_register_model.setItem(30, 0, ritem300);
    the_register_model.setItem(31, 0, ritem310);
    the_register_model.setItem(32, 0, ritem320);
    the_register_model.setItem(33, 0, ritem330);
    the_register_model.setItem(34, 0, ritem340);
    
    ritem01 = new QStandardItem(QString("$pc"));
    ritem11 = new QStandardItem(QString("$hi"));
    ritem21 = new QStandardItem(QString("$lo"));
    ritem31 = new QStandardItem(QString("$zero"));
    ritem41 = new QStandardItem(QString("$at"));
    ritem51 = new QStandardItem(QString("$v0"));
    ritem61 = new QStandardItem(QString("$v1"));
    ritem71 = new QStandardItem(QString("$a0"));
    ritem81 = new QStandardItem(QString("$a1"));
    ritem91 = new QStandardItem(QString("$a2"));
    ritem101 = new QStandardItem(QString("$a3"));
    ritem111 = new QStandardItem(QString("$t0"));
    ritem121 = new QStandardItem(QString("$t1"));
    ritem131 = new QStandardItem(QString("$t2"));
    ritem141 = new QStandardItem(QString("$t3"));
    ritem151 = new QStandardItem(QString("$t4"));
    ritem161 = new QStandardItem(QString("$t5"));
    ritem171 = new QStandardItem(QString("$t6"));
    ritem181 = new QStandardItem(QString("$t7"));
    ritem191 = new QStandardItem(QString("$s0"));
    ritem201 = new QStandardItem(QString("$s1"));
    ritem211 = new QStandardItem(QString("$s2"));
    ritem221 = new QStandardItem(QString("$s3"));
    ritem231 = new QStandardItem(QString("$s4"));
    ritem241 = new QStandardItem(QString("$s5"));
    ritem251 = new QStandardItem(QString("$s6"));
    ritem261 = new QStandardItem(QString("$s6"));
    ritem271 = new QStandardItem(QString("$t8"));
    ritem281 = new QStandardItem(QString("$t9"));
    ritem291 = new QStandardItem(QString("$k0"));
    ritem301 = new QStandardItem(QString("$k1"));
    ritem311 = new QStandardItem(QString("$gp"));
    ritem321 = new QStandardItem(QString("$sp"));
    ritem331 = new QStandardItem(QString("$fp"));
    ritem341 = new QStandardItem(QString("$ra"));
    
    the_register_model.setItem(0, 1, ritem01);
    the_register_model.setItem(1, 1, ritem11);
    the_register_model.setItem(2, 1, ritem21);
    the_register_model.setItem(3, 1, ritem31);
    the_register_model.setItem(4, 1, ritem41);
    the_register_model.setItem(5, 1, ritem51);
    the_register_model.setItem(6, 1, ritem61);
    the_register_model.setItem(7, 1, ritem71);
    the_register_model.setItem(8, 1, ritem81);
    the_register_model.setItem(9, 1, ritem91);
    the_register_model.setItem(10, 1, ritem101);
    the_register_model.setItem(11, 1, ritem111);
    the_register_model.setItem(12, 1, ritem121);
    the_register_model.setItem(13, 1, ritem131);
    the_register_model.setItem(14, 1, ritem141);
    the_register_model.setItem(15, 1, ritem151);
    the_register_model.setItem(16, 1, ritem161);
    the_register_model.setItem(17, 1, ritem171);
    the_register_model.setItem(18, 1, ritem181);
    the_register_model.setItem(19, 1, ritem191);
    the_register_model.setItem(20, 1, ritem201);
    the_register_model.setItem(21, 1, ritem211);
    the_register_model.setItem(22, 1, ritem221);
    the_register_model.setItem(23, 1, ritem231);
    the_register_model.setItem(24, 1, ritem241);
    the_register_model.setItem(25, 1, ritem251);
    the_register_model.setItem(26, 1, ritem261);
    the_register_model.setItem(27, 1, ritem271);
    the_register_model.setItem(28, 1, ritem281);
    the_register_model.setItem(29, 1, ritem291);
    the_register_model.setItem(30, 1, ritem301);
    the_register_model.setItem(31, 1, ritem311);
    the_register_model.setItem(32, 1, ritem321);
    the_register_model.setItem(33, 1, ritem331);
    the_register_model.setItem(34, 1, ritem341);
    
    mitem00 = new QStandardItem(QString("0x00000000"));
    mitem10 = new QStandardItem(QString("0x00000001"));
    mitem20 = new QStandardItem(QString("0x00000002"));
    mitem30 = new QStandardItem(QString("0x00000003"));
    mitem40 = new QStandardItem(QString("0x00000004"));
    mitem50 = new QStandardItem(QString("0x00000005"));
    mitem60 = new QStandardItem(QString("0x00000006"));
    mitem70 = new QStandardItem(QString("0x00000007"));
    mitem80 = new QStandardItem(QString("0x00000008"));
    mitem90 = new QStandardItem(QString("0x00000009"));
    mitem100 = new QStandardItem(QString("0x0000000a"));
    mitem110 = new QStandardItem(QString("0x0000000b"));
    mitem120 = new QStandardItem(QString("0x0000000c"));
    mitem130 = new QStandardItem(QString("0x0000000d"));
    mitem140 = new QStandardItem(QString("0x0000000e"));
    mitem150 = new QStandardItem(QString("0x0000000f"));
    mitem160 = new QStandardItem(QString("0x00000010"));
    mitem170 = new QStandardItem(QString("0x00000011"));
    mitem180 = new QStandardItem(QString("0x00000012"));
    mitem190 = new QStandardItem(QString("0x00000013"));
    mitem200 = new QStandardItem(QString("0x00000014"));
    mitem210 = new QStandardItem(QString("0x00000015"));
    mitem220 = new QStandardItem(QString("0x00000016"));
    mitem230 = new QStandardItem(QString("0x00000017"));
    mitem240 = new QStandardItem(QString("0x00000018"));
    mitem250 = new QStandardItem(QString("0x00000019"));
    mitem260 = new QStandardItem(QString("0x0000001a"));
    mitem270 = new QStandardItem(QString("0x0000001b"));
    mitem280 = new QStandardItem(QString("0x0000001c"));
    mitem290 = new QStandardItem(QString("0x0000001d"));
    mitem300 = new QStandardItem(QString("0x0000001e"));
    mitem310 = new QStandardItem(QString("0x00000020"));
    mitem320 = new QStandardItem(QString("0x00000021"));
    mitem330 = new QStandardItem(QString("0x00000022"));
    mitem340 = new QStandardItem(QString("0x00000023"));
    
    the_memory_model.setItem(0, 0, mitem00);
    the_memory_model.setItem(1, 0, mitem10);
    the_memory_model.setItem(2, 0, mitem20);
    the_memory_model.setItem(3, 0, mitem30);
    the_memory_model.setItem(4, 0, mitem40);
    the_memory_model.setItem(5, 0, mitem50);
    the_memory_model.setItem(6, 0, mitem60);
    the_memory_model.setItem(7, 0, mitem70);
    the_memory_model.setItem(8, 0, mitem80);
    the_memory_model.setItem(9, 0, mitem90);
    the_memory_model.setItem(10, 0, mitem100);
    the_memory_model.setItem(11, 0, mitem110);
    the_memory_model.setItem(12, 0, mitem120);
    the_memory_model.setItem(13, 0, mitem130);
    the_memory_model.setItem(14, 0, mitem140);
    the_memory_model.setItem(15, 0, mitem150);
    the_memory_model.setItem(16, 0, mitem160);
    the_memory_model.setItem(17, 0, mitem170);
    the_memory_model.setItem(18, 0, mitem180);
    the_memory_model.setItem(19, 0, mitem190);
    the_memory_model.setItem(20, 0, mitem200);
    the_memory_model.setItem(21, 0, mitem210);
    the_memory_model.setItem(22, 0, mitem220);
    the_memory_model.setItem(23, 0, mitem230);
    the_memory_model.setItem(24, 0, mitem240);
    the_memory_model.setItem(25, 0, mitem250);
    the_memory_model.setItem(26, 0, mitem260);
    the_memory_model.setItem(27, 0, mitem270);
    the_memory_model.setItem(28, 0, mitem280);
    the_memory_model.setItem(29, 0, mitem290);
    the_memory_model.setItem(30, 0, mitem300);
    the_memory_model.setItem(31, 0, mitem310);
    the_memory_model.setItem(32, 0, mitem320);
    the_memory_model.setItem(33, 0, mitem330);
    the_memory_model.setItem(34, 0, mitem340);
    
    
    stringstream pc;
    pc << "0x" << hex << setfill('0') << setw(8) << the_registers.at("$pc") << endl;
    the_register_model.setItem(0, 2, new QStandardItem(QString(QString::fromStdString(pc.str()))));
    pc.str().clear();
    pc.clear();
    
    stringstream hi;
    hi << "0x" << hex << setfill('0') << setw(8) << the_registers.at("$hi") << endl;
    the_register_model.setItem(1, 2, new QStandardItem(QString(QString::fromStdString(hi.str()))));
    hi.str().clear();
    hi.clear();
    
    stringstream lo;
    lo << "0x" << hex << setfill('0') << setw(8) << the_registers.at("$hi") << endl;
    the_register_model.setItem(2, 2, new QStandardItem(QString(QString::fromStdString(lo.str()))));
    lo.str().clear();
    lo.clear();
    
    for (int i = 0; i < 32; i++)
    {
        stringstream ss;
        string the_reg = numberToRegister("$" + to_string(i));
        ss << "0x" << hex << setfill('0') << setw(8) << the_registers.at(the_reg) << endl;
        the_register_model.setItem(i + 3, 2, new QStandardItem(QString(QString::fromStdString(ss.str()))));
        ss.str().clear();
        ss.clear();
    }
    
    for (unsigned int i = 0; i < 512; i++)
    {
        stringstream ss;
        
        if (i >= the_memory.size() - 1)
        {
            the_memory_model.setItem(i, 1, new QStandardItem(QString("0x00")));
            ss << "0x" << hex << setfill('0') << setw(8) << stol(to_string(i), 0, 10);
            the_memory_model.setItem(i, 0, new QStandardItem(QString(QString::fromStdString(ss.str()))));
        }
        else if (the_memory.size() == 0)
        {
            the_memory_model.setItem(i, 1, new QStandardItem(QString("0x00")));
            ss << "0x" << hex << setfill('0') << setw(8) << stol(to_string(i), 0, 10);
            the_memory_model.setItem(i, 0, new QStandardItem(QString(QString::fromStdString(ss.str()))));
        }
        else
        {
            ss << "0x" << hex << setfill('0') << setw(2) << the_memory.back().storedINFO[i] << endl;
            the_memory_model.setItem(i, 1, new QStandardItem(QString(QString::fromStdString(ss.str()))));
            ss.str().clear();
            ss.clear();
        }
    }
}

void VirtualMachineGUI::load (QString the_filename)
{
    ifstream strings(the_filename.toStdString(), ios::binary);
    TokenList gui_tokens = tokenize(strings);
    gui_parse = parse(gui_tokens);
    
    initializeGUI();
    
    QFile the_file(the_filename);
    the_file.open(QFile::ReadOnly|QFile::Text);
    
    the_text->insertPlainText(the_file.readAll());
    tablelayout->addWidget(the_text, 0, 0);
    
    the_text->setObjectName("text");
    
    the_file.close();
}

void VirtualMachineGUI::executeProtocol()
{
    executeProgram();
    initializeGUI();
}

