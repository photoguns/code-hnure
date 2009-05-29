////////////////////////////////////////////////////////////////////////////////

#include "scoderwizard.h"

////////////////////////////////////////////////////////////////////////////////

#include "intropage.h"
#include "opencontainerpage.h"
#include "entertextpage.h"
#include "viewtextpage.h"
#include "imagealgorithm.h"
#include "soundalgorithm.h"
#include "enterkeypage.h"
#include "savecontainerpage.h"
#include "hidepage.h"

#include <QVariant>
#include <cassert>
#include <QMessageBox>

////////////////////////////////////////////////////////////////////////////////


SCoderWizard::SCoderWizard( QWidget* _parent /* = NULL */ )
: QWizard(_parent)
{
    // Set Wizard window title
    setWindowTitle(tr("SCoder"));

    // Yo yo yo check this out
    setWizardStyle(ClassicStyle);

    // Add pages
    setPage(INTRO_PAGE,          new IntroPage);
    setPage(OPEN_CONTAINER_PAGE, new OpenContainerPage);
    setPage(ENTER_TEXT_PAGE,     new EnterTextPage);
    setPage(IMAGE_ALGORITHM,     new ImageAlgorithm);
    setPage(SOUND_ALGORITHM,     new SoundAlgorithm);
    setPage(ENTER_KEY_PAGE,      new EnterKeyPage);
    setPage(SAVE_CONTAINER_PAGE, new SaveContainerPage);
    setPage(VIEW_TEXT_PAGE,      new ViewTextPage);
    setPage(HIDE_PAGE,           new HidePage);

    // Set start page
    setStartId(INTRO_PAGE);

    setOption(HaveHelpButton, true);
    connect(this, SIGNAL(helpRequested()), this, SLOT(ShowHelp()));
}


////////////////////////////////////////////////////////////////////////////////


SCoderWizard::~SCoderWizard()
{
}


////////////////////////////////////////////////////////////////////////////////


void SCoderWizard::ShowHelp()
{
    QString message;

    const QString introHelp = tr("If you want to inject some text into picture"
        " or sound - check \"Hide Message\" radio button. If you want to get"
        " text, which has already been injected into container - check"
        " \"Get Message\" radio button");

    const QString openHelp = tr("Make sure to open a valid email container,"
        " such as BMP image or WAV sound.");

    const QString saveHelp = tr("Make sure not to save container into the same"
        " file you have opened.");

    const QString LSBHelp = tr("Least Significant Bit algorithm simply"
        " changes least significant bits of pixels (3 in each -- in red, green"
        " and blue byte. It does not need a key and has a very simple realization,"
        " but can be broken by compressing picture, or resetting all LSB's"
        " in the picture.");
    
    const QString PRIHelp = tr("Pseudo-random interval algorithm also changes"
        " LSB's. The difference is that PRI processes not all pixels. Every time"
        " it hides the bit it skips random number of pixels. Those random numbers"
        " are secret information, generated from user provided key.");

    const QString PRSHelp = tr("Pseudo-random substitution algorithm is a"
        " modification of LSB algorithm. Before hiding text is multiplied on"
        " substitution matrix, so that LSB sequence has almost random properties"
        " after this operation. This makes it harder to detect the presence of"
        " text in container. Substitution matrix is a secret key.");

    const QString BlockHelp = tr("Block algorithm splits picture on random"
        " blocks. Only one bit can be injected into a block. All LSB's of one"
        " block are added together modulo 2. If result differs from bit that is"
        " being hidden - the value of some pixel's LSB in this block has to be"
        " inverted. The secret key determines how to break picture on blocks.");

    const QString QuantHelp = tr("Quantization algorithm finds difference between"
        " brightnesses of two neighbour pixels. There is a map, that associates"
        " a bit (0 or 1) to all possible values of differences. If accociated"
        " value does not match the bit being hidden - pixels' brightnesses are"
        " modified until difference between them will be accociated with desired"
        " value of a bit. Accociation map is a secret key.");

    const QString CrossHelp = tr("Cross algorithm calculates the arithmetic mean"
        " of neighbour pixels' brightness in a small radius, then it increases"
        " or decreases it a little, depending the bit is being hidden (0 or 1)."
        " After all this value is written to center pixel.");

    const QString KochZhaoHelp = tr("Koch-Zhao algorithm is a pretty fucking good"
        " thing. I guarantee it!.");

    const QString LSBSoundHelp = tr("Least Significant Bit algorithm simply changes"
        " least significant bits of samples. It does not need a key and has a very"
        " simple realization, but can be broken by compressing sound, or resetting"
        " all LSB's in the sound file.");

    const QString EchoHelp = tr("Echo algorithm adds random echos to sound signal."
        " Depending on bit being hidden echos are added after different ammounts"
        " of time. Human ears are not able to hear those echos.");

    const QString enterKeyHelp = tr("Enter key, please.");

    const QString enterTextHelp = tr("Enter text, please.");

    const QString viewTextHelp = tr("ZAPILI TEXT OBRATNO! ZAPILI!!!");

    const QString hideHelp = tr("Press 'Hide' button, you can do it!");

    const QString failHelp = tr("This help is likely not to be of any help.");

    


    switch ( currentId() )
    {
    case INTRO_PAGE:
         message = introHelp;
         break;
     case OPEN_CONTAINER_PAGE:
         message = openHelp;
         break;
     case SAVE_CONTAINER_PAGE:
         message = saveHelp;
         break;
     case IMAGE_ALGORITHM:
         message = "    " +
             LSBHelp + "\n\n\    " +
             PRIHelp + "\n\n\    " +
             PRSHelp + "\n\n\    " +
             BlockHelp + "\n\n\    " +
             QuantHelp + "\n\n\    " +
             CrossHelp + "\n\n\    " +
             KochZhaoHelp;
         break;
     case SOUND_ALGORITHM:
         message = "    " +
             LSBSoundHelp + "\n\n\    " +
             EchoHelp;
         break;
     case ENTER_KEY_PAGE:
         message = enterKeyHelp;
         break;
     case ENTER_TEXT_PAGE:
         message = enterTextHelp;
         break;
     case VIEW_TEXT_PAGE:
         message = viewTextHelp;
         break;
     case HIDE_PAGE:
         message = hideHelp;
         break;

     default:
         message = failHelp;
    }

    QMessageBox::information(this, tr("SCoder Help"), message);
}


