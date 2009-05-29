#ifndef _CHOOSEALGORITHMPAGE_H_
#define _CHOOSEALGORITHMPAGE_H_

////////////////////////////////////////////////////////////////////////////////

#include <QWizardPage>

////////////////////////////////////////////////////////////////////////////////

class QRadioButton;

/** C++ class representing GUI Wizard page
*
*
*  @author  Roman Pasechnik
*  @since   May 24th, 2009
*  @updated May 24th, 2009
*
*/
class ChooseAlgorithmPage : public QWizardPage
{
////////////////////////////////////////////////////////////////////////////////
Q_OBJECT

public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
    ChooseAlgorithmPage( QWidget* _parent = NULL );


    /** Destructor */
    virtual ~ChooseAlgorithmPage();


    /** Next page handler */
    virtual int nextId() const;


    /** Does this algorithm need key? */
    virtual bool NeedsKey() const = 0;


////////////////////////////////////////////////////////////////////////////////
};

#endif
