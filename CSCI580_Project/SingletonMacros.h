#ifndef __MH_SINGLETON_MACROS_H__
#define __MH_SINGLETON_MACROS_H__

/**
* Macro:
* DEFINE_SINGLETON_INSTANCE(name)
*
* Input:
*  name -
*      The ClassName of the Singleton that is defining the Instance function.
*
* Description:
* Macro for easily defining the Singleton Instance() function.  The function
* checks for an active pointer (ie an initialized singleton struct) and returns
* if there is one or makes one and returns if there isn't.
*
* C++ Translation:
*
* name *name::m_pInstance = NULL;
* name *name::Instance()
* {
*      if(!m_pIntance)
*          m_pInstance = new name;
*      return m_pInstance
* }
*
*/
#define DEFINE_SINGLETON_INSTANCE(name) \
	name *##name##::m_pInstance = NULL;    \
    name *##name## ::Instance()         \
    {                                   \
        if (!m_pInstance)               \
            m_pInstance = new name##;   \
        return m_pInstance;             \
    }

#endif