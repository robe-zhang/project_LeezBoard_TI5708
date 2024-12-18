#ifndef QKEYBOARDLINEEDIT_H
#define QKEYBOARDLINEEDIT_H

#include <qglobal.h>
#include <QLineEdit>

#if QT_VERSION >= 0x050000

#include <QApplication>

#endif

class Keyboard;

class QKeyboardLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit QKeyboardLineEdit(QWidget *parent = 0);
    virtual ~QKeyboardLineEdit();
    
signals:
    
public slots:
    void mousePressEvent(QMouseEvent *);
    void keyboardClosed();


private:
    Keyboard* m_keyboardWidget;
    bool m_isBeingEdited;

    
};

#endif // QKEYBOARDLINEEDIT_H
