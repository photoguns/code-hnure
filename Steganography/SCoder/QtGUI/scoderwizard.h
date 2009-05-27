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
        SAVE_CONTAINER_PAGE,
        HIDE_PAGE
    };


    /** Constructor */
    SCoderWizard( QWidget* _parent = NULL );


    /** Destructor */
    virtual ~SCoderWizard();


    /** Hides message into container or gets it from one */
    void Process();


////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////


    /** Tells type of container */
    ContainerType GetContainerType() const;


    /** Tells type of coder */
    CoderType GetCoderType() const;


    /** Hide or get message? */
    bool IsHideMessageMode() const;


    /** Gets name of file that has to be opened */
    std::string GetOpenFileName() const;


    /** Gets name of file that has to be closed */
    std::string GetSaveFileName() const;


    /** Gets text that has to be hidden from enter text page */
    std::string GetText() const;


    /** Sets text that has been revealed on view text page */
    void SetText( std::string _text );


    /** Gets text that is used as a key */
    std::string GetKeyText() const;


////////////////////////////////////////////////////////////////////////////////
};

#endif
