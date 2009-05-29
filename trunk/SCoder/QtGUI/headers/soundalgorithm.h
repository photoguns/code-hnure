#ifndef _SOUNDALGORITHM_H_
#define _SOUNDALGORITHM_H_

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
class SoundAlgorithm : public ChooseAlgorithmPage 
{
////////////////////////////////////////////////////////////////////////////////
Q_OBJECT
public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
    SoundAlgorithm( QWidget* _parent = NULL );


    /** Destructor */
    virtual ~SoundAlgorithm();


    /** Does this algorithm need key? */
    virtual bool NeedsKey() const;


    /** Next */
    virtual bool validatePage();


////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////


    /** Sound container */
    QRadioButton* m_LSBSound;
    QRadioButton* m_Echo;


////////////////////////////////////////////////////////////////////////////////
};

#endif
