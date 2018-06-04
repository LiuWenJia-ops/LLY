#ifndef FINDWINDOW_H
#define FINDWINDOW_H

#include <QDebug>

#include <QMainWindow>
#include <QWidget>
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
    FindWindow(QWidget *parent=0);
    FindWindow(QWidget *parent,myTextEdit * textTBFptr);
    ~FindWindow();
private slots:
    void showFindText(void);
    void modeChanged(int);
    void renewSearchResult(void);
private:
    QLineEdit *findLineEdit;
    int mode;
    searchResult * resultPtr;
    myTextEdit * textTBFptr;
    int nowResult;
    bool hasResult;
    //-----指回父窗口的指针们---
    MainWindow * mwPtr;
    QTextEdit * mwTextEditPtr;//指向父窗口private成员textedit
    QTextCursor temCursor;
    //-----暂时存搜索结果----
    int nowWhere[3];
    int number;
};

#endif // FINDWINDOW_H
