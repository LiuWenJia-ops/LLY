class MainWindow : public QMainWindow  
{  
    Q_OBJECT  
    
public:  
    MainWindow(QWidget * parent = 0);  
    ~MainWindow();  
  
private:  
    void openFile();
    bool loadFile(const QString &fileName);
      
    QAction * openAction;  
    QTextEdit * textEdit;  
};  


//联系openfile返回的body 
void readFromBody(temText body)//Q:是否需要返回文件存在但为空 
{
    //标题
    setWindowTitle(filename);//Q：该操作应该由openfile完成？或请传递参数给我 
    //+考虑写入行号numberbar
    
    //按照无block版写
    if((!body.firstline.chs)&&(!body.firstline->next))
        return;   
        
    out << (body.firstline.chs) << endl;
    linehead *p=body.firstLine->next;
    while(p!=body.firstLine){
        out << (p.chs) << endl;//QTextStream中重载<< 
        p = p->next;
    }
    
    return;
}

//Q：前几日和wj讨论后认为打开文件可直接读出？ 
void Mainwindow::openFile()
{
    //单窗口 考虑加判断现在的文件是否需要保存
    QString fileName = QFileDialog::getOpenFileName(this);
    if(!fileName.isEmpty())     //文件名不为空
    {
        loadFile(fileName);     //载入文件
    }
    //ui->textEdit->setVisible(true);
}
bool Mainwindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,tr("打开文件"),tr("无法打开文件%1:\n%2").arg(fileName).arg(file.errorString()),
                                QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return false;
    } 
    
    QTextStream in(&file); // 新建文本流对象
    //QApplication::setOverrideCursor(Qt::WaitCursor);
    // 读取文件的全部文本内容，并添加到编辑器中
    ui->textEdit->setPlainText(in.readAll());      
    //QApplication::restoreOverrideCursor();

    // 设置当前文件
    curFile = QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(curFile);
    return true;
}
