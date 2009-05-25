////////////////////////////////////////////////////////////////////////////////

#include "imagealgorithm.h"

#include <QRadioButton>
#include <QVBoxLayout>

#include <cassert>

////////////////////////////////////////////////////////////////////////////////


ImageAlgorithm::ImageAlgorithm( QWidget* _parent /* = NULL */ )
: ChooseAlgorithmPage(_parent)
{
    m_LSB      = new QRadioButton(tr("&LSB"));
    m_PRI      = new QRadioButton(tr("&PRI"));
    m_PRS      = new QRadioButton(tr("&PRS"));
    m_Block    = new QRadioButton(tr("&Block"));
    m_Quant    = new QRadioButton(tr("&Quant"));
    m_Cross    = new QRadioButton(tr("&Cross"));
    m_KochZhao = new QRadioButton(tr("&Koch-Zhao"));

    m_LSB->setChecked(true);
    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(m_LSB);
    layout->addWidget(m_PRI);
    layout->addWidget(m_PRS);
    layout->addWidget(m_Block);
    layout->addWidget(m_Quant);
    layout->addWidget(m_Cross);
    layout->addWidget(m_KochZhao);

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


CoderType ImageAlgorithm::GetCoderType() const
{
    if ( m_LSB->isChecked() )
        return LSB;
    else if (m_PRS->isChecked() )
        return PRS;
    else if (m_PRS->isChecked() )
        return PRI;
    else if (m_Block->isChecked() )
        return BLOCK;
    else if (m_Quant->isChecked() )
        return QUANT;
    else if (m_Block->isChecked() )
        return BLOCK;
    else if (m_Cross->isChecked() )
        return CROSS;
    else if (m_KochZhao->isChecked() )
        return KOCHZHAO;
    else
    {
        assert(0);
        return INVALID;
    }
}


////////////////////////////////////////////////////////////////////////////////
