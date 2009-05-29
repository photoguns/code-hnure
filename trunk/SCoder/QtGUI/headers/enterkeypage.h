#ifndef _ENTERKEYPAGE_H_
#define _ENTERKEYPAGE_H_

////////////////////////////////////////////////////////////////////////////////

#include <QWizardPage>

////////////////////////////////////////////////////////////////////////////////

class QLineEdit;

/** C++ class representing GUI Wizard page
*
*
*  @author  Roman Pasechnik
*  @since   May 24th, 2009
*  @updated May 24th, 2009
*
*/
class EnterKeyPage : public QWizardPage
{
////////////////////////////////////////////////////////////////////////////////
Q_OBJECT
public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
    EnterKeyPage( QWidget* _parent = NULL );


    /** Destructor */
    virtual ~EnterKeyPage();


    /** Next page handler */
    virtual int nextId() const;


////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////


    /** Line edit */
    QLineEdit* m_Key;


////////////////////////////////////////////////////////////////////////////////
};

#endif