////////////////////////////////////////////////////////////////////////////////


ContainerType SCoderWizard::GetContainerType() const
{
    return static_cast<ContainerType>( field("ContainerType").toInt() );
}


////////////////////////////////////////////////////////////////////////////////


bool SCoderWizard::IsHideMessageMode() const
{
    return field("IsHideMessageMode").toBool();
}


////////////////////////////////////////////////////////////////////////////////

std::string SCoderWizard::GetOpenFileName() const
{
    return field("OpenFileName").toString().toStdString();
}


////////////////////////////////////////////////////////////////////////////////


std::string SCoderWizard::GetSaveFileName() const
{
    return field("SaveFileName").toString().toStdString();
}


////////////////////////////////////////////////////////////////////////////////


std::string SCoderWizard::GetText() const
{
    return field("Text").toString().toStdString();
}


////////////////////////////////////////////////////////////////////////////////


void SCoderWizard::SetText( std::string _text )
{
    setField("Text", QString::fromStdString(_text) );
}


////////////////////////////////////////////////////////////////////////////////


std::string SCoderWizard::GetKeyText() const
{
    return field("Key").toString().toStdString();
}


////////////////////////////////////////////////////////////////////////////////


CoderType SCoderWizard::GetCoderType() const
{
    return static_cast<CoderType>( field("CoderType").toInt() );
}


////////////////////////////////////////////////////////////////////////////////


void SCoderWizard::Process()
{
    // Get container
    Container* container = GetContainer ( GetContainerType(), GetOpenFileName() );

    // Get coder
    Coder* coder = GetCoder( GetCoderType() );

    // Get key
    Key* key = GetKey( GetCoderType(), GetKeyText(), Key::STRING);

    if ( IsHideMessageMode() )
    {
        // Hide and save
        coder->SetMessage(container, GetText(), key);
        container->Save( GetSaveFileName() );
    }
    else
    {
        // Reveal
        SetText ( coder->GetMessage(container, key) );
    }
}


////////////////////////////////////////////////////////////////////////////////

