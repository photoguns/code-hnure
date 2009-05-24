#ifndef _SCODER_H_
#define _SCODER_H_

////////////////////////////////////////////////////////////////////////////////

#include "container.h"
#include "coder.h"
#include "key.h"

////////////////////////////////////////////////////////////////////////////////


/** Containers */

Container* GetBMPContainer( const std::string& _fileName );

Container* GetWaveContainer( const std::string& _fileName );


////////////////////////////////////////////////////////////////////////////////


/** Coders */

Coder* GetLSBCoder();
Coder* GetPRICoder();
Coder* GetPRSCoder();
Coder* GetBlockCoder();
Coder* GetQuantCoder();
Coder* GetCrossCoder();
Coder* GetKohaJaoCoder();

Coder* GetLSBSoundCoder();
Coder* GetEchoCoder();


////////////////////////////////////////////////////////////////////////////////


/** Keys */

Key* GetPRIKey  ( const std::string& _string, Key::KeyType _type );
Key* GetPRSKey  ( const std::string& _string, Key::KeyType _type );
Key* GetBlockKey( const std::string& _string, Key::KeyType _type );
Key* GetQuantKey( const std::string& _string, Key::KeyType _type );


////////////////////////////////////////////////////////////////////////////////

#endif //_SCODER_H_
