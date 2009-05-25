#ifndef _SCODERWIZARD_H_
#define _SCODERWIZARD_H_
#include "scoder.h"

////////////////////////////////////////////////////////////////////////////////

#include <QWizard>
#include <string>

////////////////////////////////////////////////////////////////////////////////


/** C++ class for GUI Wizard
*
*
*  @author  Roman Pasechnik
*  @since   May 24th, 2009
*  @updated May 24th, 2009
*
*/
class SCoderWizard : public QWizard
{
////////////////////////////////////////////////////////////////////////////////

    Q_OBJECT

////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Wizard pages */
    enum
    {
        INTRO_PAGE,
        OPEN_CONTAINER_PAGE,
        ENTER_TEXT_PAGE,
        VIEW_TEXT_PAGE,
        IMAGE_ALGORITHM,
        SOUND_ALGORITHM,
        ENTER_KEY_PAGE,
        SAVE_CONTAINER_PAGE
    };


    /** Constructor */
    SCoderWizard( QWidget* _parent = NULL );


    /** Destructor */
    virtual ~SCoderWizard();


    /** Tells type of container */
    ContainerType GetContainerType() const;


    /** Hide or get message? */
    bool IsHideMessageMode() const;


    /** */
    std::string GetOpenFileName() const;
    std::string GetSaveFileName() const;

    /** */
    std::string GetText() const;
    void SetText( std::string _text );


    /** */
    std::string GetKey() const;


    /** */
    CoderType GetCoderType() const;


    /** Hide message into container */
    void Process();


////////////////////////////////////////////////////////////////////////////////
};

#endif
