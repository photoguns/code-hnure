////////////////////////////////////////////////////////////////////////////////

#include "scoder.h"

////////////////////////////////////////////////////////////////////////////////

#include <cassert>

#include "bmpcontainer.h"
#include "wavcontainer.h"

////////////////////////////////////////////////////////////////////////////////

#include "lsbcoder.h"
#include "pricoder.h"
#include "prscoder.h"
#include "blockcoder.h"
#include "quantcoder.h"
#include "crosscoder.h"
#include "kochzhaocoder.h"

#include "lsbsoundcoder.h"
#include "echocoder.h"

////////////////////////////////////////////////////////////////////////////////

#include "prikey.h"
#include "prskey.h"
#include "blockkey.h"
#include "quantkey.h"
#include "kochzhaokey.h"

////////////////////////////////////////////////////////////////////////////////


Container* GetContainer( ContainerType _type, const std::string& _fileName )
{
    switch (_type)
    {
    case IMAGE:
        return new BMPContainer(_fileName);
    case SOUND:
        return new WAVContainer(_fileName);
    default:
        assert(0);
        return NULL;
    }
}


////////////////////////////////////////////////////////////////////////////////


Coder* GetCoder( CoderType _type )
{
    switch (_type)
    {
    case LSB:
        return new LSBCoder();
    case PRS:
        return new PRSCoder();
    case PRI:
        return new PRICoder();
    case BLOCK:
        return new BlockCoder();
    case QUANT:
        return new QuantCoder();
    case CROSS:
        return new CrossCoder();
    case KOCHZHAO:
        return new KochZhaoCoder();
    case LSBSOUND:
        return new LSBSoundCoder();
    case ECHO:
        return new EchoCoder();
    default:
        assert(0);
        return NULL;
    }
}


////////////////////////////////////////////////////////////////////////////////


Key* GetKey( CoderType _coderType, const std::string& _string, Key::KeyType _type )
{
    switch (_coderType)
    {
    case PRS:
        return new PRSKey(_string, _type);
    case PRI:
        return new PRIKey(_string, _type);
    case BLOCK:
        return new BlockKey(_string, _type);
    case QUANT:
        return new QuantKey(_string, _type);
    case KOCHZHAO:
        return new KochZhaoKey(_string, _type);
    default:
        return NULL;
    }
}


////////////////////////////////////////////////////////////////////////////////
