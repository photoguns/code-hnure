#ifndef _SAVECONTAINERPAGE_H_
#define _SAVECONTAINERPAGE_H_

////////////////////////////////////////////////////////////////////////////////

#include <QWizardPage>

////////////////////////////////////////////////////////////////////////////////

class QPushButton;
class QLineEdit;

/** C++ class representing GUI Wizard page
*
*
*  @author  Roman Pasechnik
*  @since   May 24th, 2009
*  @updated May 24th, 2009
*
*/
class SaveContainerPage : public QWizardPage
{
////////////////////////////////////////////////////////////////////////////////

    Q_OBJECT

////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
    SaveContainerPage( QWidget* _parent = NULL );


    /** Destructor */
    virtual ~SaveContainerPage();


    /** Hide message and save container to file */
    virtual bool validatePage();


    /** Next page */
    virtual int nextId() const;


////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////


    /** Open container button */
    QPushButton* m_Save;


    /** Path for saving file */
    QLineEdit* m_Path;


////////////////////////////////////////////////////////////////////////////////

private slots:

////////////////////////////////////////////////////////////////////////////////


    /** Save File slot */
    void SaveFile();

////////////////////////////////////////////////////////////////////////////////
};

#endif