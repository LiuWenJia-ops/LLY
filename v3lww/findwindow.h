#ifndef FINDWINDOW_H
#define FINDWINDOW_H

#include <QDebug>

#include <QWidget>
#include <QLineEdit>
#include <QDialog>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>

#include <QTextEdit>
#include <QTextCursor>
#include <QTextBlock>
#include <QLabel>

#include "back.h"

class FindWindow;

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
private:
    QLineEdit *findLineEdit;
    //QDialog *findDlg;
    int mode;
    searchResult * resultPtr;
    myTextEdit * textTBFptr;
};

#endif // FINDWINDOW_H
