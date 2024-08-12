#include "StdOutSystem.h"
#include "core/rtl/string.h"

#include <stdio.h>

using radium::StdoutSystem;

void StdoutSystem::log(const rtl::string& str)
{
    fprintf(m_opfp, str.c_str());
}

void StdoutSystem::flush()
{

}