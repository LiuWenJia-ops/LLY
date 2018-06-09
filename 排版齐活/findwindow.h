#ifndef FINDWINDOW_H
#define FINDWINDOW_H

#include <QDebug>

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

class FindWindow;
class MainWindow;

class FindWindow :public QDialog
{
    Q_OBJECT
public:
    FindWindow(QWidget *parent,myTextEdit * textTBFptr);
    ~FindWindow();
private slots:
    void showFindText(void);
    void modeChanged(int);
    void renewSearchResult(void);
private:
    QLineEdit *findLineEdit;
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
};

#endif // FINDWINDOW_H
