#ifndef MESSAGE_H
#define MESSAGE_H

#include <QWidget>
#include <QLabel>

class message : public QWidget
{
    Q_OBJECT
public:
    explicit message(QString text);

private:
    QLabel* m_icon;
    QLabel* m_text;
signals:
};

#endif // MESSAGE_H
