#ifndef REPLACEWINDOW_H
#define REPLACEWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QDialog>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QTextEdit>
#include <QTextCursor>
#include <QTextBlock>
#include <QLabel>

#include "back.h"
class ReplaceWindow;
class MainWindow;
class ReplaceWindow :public QDialog
{
    Q_OBJECT
public:
    ReplaceWindow(QWidget *parent,myTextEdit * textTBFptr);
     ~ReplaceWindow();

private slots:
    void showFindText(void);
    void modeChanged(int);
    void renewSearchResult(void);
private:
    void flush();
    void correctEditCursor(int *);
    int getAbsadd(int ,int);
    //-------------用来刷新父窗口坐标的------
    QLineEdit *findLineEdit;
    QLineEdit *replaceLineEdit;
    int mode;
    myTextEdit * textTBFptr;
    //-----指回父窗口的指针们---
    MainWindow * mwPtr;
    QTextEdit * mwTextEditPtr;//指向父窗口private成员textedit
    QTextCursor temCursor;
    //-----暂时存搜索结果----
    searchResult * resultPtr;
    int nowWhere[3];
    int number;
    int nowResult;
    bool hasResult;
    std::string str;//转换string的中间量
};

#endif // REPLACEWINDOW_H
