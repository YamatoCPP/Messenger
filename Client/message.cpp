#include "message.h"

#include <QHBoxLayout>

message::message(QString text)
    : m_text(new QLabel(text))
    , m_icon(new QLabel())
{
    m_text->setMaximumWidth(1000);
    m_text->setStyleSheet("QLabel{"
                          "background-color : white;"
                          "border-radius : 20px; }");
    m_text->adjustSize();
    m_text->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_text->setWordWrap(true);
    m_text->setContentsMargins(10,5,10,0);

    m_icon->setFixedSize(50, 50);
    m_icon->setStyleSheet("QLabel{"
                          "background-color : white;"
                          "border-radius : 25px; }");


    QHBoxLayout* baseLayout = new QHBoxLayout();
    baseLayout->addWidget(m_icon);
    baseLayout->addWidget(m_text);
    baseLayout->setAlignment(m_icon, Qt::AlignTop);

    this->setLayout(baseLayout);
    this->setMaximumWidth(1100);
}
