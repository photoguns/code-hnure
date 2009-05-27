#ifndef _KEY_H_
#define _KEY_H_

////////////////////////////////////////////////////////////////////////////////

#include <string>

////////////////////////////////////////////////////////////////////////////////


/** C++ interface class for keys generation
*
*
*  @author  Roman Pasechnik
*  @since   Mar 25th, 2009
*  @updated Mar 25th, 2009
*
*/
class Key
{
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Type of the key -- string or file */
    enum KeyType
    {
        STRING,
        FILE
    };


    /** Constructor */
    Key( const std::string& _string, KeyType _type );


    /** Destructor */
    virtual ~Key();


    /** Tells if this key is PRI key */
    virtual bool IsPRIKey() const { return false; }

    /** Tells if this key is PRS key */
    virtual bool IsPRSKey() const { return false; }

    /** Tells if this key is Block key */
    virtual bool IsBlockKey() const { return false; }

    /** Tells if this key is Quant key */
    virtual bool IsQuantKey() const { return false; }

    /** Tells if this key is Cross key */
    virtual bool IsCrossKey() const { return false; }

    /** Tells if this key is KochZhao key */
    virtual bool IsKochZhaoKey() const { return false; }
    
    /** Tells if this key is Echo key */
    virtual bool IsEchoKey() const { return false; }


////////////////////////////////////////////////////////////////////////////////

protected:


    /** Get MD5 hash of key */
    std::string GetKeyHash() const;


////////////////////////////////////////////////////////////////////////////////

private:


    /** MD5 hash key */
    std::string m_Key;


////////////////////////////////////////////////////////////////////////////////
};

#endif
