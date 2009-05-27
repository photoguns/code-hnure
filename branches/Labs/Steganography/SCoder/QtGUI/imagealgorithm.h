#ifndef _IMAGEALGORITHM_H_
#define _IMAGEALGORITHM_H_

////////////////////////////////////////////////////////////////////////////////

#include "choosealgorithmpage.h"
#include "scoder.h"

////////////////////////////////////////////////////////////////////////////////


/** C++ class representing GUI Wizard page
*
*
*  @author  Roman Pasechnik
*  @since   May 25th, 2009
*  @updated May 25th, 2009
*
*/
class ImageAlgorithm : public ChooseAlgorithmPage 
{
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
    ImageAlgorithm( QWidget* _parent = NULL );


    /** Destructor */
    virtual ~ImageAlgorithm();


    /** Does this algorithm need key? */
    virtual bool NeedsKey() const;


    /** Next */
    virtual bool validatePage();


////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////


    /** Algorithms */

    /** Image container */
    QRadioButton* m_LSB;
    QRadioButton* m_PRI;
    QRadioButton* m_PRS;
    QRadioButton* m_Block;
    QRadioButton* m_Quant;
    QRadioButton* m_Cross;
    QRadioButton* m_KochZhao;


////////////////////////////////////////////////////////////////////////////////
};

#endif
