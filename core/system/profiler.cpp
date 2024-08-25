#include "profiler.h"

#include <time.h>
#include <core/io/file.h>
using radium::FunctionProfile;
using radium::ProfilerManager;
using radium::AutoProfiler;


///////////////////////////////
//////// AUTO PROFILER ////////
///////////////////////////////

AutoProfiler::AutoProfiler(const char* name)
{
    m_name = name;
    m_timer.reset();
    m_timer.tick();
}

AutoProfiler::~AutoProfiler()
{
    m_timer.tick();
    radium::ProfilerManager::get().addProfile(m_name, m_timer.getTotal());
}





////////////////////////////////
/////// PROFILER MANAGER ///////
////////////////////////////////


void ProfilerManager::addProfile(const rtl::string& name, double time)
{
    FunctionProfile& fp = m_profileMap[name];

    ++fp.numTimesCalled;
    fp.profileTimes.push_back(time);

}

void ProfilerManager::dumpProfile()
{
    if (m_profileMap.size() == 0)
        return;

    rtl::string outfile = "radium-profile.";

    generateFileName(outfile);
    outfile += ".csv";
    File output;
    output.open(outfile, File::WRITE);
    
    rtl::string profileLine;

    char numberBuffer[24];

    for (const auto& prof : m_profileMap)
    {
        memset(numberBuffer, 0, sizeof(numberBuffer));

        profileLine = prof.first;
        profileLine += ",";

        _itoa(prof.second.numTimesCalled, numberBuffer, 10);

        profileLine += numberBuffer;

        memset(numberBuffer, 0, sizeof(numberBuffer));

        sprintf(numberBuffer , ",%lf\n", getAverage(prof.second.profileTimes));
        profileLine += numberBuffer;

        output.write(profileLine.c_str(), profileLine.length());
        profileLine.setPos(0);
    }

}

void radium::ProfilerManager::generateFileName(rtl::string& output)
{    
    // @todo: add time api
    char timeBuffer[25];

    time_t timeOfLog = time(NULL);
    struct tm* timeInfo = nullptr;
    timeInfo = localtime(&timeOfLog);

    strftime(timeBuffer, 24, "%d-%b-%Y-%H-%M", timeInfo);
    timeBuffer[24] = 0;
    output += timeBuffer;
}

double ProfilerManager::getAverage(const rtl::array<double>& list)
{
    size_t listSize = list.size();

    double counter = 0;

    for (int i = 0; i < listSize; i++)
        counter += list[i];

    return counter/listSize;
}
