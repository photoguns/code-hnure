////////////////////////////////////////////////////////////////////////////////

#include "imagealgorithm.h"

#include <QRadioButton>
#include <QVBoxLayout>

////////////////////////////////////////////////////////////////////////////////


ImageAlgorithm::ImageAlgorithm( QWidget* _parent /* = NULL */ )
: ChooseAlgorithmPage(_parent)
{
    m_LSB   = new QRadioButton(tr("&LSB"));
    m_PRI   = new QRadioButton(tr("&PRI"));
    m_PRS   = new QRadioButton(tr("&PRS"));
    m_Block = new QRadioButton(tr("&Block"));
    m_Quant = new QRadioButton(tr("&Quant"));
    m_Cross = new QRadioButton(tr("&Cross"));

    m_LSB->setChecked(true);
    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(m_LSB);
    layout->addWidget(m_PRI);
    layout->addWidget(m_PRS);
    layout->addWidget(m_Block);
    layout->addWidget(m_Quant);
    layout->addWidget(m_Cross);

    setLayout(layout);
}


////////////////////////////////////////////////////////////////////////////////


ImageAlgorithm::~ImageAlgorithm()
{
}


////////////////////////////////////////////////////////////////////////////////


bool ImageAlgorithm::NeedsKey() const
{
    return !m_LSB->isChecked()   &&
           !m_Cross->isChecked();
}

////////////////////////////////////////////////////////////////////////////////
