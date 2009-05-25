#ifndef _SCODER_H_
#define _SCODER_H_

////////////////////////////////////////////////////////////////////////////////

#include "container.h"
#include "coder.h"
#include "key.h"

////////////////////////////////////////////////////////////////////////////////

enum CoderType
{
    LSB,
    PRS,
    PRI,
    BLOCK,
    QUANT,
    CROSS,
    KOCHZHAO,
    LSBSOUND,
    ECHO,

    INVALID
};

enum ContainerType
{
    IMAGE,
    SOUND
};

/** Containers */

Container* GetBMPContainer( const std::string& _fileName );
Container* GetWAVContainer( const std::string& _fileName );


////////////////////////////////////////////////////////////////////////////////


/** Coders */

Coder* GetLSBCoder();
Coder* GetPRICoder();
Coder* GetPRSCoder();
Coder* GetBlockCoder();
Coder* GetQuantCoder();
Coder* GetCrossCoder();
Coder* GetKochZhaoCoder();

Coder* GetLSBSoundCoder();
Coder* GetEchoCoder();


////////////////////////////////////////////////////////////////////////////////


/** Keys */

Key* GetPRIKey     ( const std::string& _string, Key::KeyType _type );
Key* GetPRSKey     ( const std::string& _string, Key::KeyType _type );
Key* GetBlockKey   ( const std::string& _string, Key::KeyType _type );
Key* GetQuantKey   ( const std::string& _string, Key::KeyType _type );
Key* GetKochZhaoKey( const std::string& _string, Key::KeyType _type );


////////////////////////////////////////////////////////////////////////////////

#endif //_SCODER_H_
